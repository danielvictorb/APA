CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall
SRC      = src/main.cpp src/sorts.cpp src/generator.cpp src/benchmark.cpp
BIN      = benchmark

all: run plot

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC)

test-random: $(BIN)
	@mkdir -p results
	./$(BIN) random

test-few-unique: $(BIN)
	@mkdir -p results
	./$(BIN) few_unique

test-sorted: $(BIN)
	@mkdir -p results
	./$(BIN) sorted

test-reversed: $(BIN)
	@mkdir -p results
	./$(BIN) reversed

run: clean-results $(BIN)
	@mkdir -p results
	./$(BIN) all

plot:
	python3 scripts/plot.py

clean-results:
	rm -f results/results.csv

clean:
	rm -f $(BIN)
	rm -rf results/*

.PHONY: all run plot clean clean-results test-random test-few-unique test-sorted test-reversed
