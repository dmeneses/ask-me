#include "answer.h"
#include "../../textpreprocessor/textpreprocessor.h"
#include "../../answer.h"

using namespace v8;

void AnswerJS::Init(v8::Handle<v8::Object> target)
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

v8::Handle<v8::Value> AnswerJS::New(const v8::Arguments& args)
{
	HandleScope scope;
	Answer* answer = new Answer();
//	answer->Wrap(args.This());	

    return args.This();
}
v8::Handle<v8::Value> AnswerJS::Reply(const v8::Arguments& args)
{
	HandleScope scope;
	if(!args[0]->IsString() && !args[1]->IsNumber() && !args[2]->IsNumber() && !args[3]->IsNumber())
		return scope.Close(Array::New(0));
	
	Location location;
	String::Utf8Value value(args[0]->ToString());
	std::string word = *value;
	location.latitude_ = Handle<Number>::Cast(args[1])->Value();
	location.longitude_ = Handle<Number>::Cast(args[2])->Value();
	float radio = Handle<Number>::Cast(args[3])->Value();
	Answer answer;
	std::vector<Result> results = answer.ask(word, location, radio, TWITTER);	
	
	Handle<Array> messages = Array::New(results.size());

	for(int i = 0; i < results.size(); i++)
	{
		SocialInformation info = results.at(i).information;
		Local<Object> jsobject = Object::New();
		jsobject->Set(String::NewSymbol("message"), String::New(info.message_.c_str()));
		jsobject->Set(String::NewSymbol("latitude"), Number::New(info.location_.latitude_));
		jsobject->Set(String::NewSymbol("longitude"), Number::New(info.location_.longitude_));
		jsobject->Set(String::NewSymbol("source"), String::New(info.source_.c_str()));
		messages->Set(i, jsobject);
	}

	return scope.Close(messages);
}

