#include "squid.h"
#include <cmath>

int Squid::id_count_ =0;
// Constructor
Squid::Squid(){}
Squid::Squid(UserInput user_input, double time_step, std::vector<double> pixel_signal) : 
  id_(++id_count_),
  modulation_freq_(user_input.modulation_freq_1*4*id_), 
  modulation_amp_(user_input.modulation_amp),
  pixel_signal_(pixel_signal),
  time_step_(time_step) {
    // Constructor initializes modulation_frequency_ and modulation_amplitude_
   signal_.resize(pixel_signal.size(), 0);
}

// Apply sinusoidal modulation to the signal
void Squid::apply_squid() {
    const int num_points = pixel_signal_.size();

    // Generate the sinusoidal modulation signal and add it to the original signal
    for (int i = 0; i < num_points; i++) {
        double t = time_step_*i;
        double modulation_value = modulation_amp_ *  std::cos((2.0 * M_PI * modulation_freq_ + pixel_signal_[i])*t );
        signal_[i] += static_cast<double>(modulation_value);
    }
}

std::vector<double> Squid::get_signal(){
  std::cout<<time_step_;
  return signal_;
}