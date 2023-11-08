#include "pixel.h"
int Pixel::id_count_ =0;

Pixel::Pixel(UserInput user_input, Lut& lut)
    : mmc_pos_(user_input, lut, 1), mmc_neg_(user_input, lut, -1), id_(++id_count_) {
  // Constructor initializes two Mmc objects
}



void Pixel::generate_signal() {
  std::vector<double> signal_pos = mmc_pos_.generate_pulses();
  std::vector<double> signal_neg = mmc_neg_.generate_pulses();

  // Sum the two signals
  std::vector<double> combined_signal;
  for (size_t i = 0; i < signal_pos.size(); i++) {
    combined_signal.push_back(signal_pos[i] + signal_neg[i]);
  }

  signal_ = combined_signal;
}

std::vector<double> Pixel::get_signal(){
  return signal_;
}