#include <stdio.h>
#include <stdlib.h>

#define CARD_SIZE 25

/* ================================ */
/* Simple vector implementation */
typedef struct {
    int* data;
    size_t len; /* Number of stored elements */
    size_t size; /* Total space available */
} vector;

vector vector_init(size_t size) {
    vector v = {0};
    v.data = malloc(size*sizeof(int));
    v.len = 0;
    v.size = size;
    return v;
}

void vector_push(vector* v, int item) {
    if (v->len == v->size) {
        v->data = realloc(v->data, v->size*2*sizeof(int));
        v->size *= 2;
    }
    v->data[v->len] = item;
    v->len++;
}

int* vector_at(vector* v, size_t index) {
    if (index >= v->len) {
        fprintf(stderr, "Vector out of bound");
        exit(1);
    }

    return &(v->data[index]);
}

void vector_print(vector* v) {
    for (size_t i = 0; i < v->len; i++) {
        printf("%zu: %d\n", i, v->data[i]);
    }
}

void vector_delete(vector* v) {
    free(v->data);
}
/* ================================ */

void read_extracted_numbers(FILE* fp, vector* v) {
    char c = fgetc(fp);
    while (c != '\n') {
        char num[5] = {0};

        for (int i = 0; c != ',' && c != '\n' && i < 5; i++) {
            num[i] = c;
            c = fgetc(fp);
        }

        if (c == ',') c = fgetc(fp);

        vector_push(v, atoi(num));
    }
}

int read_card(FILE* fp, vector* v) {
    /* Ignoring the newline before the card */
    char c = fgetc(fp);
    if (c == EOF)
        return -1;

    size_t newline_count = 0;

    while (newline_count < 5) {
        c = fgetc(fp);
        while (c == ' ')
            c = fgetc(fp);

        char num[5] = {0};
        for (int i = 0; c != ' ' && c != '\n' && i < 5; i++) {
            num[i] = c;
            c = fgetc(fp);
        }
        vector_push(v, atoi(num));

        if (c == '\n')
            newline_count++;
    }
    return 0;
}

int* card_at(vector* v, size_t card_index, size_t row, size_t col) {
    if (CARD_SIZE*card_index + row*5 + col >= v->len ||
            row > 4 || col > 4
       ) {
        fprintf(stderr, "Vector out of bound");
        exit(1);
    }

    return vector_at(v, card_index*CARD_SIZE + row*5 + col);
}

int check_win(vector* v) {
    for (int card = 0; card < v->len / CARD_SIZE; card++) {

        /* Check rows */
        for (int i = 0; i < 5; i++) {
            if ( *card_at(v, card, i, 0) == -1 &&
                    *card_at(v, card, i, 1) == -1 &&
                    *card_at(v, card, i, 2) == -1 &&
                    *card_at(v, card, i, 3) == -1 &&
                    *card_at(v, card, i, 4) == -1) {
                return card;
            }
        }

        /* Check cols */
        for (int i = 0; i < 5; i++) {
            if ( *card_at(v, card, 0, i) == -1 &&
                    *card_at(v, card, 1, i) == -1 &&
                    *card_at(v, card, 2, i) == -1 &&
                    *card_at(v, card, 3, i) == -1 &&
                    *card_at(v, card, 4, i) == -1) {
                return card;
            }
        }
    }

    /* If there is no winner card return -1 */
    return -1;
}

int main(void) {
    FILE* fp = fopen("input.txt", "r");
    vector extracted = vector_init(10);
    vector cards = vector_init(50);
    unsigned int winner_card_index = -1;
    unsigned int last_extracted_number = -1;

    read_extracted_numbers(fp, &extracted);
    while(read_card(fp, &cards) != -1) {}

    /* Checking cards with extractions */
    for (int i = 0; i < extracted.len; i++) {
        int extraction = *vector_at(&extracted, i);
        for (int j = 0; j < cards.len; j++) {
            int* card_number = vector_at(&cards, j);

            if (extraction == *card_number) {
                *card_number = -1;
            }
        }

        winner_card_index = check_win(&cards);
        if (winner_card_index != -1) {
            last_extracted_number = extraction;
            break;
        }
    }

    /* Getting the challenge result */
    unsigned int result = 0;
    for (int i = winner_card_index * CARD_SIZE;
            i < winner_card_index * CARD_SIZE + CARD_SIZE;
            i++) {
        int item = *vector_at(&cards, i);
        if (item != -1)
            result += item;
    }

    printf("Card %d is the winner\n", winner_card_index);
    printf("The result is %d\n", result*last_extracted_number);

    fclose(fp);
    vector_delete(&extracted);
    vector_delete(&cards);
    return 0;
}
