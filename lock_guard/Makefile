# Condition Variable Demo Makefile
CXX		 = g++
CXXFLAGS = -Wall -std=c++17 -pthread
TARGET	 = lock_guard.exe
SRC		 = lock_guard.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)