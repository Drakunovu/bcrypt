CXX = g++
CXXFLAGS = -m32 -O2 -Wall -Wextra -std=c++11 -fPIC -I./sdk -I./bcrypt_lib -I../amxmodx/public
LDFLAGS = -m32 -shared

SOURCES = amxx_bcrypt.cpp \
          sdk/amxxmodule.cpp \
          bcrypt_lib/bcrypt.cpp \
          bcrypt_lib/blowfish.cpp

OBJECTS = $(SOURCES:.cpp=.o)

TARGET = bcrypt_amxx_i386.so

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "==> Linking $@..."
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTS)
	@echo "==> Done."

%.o: %.cpp
	@echo "==> Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "==> Cleaning build files..."
	rm -f $(OBJECTS) $(TARGET)
	@echo "==> Cleaned."

.PHONY: all clean