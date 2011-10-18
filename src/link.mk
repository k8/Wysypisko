# Zależności dla każdej biblioteki dodawajny oddzielnie i komentujmy
# dla jakiej biblioteki one są.

# OGRE
LIBS += -lOgreMain -lOIS

OBJECTS=$(wildcard *.o)

Wysypisko: $(OBJECTS)
	$(CXX) $(LIBS) -o $@ $(OBJECTS)
