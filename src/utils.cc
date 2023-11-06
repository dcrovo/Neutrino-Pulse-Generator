#include "utils.h"

int SaveSignal(std::vector<uint16_t> signal_array, char path[]){

    FILE *csv_file = fopen(path, "w");
    if (csv_file == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    for (int i = 0; i < signal_array.size(); i++) {
        fprintf(csv_file, "%u\n", signal_array[i]);
    }

    fclose(csv_file);

    printf("Signal saved to %s \n", path);
    return 0;
}
int SaveSignal(std::vector<uint32_t> signal_array, char path[]){

    FILE *csv_file = fopen(path, "w");
    if (csv_file == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    for (int i = 0; i < signal_array.size(); i++) {
        fprintf(csv_file, "%u\n", signal_array[i]);
    }

    fclose(csv_file);

    printf("Signal saved to %s \n", path);
    return 0;
}

int SaveSignal(std::vector<int32_t> signal_array, char path[]){

    FILE *csv_file = fopen(path, "w");
    if (csv_file == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    for (int i = 0; i < signal_array.size(); i++) {
        fprintf(csv_file, "%u\n", signal_array[i]);
    }

    fclose(csv_file);

    printf("Signal saved to %s \n", path);
    return 0;
}

