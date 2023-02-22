#include <cs50.h>
#include <stdio.h>

int main(void) {
    //Get height of pyramid
    int height = 0;
    while (height < 1 || height > 8) {
        height = get_int("Height: ");
    }

    //Draw pyramid
    for (int i = height; i > 0; --i) {
        //Draw left half
        for (int j = 0; j < height; ++j) {
            if (j < i - 1)  printf(" ");
            
            else printf("#");
        }

        //Draw gap
        printf("  ");

        //Draw right half
        for (int j = height - i + 1; j > 0; --j) 
            printf("#");

        //Next row
        printf("\n");
    }

    return 0;
}