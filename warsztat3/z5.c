///@file z5.c
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include "stack.h"

/* Błażej Wróbel, Politechnika Wrocławska, Wydział Informatyki i Telekomunikacji */

/**
 * Funkcja pomocnicza, która sprawdza czy dany znak jest nawiasem otwierającym.
 * 
 * @param symbol 
 * @return true 
 * @return false 
 */
static bool inOpeningBracktes(char symbol){

    char openingBrackets[4] = {'(', '[', '{'};

    size_t size = strlen(openingBrackets);

    for(size_t i = 0 ; i < size ; i++){

        if(symbol == openingBrackets[i]){
            return true;
        }
    }

    return false;
}

/**
 * Funkcja pomocnicza, która sprawdza czy dany znak jest nawiasem zamykającym.
 * 
 * @param symbol 
 * @return true 
 * @return false 
 */
static bool inClosingBrackets(char symbol){

    char closingBrackets[4] = {')', ']', '}'};

    size_t size = strlen(closingBrackets);

    for(size_t i = 0 ; i < size ; i++){

        if(symbol == closingBrackets[i]){
            return true;
        }
    }

    return false;

}

/**
 * Funkcja sprawdzająca poprawność nawiasowania w napisie (ciągu znaków).
 * 
 * @param[in] str 
 * @return true 
 * @return false 
 */
bool checkBalanced(char* str){

    /* Jeśli napis wejściowy jest NULL to kończymy */
    if(str == NULL){

        return true;

    }

    size_t size = strlen(str);

    StackType pStack;

    stackInitialize(&pStack);

    /* Iterujemy po napisie wejściowym */
    for(size_t i = 0 ; i < size ; i++){
        
        /* Jeśli aktualny znak jest nawiasem otwierającym, to dajemy go na stos */
        if(inOpeningBracktes(str[i])){

            stackPush(&str[i], sizeof(char), &pStack);
            continue;

        } 

        if(!inClosingBrackets(str[i])){
            continue;
        }

        /* W innym razie, mamy nawias zamykający */

        /* Stos jest pusty, a mamy jeszcze jakiś nawias zamykający - błąd */
        if(stackEmpty(pStack)){

            return false;

        }

        /* Znak na szczycie stosu */
        char* topChar = (char*) stackTop(pStack);

        /* Sprawdzam, czy na szczycie stosu jest odpowiedni nawias otwierający (dla bieżącego nawiasu zamykającego) */
        switch(str[i]){
            
            case ')':
                if(*topChar == '('){
                    stackPop(&pStack);
                }
                break;
            case ']':
                if(*topChar == '['){
                    stackPop(&pStack);
                }
                break;
            case '}':
                if(*topChar == '{'){
                    stackPop(&pStack);
                }
                break;
            default:
                break;      
        }

    }

    /* Stos jest pusty - zwracamy true */
    if(stackEmpty(pStack)){

        return true;

    }

    /* Stos nie jest pusty - zwracamy false */
    return false;
}

/**
 * Funkcja do usuwania napisów (w języku C) z bufora. Podczas sprawdzania poprawności nawiasowania
 * w pliku źródłowym, napisy powinny być ignorowane.
 * 
 * @param buffer 
 * @param buffer_length 
 */
void deleteStringsFromStream(char* buffer, size_t buffer_length){

    if(buffer == NULL){

        return;

    }

    // Statyczna flaga - jeden napis może się "rozciągać" na dwa bufory
    static bool inStringFlag = false;

    char prev_symbol = 0;

    ssize_t string_beg = -1;
    ssize_t string_end = -1;

    for(size_t i = 0 ; i < buffer_length ; ++i){

        if(i > 0){

            prev_symbol = buffer[i - 1];

        }

        if(buffer[i] == '"' && !inStringFlag){

            inStringFlag = true;
            
            string_beg = i;

        } else if(buffer[i] == '"' && prev_symbol != '\\' && inStringFlag){

            inStringFlag = false;

            string_end = i;

            if(string_beg == -1){

                memset(buffer, 0, string_end + 1);

                string_end = -1;

            }
        }

        if(string_beg != -1 && string_end != -1){

            memset(buffer + string_beg, 0, string_end - string_beg + 1);

            string_beg = -1;
            string_end = -1;
        }

    }

    if(string_beg != -1 && string_end == -1){

        memset(buffer + string_beg, 0, buffer_length - string_beg);

    } 

}

