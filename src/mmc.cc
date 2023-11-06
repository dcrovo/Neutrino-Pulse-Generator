#include "mmc.h"

Mmc::Mmc(UserInput user_input, Lut &lut)
    : lut_(lut),
      activity_(user_input.activity),
      total_time_(user_input.simulation_window),
      noise_amplitude_(user_input.random_noise_amplitude), 
      amplitude_(user_input.amplitude){
  this->time_step_ = lut.get_time_step();
  this->num_points_ = static_cast<int>(this->total_time_ / this->time_step_)+1;
  this->generator_.seed(std::random_device()()); // Seed the random number generator.
  std::cout<<"num_points"<<num_points_<<'\n';
}

Mmc::~Mmc() {}

std::vector<int32_t> Mmc::generate_pulses(){
  generate_time_points();
  generate_trigger_times();
  generate_pulse_shapes();
  //add_noise();
  return signal_;
}

void Mmc::generate_time_points(){
  time_points_.resize(num_points_);
  for (int i = 0; i<num_points_; i++){
    time_points_[i] = i * time_step_;
  }
}

void Mmc::generate_trigger_times(){
  std::poisson_distribution<int> poisson(activity_*total_time_);
  const int num_pulses = poisson(generator_);
  std::cout<<"number of pulses: "<<num_pulses<<'\n';
  std::uniform_real_distribution<double> uniform(0,total_time_);
  trigger_times_.resize(num_pulses);
  std::cout<<"Size: "<<trigger_times_.size()<<'\n';

  for(int i = 0; i<num_pulses; i++){
    trigger_times_[i] = uniform(generator_);
    std::cout<<trigger_times_[i]<<'\n';
  }
  std::sort(trigger_times_.begin(), trigger_times_.end());
}

void Mmc::generate_pulse_shapes(){ 
  signal_.resize(num_points_, 0);
  int lut_index = 0;
  for(auto trigger_time : trigger_times_){ 
    for(int i = 0; i<num_points_; i++){
      if(time_points_[i] >= trigger_time && lut_index<lut_.get_nsamples()){
        signal_[i] +=(amplitude_)*(lut_.get_lut()[lut_index]);
        lut_index++;
      }
    }
    std::cout<<"amplitude: "<<static_cast<int32_t>(amplitude_)<<'\n';
    lut_index =0;
  }
}

void Mmc::add_noise(){ 
  std::normal_distribution<double> normal(0, noise_amplitude_);
  for(int i=0; i<num_points_; i++){
    signal_[i] += static_cast<int32_t>(normal(generator_));
  }
}
