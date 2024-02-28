#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

int g_count = 0; 

inline int cpa_max(int n1, int n2){
    return (n1 > n2 ? n1 : n2); 
}

int lcs(char* s1, int n1, char* s2, int n2); 

int main(void){
    char* s1 = "AACGTAAGGT"; 
    char* s2 = "AXXXCYYYTZZZGPPPTLLL"; 
    int result = lcs(s1, strlen(s1), s2, strlen(s2)); 
    printf("result = %d, g_count = %d\n", result, g_count); 
    return (0); 
}

int lcs(char* s1, int n1, char* s2, int n2){ 
    ++g_count; 
    if(n1 == 0 || n2 == 0)
        return (0); 
    else if(s1[n1-1] == s2[n2-1])
        return 1 + lcs(s1, n1-1, s2, n2-1); 
    else
        return cpa_max(lcs(s1, n1, s2, n2-1), lcs(s1, n1-1, s2, n2)); 
}