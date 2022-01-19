///@file measurments.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "my_memset.h"

# define measure_function( function , label ) \
do { \
struct timespec start = {0}; \
struct timespec end = {0}; \
( void ) clock_gettime ( CLOCK_MONOTONIC , &start); \
( void ) function ; \
( void ) clock_gettime ( CLOCK_MONOTONIC , &end); \
const double seconds = end.tv_sec - start.tv_sec; \
const double nanoseconds = end.tv_nsec - start.tv_nsec; \
const double final_time = \
(( seconds * 1e9 ) + nanoseconds ) * 1e-9; \
printf ( " Measured time of function %s = %lf \n " , \
label , final_time ) ; \
} while (0)

/**
 * Główna funkcja, w której są wykonywane pomiary czasu działania poszczególnych implementacji
 * funkcji memset.
 * 
 * @return int 
 */
int main(void){

    char buffer1[500], buffer2[1024*1024];

    printf("################## \n");
    measure_function(memset(&buffer1[0], '$', sizeof(buffer1)), "memset");
    measure_function(memset(&buffer2[0], '$', sizeof(buffer2)), "memset");
    printf("################## \n");

    printf("\n");

    memset(&buffer1[0], 0, sizeof(buffer1));
    memset(&buffer2[0], 0, sizeof(buffer2));

    printf("################## \n");
    measure_function(my_memset_ver1(&buffer1[0], '$', sizeof(buffer1)), "my_memset_ver1");
    measure_function(my_memset_ver1(&buffer2[0], '$', sizeof(buffer2)), "my_memset_ver1");
    printf("################## \n");

    printf("\n");

    memset(&buffer1[0], 0, sizeof(buffer1));
    memset(&buffer2[0], 0, sizeof(buffer2));

    printf("################## \n");
    measure_function(my_memset_ver2(&buffer1[0], '$', sizeof(buffer1)), "my_memset_ver2");
    measure_function(my_memset_ver2(&buffer2[0], '$', sizeof(buffer2)), "my_memset_ver2");
    printf("################## \n");

    printf("\n");

    memset(&buffer1[0], 0, sizeof(buffer1));
    memset(&buffer2[0], 0, sizeof(buffer2));

    printf("################## \n");
    measure_function(my_memset_ver3(&buffer1[0], '$', sizeof(buffer1)), "my_memset_ver3");
    measure_function(my_memset_ver3(&buffer2[0], '$', sizeof(buffer2)), "my_memset_ver3");
    printf("################## \n");

    printf("\n");

    memset(&buffer1[0], 0, sizeof(buffer1));
    memset(&buffer2[0], 0, sizeof(buffer2));

    printf("################## \n");
    measure_function(my_memset_ver4(&buffer1[0], '$', sizeof(buffer1)), "my_memset_ver4");
    measure_function(my_memset_ver4(&buffer2[0], '$', sizeof(buffer2)), "my_memset_ver4");
    printf("################## \n");

    printf("\n");

    memset(&buffer1[0], 0, sizeof(buffer1));
    memset(&buffer2[0], 0, sizeof(buffer2));

    printf("################## \n");
    measure_function(my_memset_ver5(&buffer1[0], '$', sizeof(buffer1)), "my_memset_ver5");
    measure_function(my_memset_ver5(&buffer2[0], '$', sizeof(buffer2)), "my_memset_ver5");
    printf("################## \n");

    printf("\n");

    printf("################## \n");
    measure_function(my_memset_ver6(&buffer1[0], '$', sizeof(buffer1)), "my_memset_ver6");
    measure_function(my_memset_ver6(&buffer2[0], '$', sizeof(buffer2)), "my_memset_ver6");
    printf("################## \n");

    printf("\n");

    return 0;
}