#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <memory>
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
        .modulation_freq_1 = 1e3,
        .modulation_amp = 4,
        .sample_rate = 800e6,
        .amplitude_lut = 1,
        .amplitude = 1, 
        .taus = {9.40e-3, 2.72e-3, 45.0e-3, 0.38e-3},
        .simulation_time = 1e-3,
        .num_samples = 4096,
        .time_step = (45.0e-3*10)/4056,
        .lut_tau = 1,
        .random_noise_amplitude = 0.01,
        .simulation_window = 1,
        .activity = 2.0,
        .num_channels=8,
        .clock_rate = 1e-5,
    };

    Lut lut(user_input);
    std::vector<Channel> channels;
    //channels.resize(user_input.num_channels);
    char channel_path[] = "data/";
    //channels.resize(user_input.num_channels);
    //Mmc mmc1(user_input, lut,1);
    for(int i=0 ; i<user_input.num_channels;i++){
        Channel channel(user_input, lut);
        channels.push_back(channel);
    }

    int i=0;

    for (auto channel : channels){
        channel.run_channel();
        std::string new_path = "data/channel" + std::to_string(i) + ".csv";
        std::string new_path_pixel = "data/pixel"+ std::to_string(i) + ".csv";
        SaveSignal(channel.get_signal(), new_path);
        SaveSignal(channel.get_pixel_signal(), new_path_pixel);
        i++;
    }


   

    char lut_path[] = "data/lut.csv";
    char signal_path[] = "data/signal.csv";
    char mod_path[] = "data/mod.csv";


    Pixel pixel(user_input, lut);
    //std::cout<<"CHANEL SIZE"<<channel.get_signal().size();
    //SaveSignal(channel.get_signal(), "data/channel0.csv");

    // user_input.simulation_window = p_lut->get_time_step()*user_input.num_samples;
    // uint16_t seed = 12345;
    pixel.generate_signal();
    std::vector<double> pixel_signal = pixel.get_signal();
    // Squid squid(user_input, lut->get_time_step(), pixel_signal);

    // squid.apply_squid();
    // SaveSignal(lut.get_lut(), lut_path);
    SaveSignal(pixel_signal, signal_path);
    //SaveSignal(squid.get_signal(), mod_path);

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