/**
 * Funkcja do usuwania komentarzy (jednolinijkowych oraz wielolinijkowych) z bufora. Podczas sprawdzania
 * poprawności nawiasowania, komentarze mają być ignorowane.
 * 
 * @param buffer 
 * @param buffer_length 
 */
void deleteCommentsFromStream(char* buffer, size_t buffer_length){

    if(buffer == NULL){
        
        return;

    }

    // Rozważam dwa przypadki - komentarze jednolinijkowe oraz wielolinijkowe
    // Flagi są potrzebne, ponieważ jeden komentarz może "rozciągać" się na dwa bufory
    static bool inMultiLineCommentFlag = false;
    static bool inSingleLineCommentFlag = false;

    ssize_t beg_of_comment = -1;
    ssize_t end_of_comment = -1;

    char prev_symbol = 0;
    char current_symbol = buffer[0];

    for(size_t i = 0 ; i < buffer_length ; ++i){

        if(i > 0){

            prev_symbol = buffer[i - 1];
            current_symbol = buffer[i];

        }

        if(prev_symbol == '/' && current_symbol == '/' && !(inSingleLineCommentFlag || inMultiLineCommentFlag)){

            inSingleLineCommentFlag = true;

            beg_of_comment = i;

        } else if(prev_symbol == '/' && current_symbol == '*' && !(inSingleLineCommentFlag || inMultiLineCommentFlag)){

            inMultiLineCommentFlag = true;

            beg_of_comment = i;

        } else if(prev_symbol == '*' && current_symbol == '/' && inMultiLineCommentFlag && !inSingleLineCommentFlag){

            inMultiLineCommentFlag = false;

            end_of_comment = i;

            if(beg_of_comment == -1){

                memset(buffer, 0, end_of_comment + 1);

                end_of_comment = -1;
            }

        } else if(current_symbol == '\n' && inSingleLineCommentFlag && !inMultiLineCommentFlag){

            inSingleLineCommentFlag = false;

            end_of_comment = i;

            if(beg_of_comment == -1){

                memset(buffer, 0, end_of_comment + 1);

                end_of_comment = -1;
            }

        }

        if(beg_of_comment != -1 && end_of_comment != -1){

            memset(buffer + beg_of_comment, 0, end_of_comment - beg_of_comment + 1);

            beg_of_comment = -1;
            end_of_comment = -1;
        }

    }

    if(beg_of_comment != -1 && end_of_comment == -1){

        memset(buffer + beg_of_comment, 0, buffer_length - beg_of_comment);

    }

}

/**
 * Funkcja sprawdzająca poprawność nawiasowania w "strumieniu" (czyli aktualnie analizowanej części
 * przetwarzanego pliku).
 * 
 * @param buffer 
 * @param errorFlag 
 * @param pStack 
 */
void checkBalancedInStream(char* buffer, bool* errorFlag, StackType* pStack){

    if(buffer == NULL || pStack == NULL || errorFlag == NULL){

        return;

    }

    size_t size = strlen(buffer);

    deleteStringsFromStream(buffer, size);
    deleteCommentsFromStream(buffer, size);

    /* Iterujemy po napisie wejściowym */
    for(size_t i = 0 ; i < size ; i++){
        
        /* Jeśli aktualny znak jest nawiasem otwierającym, to dajemy go na stos */
        if(inOpeningBracktes(buffer[i])){

            stackPush(&buffer[i], sizeof(char), pStack);
            continue;

        } 

        if(!inClosingBrackets(buffer[i])){

            continue;
        }

        /* W innym razie, mamy nawias zamykający */

        /* Stos jest pusty, a mamy jeszcze jakiś nawias zamykający - błąd */
        if(stackEmpty(*pStack)){

            *errorFlag = false;
            return;

        }

        /* Znak na szczycie stosu */
        char* topChar = (char*) stackTop(*pStack);

        /* Sprawdzam, czy na szczycie stosu jest odpowiedni naiwas otwierający (dla bieżącego nawiasu zamykającego) */
        switch(buffer[i]){
            
            case ')':
                if(*topChar == '('){
                    stackPop(pStack);
                }
                break;
            case ']':
                if(*topChar == '['){
                    stackPop(pStack);
                }
                break;
            case '}':
                if(*topChar == '{'){
                    stackPop(pStack);
                }
                break;
            default:
                break;      
        }

    }

}

