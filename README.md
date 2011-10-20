# Zależności

Dla kodu (z repo Archa):

- g++, make, pkg-config
- ogre
- mygui
- gdb
- boost
- boost-lib

Dla dokumentacji:

- xelatex (texlive)
- czcionki Linux Libertine <http://www.linuxlibertine.org/> -- pliki *.otf skopiować cza do katalogu ~/.fonts
- oraz czcionka Inconsolata (pakiet community/ttf-inconsolata)

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

Zależności są obsługiwane przez pkg-config. Do pliku Makefile w
podkatalogu projektu, gdzie potrzebujemy danej biblioteki (np. OGRE w
`play`) dodajemy do zmiennej DEPS (przez +=) zależności używając nazw
znanych pkg-config'owi (`pkg-config --list-all` wyciąga nazwy i opisy
wszystkich pakietów o których wie).

# Eclipse

Póki co nie jestem pewien czy wszystko działa. Konfiguracja Eclipse wygląda m/w tak:

1. Instalujemy Eclipse C++ [stąd](http://www.eclipse.org/downloads/packages/eclipse-ide-cc-linux-developers-includes-incubating-components/indigosr1) albo doinstalowujemy CDT jeśli mamy już Eclipse.
1. Tworzymy przestrzeń roboczą gdziekolwiek byle nie w katalogu projektu (nie musimy tworzyć nowej przestrzeni roboczej jeśli jakąś już mamy)
2. Importujemy projekt do workspace'a:
   1. File -> Import...
   2. General -> Existing Projects into Workspace
   3. w następnym ekranie wybieramy "root directory": główny katalog projetku
   4. Finish
3. Powinien się załadować projekt. Na tym etapie proponuję przetestować budowanie i czyszczenie.
Cały kod powinien pozostać w katalogu gdzie sklonowaliśmy projekt z gita i tam też będzie się budował.
4. Importujemy konfigurację uruchomieniową:
   1. File -> Import...
   2. Run/Debug -> Launch Configurations
   3. Wybieramy katalog projektu w "From Directory"
   4. Klikamy w "Wysypisko" (nie zaznaczając kratki).
   5. Zaznaczamy "Wysypisko Default.launch"
5. W tym momencie projekt powinien się uruchamiać i debugować (o ile mamy gdb zainstalowane)

Ogólna czerwoność na plikach h i cpp teoretycznie powinna zniknąć po
przebudowaniu i zrobieniu "Run C/C++ Code Analysis z menu
kontekstowego (tzn. mi tak się stało za którymś razem)
