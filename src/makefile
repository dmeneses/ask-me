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
      answer.cpp 

OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))

OUT = libaskme.a

INCLUDES = -I/usr/include/curl -I../third-party/boost_1_54_0 \
	   -I../third-party/libstemmer/include \
	   -I../include -Icrawlers/Twitter-lib \
	   -I../third-party/jsoncpp-src-0.5.0/include \
	   -I../third-party/wnb-0.6/include
	
#library paths
LIBS = 

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
