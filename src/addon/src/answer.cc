#include "answer.h"
#include "../../textpreprocessor/textpreprocessor.h"

using namespace v8;

void Answer::Init(v8::Handle<v8::Object> target)
{
	// Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("Answer"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    // Prototype
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reply"),
      FunctionTemplate::New(Reply)->GetFunction());

  Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("Answer"), constructor);
}

v8::Handle<v8::Value> Answer::New(const v8::Arguments& args)
{
}
v8::Handle<v8::Value> Answer::Reply(const v8::Arguments& args)
{
}
