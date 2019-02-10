#pragma once

#define VC_EXTRALEAN

#include <v8.h>
#include <node.h>
#include <nan.h>
#include <string>
#include <vector>

#include <psapi.h>
#include <TlHelp32.h>

#pragma comment (lib, "ntdll.lib")
#pragma comment( lib, "psapi.lib" )

#include <nan.h>

class Injector : public Nan::ObjectWrap {
 public:

  static void Init (v8::Local<v8::Object> exports);

  Nan::Callback* log;

 private:

  explicit Injector();
  ~Injector();

  static void New (const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void On (const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void Inject (const Nan::FunctionCallbackInfo<v8::Value>& info);

  static void Log (Nan::Callback* cb, const char* type, const char* message);
  static BOOL FileExists (CHAR* Path);

  static Nan::Persistent<v8::Function> constructor;

};
