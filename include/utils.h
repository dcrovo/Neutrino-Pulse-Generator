#ifndef NPG_UTILS_H_
#define NPG_UTILS_H_
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <iostream>
#include <fstream>

typedef struct UserInput UserInput;
struct UserInput{ 
    double modulation_freq_1;
    double modulation_amp;
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
    int num_channels;

};
int SaveSignal(std::vector<uint16_t> signal_array, char path[]);
int SaveSignal(std::vector<uint32_t> signal_array, char path[]);
int SaveSignal(const std::vector<int32_t> signal_array, const char* path);
int SaveSignal(const std::vector<double> signal_array, const char* path);
int SaveSignal(const std::vector<double> signal_array, const std::string path);
#endif