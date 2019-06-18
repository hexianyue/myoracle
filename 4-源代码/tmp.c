#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

struct stu 
{
    int x;
    int y;
    char sex;
};

int main(void)
{
    int n = 0;

    int *p = NULL;

    struct stu s = {1, 2, 'M'};

    while(1)
    {
        //1M 
        p = malloc(1 * 1024 * 1024); 
        if (NULL == p)
        {
            break; 
        }
        printf("n = %d\n", n++);
    
    }
    printf(";;;;;;;;;;;;;;;;;;;;;;\n");


    return 0;
}
