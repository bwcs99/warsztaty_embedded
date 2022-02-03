Implementacja wektora w języku C. Program kompiluje się za pomocą polecenia make, a uruchamia za pomocą pliku wykonywalnego tests (./tests). Program testowy wyświetla raport z przeprowadzonych testów. W celu sprawdzenia, czy nie ma wycieków pamięci można skorzystać z valgrinda (valgrind --leak-check=yes ./tests w terminalu). 

Oto ślad działania programu (wraz ze sprawdzeniem wycieków pamięci): 
==32395== Memcheck, a memory error detector
==32395== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==32395== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==32395== Command: ./tests
==32395== 
---- TESTY WEKTORA ! ---- 

Inicjuje wektory 

Wypełniam wektor przykładowymi danymi: 
Wielkość wektora: 7 

Pojemność wektora: 10 

Czy wektor jest pusty: NIE 

Zawartość wektora: 
Element wektora: aa 
Element wektora: ab 
Element wektora: ac 
Element wektora: ba 
Element wektora: ca 
Element wektora: da 
Element wektora: ala ma kota 

Zawartość wektora po modyfikacji: 
Element wektora: aa 
Element wektora: ab 
Element wektora: abc 
Element wektora: ba 
Element wektora: ca 
Element wektora: da 
Element wektora: ala ma kota 

Odwracam zawartość wektora: 

Zawartość wektora po odwróceniu: 
Element wektora: ala ma kota 
Element wektora: da 
Element wektora: ca 
Element wektora: ba 
Element wektora: abc 
Element wektora: ab 
Element wektora: aa 

Zawartość sklonowanego wektora: 
Element wektora: ala ma kota 
Element wektora: da 
Element wektora: ca 
Element wektora: ba 
Element wektora: abc 
Element wektora: ab 
Element wektora: aa 

Efekt konwersji wektora na tablicę: 
Element tablicy: ala ma kota
Element tablicy: da
Element tablicy: ca
Element tablicy: ba
Element tablicy: abc
Element tablicy: ab
Element tablicy: aa

Zawartość wektora po usunięciu ostatniego elementu: 
Element wektora: ala ma kota 
Element wektora: da 
Element wektora: ca 
Element wektora: ba 
Element wektora: abc 
Element wektora: ab 

Wektor po dodaniu dwóch nowych wartości z przodu: 
Element wektora: vvvvvv 
Element wektora: bbbbb 
Element wektora: ala ma kota 
Element wektora: da 
Element wektora: ca 
Element wektora: ba 
Element wektora: abc 
Element wektora: ab 

Wektor po usunięciu trzech wartości z początku: 
Element wektora: da 
Element wektora: ca 
Element wektora: ba 
Element wektora: abc 
Element wektora: ab 

Liczby całkowite: 
Element wektora: -11 
Element wektora: 10 
Element wektora: 0 
Element wektora: 3 
Element wektora: 2 
Element wektora: 1 
Element wektora: 8 
Element wektora: 6 
Element wektora: 2 
Element wektora: -1 

Czyszczenie wektora z napisami: 
Zawartość wyczyszczonego wektora: 

Niszczenie wektora z liczbami całkowitymi: 
Niszczenie wektora z napisami: 

==32395== 
==32395== HEAP SUMMARY:
==32395==     in use at exit: 0 bytes in 0 blocks
==32395==   total heap usage: 9 allocs, 9 frees, 1,480 bytes allocated
==32395== 
==32395== All heap blocks were freed -- no leaks are possible
==32395== 
==32395== For lists of detected and suppressed errors, rerun with: -s
==32395== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Jak widać valgrind nie zgłosił żadnych problemów.

