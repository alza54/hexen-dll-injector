#include "src/Injector.h"

using namespace v8;
using namespace Nan;
using namespace std;

void NodeInit(Local<Object> exports) {
	Injector::Init(exports);
}

NODE_MODULE(node_injector, NodeInit)
