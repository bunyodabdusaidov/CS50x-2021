#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./%s image\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Failed to open %s\n", argv[1]);
        return 1;
    }
    int jpg[512];
    
}