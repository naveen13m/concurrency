# Condition Variable Demo Makefile
CXX		 = g++
CXXFLAGS = -Wall -std=c++17 -pthread
TARGET	 = producer_consumer_pattern.exe
SRC		 = producer_consumer_pattern.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)