/**
 * Funkcja wczytująca plik i sprawdzająca poprawność nawiasowania.
 * 
 * @param fileName 
 * @return true 
 * @return false 
 */
bool checkBalancedInFile(const char* fileName){

    /* Jeśli nazwa pliku jest NULL, to kończymy */
    if(fileName == NULL){

        perror("Nie podano nazwy pliku ! \n");
        return false;

    }

    StackType pStack2;

    FILE* fptr;

    /* Otwieramy plik */
    fptr = fopen(fileName, "r");

    /* Podczas otwierania pliku wystąpiły problemy - kończymy */
    if(fptr == NULL){
        perror("Błąd podczas otwierania pliku ! \n");
        return false;
    }

    bool errorFlag = true;

    /* Rozmiar bufora */
    size_t bufferSize = 1024;

    /* Bufor na część zawartości czytanego pliku */
    char fileBuffer[bufferSize];
    
    stackInitialize(&pStack2);

    /* Inicjalizuję bufor zerami */
    (void)memset(&fileBuffer[0], 0, bufferSize);

    /* Pobieram wielkość plików (w bajtach) */
    fseek(fptr, 0, SEEK_END);

    long int fileSize = ftell(fptr);

    /* Wracam na początek pliku - można też użyć funkcji rewind */
    fseek(fptr, 0, SEEK_SET);

    /* Liczba zapisów do bufora */
    long int numberOfIterations = fileSize / (long int) bufferSize;

    /* Reszta */
    long int remainingSize = fileSize % bufferSize;

    /* Pozycja bitu od którego zaczynamy czytać plik */
    size_t bytePosition = 0;

    /* Czytanie zawartości do bufora */
    while(numberOfIterations > 0){

        /* Zawartość do bufora */
        fread(fileBuffer, 1, bufferSize, fptr);

        checkBalancedInStream(fileBuffer, &errorFlag, &pStack2);

        if(errorFlag == false){
            return false;
        }

        (void)memset(&fileBuffer[0], 0, bufferSize);

        /* Przesuwamy aktualną pozycję */
        bytePosition += 1024;

        /* Przesuwamy wskaźnik w pliku */
        fseek(fptr, bytePosition, SEEK_SET);

        numberOfIterations -= 1;

    }

    /* Czytamy resztę pliku */
    if(remainingSize > 0){

        fread(fileBuffer, 1, remainingSize, fptr);

        checkBalancedInStream(fileBuffer, &errorFlag, &pStack2);

        if(errorFlag == false){
            return false;
        }

    }

    /* Zamykamu strumień */
    fclose(fptr);

    /* Jeśli stos jest pusty, to nawiasowanie jest ok ! */
    if(stackEmpty(pStack2)){

        return true;

    }
    
    /* w przeciwnym przypadku niszczymy stos i zwracamy false */
    stackDestroy(&pStack2);

    return false;

}

/**
 * Funkcja używana do testów - zwiększa wartość każdego elementu stosu o 1.
 * 
 * @param s 
 */
void increaseByOne(StackType s){

    int* value = (int*)(s->storage);
    *value += 1;

}

/**
 * Funkcja używana do testów - wyświetla wartość elementu znajdującego się na stosie.
 * 
 * @param s 
 */
