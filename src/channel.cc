#include "channel.h"

int Channel::id_count_ =0;

Channel::Channel(UserInput user_input, Lut& lut) : 
  id_(++id_count_), 
  lut_(lut),
  pixel_(user_input, lut){
    pixel_.generate_signal();
    Squid squid_(user_input, lut_.get_time_step(),pixel_.get_signal());

  }
Channel::~Channel(){

}


void Channel::run_channel(){
  squid_.apply_squid();
  signal_ = squid_.get_signal();
}

std::vector<double> Channel::get_signal(){return signal_;}