# Standardowy szablon do katalogów z plikami cpp.
# użycie:
# INCLUDES = -I/includedir1 -I/includedir2... # nagłówki zależności
# include ../cpp.mk

INPUTS = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp,$(PROGRAM_OUTPUT_DIR)/%.o,$(INPUTS))

all: $(OBJECTS)

$(PROGRAM_OUTPUT_DIR)/%.o : %.cpp
	$(CXX) $(INCLUDES) -c $< -o $@

.PHONY: all
