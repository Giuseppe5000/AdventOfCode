/*

https://adventofcode.com/2021/day/3

*/

#include <stdio.h>
#include <stdlib.h>

#define COLS 12

/* Saving column ones data*/
void save_col_ones_data(int* col_ones, int* lines, FILE* fp) {

    char input[COLS + 2]; /* Each line has COLS + 2 characters */

    while (fgets(input, COLS + 2, fp) != NULL) {
        for (int col = 0; col < COLS; col++)
            if (input[col] == '1') col_ones[col]++;

        (*lines)++;
    }
}

int main(void) {
    FILE* fp = fopen("input.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open file");
        exit(1);
    }

    int col_ones[COLS] = {0}; /* Number of ones for each column*/
    int lines = 0;
    int gamma = 0;
    int epsilon = 0;

    save_col_ones_data(col_ones, &lines, fp);

    for (int col = 0; col < COLS; col++) {
        if (col_ones[col] >= lines/2) {
            gamma += 1;
            epsilon += 0;
        }

        if (col_ones[col] < lines/2) {
            gamma += 0;
            epsilon += 1;
        }

        gamma = gamma << 1;
        epsilon = epsilon << 1;
    }
    gamma = gamma >> 1;
    epsilon = epsilon >> 1;

    fclose(fp);

    printf("gamma = %d\nepsilon = %d\n", gamma, epsilon);
    printf("gamma * epsilon = %d\n", gamma * epsilon);

    return 0;
}
