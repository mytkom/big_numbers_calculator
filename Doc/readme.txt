Kalkulator dla duzych liczb i systemow liczbowych o podstawie 2-16
autor: Marek Mytkowski
---------------------------------------------------------------------------------------------------------------------------------
UWAGA: Jesli myslniki oddzielajace sekcje zawijaja sie nalezy powiekszyc okno lub
zmniejszyc rozmiar wyświetlanej czcionki!
---------------------------------------------------------------------------------------------------------------------------------
Opis danych wejsciowych i wyjsciowych:
---------------------------------------------------------------------------------------------------------------------------------
Dane wejsciowe

Wzor dla operacji arytmetycznych:
---------------------------------------------------------------------------------------------------------------------------------
<symbol> <podstawa systemu liczbowego liczb>

<argument1>

<argument2>


---------------------------------------------------------------------------------------------------------------------------------
Operacje arytmetyczne mozliwe do wykonania: 
---------------------------------------------------------------------------------------------------------------------------------
Dodawanie - symbol: "+"
Dzielenie calkowite - symbol: "/"
Reszta z dzielenia (modulo) - symbol: "%"
Mnozenie - symbol: "*"
Potegowanie - symbol: "^"
---------------------------------------------------------------------------------------------------------------------------------
Wzor dla konwersji miedzy systemami liczbowymi:
---------------------------------------------------------------------------------------------------------------------------------
<podstawa systemu liczbowego liczby konwertowanej> <docelowa podstawa systemu liczbowego>

<konwertowana liczba>


---------------------------------------------------------------------------------------------------------------------------------
Kolejne operacje nalezy podac w jednym pliku pod soba
---------------------------------------------------------------------------------------------------------------------------------
Dane Wyjsciowe

W zalezności od argumentow uruchomienia w jednym pliku pod soba lub oddzielnie kazda operacja w innym pliku wedlug schematu:
Dla kazdej operacji arytmetycznych:
---------------------------------------------------------------------------------------------------------------------------------
<symbol> <podstawa systemu liczbowego liczb>

<argument1>

<argument2>

<wynik>

---------------------------------------------------------------------------------------------------------------------------------
Dla kazdej konwersji miedzy systemami liczbowymi:
---------------------------------------------------------------------------------------------------------------------------------
<podstawa systemu liczbowego liczby konwertowanej> <docelowa podstawa systemu liczbowego>

<konwertowana liczba>

<przekonwertowana liczba>

---------------------------------------------------------------------------------------------------------------------------------
Uruchomienie programu
---------------------------------------------------------------------------------------------------------------------------------
Uruchomienie programu nastepuje poprzez uruchomienie go razem z argumentami lub bez nich (np. w przypadku windows - w cmd)

Argumenty uruchomienia kalk.exe:
Brak argumentow:
	domyslnie ustala plik wejsciowy na "input.txt" znajdujacy sie w folderze programu
	oraz plik wyjsciowy na "output.txt" znajdujacy sie w folderze programu

-n
	ustawia niestandardowe nazwy plikow (wejsciowego i wyjsciowego)(jesli nie zostanie podana sciezka do pliku to plik jest 
	traktowany jakby byl w folderze w ktorym znajduje sie program) wedlug wzoru:
	"kalk.exe -n <nazwa (opcjonalnie ze sciezka do) pliku wejsciowego> <nazwa (opcjonalnie ze sciezka do) pliku wyjsciowego>"

-p	
	dzieli okreslony plik wejsciowy na oddzielne operacje (kazda w innym pliku, nazwane liczbami porzadkowymi operacji):
	"kalk.exe -p <nazwa (opcjonalnie ze sciezka do) pliku wejsciowego>

--help
	wyswietla zawartosc pliku readme.txt

UWAGA: kalk.exe z argumentem -p nie usuwa poprzednio utworzonych przez niego plikow, nalezy zrobic to recznie
UWAGA2: nazwy plikow prosze podawac z rozszerzeniem
---------------------------------------------------------------------------------------------------------------------------------
Obsluga blednych danych
---------------------------------------------------------------------------------------------------------------------------------
W przypadkach opisanych ponizej program obsluguje niepoprawne dane:
-gdy nie znaleziono pliku podanego jako argumentu ( lub w przypadku wywolania bez argumentow nie znaleziono input.txt) lub nie 
 rozpoznano opcji uruchomienia, program drukuje komunikat i konczy sie wykonywac z kodem 0 (todo)
-gdy wprowadzono nieznana operacje to program drukuje komunikat i konczy sie wykonywac z kodem 0
-gdy wprowadzono zbyt duza podstawe systemu liczbowego program drukuje komunikat i konczy sie wykonywac z kodem 0
-gdy wprowadzono niepoprawna liczbe program wyswietla komunikat i konczy sie wykonywac z kodem 0(todo)
-gdy wystepuje dzielenie przez zero lub modulo przez zero program drukuje komunikat i konczy sie wykonywac z kodem 0
---------------------------------------------------------------------------------------------------------------------------------
Kompilacja
---------------------------------------------------------------------------------------------------------------------------------
Plik wykonywalny programu (kalk.exe) zostal skompilowany w wersji release x64 przy pomocy programu Microsoft Visual Studio 2022 
Current na podstawie pliku zrodlowego main.c w systemie Windows 10 64-bit
---------------------------------------------------------------------------------------------------------------------------------