# Condition Variable Demo Makefile
CXX		 = g++
CXXFLAGS = -Wall -std=c++17 -pthread
TARGET	 = hello_concurrent_world.exe
SRC		 = hello_concurrent_world.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)