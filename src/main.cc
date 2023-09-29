#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "utils.h"
#include "generate_exp_decay_array.h"
#include "xorrshiro128.h"

static short shift_reg;

static char STATE;

short PseudoRandomSequence(short *sreg) {
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
    // Parameters for the exponential decay signal
    UserInput user_input = {
        .sample_rate = 800e6,
        .amplitude = 1.0, 
        .decay_constant = 1e-7,
        .simulation_time = 1e-3,
        .num_samples = 1024,
    };

    uint16_t signal_array[user_input.num_samples];
    uint16_t random_array[user_input.num_samples];
    char exp_path[] = "data/exp_decay.csv";
    char random_path[] = "data/random.csv";
    uint16_t seed = 12345;
    GenerateExpDecayArray(user_input, signal_array);
    SaveSignal(user_input.num_samples, signal_array, exp_path);
    //Seed(seed);
    //GenerateRandomArray(user_input.num_samples, random_array);
    //SaveSignal(random_array, random_path);


    while(1){
        switch (STATE)
        {
        case 0:
            break;
        
        default:
            break;
        }
    }

    return 0;
}


