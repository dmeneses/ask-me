#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "src/answer.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  AnswerJS::Init(exports);
}

NODE_MODULE(addon, InitAll)
