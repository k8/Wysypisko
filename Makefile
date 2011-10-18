# Buduje dokumentację i źródła

all: program docs

docs:
	$(MAKE) -C docs

program:
	$(MAKE) -C src

clean:
	rm -rf build

.PHONY: all docs program clean
