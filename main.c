#include <stdio.h>
#include <inttypes.h>
#include <time.h>


void getBigrams(uint32_t* letters, FILE* fptr, const int max_word_length);
void printResults(uint32_t* letters);

int main(){
    FILE* fptr = fopen("../words.txt", "r");
    uint32_t letters[26];  // Bigrams
    for(short i = 0; i < 26; i++) letters[i] = 0;

    // TIME
    struct timespec res1,res2;
    clock_gettime(CLOCK_REALTIME,&res1);
    // END TIME


    getBigrams(letters, fptr, 100);

    // TIME
    clock_gettime(CLOCK_REALTIME,&res2);
    printf("Difference: %lu\n",res2.tv_nsec-res1.tv_nsec);
    // END TIME

    fclose(fptr);
    printResults(letters);
    return 0;
}

void getBigrams(uint32_t* letters, FILE* fptr, const int max_word_length){
    char current_word[max_word_length];
    while(fgets(current_word, max_word_length, fptr)){
        char* letter = current_word + 1;
        char previous_letter = *current_word;

        while(*letter){
            if(*letter < 'a' || *letter > 'z'){
                letter++;
                continue;
            }
            if(!(letters[previous_letter - 'a'] & 1 << (*letter - 'a')))
                letters[previous_letter - 'a'] |= 1 << (*letter - 'a');
            previous_letter = *letter;
            letter++;
        }
    }
}

void printResults(uint32_t* letters){
    for(short i = 0; i < 26; i++){
        printf("\n%c: ", i + 'a');

        uint32_t* word = letters + i;
        char counter = 0;
        while(*word){
            if(*word & 1) printf("%c", 'a' + counter);
            *word >>= 1;
            counter++;
        }
    }
}
