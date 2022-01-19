Źródła poszczególnych funkcji znajdują się w pliku my_memset.c

Porgram kompilujemy za pomocą komendy make (w terminalu) i uruchamiamy plik wykonywalny: ./measurments

Testy przeprowadziłem na tablicach o rozmiarach 500 i 1048576 bajtów.

Wyniki:

Pierwsza próba:
################## 
 Measured time of function memset = 0.000000 
  Measured time of function memset = 0.000060 
 ################## 

################## 
 Measured time of function my_memset_ver1 = 0.000003 
  Measured time of function my_memset_ver1 = 0.005992 
 ################## 

################## 
 Measured time of function my_memset_ver2 = 0.000001 
  Measured time of function my_memset_ver2 = 0.000208 
 ################## 

################## 
 Measured time of function my_memset_ver3 = 0.000001 
  Measured time of function my_memset_ver3 = 0.001751 
 ################## 

################## 
 Measured time of function my_memset_ver4 = 0.000001 
  Measured time of function my_memset_ver4 = 0.000208 
 ################## 

################## 
 Measured time of function my_memset_ver5 = 0.000001 
  Measured time of function my_memset_ver5 = 0.000199 
 ################## 

################## 
 Measured time of function my_memset_ver6 = 0.000001 
  Measured time of function my_memset_ver6 = 0.000181 
 ################## 
 
Druga próba:
################## 
 Measured time of function memset = 0.000000 
  Measured time of function memset = 0.000063 
 ################## 

################## 
 Measured time of function my_memset_ver1 = 0.000003 
  Measured time of function my_memset_ver1 = 0.008141 
 ################## 

################## 
 Measured time of function my_memset_ver2 = 0.000001 
  Measured time of function my_memset_ver2 = 0.000169 
 ################## 

################## 
 Measured time of function my_memset_ver3 = 0.000001 
  Measured time of function my_memset_ver3 = 0.001544 
 ################## 

################## 
 Measured time of function my_memset_ver4 = 0.000001 
  Measured time of function my_memset_ver4 = 0.000171 
 ################## 

################## 
 Measured time of function my_memset_ver5 = 0.000001 
  Measured time of function my_memset_ver5 = 0.000163 
 ################## 

################## 
 Measured time of function my_memset_ver6 = 0.000001 
  Measured time of function my_memset_ver6 = 0.000161 
 ################## 


Trzecia próba:
################## 
 Measured time of function memset = 0.000004 
  Measured time of function memset = 0.000095 
 ################## 

################## 
 Measured time of function my_memset_ver1 = 0.000003 
  Measured time of function my_memset_ver1 = 0.006388 
 ################## 

################## 
 Measured time of function my_memset_ver2 = 0.000001 
  Measured time of function my_memset_ver2 = 0.000271 
 ################## 

################## 
 Measured time of function my_memset_ver3 = 0.000001 
  Measured time of function my_memset_ver3 = 0.002271 
 ################## 

################## 
 Measured time of function my_memset_ver4 = 0.000001 
  Measured time of function my_memset_ver4 = 0.000269 
 ################## 

################## 
 Measured time of function my_memset_ver5 = 0.000001 
  Measured time of function my_memset_ver5 = 0.000254 
 ################## 

################## 
 Measured time of function my_memset_ver6 = 0.000002 
  Measured time of function my_memset_ver6 = 0.000246 
 ################## 


Wnioski:
1.) "Prosta" implementacja funkcji my_memset (czyli funkcja my_memset_ver1) jest około 100 razy wolniejsza od bibliotecznej funkcji memset.
2.) Funkcja memset z rozwiniętą pętlą (możliwe zwiększenie efektywności kodu) jest około 25 razy wolniejsza od bibliotecznej funkcji memset (zatem mamy około 4 krotną poprawę w stosunku do funkcji my_memset_ver1).
3.) Czas działania wszystkich funkcji (my_memset_ver2, my_memset_ver4, my_memset_ver5, my_memset_ver6), w których wykorzystano instrukcje wektorowe (AVX) jest podobny i jest około 3 razy większy w stosunku do czasu działania bibliotecznej funkcji memset. W szczególności nie pomogło (nie poprawiło czasu działania) zastosowanie słowa kluczowego restrict oraz zwiększenie liczby kopiowanych bajtów w jednym przebiegu pętli.

Drugi eksperyment:

Na mojej maszynie rozmiar lini cache wynosi 128 kB (otrzymałem to za pomocą lscpu | grep "cache" w terminalu). Przeprowadziłem eksperyment z tablicą o tym rozmiarze i otrzymałem następujące wyniki:

Pierwsza próba:
################## 
 Measured time of function memset = 0.000000 
  Measured time of function memset = 0.000006 
 ################## 

