#include "Injector.h"

Nan::Persistent<v8::Function> Injector::constructor;

Injector::Injector () {}

Injector::~Injector () {}

void Injector::Init (v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Core").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "on", On);
  Nan::SetPrototypeMethod(tpl, "inject", Inject);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("Core").ToLocalChecked(), tpl->GetFunction());

}

void Injector::New (const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Injector* injector = new Injector();

  injector->Wrap(info.This());

  Nan::SetInternalFieldPointer(info.This(), 0, injector);

  info.GetReturnValue().Set(info.This());
}

void Injector::On (const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Injector* injector = ObjectWrap::Unwrap<Injector>(info.Holder());

  v8::String::Utf8Value arg0(info[0]->ToString());
  std::string callbackName = std::string(*arg0);

  if (callbackName == "log") {
    injector->log = new Nan::Callback(info[1].As<v8::Function>());
  }
}

void Injector::Log (Nan::Callback* cb, const char* type, const char* message) {
  v8::Local<v8::Value> args[] = {
    Nan::New<v8::String>(type).ToLocalChecked(),
    Nan::New<v8::String>(message).ToLocalChecked(),
    Nan::New<v8::Array>()
  };
  cb->Call(3, args);
}

void Injector::Inject (const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Injector* injector = ObjectWrap::Unwrap<Injector>(info.Holder());

  if (info.Length() < 2) {
    return Nan::ThrowTypeError("Wrong number of arguments");
  }

  if (!info[0]->IsNumber() || !info[1]->IsString()) {
    return Nan::ThrowTypeError("Wrong arguments");
  }

  Nan::Utf8String Utf8Value(info[1]);

  int length = Utf8Value.length();

  if (length <= 0) {
    return Nan::ThrowTypeError("Path must be a non-empty string");
  }

  std::string pathSting(*Utf8Value, length);
  const char* path = pathSting.c_str();

  DWORD id = (DWORD)info[0]->NumberValue();

  char buf[MAX_PATH] = { 0 };
  LPVOID LoadLibAddr = NULL;
  LPVOID RemoteString = NULL;
  HANDLE RemoteThread = NULL;

  HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);

  bool injectionSuccess = false;

  do {
    if (!handle) {
      Log(injector->log, "error", "Failed to open the target process.");
      break;
    }

    GetFullPathNameA(path, MAX_PATH, buf, NULL);

    if (!FileExists(buf)) {
      Log(injector->log, "error", "DLL module not found.");
      break;
    }

    Log(injector->log, "success", "Got DLL Full Path.");

    LoadLibAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

    if (!LoadLibAddr) {
      Log(injector->log, "error", "Failed to get ProcAddress.");
      break;
    }

    Log(injector->log, "success", "Got ProcAddress.");

    RemoteString = (LPVOID)VirtualAllocEx(handle, NULL, strlen(buf) + 1,
      MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    if (!RemoteString) {
      Log(injector->log, "error", "Failed to allocate the memory.");
      break;
    }

    Log(injector->log, "success", "Memory has been allocated.");

    BOOL __wr = WriteProcessMemory(handle, (LPVOID)RemoteString, buf, strlen(buf) + 1, NULL);

    if (!__wr) {
      Log(injector->log, "error", "Failed to write process memory.");
      break;
    }

    Log(injector->log, "success", "Wrote DLL name into process memory.");

    RemoteThread = CreateRemoteThread(handle, NULL, NULL,
      (LPTHREAD_START_ROUTINE)LoadLibAddr, (LPVOID)RemoteString, NULL, NULL);

    if (!RemoteThread) {
      Log(injector->log, "error", "Failed to create remote thread.");
      break;
    }

    Log(injector->log, "success", "Remote Thread Created.");

    WaitForSingleObject(RemoteThread, -1);

    Log(injector->log, "success", "Remote Thread Started.");
    Log(injector->log, "warn", "Injected successfully! Thanks for using HEX-EN Injector and have fun!");

    injectionSuccess = true;

  } while (0);

  if (handle) {
    VirtualFreeEx(handle, RemoteString, strlen(buf), MEM_RELEASE);
  }

  if (RemoteThread) {
    CloseHandle(RemoteThread);
  }

  if (handle) {
    CloseHandle(handle);
  }

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(injectionSuccess));
}

BOOL Injector::FileExists(CHAR* Path) {
  DWORD Attributes = GetFileAttributesA(Path);
  return (Attributes != INVALID_FILE_ATTRIBUTES && !(Attributes & FILE_ATTRIBUTE_DIRECTORY));
}
