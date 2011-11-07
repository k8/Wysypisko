# Użycie: (skopiuje wszystkie pliki 
#
# EXTENSIONS = cfg
#
# include ../copy.mk

INPUTS = $(foreach EXT, $(EXTENSIONS), $(wildcard *.$(EXT)))
OUTPUTS = $(patsubst %,$(PROGRAM_OUTPUT_DIR)/%,$(INPUTS))

copy: $(OUTPUTS)

$(OUTPUTS) : Makefile

$(OUTPUTS): $(PROGRAM_OUTPUT_DIR)/% : %
	cp $< $@

.PHONY: copy
