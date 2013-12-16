# source files

SRC = conceptnetcrawler.cpp

OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))

OUT = libConceptNetCrawler.a

#Compiler flags
CCFLAGS = -fPIC -g -Wall
LDFLAGS = rcs

INCLUDES = -I../../../third-party/curl-7.33.0/include \
	   -I../../../third-party/jsoncpp-src-0.5.0/include

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
