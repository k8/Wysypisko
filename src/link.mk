LIBS = $(shell pkg-config --libs $(shell cat $(PROGRAM_OUTPUT_DEPS)))

OBJECTS=$(wildcard *.o)

Wysypisko: $(OBJECTS)
	$(CXX) $(LIBS) -o $@ $(OBJECTS)
