#include "utils.h"

int SaveSignal(int array_size, uint16_t signal_array[], char path[]){

    FILE *csv_file = fopen(path, "w");
    if (csv_file == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    for (int i = 0; i < array_size; i++) {
        fprintf(csv_file, "%u\n", signal_array[i]);
    }

    fclose(csv_file);

    printf("Signal saved to %s \n", path);
    return 0;
}


