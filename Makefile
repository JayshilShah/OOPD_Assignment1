CXX = g++
CXXFLAGS = -std=c++11 -Wall
SOURCES = ForSpain.cpp
EXECUTABLE = investment_calculator_spain

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(EXECUTABLE)