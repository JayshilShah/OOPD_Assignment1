CXX = g++
CXXFLAGS = -std=c++11 -Wall
SOURCES = ForIndia.cpp
EXECUTABLE = investment_calculator_india

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(EXECUTABLE)