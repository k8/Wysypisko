DOCS_OUTPUT_DIR = $(patsubst %/docs,%/build/docs,$(CURDIR))
TMP_DIR =  $(patsubst %/docs,%/build/tmp,$(CURDIR))
DIRS = $(TMP_DIR) $(DOCS_OUTPUT_DIR)

LATEX ?= xelatex
LATEX_ARGS = -interaction=nonstopmode -output-directory=$(TMP_DIR)

INPUTS = $(wildcard *.tex)
OUTPUTS = $(patsubst %.tex,$(DOCS_OUTPUT_DIR)/%.pdf,$(INPUTS))

all: $(DIRS) $(OUTPUTS)

# buduje 2 razy, żeby wygenerował się spis treści
$(DOCS_OUTPUT_DIR)/%.pdf : %.tex
	$(LATEX) $(LATEX_ARGS) $<
	$(LATEX) $(LATEX_ARGS) $<
	mv $(TMP_DIR)/$(patsubst %.tex,%.pdf,$<) $(DOCS_OUTPUT_DIR)


$(DIRS):
	mkdir -p $@

clean:
	rm -rf $(DIRS)
