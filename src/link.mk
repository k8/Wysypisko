# Plik o ścieżce PROGRAM_OUTPUT_DEPS jest składany w trakcie budowania
# poszczególnych części projektu (trafiają tam wszystkie wartości
# zmiennej DEPS z każdej części). Tu jest czytany i podawany do
# pkg-config, żeby wyciągnął biblioteki do zlinkowania.
LIBS = $(shell pkg-config --libs $(shell cat $(PROGRAM_OUTPUT_DEPS)))

OBJECTS = $(wildcard *.o)

Wysypisko: $(OBJECTS)
	$(CXX) $(LIBS) -o $@ $(OBJECTS)
