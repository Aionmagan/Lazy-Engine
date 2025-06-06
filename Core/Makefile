TARGET = libLazy.a
CC = g++
CFLAGS += -D__PC__=1 

#LIBS = -lpng -lm -lSDL2 -lSDL2main -lGLEW -lGL -lGLU
LIBS = -lSDL2 -lSDL2main -lGLEW -lGL -lGLU -lm 
INC = -Iinclude
#OBJS = src/*.o
#OBJS = $(wildcard src/*.o)
SDIR = src
ODIR = bin

SRC = $(wildcard src/*.cpp)
OBJS = $(notdir $(SRC:%.cpp=%.o))
OBJ = $(addprefix $(ODIR)/, $(OBJS))

#src/%.o: %.c
#	$(CC) -c -o $@ $<
#%.o: %.cpp
#	$(CC) -c $(input) -o $(output)

#all: $(TARGET)
	
	
#$(TARGET): $(OBJS)
#	$(CC) $(OBJS) -o $(TARGET) $(LIBS)
    
#clean:
#	rm -f $(OBJS) $(TARGET)
    
#run: $(TARGET)
#	./$(TARGET)
#$(ODIR)/%.o: $(SDIR)/%.cpp
#	$(CC) -c -Iinc -o $@ $<
		#$(CC) $(INC) -c $(SRC) -o $(OBJ)
	#mv $(OBJS) bin/
	
		
all: $(OBJ)
	ar rcs -o $(TARGET) $(OBJ)
	
$(ODIR)/%.o: $(SDIR)/%.cpp | $(ODIR)
	$(CC) $(CFLAGS) $(INC) $(LIBS) -c $< -o $@
	
old:
	$(CC) $(INC) -c $(SRC)
	mv $(OBJS) bin/
	ar rcs -o $(TARGET) $(OBJ)
    
clean:
	rm -f $(OBJ) $(TARGET)