void displayStack(StackType s){

    int* value = (int*)(s->storage);
    printf("Wartość: %d \n", *value);

}

/**
 * Główna funkcja do testowania zaimplementowanych funkcjonalności.
 * 
 * @return int 
 */
int main(void){

    /* zbalansowany */
    char* test1 = "[()]{}{[()()]()}";

    /* nie zbalansowany */
    char* test2 = "[(])";

    /* zbalansowany */
    char* test3 = "([])()(())()()";

    /* nie zbalansowany */
    char* test4 = "())((())";

    /* zbalansowany */
    char* test5 = "{()}[]";

    /* nie zbalansowany */
    char* test6 = "(){]";

    /*nie zbalansowany */
    char* test7 = "((((())))))))";

    printf("***** TESTY POPRAWNOSCI BALANSOWANIA ***** \n");

    printf("Test 1 : %s \n", checkBalanced(test1) ? "Tak":"Nie");
    printf("Test 2 : %s \n", checkBalanced(test2) ? "Tak":"Nie");
    printf("Test 3 : %s \n", checkBalanced(test3) ? "Tak":"Nie");
    printf("Test 4 : %s \n", checkBalanced(test4) ? "Tak":"Nie");
    printf("Test 5 : %s \n", checkBalanced(test5) ? "Tak":"Nie");
    printf("Test 6 : %s \n", checkBalanced(test6) ? "Tak":"Nie");
    printf("Test 7 : %s \n", checkBalanced(test7) ? "Tak":"Nie");

    printf("\n");

    printf("***** TESTY POPRAWNOSCI BALANSOWANIA Z PLIKU ***** \n");

    /* poprawne nawiasowanie */
    printf("Test 1: %s \n", checkBalancedInFile("testy/test1.c") ? "Tak":"Nie");

    /* niepoprawne nawiasowanie */
    printf("Test 2: %s \n", checkBalancedInFile("testy/test2.c") ? "Tak":"Nie");

    /* poprawne nawiasowanie */
    printf("Test 3: %s \n", checkBalancedInFile("testy/test3.c") ? "Tak":"Nie");

    /* niepoprawne nawiasowanie */
    printf("Test 4: %s \n", checkBalancedInFile("testy/test4.c") ? "Tak":"Nie");

    /* poprawne nawiasowanie */
    printf("Test 5: %s \n", checkBalancedInFile("testy/test5.c") ? "Tak":"Nie");

    printf("\n"); 

    printf("***** TESTY POPRAWNOŚCI USUWANIA STOSU I PRZECHODZENIA PO NIM ***** \n");

    StackType stack1;

    stackInitialize(&stack1);

    int a = 5;
    int b = 6;
    int c = -1;
    int d = 1000;
    int e = 586879;

    stackPush(&a, sizeof(int), &stack1);
    stackPush(&b, sizeof(int), &stack1);
    stackPush(&c, sizeof(int), &stack1);
    stackPush(&d, sizeof(int), &stack1);
    stackPush(&e, sizeof(int), &stack1);

    printf("Wyświetlanie stosu: \n");
    traverseStack(stack1, &displayStack);

    printf("Liczba elementów na stosie: %zu\n", getNbrOfElements(stack1));

    printf("Usuwanie elementu ze stosu: \n");
    stackPop(&stack1);

    printf("Liczba elementów na stosie: %zu \n", getNbrOfElements(stack1));

    printf("Wyświetlenie stosu: \n");
    traverseStack(stack1, &displayStack);

    printf("Modyfikowanie zawartości stosu: \n");
    traverseStack(stack1, &increaseByOne);

    printf("Wyświetlenie zawartości stosu (jeszcze raz): \n");
    traverseStack(stack1, &displayStack);

    printf("Zniszczenie stosu ! \n");
    stackDestroy(&stack1);

    printf("Liczba elementów w pustym stosie: %zu \n", getNbrOfElements(stack1));

    printf("Pusty stos: \n");
    traverseStack(stack1, &displayStack);

    printf("\n");

    printf("Koniec testów ! \n");

    return 0;
}