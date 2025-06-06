INCHEADER = -I ../Core/include/
INCLIBS = -L ../Core/ -lLazy

INCLUDES = $(INCHEADER) $(INCLIBS)
LDFLAG = -L ../Core/ -lLazy

#CC = g++
LIBS = -lSDL2 -lSDL2main -lGLEW -lGL -lGLU -lm -L ../Core/ -lLazy
SRC  = $(wildcard *.cpp)
OBJS = $(SRC:.cpp=.o)
CXXFLAGS = -g -Wall -ggdb -fsanitize=address #-Wformat

TARGET = Game

%.o:%.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $<

#%.o:$(IMGUI_DIR)/%.cpp
#	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(TARGET)
	
$(TARGET): $(OBJS)
	$(CXX) $(INCLUDES) -o $@ $^ $(CXXFLAGS) $(LIBS)
	#$(CXX) $(OBJS) -o $(TARGET) $(INCLUDES) $(LIBS) $(CXXFLAGS)
	
#$(OBJS):
#	$(CXX) -D__PC__=1 -c $(SRC) $(INCLUDES)

clean:
	rm -f $(OBJS) $(TARGET)
	
run: $(TARGET)
	#$(MAKE) -f Makefile clean
	#$(MAKE) -f Makefile
	./$(TARGET)
