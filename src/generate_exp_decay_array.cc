#include "generate_exp_decay_array.h"


// Function to generate the exponential decaying signal and store it in an array
void GenerateExpDecayArray(UserInput user_input, uint16_t signal_array[]) {
    double sum= 0;

    for (int i = 0; i < user_input.num_samples; i++) {
        double t = i*user_input.time_step;
        for(int j = 0; j<4; j++){

            double signal = user_input.amplitude * exp(-t / user_input.decay_constant[j]);
            sum += signal;
        }

        signal_array[i] = (uint16_t)((sum * 65535.0)/4);
        sum=0;

    }
}