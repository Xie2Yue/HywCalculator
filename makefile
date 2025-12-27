CXX = g++
CXXFLAGS = -std=c++17 -Wall
OBJ = main.o BigInt.o BigIntNumberTheory.o Fraction.o Polynomial.o PolynomialFactorization.o ModuleLongLong.o
BIN = HywCalculator

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJ)
    $(CXX) $^ -o $@ -static-libgcc

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f $(OBJ) $(BIN)
