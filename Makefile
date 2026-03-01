# 1. OS Detection logic
ifeq ($(OS),Windows_NT)
    PLATFORM = WINDOWS
    EXTENSION = .exe
	INC_DIR =
    # Windows libs (static for portability)
    LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows -static -lpthread -lws2_32
    # Check if resource.res exists for the icon (only for your local release)
    RES_FILE = $(wildcard *.res)
    RM = del /Q
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        PLATFORM = LINUX
        INC_DIR =
        EXTENSION = 
        LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
        RM = rm -f
    endif
ifeq ($(UNAME_S),Darwin)
        PLATFORM = MAC
        EXTENSION = 
        INC_DIR = -I/opt/homebrew/include
        LIB_DIR = -L/opt/homebrew/lib
        LIBS = $(LIB_DIR) -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL
        RM = rm -f
    endif
endif

# 2. General Settings
CXX = g++
CXXFLAGS = -Wall -std=c++17 -O2
TARGET = MyGame$(EXTENSION)
# Assumes source files are in src/ folder
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# 3. Build Rules
all: $(TARGET)

# Linking - Includes RES_FILE only if it exists
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(RES_FILE) -o $(TARGET) $(LIBS)
	@echo "Build successful for $(PLATFORM)"

# Compiling source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC_DIR) -c $< -o $@

# Execute the game
run: all
	./$(TARGET)

# Clean build files
clean:
ifeq ($(PLATFORM),WINDOWS)
	$(RM) src\*.o $(TARGET)
else
	$(RM) src/*.o $(TARGET)
endif

.PHONY: all run clean
