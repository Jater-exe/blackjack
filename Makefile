# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# SFML Paths (Modify if SFML is installed in a custom location)
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
SFML_INCLUDE = -I/usr/include
SFML_LIBDIR = -L/usr/lib

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = build

# Source files (Now looking for .cc files)
SOURCES = $(wildcard $(SRCDIR)/*.cc)

# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SOURCES))

# Output binary
TARGET = game

# Default target
all: $(TARGET)

# Linking step
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SFML_LIBDIR) $(SFML_LIBS)

# Compilation step (Now compiling .cc files)
$(OBJDIR)/%.o: $(SRCDIR)/%.cc | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $(SFML_INCLUDE) -c $< -o $@

# Create build directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean compiled files
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Run the game
run: $(TARGET)
	./$(TARGET)
