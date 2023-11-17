#include "channel.h"

int Channel::id_count_ =0;

Channel::Channel(UserInput user_input, Lut& lut) : 
id_(++id_count_),
lut_(lut),
pixel_(user_input, lut),
squid_(user_input, user_input.clock_rate){}



void Channel::run_channel(){
  pixel_.generate_signal();
  squid_.set_pixel_signal(pixel_.get_signal());
  squid_.apply_squid();
  signal_ = squid_.get_signal();
}

std::vector<double> Channel::get_signal(){return signal_;}
std::vector<double> Channel::get_pixel_signal(){return pixel_.get_signal();}