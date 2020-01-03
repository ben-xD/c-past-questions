OBJ = main.cpp soundex.cpp
CXXFLAGS = -Wall -Wextra -g -MMD -std=c++17
CXX = g++
EXE = soundex

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf soundex *.d *.o

.PHONY: clean