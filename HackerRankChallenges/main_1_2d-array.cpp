/*
 * https://www.hackerrank.com/challenges/2d-array
 */

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

// Complete the hourglassSum function below.
int hourglassSum(int arr_rows, int arr_columns, int** arr) {
    int r, c;
    int hourglass_sum;
    int max_sum;
    int flag_sum = 0;
    for ( r = 1; r < arr_rows -1 ; r++ ) {
        for ( c = 1 ; c < arr_columns - 1 ; c++ ) {
          hourglass_sum = arr[r][c] + arr[r - 1][c - 1] + arr[r + 1][c + 1] +
                          arr[r - 1][c + 1] + arr[r + 1][c - 1] +
                          arr[r - 1][c] + arr[r + 1][c];
          if (!flag_sum) {
            max_sum = hourglass_sum;
            flag_sum = 1;
            } else if ( max_sum < hourglass_sum) {
              max_sum = hourglass_sum;
            }
        }
    }

    return max_sum;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int** arr = (int**)malloc(6 * sizeof(int*));

    for (int i = 0; i < 6; i++) {
        *(arr + i) = (int*)malloc(6 * (sizeof(int)));

        char** arr_item_temp = split_string(readline());

        for (int j = 0; j < 6; j++) {
            char* arr_item_endptr;
            char* arr_item_str = *(arr_item_temp + j);
            int arr_item = strtol(arr_item_str, &arr_item_endptr, 10);

            if (arr_item_endptr == arr_item_str || *arr_item_endptr != '\0') { exit(EXIT_FAILURE); }

            *(*(arr + i) + j) = arr_item;
        }
    }

    int arr_rows = 6;
    int arr_columns = 6;

    int result = hourglassSum(arr_rows, arr_columns, arr);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = (char*)malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = (char*)realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = (char*)realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = (char**)realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
