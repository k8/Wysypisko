# Kopiuje konfigurację stąd do katalogu wyjściowego
INPUTS = $(wildcard *.cfg)
OUTPUTS = $(patsubst %,$(PROGRAM_OUTPUT_DIR)/%,$(INPUTS))

all: $(OUTPUTS)

$(OUTPUTS): $(PROGRAM_OUTPUT_DIR)/% : %
	cp $< $@

.PHONY: all
