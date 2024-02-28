/* Word counting 
    # app.exe 
    # ./app 
*/ 

#include <stdio.h> 
#include <stdlib.h> 

#define LINE_LEN 256 
char line[LINE_LEN]; 

int main(void){
    int nr_words; 
    fgets(line, LINE_LEN, stdin); 
    /*  Count the number of words in line and print them 
        While traversing through the line 
        initially you are OUTSIDE ANY WORD. (state = OUT | IN)

        state -> OUT -> NON-WHITESPACE CHAR -> state -> (OUT->IN) -> nr_words++ 
        state -> OUT -> WHITE-SPACE CHAR -> state -> OUT -> DO NOTHING 

        state -> IN -> NON_WHITESPACE CHAR -> state -> IN -> DO NOTHING 
        state -> IN -> WHITESPACE CAHR -> state->(IN->OUT) -> DO NOTHING 

        (Make use of ctype.h header for character classify)
    */ 

    #define OUT 1 
    #define IN 2 
    int state = OUT; 
    for(i = 0; i < strlen(line); ++i)
    {
        line[i]
    }
   

    "\t\t    abc      \t\t\t   pqr       \t\t\t\t\t\t\t   lmn      \t\t"
}