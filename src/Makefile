export CXX=g++ -Wall
export PROGRAM_OUTPUT_DIR = $(patsubst %/src,%/build/program,$(CURDIR))
export PROGRAM_OUTPUT_DEPS = $(patsubst %/src,%/build/program/deps,$(CURDIR))

PROGRAM_OUTPUT_MAKEFILE = $(PROGRAM_OUTPUT_DIR)/Makefile
# wyciąga nazwy katalogów, usuwa "/" z wyniku polecenia ls -d */
INPUT_DIRS = $(patsubst %/,%,$(shell ls -d */))

# kompiluje wszystkie katalogi i wywołuje linkowanie w katalogu
# wyjściowym
all: $(PROGRAM_OUTPUT_MAKEFILE)
	for DIR in $(INPUT_DIRS); do $(MAKE) -C $$DIR; done
	$(MAKE) -C $(PROGRAM_OUTPUT_DIR)

$(PROGRAM_OUTPUT_DIR):
	mkdir -p $(PROGRAM_OUTPUT_DIR)

# kopiuje plik link.mk jako Makefile do katalogu wyjściowego, gdzie
# wykona się linkowanie
$(PROGRAM_OUTPUT_MAKEFILE) : link.mk $(PROGRAM_OUTPUT_DIR)
	cp $< $@

clean:
	rm -rf $(PROGRAM_OUTPUT_DIR)

.PHONY: all clean
