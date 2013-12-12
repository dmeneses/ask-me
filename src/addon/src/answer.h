#ifndef ANSWER_H
#define ANSWER_H

#include <node.h>
#include <vector>

class Answer : public node::ObjectWrap {
 public:
	static void Init(v8::Handle<v8::Object> target);
 private:
	static v8::Handle<v8::Value> New(const v8::Arguments& args);
	static v8::Handle<v8::Value> Reply(const v8::Arguments& args);
};

#endif
