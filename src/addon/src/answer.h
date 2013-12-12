#ifndef ANSWERJS_H
#define ANSWERJS_H

#include <node.h>
#include <vector>
#include "textpreprocessor.h"

class AnswerJS : public node::ObjectWrap {
 public:
	static void Init(v8::Handle<v8::Object> target);
 private:
	static v8::Handle<v8::Value> New(const v8::Arguments& args);
	static v8::Handle<v8::Value> Reply(const v8::Arguments& args);
	static v8::Handle<v8::Array> ConvertVectorToArrayJS(std::vector<Result>& results);
};

#endif
