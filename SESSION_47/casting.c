#include <stdio.h> 
#include <stdlib.h> 

int main(void){
    int val = 0xa0b0c0d0; 

    //  x     x+1     x+2     x+3 
    // 0xd0   0xc0    0xb0    0xa0 
    printf("%X\n", *((short*)(((char*)&val) + 1))); 
    return (0); 
}

/* 
    movl    src, dest

    unum = usnum; 

    signed char s_char= -1; 
    short s_num; 

    s_num = s_char; 

    1111 1111 

    0000 0000 1111 1111 = 255

    movzx 
    movsx 
*/