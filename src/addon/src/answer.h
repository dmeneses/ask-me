#ifndef ANSWER_H
#define ANSWER_H

#include <node.h>
#include <vector>

class Answer : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> target);

 private:
};

#endif
