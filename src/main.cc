#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "utils.h"
#include "lut.h"
#include "mmc.h"

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
        .amplitude_lut = 1,
        .amplitude = -1, 
        .taus = {9.40e-3, 2.72e-3, 45.0e-3, 0.38e-3},
        .simulation_time = 1e-3,
        .num_samples = 2048,
        .time_step = (45.0e-3*10)/4056,
        .lut_tau = 1,
        .random_noise_amplitude = 0.1,
        .simulation_window = 1.0,
        .activity = 5.0,
    };

    Lut lut(user_input);
    Mmc mmc1(user_input, lut);
    char lut_path[] = "data/lut.csv";
    char signal_path[] = "data/signal.csv";
    uint16_t seed = 12345;

    SaveSignal(lut.get_lut(), lut_path);
    SaveSignal(mmc1.generate_pulses(), signal_path);

    //Seed(seed);
    //GenerateRandomArray(user_input.num_samples, random_array);
    //SaveSignal(random_array, random_path);

    // while(0){
    //     switch (STATE)
    //     {
    //     case 0:
    //         break;
        
    //     default:
    //         break;
    //     }
    // }

    return 0;
}


