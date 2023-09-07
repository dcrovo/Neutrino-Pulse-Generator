#include <stdio.h>
#include <math.h>
#include <stdint.h>

static short shift_reg;
// Function to generate the exponential decaying signal and store it in an array
void generate_signal(double amplitude, double decay_constant, int16_t signal_array[], int num_samples, int num_repetitions) {
    double sampling_rate = 44100.0;
    double time_step = 1.0 / sampling_rate;

    for (int r = 0; r < num_repetitions; r++) {
        for (int i = 0; i < num_samples; i++) {
            double t = i * time_step;

            double signal = amplitude * exp(-t / decay_constant);

            signal_array[r * num_samples + i] = (int16_t)(signal * 32767.0);
        }
    }
}
short pn_sequence(short *sreg) {
    short b2, b11, b15;
    short x1, x2; /* x2 also used for x */
    
    b15 = *sreg >> 15;
    b11 = *sreg >> 11;
    x2 = b15 ^ b11; /* First b15 XOR b11 */
    
    b2 = *sreg >> 2;
    x1 = *sreg ^ b2; /* Second b2 XOR b0 */
    x2 = x1 ^ x2; /* Final x1 XOR x2 */
    x2 &= 1;
    
    *sreg = *sreg << 1;
    *sreg = *sreg | x2; /* Update the shift register */
    x2 = *sreg - 0x4000; /* Zero-mean random number */
    
    return x2;
}

int main() {
    // short sreg = 0x1234; // Initial value of shift register
    // for(int i=0;i<10;i++){
    //     short result = pn_sequence(&sreg);
    
    //     printf("Generated %d\n", result);
    // }
    // Parameters for the exponential decay signal
    double amplitude = 1.0;
    double decay_constant = 0.01;
    int num_samples = 1000;
    int num_repetitions = 3;  // Number of repetitions

    int16_t signal_array[num_samples * num_repetitions];

    generate_signal(amplitude, decay_constant, signal_array, num_samples, num_repetitions);

    FILE *csv_file = fopen("exponential_signal_repeated.csv", "w");
    if (csv_file == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }

    for (int r = 0; r < num_repetitions; r++) {
        for (int i = 0; i < num_samples; i++) {
            fprintf(csv_file, "%d\n", signal_array[r * num_samples + i]);
        }
    }

    fclose(csv_file);

    printf("Signal saved to 'exponential_signal_repeated.csv'\n");

    return 0;
}


