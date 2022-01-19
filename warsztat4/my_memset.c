///@file my_memset.c
#include <stdio.h>
#include <immintrin.h>
#include <stdint.h>
#include <string.h>

/** 
 *  Funkcja my_memset_ver1 - pierwsza wersja, czyli ustawianie każdego bajtu na zadaną wartość
 *  po kolei (bajt po bajcie).
 *  @param[in] ptr
 *  @param[in] value
 *  @param[in] num
 *  @return void* 
 */
void* my_memset_ver1(void* ptr, int value, size_t num){

    if(ptr == NULL){
        return NULL;
    }

    unsigned char* cptr = (unsigned char*)ptr;

    for(size_t i = 0 ; i < num ; ++i){

        (*cptr) = (unsigned char)value;

        cptr += 1;

    }

    return ptr;

}

/**
 * Funkcja memset (wersja 2), w której wykorzystano instrukcje wektorowe (kopiuje 32 bajty do tablicy naraz).
 * @param[in] ptr 
 * @param[in] value 
 * @param[in] num 
 * @return void*  
 */

void* my_memset_ver2(void* ptr, int value, size_t num){

    if(ptr == NULL){
        return NULL;
    }

    __m256i v = _mm256_set1_epi8((unsigned char)value);

    size_t number_of_iterations = num/sizeof(__m256i);
    size_t rest = num%sizeof(__m256i);

    for(size_t i = 0 ; i < number_of_iterations ; ++i){

        _mm256_storeu_si256((__m256i*)ptr, v);

        ptr += sizeof(__m256i);

    }

    unsigned char* cptr2 = (unsigned char*)ptr;

    for(size_t i = 0 ; i < rest ; ++i){

        (*cptr2) = (unsigned char)value;

        cptr2 += 1;

    }

    return ptr;

}

/**
 * Funkcja memset (wersja 3) z rozwiniętą pętlą (możliwe zwiększenie efektywności kodu).
 * 
 * @param[in] ptr 
 * @param[in] value 
 * @param[in] num 
 * @return void*  
 */
void* my_memset_ver3(void* ptr, int value, size_t num){

    if(ptr == NULL){
        return NULL;
    }

    unsigned char* _ptr = (unsigned char*)ptr;

    unsigned char casted_value = (unsigned char)value; 

    size_t batch_size = 16;

    size_t number_of_iterations = num/batch_size;
    size_t rest = num%batch_size;

    size_t p = 0;

    for(size_t i = 0 ; i < number_of_iterations ; i++){

        _ptr[p] = casted_value;
        _ptr[p + 1] = casted_value;
        _ptr[p + 2] = casted_value;
        _ptr[p + 3] = casted_value;
        _ptr[p + 4] = casted_value;
        _ptr[p + 5] = casted_value;
        _ptr[p + 6] = casted_value;
        _ptr[p + 7] = casted_value;
        _ptr[p + 8] = casted_value;
        _ptr[p + 9] = casted_value;
        _ptr[p + 10] = casted_value;
        _ptr[p + 11] = casted_value;
        _ptr[p + 12] = casted_value;
        _ptr[p + 13] = casted_value;
        _ptr[p + 14] = casted_value;
        _ptr[p + 15] = casted_value;

        p += 16;

    }

    _ptr += number_of_iterations*16;

    for(size_t i = 0 ; i < rest ; ++i){

        _ptr[i] = casted_value;

    }

    return ptr;
}

/**
 * Funkcja memset (wersja 4), w której wykorzystano instrukcje wektorowe (kopiuje 32 bajty to tablicy naraz)
 * oraz słowo kluczowe restrict (możliwość optymalizacji przez kompilator).
 * 
 * @param[in] ptr 
 * @param[in] value 
 * @param[in] num 
 * @return void* 
 */
void* my_memset_ver4(void* restrict ptr, int value, size_t num){

    if(ptr == NULL){
        return NULL;
    }

    __m256i v = _mm256_set1_epi8((unsigned char)value);

    size_t number_of_iterations = num/sizeof(__m256i);
    size_t rest = num%sizeof(__m256i);

    for(size_t i = 0 ; i < number_of_iterations ; ++i){

        _mm256_storeu_si256((__m256i*)ptr, v);

        ptr += sizeof(__m256i);

    }

    unsigned char* cptr2 = (unsigned char*)ptr;

    for(size_t i = 0 ; i < rest ; ++i){

        (*cptr2) = (unsigned char)value;

        cptr2 += 1;

    }

    return ptr;

}

/**
 * Funkcja memset (wersja 5) - kopiuje po 64 bajty do tablicy w jednym przebiegu pętli (za pomocą 
 * instrukcji wektorowych).
 * 
 * @param[in] ptr 
 * @param[in] value 
 * @param[in] num 
 * @return void*  
 */
void* my_memset_ver5(void* ptr, int value, size_t num){

    if(ptr == NULL){
        return NULL;
    }

    __m256i v1 = _mm256_set1_epi8((unsigned char) value);
   
    size_t number_of_iterations = (num)/(2*sizeof(__m256i));
    size_t rest = (num)%(2*sizeof(__m256i));

    for(size_t i = 0 ; i < number_of_iterations ; i++){

        _mm256_storeu_si256((__m256i*)ptr, v1);

        ptr += sizeof(__m256i);

        _mm256_storeu_si256((__m256i*)ptr, v1);

        ptr += sizeof(__m256i);

    }

    unsigned char* cptr = (unsigned char*)ptr;

    for(size_t i = 0 ; i < rest ; i++){
        *cptr = (unsigned char)value;

        cptr += 1;
    }

    return ptr;

}

/**
 * Funkcja memset (wersja 6) - kopiuje po 128 bajtów do tablicy w jednym przebiegu pętli (za pomocą 
 * instrukcji wektorowych).
 * 
 * @param[in] ptr 
 * @param[in] value 
 * @param[in] num 
 * @return void* 
 */
void* my_memset_ver6(void* ptr, int value, size_t num){

    if(ptr == NULL){
        return NULL;
    }

    __m256i v1 = _mm256_set1_epi8((unsigned char) value);
   
    size_t number_of_iterations = (num)/(4*sizeof(__m256i));
    size_t rest = (num)%(4*sizeof(__m256i));

    for(size_t i = 0 ; i < number_of_iterations ; i++){

        _mm256_storeu_si256((__m256i*)ptr, v1);

        ptr += sizeof(__m256i);

        _mm256_storeu_si256((__m256i*)ptr, v1);

        ptr += sizeof(__m256i);

        _mm256_storeu_si256((__m256i*)ptr, v1);

        ptr += sizeof(__m256i);

        _mm256_storeu_si256((__m256i*)ptr, v1);

        ptr += sizeof(__m256i);

    }

    unsigned char* cptr = (unsigned char*)ptr;

    for(size_t i = 0 ; i < rest ; i++){
        *cptr = (unsigned char)value;

        cptr += 1;
    }

    return ptr;

}

