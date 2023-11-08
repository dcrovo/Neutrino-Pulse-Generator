
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


int SaveSignal(const std::vector<double> signal_array, const char* path) {
    std::ofstream csv_file(path);  // Open the file for writing using C++ streams

    if (!csv_file.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1;
    }

    for (int i = 0; i < signal_array.size(); i++) {
        csv_file << signal_array[i];
        if (i < signal_array.size() - 1) {
            csv_file << ',';  // Add a comma as a CSV separator
        }
    }

    csv_file.close();

    std::cout << "Signal saved to " << path << std::endl;
    return 0;
}

int SaveSignal(const std::vector<int32_t> signal_array, const char* path) {
    std::ofstream csv_file(path);  // Open the file for writing using C++ streams

    if (!csv_file.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1;
    }

    for (int i = 0; i < signal_array.size(); i++) {
        csv_file << signal_array[i];
        if (i < signal_array.size() - 1) {
            csv_file << ',';  // Add a comma as a CSV separator
        }
    }

    csv_file.close();

    std::cout << "Signal saved to " << path << std::endl;
    return 0;
}
int SaveSignal(const std::vector<double> signal_array, const std::string path) {
    std::ofstream csv_file(path);  // Open the file for writing using C++ streams

    if (!csv_file.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1;
    }

    for (int i = 0; i < signal_array.size(); i++) {
        csv_file << signal_array[i];
        if (i < signal_array.size() - 1) {
            csv_file << ',';  // Add a comma as a CSV separator
        }
    }

    csv_file.close();

    std::cout << "Signal saved to " << path << std::endl;
    return 0;
}