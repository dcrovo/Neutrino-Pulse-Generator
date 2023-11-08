#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "utils.h"
#include "lut.h"
#include "mmc.h"
#include "squid.h"
#include "pixel.h"
#include "channel.h"
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
        .modulation_freq_1 = 0.05e3,
        .modulation_amp = 4,
        .sample_rate = 800e6,
        .amplitude_lut = 1,
        .amplitude = 1, 
        .taus = {9.40e-3, 2.72e-3, 45.0e-3, 0.38e-3},
        .simulation_time = 1e-3,
        .num_samples = 4096,
        .time_step = (45.0e-3*10)/4056,
        .lut_tau = 1,
        .random_noise_amplitude = 0.05,
        .simulation_window = 1.0,
        .activity = 2.0,
        .num_channels=2,
    };

    Lut lut(user_input);
    std::vector<Channel> channels;
    //channels.resize(user_input.num_channels);
    char channel_path[] = "data/";
    //channels.resize(user_input.num_channels);
    //Mmc mmc1(user_input, lut,-1);
    
    Channel channel(user_input, lut);
    channel.run_channel();
    channels.push_back(channel);
    Channel channel2(user_input, lut);
    channel2.run_channel();
    channels.push_back(channel2);
    int i=0;

        for (auto channel : channels){
            std::string new_path = "data/channel" + std::to_string(i) + ".csv";        
            SaveSignal(channel.get_signal(), new_path);
            i++;
        }


    Pixel pixel(user_input, lut);

    char lut_path[] = "data/lut.csv";
    char signal_path[] = "data/signal.csv";
    char mod_path[] = "data/mod.csv";

    user_input.simulation_window = lut.get_time_step()*user_input.num_samples;
    uint16_t seed = 12345;
    pixel.generate_signal();
    std::vector<double> pixel_signal = pixel.get_signal();
    Squid squid(user_input, lut.get_time_step(), pixel_signal);

    squid.apply_squid();
    SaveSignal(lut.get_lut(), lut_path);
    SaveSignal(pixel_signal, signal_path);
    SaveSignal(squid.get_signal(), mod_path);

    //Seed(seed);
    //GenerateRandomArray(user_input.num_samples, random_aSrray);
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


