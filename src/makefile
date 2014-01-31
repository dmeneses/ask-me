# source files

SRC = structs/trienode.cpp \
      structs/trie.cpp \
      textpreprocessor/textcleaner.cpp \
      textpreprocessor/textpreprocessor.cpp \
      textpreprocessor/matcher.cpp \
      crawlers/Wordnet/wordnetinterface.cpp \
      stemmer/stemmer.cpp \
      crawlers/ConceptNet/conceptnetcrawler.cpp \
      crawlers/foursquare/foursquarecrawler.cpp \
      answer.cpp \
      crawlers/alchemyapp/alchemyappcrawler.cpp \
      crawlers/Twitter-lib/utils.cpp \
      langrecognition/recognizer.cpp

OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))

OUT = libaskme.a

INCLUDES = -I/usr/include/curl -I../third-party/boost_1_54_0 \
	   -I../third-party/libstemmer/include \
	   -I../include -Icrawlers/Twitter-lib \
	   -I../third-party/jsoncpp-src-0.5.0/include \
	   -I../third-party/wnb-0.6/include \
	   -I../third-party/FANN-2.2.0/include
	
#library paths
LIBS = -L/user/local/lib -lm -L../third-party/boost_1_54_0/lib/regex/ \
       -lboost_regex-gcc-1_53 -L../third-party/libstemmer/lib -lstemmer \
       -L../third-party/FANN-2.2.0/lib -lfann

#Compiler flags
CCFLAGS = -fPIC -g -Wall
LDFLAGS = rcs

#compiler
CCC = g++
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