################## 
 Measured time of function my_memset_ver1 = 0.000003 
  Measured time of function my_memset_ver1 = 0.000731 
 ################## 

################## 
 Measured time of function my_memset_ver2 = 0.000001 
  Measured time of function my_memset_ver2 = 0.000025 
 ################## 

################## 
 Measured time of function my_memset_ver3 = 0.000001 
  Measured time of function my_memset_ver3 = 0.000213 
 ################## 

################## 
 Measured time of function my_memset_ver4 = 0.000001 
  Measured time of function my_memset_ver4 = 0.000026 
 ################## 

################## 
 Measured time of function my_memset_ver5 = 0.000001 
  Measured time of function my_memset_ver5 = 0.000024 
 ################## 

################## 
 Measured time of function my_memset_ver6 = 0.000001 
  Measured time of function my_memset_ver6 = 0.000024 
 ################## 

Druga próba:
################## 
 Measured time of function memset = 0.000000 
  Measured time of function memset = 0.000006 
 ################## 

################## 
 Measured time of function my_memset_ver1 = 0.000003 
  Measured time of function my_memset_ver1 = 0.000753 
 ################## 

################## 
 Measured time of function my_memset_ver2 = 0.000001 
  Measured time of function my_memset_ver2 = 0.000026 
 ################## 

################## 
 Measured time of function my_memset_ver3 = 0.000001 
  Measured time of function my_memset_ver3 = 0.000214 
 ################## 

################## 
 Measured time of function my_memset_ver4 = 0.000001 
  Measured time of function my_memset_ver4 = 0.000025 
 ################## 

################## 
 Measured time of function my_memset_ver5 = 0.000001 
  Measured time of function my_memset_ver5 = 0.000024 
 ################## 

################## 
 Measured time of function my_memset_ver6 = 0.000001 
  Measured time of function my_memset_ver6 = 0.000024 
 ################## 

Trzecia próba:
################## 
 Measured time of function memset = 0.000000 
  Measured time of function memset = 0.000009 
 ################## 

################## 
 Measured time of function my_memset_ver1 = 0.000003 
  Measured time of function my_memset_ver1 = 0.000731 
 ################## 

################## 
 Measured time of function my_memset_ver2 = 0.000001 
  Measured time of function my_memset_ver2 = 0.000029 
 ################## 

################## 
 Measured time of function my_memset_ver3 = 0.000001 
  Measured time of function my_memset_ver3 = 0.000213 
 ################## 

################## 
 Measured time of function my_memset_ver4 = 0.000001 
  Measured time of function my_memset_ver4 = 0.000025 
 ################## 

################## 
 Measured time of function my_memset_ver5 = 0.000001 
  Measured time of function my_memset_ver5 = 0.000035 
 ################## 

################## 
 Measured time of function my_memset_ver6 = 0.000001 
  Measured time of function my_memset_ver6 = 0.000030 
 ################## 


Wnioski:
1.) Po zastosowaniu tablicy o rozmiarze lini cache, można zaobserwować znaczną poprawę czasu działania wszystkich funkcji (w tym bibliotecznej funkcji memset). 
2.) Czas działania prostej funkcji memset (my_memset_ver1) jest około 120 razy większy niż czas działania bibliotecznej funkcji memset. Dla funkcji memset z rozwiniętą pętlą (my_memset_ver3) ten stosunek wynosi około 30 (czyli nadal mamy około 4 krotną poprawę), a dla wersji z instrukcjami wektorowymi (AVX - my_memset_ver2, my_memset_ver4, my_memset_ver5, my_memset_ver6) ten stosunek wynosi około 4. Dodatkowo wnioski z poprzedniego eksperymentu nadal pozostają w mocy tj. zastosowanie słowa kluczowego restrict oraz zwiększenie liczby kopiowanych bajtów w jednym przebiegu pętli, nie przyniosło żadnej (dużej) poprawy czasu działania zaimplementowanych funkcji.

Ponadto, wykonałem eksperyment z większą linią cache (256 kB) i również otrzymałem poprawę czasu działania wszystkich funkcji, jednak te czasy były większe niż te otrzymane dla lini cache o rozmiarze 128 kB.

-----> Wnioski ogólne: mimo zastosowania różnych optymalizacji w implementacji funkcji my_memset_ver2, my_memset_ver3 itd. w żadnym wypadku nie otrzymaliśmy podobnego czasu działania do tego w jakim działa biblioteczna funkcja memset (dla zoptymalizowanych wersji stosunki wynosiły 25, 3, 30 i 4. Zatem można powiedzieć, że zaimplementowane funkcje (mimo zastosowanych optymalizacji) działają dużo wolniej od bibliotecznej funkcji memset). 

