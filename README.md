# 209.4-kasyno

Aplikacja-kasyno w którym można grać w Texas Holdem, ruletkę oraz jackpota.

## Gry

### Texas Holdem

Jeden z popularnych wariantów pokera, wygrywa osoba z najsilniejszym układem kart na koniec

### Ruletka

Niemalże synonim kasyna, szatańska gra, stawiamy zakłady i na podstawie wylosowanego numeru wypłacane są wygrane

### Jackpot

Loteria w której możemy zwiększać swoje szanse stawiając większą ilość pieniędzy od pozostałych, łatwy sposób na zdobycie pieniędzy do dalszej zabawy

## Dokumentacja

Poniżej znajduje się krótkie podsumowanie wszystkich klas, szczegółowa dokumentacja znajduje się w kodzie

- **GamblerLib**:
    - Gambler - klasa reprezentująca podstawowego gracza kasynowego
    - GamblerBot - klasa reprezentujące bota grającego w kasynie z metodami umożliwiającymi mu wykonywanie ruchów i dołączanie do gier tak jak sam zarządzi
    - JackpotBot, RouletteBot, TexasBot - klasy botów wyspecjalizowanych do grania w daną grę
    - Shop - @kmichal4 uzupełnij
    - (inne też)
- **GamblerTest**:
    - Folder zawierający testy dla klasy gracza oraz jego pochodnych
- **GameExample**:
    - GameManagerTest - program uruchamiający menedżera gier i sprawdzający, czy wszystko działa poprawnie, używany do stwierdzenia czy gra jest w stanie działać przez dłuższy czas bez bankrutujących botów lub kończenia się na błędzie
    - JackpotUITest, RouletteUITest, TexasHoldeUITest - programy z testowym interfejsem graficznym w których można grać w dane gry, używane były do testowania czy gry działają, potem ich fragmenty zostały użyte w końcowej aplikacji
    - TestTexasSimulation - program w którym symulowana jest gra graczy w Texas Holdem, była używana do stwierdzania czy algorytm rozstrzygający remisy działa poprawnie na "przykładach praktycznych"
- **GameLib**:
    - Card - klasa reprezentująca kartę do gry
    - CardGame - klasa dziedzicząca po klasie Game dodająca obsługę kart
    - Game - bazowa klasa gry kasynowej po której wszystkie gry dziedziczą
    - GameManager - klasa uruchamiająca i zarządzająca logiką kasyna, czyli wszystkimi grami i botami
    - Jackpot - klasa gry Jackpot, zawierająca wszystkie metody potrzebne do gry, dziedziczy tak jak wszystkie klasy gier po klasie Game
    - Roulette - klasa gry w ruletkę
    - TexasHoldem - klasa gry w Texas Hold'em, dziedziczy po CardGame
- **GameTest**:
    - Folder zawierający testy dla klasy Game i jej pochodnych
- **GUI**:
    - Folder zawierający interfejsy graficzne ułożone w Qt Designerze wraz z ich skompilowanymi wersjami, oraz klasy
    - CasinoWindow, klasę głównego okna gry
    - TexasHoldemGUITableItem, definiującą w związły sposób konkretną grupę obiektów w interfejsie graficznym
- **WindowsQt5files**:
    - Folder zawierający biblioteki dynamiczne potrzebne do uruchomienia skompilowanego programu pod systemem Windows, dołączone są pliki dla wersji kompilowanej kompilatorem Visual Studio 2019 na architekturę x86_amd64
- **Casino.cpp**:
    - Program uruchamiający okno główne gry
- **CMakeLists.txt**:
    - Skrypt CMake potrzebny do kompilacji projektu i wszystkich jego składników, działający zarówno na Windowsie jak i na Linuksie

## Kompilacja

Do kompilacji jest wymagany CMake w wersji 3.11 lub nowszej (Zw względu na użycie FetchContent do biblioteki GoogleTest) oraz biblioteka Qt5, bibliotekę tą można pobrać ze strony qt.io, lub używając package managera. Przy kompilacji na systemie windows potrzebne będzie podanie lokalizacji instalacji biblioteki Qt5 w linii
```cmake
set(PATH_TO_QT5 "D:\\Kody\\Qt5\\5.15.2\\msvc2019_64;C:\\Qt\\5.15.2\\msvc2019_64") # path to your Qt5 directory goes here
```
Zawartość zmiennej `PATH_TO_QT5` należy zastąpić ścieżką do własnej instalacji. Do projektu są dołączone biblioteki dynamiczne zgodne z kompilatorem MSVC i architekturą x86_amd64. Dla innych kompilatorów potrzeba będzie skopiować z folderu `bin` instalacji Qt5 pliki z katalogów Debug i Release. Dostępne cele kompilacji to:
- GamblerLib i GameLib, biblioteki zawierające klasy graczy i gier
- TestTexasSimulation, GameManagerTest, testy "praktyczne" klasy TexasHoldem i GameManager
- TexasHoldemUITest, JackpotUITest i RouletteUITest, gry z testowym interfejsem
- Casino, pełna aplikacja kasyna
- Wiele testów w GoogleTest