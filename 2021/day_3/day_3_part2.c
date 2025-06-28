/*

https://adventofcode.com/2021/day/3

This implementation is inefficient because it reads COLS times the input.txt.
I don't want to implement a data structure for processing the data, so...

*/

#include <stdio.h>
#include <stdlib.h>

#define COLS 12

int is_prefix(const char* s1, const char* s2) {
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 != *s2)
            return 0;

        s1++;
        s2++;
    }

    return 1;
}


int binary_string_to_int(const char* s) {
    int res = 0;

    while (*s != '\0') {
        if (*s == '1') res += 1;
        else res += 0;

        res = res << 1;
        s++;
    }

    return res >> 1;
}

int main(void) {
    FILE* fp = fopen("input.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open file");
        exit(1);
    }

    char input[COLS + 2];      /* Each line has COLS + 2 characters */

    /* Bits choice criteria pattern */
    char oxygen_criteria[COLS + 1] = {0};
    char co2_criteria[COLS + 1] = {0};

    for (int col = 0; col < COLS; col++) {
        int col_ones_oxygen = 0;
        int col_zeros_oxygen = 0;
        int col_ones_co2 = 0;
        int col_zeros_co2 = 0;

        /* Count only the lines that matches the criteria */
        while (fgets(input, COLS + 2, fp) != NULL) {
            if (is_prefix(oxygen_criteria, input)) {
                if (input[col] == '1') col_ones_oxygen++;
                else col_zeros_oxygen++;
            }

            if (is_prefix(co2_criteria, input)) {
                if (input[col] == '1') col_ones_co2++;
                else col_zeros_co2++;
            }
        }

        /* Calc the criterias */

        if (col_ones_oxygen >= col_zeros_oxygen)
            oxygen_criteria[col] = '1';
        else
            oxygen_criteria[col] = '0';

        /* Check if there is only one number */
        if (col_ones_co2 + col_zeros_co2 == 1) {

            /*
             * In this case we have to set the criteria bit to the
             * found bit, otherwise we lose the last number
             */
            if (col_ones_co2)
                co2_criteria[col] = '1';

            if (col_zeros_co2)
                co2_criteria[col] = '0';

        } else {

            if (col_ones_co2 >= col_zeros_co2)
                co2_criteria[col] = '0';
            else
                co2_criteria[col] = '1';
        }

        rewind(fp);
    }

    printf("Oxygen: %d\n", binary_string_to_int(oxygen_criteria));
    printf("CO2: %d\n", binary_string_to_int(co2_criteria));
    printf("life support rating: %d\n",
            binary_string_to_int(oxygen_criteria) *
            binary_string_to_int(co2_criteria));

    return 0;
}
