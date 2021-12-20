W tym zadaniu zaimplementowałem algorytmy szukania dwójek, trójek i czwórek sumujących
się do zadanego parametru. Dodatkowo, w celu napisania algorytmu szukania czwórek, musiałem
utworzyć nowy interfejs (strukturę danych) sum_item.

Przykład uruchomienia programu (po uruchomieniu programu jest drukowany raport z 
przeprowadzonych testów):

Kompilacja struktur danych z interfaces:

/warsztaty_embedded/warsztat1/zadania_pwr2-master/interfaces/dynamic_array$ make
gcc -Wall -c -std=c99 *.c -o array

/warsztaty_embedded/warsztat1/zadania_pwr2-master/interfaces/hash_table$ make
gcc -DHASH_TEST -Wall -std=c99 *.c -lm -o hash

/warsztaty_embedded/warsztat1/zadania_pwr2-master/interfaces/sum_item$ make
gcc -Wall -c -std=c99 *.c -o sum_item

Kompilacja i uruchomienie programu:

/warsztaty_embedded/warsztat1/zadania_pwr2-master/two_and_three_sum$ make
gcc -Wall -std=c99 *.c ../interfaces/hash_table/*.c ../interfaces/dynamic_array/*.c ../interfaces/sum_item/*.c -lm -o example

/warsztaty_embedded/warsztat1/zadania_pwr2-master/two_and_three_sum$ ./example
**** DWÓJKI - TEST 1 ****
Znaleziona dwójka: 1, -3
**** DWÓJKI - TEST 2 ****
Nie znaleziono żadnych dwójek...
**** DWÓJKI - TEST 3 ****
Znaleziona dwójka: 10, 6
**** DWÓJKI - TEST 4 ****
Znaleziona dwójka: 2, 8
Znaleziona dwójka: 3, 7
################## 
**** TRÓJKI - TEST 1 ****
Znaleziona trójka: 3, 9, 12
**** TRÓJKI - TEST 2 ****
Znaleziona trójka: 1, 3, 5
Znaleziona trójka: 2, 3, 4
**** TRÓJKI - TEST 3 ****
Znaleziona trójka: 4, 8, 10
**** TRÓJKI - TEST 4 ****
Znaleziona trójka: 4, 7, 10
Znaleziona trójka: 5, 7, 9
################## 
**** CZWÓRKI - TEST 1 ****
Znaleziona czwórka: 2, 3, 10, 8
Znaleziona czwórka: 2, 4, 9, 8
Znaleziona czwórka: 2, 5, 9, 7
Znaleziona czwórka: 3, 5, 7, 8
**** CZWÓRKI - TEST 2 ****
Znaleziona czwórka: 1, 2, 5, 8
Znaleziona czwórka: 1, 3, 5, 7
Znaleziona czwórka: 2, 3, 4, 7
**** CZWÓRKI - TEST 3 ****
Znaleziona czwórka: 20, 1, 30, 40
**** CZWÓRKI - TEST 4 ****
Znaleziona czwórka: 1, 4, 6, 10
################## 
KONIEC TESTÓW...

