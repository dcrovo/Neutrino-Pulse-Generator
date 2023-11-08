#include "mmc.h"
int Mmc::id_count_=0;
Mmc::Mmc(UserInput user_input, Lut &lut, int polarity)
    : id_(++id_count_),
      lut_(lut),
      activity_(user_input.activity),
      total_time_(user_input.simulation_window),
      noise_amplitude_(user_input.random_noise_amplitude),
      amplitude_(user_input.amplitude),
      polarity_(polarity) {
  this->time_step_ = lut.get_time_step();
  this->num_points_ =
      static_cast<int>(this->total_time_ / this->time_step_) + 1;
  this->generator_.seed(
      std::random_device()());  // Seed the random number generator.
    std::cout<<"MMC created with Id:"<<id_<<"\n";
  }

Mmc::Mmc(const Mmc& other)
    : total_time_(other.total_time_),
      tau_(other.tau_),
      activity_(other.activity_),
      num_points_(other.num_points_),
      time_step_(other.time_step_),
      amplitude_(other.amplitude_),
      noise_amplitude_(other.noise_amplitude_),
      polarity_(other.polarity_),
      id_(other.id_),
      time_points_(other.time_points_),
      signal_(other.signal_),
      trigger_times_(other.trigger_times_),
      lut_(other.lut_),
      generator_(other.generator_) {
  // Copy any other member variables or perform additional setup if needed
}

Mmc::~Mmc() {}

std::vector<double> Mmc::generate_pulses() {
  generate_time_points();
  generate_trigger_times1();
  generate_pulse_shapes();
  add_noise();
  return signal_;
}

void Mmc::generate_time_points() {
  time_points_.resize(num_points_);
  for (int i = 0; i < num_points_; i++) {
    time_points_[i] = i * time_step_;
  }
}

void Mmc::generate_trigger_times() {
  std::poisson_distribution<int> poisson(activity_ * total_time_);
  const int num_pulses = poisson(generator_);
  std::cout << "number of pulses: " << num_pulses << '\n';
  std::uniform_real_distribution<double> uniform(0, total_time_);
  trigger_times_.resize(num_pulses);
  std::cout << "total_time: " << total_time_ << '\n';

  for (int i = 0; i < num_pulses; i++) {
    trigger_times_[i] = uniform(generator_);
    std::cout << trigger_times_[i] << '\n';
  }
  std::sort(trigger_times_.begin(), trigger_times_.end());
}

void Mmc::generate_trigger_times1() {
  std::uniform_real_distribution<double> uniform(0, total_time_);
  const int num_pulses = static_cast<int>(activity_ * total_time_);
  trigger_times_.resize(num_pulses);

  for (int i = 0; i < num_pulses; i++) {
    trigger_times_[i] = uniform(generator_);
  }
  std::sort(trigger_times_.begin(), trigger_times_.end());
}

void Mmc::generate_pulse_shapes() {
  signal_.resize(num_points_, 0);
  int lut_index = 0;
  for (auto trigger_time : trigger_times_) {
    for (int i = 0; i < num_points_; i++) {
      if (time_points_[i] >= trigger_time && lut_index < lut_.get_nsamples()) {
        signal_[i] += (amplitude_ * polarity_) * (lut_.get_lut()[lut_index]);
        lut_index++;
      }
    }
    lut_index = 0;
  }
}

void Mmc::add_noise() {
  std::normal_distribution<double> normal(0, noise_amplitude_);
  for (int i = 0; i < num_points_; i++) {
    signal_[i] += normal(generator_);
  }
}
