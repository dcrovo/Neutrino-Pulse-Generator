#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "utils.h"
#include "generate_exp_decay_array.h"

static short shift_reg;



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
    UserInput user_input = {
        .sample_rate = 800e6,
        .amplitude = 1.0,
        .decay_constant = 1e-7,
        .simulation_time = 1e-3,
        .num_samples = 1000,
    };

    uint16_t signal_array[user_input.num_samples];
    GenerateExpDecayArray(user_input, signal_array);

    FILE *csv_file = fopen("exponential_signal.csv", "w");
    if (csv_file == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }

        for (int i = 0; i < user_input.num_samples; i++) {
            fprintf(csv_file, "%u\n", signal_array[i]);
        }

    fclose(csv_file);

    printf("Signal saved to 'exponential_signal.csv'\n");

    return 0;
}


