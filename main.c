#include <stdio.h>
#include <inttypes.h>


int main(){
    FILE* fptr = fopen("../words.txt", "r");
    const int max_word_length = 100;
    char current_word[max_word_length];

    uint32_t letters[26];  // Bigrams
    for(short i = 0; i < 26; i++) letters[i] = 0;

    // Get bigrams
    while(fgets(current_word, max_word_length, fptr)){
        char* letter = current_word + 1;
        char previous_letter = *current_word;

        while(*letter){
            if(*letter < 'a' || *letter > 'z'){
                letter++;
                continue;
            }
            letters[previous_letter - 'a'] |= 1 << (*letter - 'a');
            previous_letter = *letter;
            letter++;
        }
    }
    fclose(fptr);

    // Print results
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
    return 0;
}
