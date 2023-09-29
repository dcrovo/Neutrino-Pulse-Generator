#ifndef NPG_UTILS_H_
#define NPG_UTILS_H_
#include <stdio.h>
#include <stdint.h>


typedef struct UserInput UserInput;
struct UserInput{ 
    double sample_rate;
    double amplitude;
    double decay_constant;
    double simulation_time;
    int num_samples;
    int num_repetitions; 

};
int SaveSignal(int array_size, uint16_t signal_array[], char path[]);

#endif