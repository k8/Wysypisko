# Standardowy szablon do katalogów z plikami cpp.
#
# użycie:
#
# # zależności tak jak dla pkg-config
# DEPS = OGRE
# # ew. dodatkowe flagi dla linkera
# LIBS = -lMyGUI.OgrePlatform
# # opcjonalnie dodatkowe include'y
# INCLUDES = -I/includedir1 -I/includedir2...
# # obowiązkowo na końcu:
# include ../cpp.mk

INPUTS = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp,$(PROGRAM_OUTPUT_DIR)/%.o,$(INPUTS))

# Wczytanie zależności dla kompilatora (tylko include'y)
INCLUDES += $(shell pkg-config --cflags $(DEPS))

# W tym kroku dopisywane są zależności danej części do zależności dla
# linkera.
cpp: $(OBJECTS) Makefile
	echo $(DEPS) >> $(PROGRAM_OUTPUT_DEPS)
	echo $(LIBS) >> $(PROGRAM_OUTPUT_LIBS)

$(PROGRAM_OUTPUT_DIR)/%.o : %.cpp
	$(CXX) $(INCLUDES) -c $< -o $@

.PHONY: cpp
