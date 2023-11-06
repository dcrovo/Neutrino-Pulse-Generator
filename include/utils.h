#ifndef NPG_UTILS_H_
#define NPG_UTILS_H_
#include <stdio.h>
#include <stdint.h>
#include <vector>

typedef struct UserInput UserInput;
struct UserInput{ 
    double sample_rate;
    double amplitude_lut;
    double amplitude;
    double taus[4];
    double simulation_time;
    int num_samples;
    double time_step; 
    double lut_tau;
    double random_noise_amplitude;
    double simulation_window;
    double activity;

};
int SaveSignal(std::vector<uint16_t> signal_array, char path[]);
int SaveSignal(std::vector<uint32_t> signal_array, char path[]);
int SaveSignal(std::vector<int32_t> signal_array, char path[]);

#endif