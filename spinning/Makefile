# Condition Variable Demo Makefile
CXX		 = g++
CXXFLAGS = -Wall -std=c++17 -pthread
TARGET	 = spinning_demo.exe
SRC		 = spinning_demo.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)