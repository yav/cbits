.PHONY: clean default

BUILD=build
TEST=test
SRC=src
INC=include

default: main


$(BUILD)/large_bits.o: $(SRC)/large_bits.c $(INC)/large_bits.h Makefile $(BUILD)
	gcc -Wall -I$(INC) -c -o $@ $<

main: $(TEST)/main.c $(INC)/small_bits.h $(BUILD)/large_bits.o Makefile
	gcc -Wall -I$(INC) -o $@ $< $(BUILD)/large_bits.o

$(BUILD):
	mkdir -p $@

clean:
	rm -rf $(BUILD)

