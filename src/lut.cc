#include "lut.h"

#include <algorithm>
#include <functional>
#include <iostream>

Lut::Lut(UserInput user_input) {
  this->amplitude = user_input.amplitude_lut;
  this->num_samples = user_input.num_samples;
  this->lut_tau = user_input.lut_tau;
  set_taus(user_input.taus);
  generate_lut();
  generate_canonical_lut();
}

Lut::~Lut() {}

void Lut::generate_lut() {
  double sum = 0;
  auto largest_tau = *std::max_element(this->taus.begin(), this->taus.end());
  this->time_step = (t_scaling_factor * largest_tau) / num_samples;
  for (int i = 0; i < this->num_samples; i++) {
    double t = i * time_step;
    for (int j = 0; j < this->taus.size(); j++) {
      double signal = this->amplitude * exp(-t / this->taus[j]);
      sum += signal;
    }

    this->lut.push_back(sum );
    sum = 0;
  }
}

void Lut::generate_canonical_lut() {
  this->time_step_c = t_scaling_factor * lut_tau / num_samples;
  for (int i = 0; i < this->num_samples; i++) {
    double t = i * time_step;

    double signal = this->amplitude * exp(-t / lut_tau);

    this->canonical_lut.push_back(signal);
  }
}
void Lut::set_amplitude(double amplitude) { this->amplitude = amplitude; }
void Lut::set_taus(double taus[]) {
  for (int i = 0; i < 4; i++) {
    this->taus.push_back(taus[i]);
  }
}
void Lut::set_taus(std::vector<double> taus) { this->taus; }
void Lut::set_nsamples(int n_samples) { this->num_samples = n_samples; }
void Lut::set_lut_tau(double lut_tau) { this->lut_tau = lut_tau; }

double Lut::get_amplitude(void) { return this->amplitude; }
double Lut::get_lut_tau(void) { return this->lut_tau; }
std::vector<double> Lut::get_taus(void) { return this->taus; }
int Lut::get_nsamples(void) { return this->num_samples; }

double Lut::get_time_step(void) { return this->time_step; }
double Lut::get_time_step_c(void) { return this->time_step_c; }
std::vector<double> Lut::get_lut(void) { return this->lut; }
std::vector<double> Lut::get_canonical_lut(void) {
  return this->canonical_lut;
}

std::vector<double> Lut::generate_new_signal(double new_amplitude,
                                               double new_tau) {
  // Generates a new signal from the cannonical LUT
  std::vector<double> new_signal;

  double time_step = 0.1 * lut_tau / num_samples;
  for (int i = 0; i < num_samples; i++) {
    double t = i * time_step;
    double t_over_tau = t / new_tau;  // Calculate t/tau for the new tau

    // Calculate the index and interpolation weight
    double index = t_over_tau / time_step;
    int index1 = static_cast<int>(index);
    int index2 = std::min(index1 + 1, num_samples - 1); /*  */
    double weight = index - index1;

    if (index1 >= num_samples) {
      new_signal.push_back(0);  // Handle out-of-bounds
    } else {
      // Interpolate between the LUT values linearly
      double lut_value1 = canonical_lut[index1] / 65535.0;
      double lut_value2 = canonical_lut[index2] / 65535.0;
      double interpolated_value =
          (1.0 - weight) * lut_value1 + weight * lut_value2;
      double new_signal_value = new_amplitude * interpolated_value;
      new_signal.push_back(static_cast<uint16_t>(new_signal_value * 65535.0));
    }
  }

  return new_signal;
}

std::vector<uint16_t> Lut::generate_new_signal(UserInput user_input) {
  std::vector<uint16_t> new_signal;
  auto largest_tau = *std::max_element(this->taus.begin(), this->taus.end());

  double time_step = (t_scaling_factor * largest_tau) / num_samples;
  // for (int i = 0; i < num_samples; i++) {
  //     double t = i * time_step;
  //     double sum = 0;

  //     for (int j = 0; j < 4; j++) {
  //         double t_over_tau = t / user_input.taus[j]; // Calculate t/tau for
  //         the new tau

  //         // Calculate the index and interpolation weight
  //         double index = t_over_tau / time_step;
  //         int index1 = static_cast<int>(index);
  //         int index2 = std::min(index1 + 1, num_samples - 1);
  //         double weight = index - index1;

  //         if (index1 >= num_samples) {
  //             sum += 0; // Handle out-of-bounds
  //         } else {
  //             // Interpolate between the LUT values linearly
  //             double lut_value1 = canonical_lut[index1] / 65535.0;
  //             double lut_value2 = canonical_lut[index2] / 65535.0;
  //             double interpolated_value = (1.0 - weight) * lut_value1 +
  //             weight * lut_value2; double new_signal_value =
  //             user_input.amplitude * interpolated_value; sum +=
  //             new_signal_value;
  //         }
  //     }

  // // Average the sum over the four tau values
  // double average_value = sum / 4.0;
  // new_signal.push_back(static_cast<uint16_t>(average_value * 65535.0));
  // }
  std::vector<uint16_t> s1, s2, s3, s4;
  s1 = Lut::generate_new_signal(user_input.amplitude, user_input.taus[0]);
  s2 = Lut::generate_new_signal(user_input.amplitude, user_input.taus[1]);
  s3 = Lut::generate_new_signal(user_input.amplitude, user_input.taus[2]);
  s4 = Lut::generate_new_signal(user_input.amplitude, user_input.taus[3]);
  int idx = 0;
  std::vector<uint16_t> output;
  for (auto i : s1) {
    output.push_back(
        static_cast<uint16_t>((s1[idx] + s2[idx] + s3[idx] + s4[idx]) / 4));
    idx++;
  }
  return output;
}
