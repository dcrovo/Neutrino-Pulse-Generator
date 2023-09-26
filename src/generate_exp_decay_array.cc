#include "generate_exp_decay_array.h"


// Function to generate the exponential decaying signal and store it in an array
void GenerateExpDecayArray(UserInput user_input, uint16_t signal_array[]) {
    double time_step = 1.0 / user_input.sample_rate;
    for (int i = 0; i < user_input.num_samples; i++) {
        double t = i * time_step;

        double signal = user_input.amplitude * exp(-t / user_input.decay_constant);

        signal_array[i] = (uint16_t)(signal * 65535.0);
    }
}