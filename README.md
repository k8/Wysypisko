# Zależności

Dla kodu (z repo Archa):

- ogre
- mygui

Dla dokumentacji:

- xelatex (texlive)
- czcionki Linux Libertine <http://www.linuxlibertine.org/> -- pliki *.otf skopiować cza do katalogu ~/.fonts

# Budowanie

- wszystko: `make` w głównym katalogu
- tylko dokumentacja: `make` w katalogu `docs` lub `make docs` w katalogu głównym
- tylko program: `make` w katalogu `src` lub `make program` w katalogu głównym

Po zbudowaniu program jest w katalogu `build/program` a dokumentacja w `build/docs`.

Czyszczenie: `make clean` w katalogu głównym albo w katalogu `docs` bądź `src` (czyści odpowiednią rzecz).

# Uruchamianie

- po pomyślnym zbudowaniu w katalogu `build/program` jest plik
  `Wysypisko`. Powinno wyskorzyć okienko Ogre'a.

# Podział kodu

Aby nie mieszały się klasy z różnych części gry, podzieliłem
wstępnie kod na katalogi.

- `conf` zawiera pliki konf. dla Ogre'a a jego zawartość jest
kopiowana do katalogu `build/program` podczas buodwania.
- `characters` - klasy postaci
- `gui` - ekran startowy, menu, to co będzie napisane z uż. mygui generalnie
- `logic` - logika, w tym SI
- `net` - sprawunki sieciowe
- `play` - kod rozgrywki (generalnie to co ma związek z areną i właściwą rozgrywką)

Oczywiście możemy dodawać dodatkowe podkatalogi. Musimy dodać tylko
tam Makefile'a. To jak to robić jest opisane w `src/cpp.mk`. Resztę
system budowniczy sobie podłapie.

# Dodawanie nowych zależności

Katalogi z nagłówkami dodajemy do INCLUDES w Makefile'u odpowiedniej
części. Biblioteki do zlinkowania dodajemy do pliku `src/link.mk` wg
instrukcji tam zawartej.
