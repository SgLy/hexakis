#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/block.h"

int main() {
    for (int x = 0; x < 7; ++x) {
        printf("Shape #%d:\n", x);
        block_shape bs = PRESET(x);
        for (int p = 0; p < 5; ++p) {
            for (int i = 0; i < bs.height; ++i)
                for (int j = 0; j < bs.width; ++j) {
                    if (bs.b[i][j]) printf("*");
                    else printf(" ");
                    if (j == bs.width - 1) printf("\n");
                }
            printf("%d\n", bs.toInt());
            bs.RotateCounterClockwise();
        }
        printf("\n");
    }
    return 0;
}