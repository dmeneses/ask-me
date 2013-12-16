# source files

SRC = structs/trienode.cpp \
      structs/trie.cpp \
      textpreprocessor/textcleaner.cpp \
      textpreprocessor/textpreprocessor.cpp \
      textpreprocessor/matcher.cpp \
      stemmer/stemmer.cpp \
      crawlers/ConceptNet/conceptnetcrawler.cpp \
      answer.cpp

OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))

OUT = libaskme.a

INCLUDES = -I../third-party/boost_1_54_0 -I../third-party/libstemmer/include \
	   -I../include -Icrawlers/Twitter-lib \
	   -I../third-party/curl-7.33.0/include \
	   -I../third-party/jsoncpp-src-0.5.0/include
	
#library paths
LIBS = -L/user/local/lib -lm -L../third-party/boost_1_54_0/lib/regex/ \
       -lboost_regex-gcc-1_53 -L../third-party/libstemmer/lib -lstemmer

#Compiler flags
CCFLAGS = -fPIC -g -Wall
LDFLAGS = rcs

#compiler
CCC = g++ -m32
AR = ar

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
	@mkdir -p lib
	$(AR) $(LDFLAGS) lib/$(OUT) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -rf obj
	rm -rf lib
