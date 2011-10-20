# Zależności dla każdej biblioteki dodawajny oddzielnie i komentujmy
# dla jakiej biblioteki one są. Pomoże to przy ew. usuwaniu zbędnych
# bibliotek.

# OGRE
#LIBS += -lOgreMain -lOIS

LIBS = $(shell pkg-config --libs `cat deps`)

OBJECTS=$(wildcard *.o)

Wysypisko: $(OBJECTS)
	$(CXX) $(LIBS) -o $@ $(OBJECTS)
