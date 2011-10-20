# Standardowy szablon do katalogów z plikami cpp.
# użycie:
#
# # zależności tak jak dla pkg-config
# DEPS = OGRE
# # opcjonalnie dodatkowe include'y
# INCLUDES = -I/includedir1 -I/includedir2...
# include ../cpp.mk

INPUTS = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp,$(PROGRAM_OUTPUT_DIR)/%.o,$(INPUTS))

INCLUDES += $(shell pkg-config --cflags $(DEPS))

all: $(OBJECTS)
	echo $(DEPS) >> $(PROGRAM_OUTPUT_DEPS)

$(PROGRAM_OUTPUT_DIR)/%.o : %.cpp
	$(CXX) $(INCLUDES) -c $< -o $@

.PHONY: all
