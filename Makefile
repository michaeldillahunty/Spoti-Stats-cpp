CXXFLAGS := -std=c++17 -Wall -I./include -I./spotify-api-plusplus/src -ggdb -O0 $(CURL_CXXFLAGS)
LDLIBS := $(CURL_LIBS) -lcurl -L/usr/local/lib -lcpr
HEADERS := $(wildcard *.hpp)  # if you use '*.hpp' then amend this line accordingly
SRCDIR = ./src
SOURCES := $(wildcard $(SRCDIR)/*.cpp) # if you use '*.cc' then amend this line accordingly
OBJS := $(SOURCES:%.cpp=%.o)


TARGET := main

.PHONY : all
	all $(TARGET)

%.o : %.cpp $(HEADERS) # explicitly writing a rule to generate object files '.o' files, this will be used in line 5 for generating OBJS
	g++ $(CXXFLAGS) -c $< -o $@
  
$(TARGET) : $(OBJS) # rule to generate executable by invoking the linker.
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@


.PHONY : clean
clean :
	rm -rf $(TARGET) $(OBJS)
