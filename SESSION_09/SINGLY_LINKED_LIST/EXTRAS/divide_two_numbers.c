#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

int main(void)
{
    int numerator, denomenator; 
    int Q, R; 

    printf("Enter numerator:"); 
    scanf("%d", &numerator); 

    printf("Enter denomenator:"); 
    scanf("%d", &denomenator); 

    assert(denomenator != 0); 

    Q = numerator/denomenator; 
    R = numerator%denomenator; 

    printf("Q=%d, R=%d\n", Q, R); 

    return (0); 
}
