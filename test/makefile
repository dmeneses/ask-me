SRC = structs/trietest.cpp \
      textpreprocessor/textcleanertest.cpp \
      textpreprocessor/textpreprocessortest.cpp \
      textpreprocessor/wordnetinterfacetest.cpp \
      stemmer/stemmertests.cpp \
      testrunner.cpp 

OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))

OUT = askmetest

#include directories
INCLUDES = -I../src \
           -I../third-party/GMock-1.7.0/Include \
           -I../third-party/GTest-1.7.0/Include \
	   -I../third-party/boost_1_54_0 \
	   -I../third-party/libstemmer/include \
	   -I../include \
	   -I../../../third-party/curl-7.33.0/include \
	   -I../../../third-party/jsoncpp-src-0.5.0/include \
	   -I../third-party/jsoncpp-src-0.5.0/include \
	   -I../third-party/wnb-0.6/include
	
#library paths
LIBS = -L/user/local/lib -L../src/lib -laskme -lcurl \
       -L../third-party/GMock-1.7.0/Lib -L../third-party/GTest-1.7.0/Lib \
       -L../third-party/GMock-1.7.0/Lib64 -L../third-party/GTest-1.7.0/Lib64 -lgtest -lgmock -lm -lpthread \
       -L../third-party/boost_1_54_0/lib/regex/ -L../third-party/boost_1_54_0/lib64/regex/ -lboost_regex \
       -L../third-party/libstemmer/lib -L../third-party/libstemmer/lib64 -lstemmer  \
       -L../third-party/jsoncpp-src-0.5.0/lib -L../third-party/jsoncpp-src-0.5.0/lib64 -ljson \
       -L../third-party/wnb-0.6/lib -lwnb

#Compiler flags
CCFLAGS = -fPIC -g -Wall
LDFLAGS = rcs

#compiler
CCC = g++

default: $(OUT)

$(OBJ): | obj

obj:
	@echo creating objects directory $@
	@mkdir -p $@
	@mkdir -p $(patsubst %/, $@/%, $(sort $(dir $(SRC))))

obj/%.o : %.cpp
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

#archive the library
$(OUT):$(OBJ)
	$(CCC) -o $(OUT) $(CCFLAGS) $(OBJ) $(LIBS)

clean:
	rm -f $(OBJ)
	rm -f $(OUT)
	rm -rf obj
