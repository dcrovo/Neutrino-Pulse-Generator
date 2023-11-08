#ifndef NPG_LUT_H_
#define NPG_LUT_H_

#include <math.h>
#include <stdint.h>

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

#include "utils.h"

static const double t_scaling_factor = 10.2;

class Lut {
 public:
  Lut();
  Lut(UserInput user_input);
  ~Lut();

  void generate_lut();
  void generate_canonical_lut();

  void set_amplitude(double amplitude);
  void set_taus(double taus[]);
  void set_taus(std::vector<double> taus);
  void set_nsamples(int n_samples);
  void set_lut_tau(double tau);

  double get_amplitude(void);
  std::vector<double> get_taus(void);
  int get_nsamples(void);
  double get_time_step(void);
  double get_time_step_c(void);

  std::vector<double> get_lut(void);
  double get_lut_tau();
  std::vector<double> get_canonical_lut(void);
  std::vector<double> generate_new_signal(double new_amplitude,
                                            double new_tau);
  std::vector<double> generate_new_signal(UserInput user_input);

 private:
  double amplitude;
  std::vector<double> taus;
  int num_samples;
  std::vector<double> lut;
  std::vector<double> canonical_lut;
  double lut_tau;
  double time_step;
  double time_step_c;
};

#endif  // NPG_LUT_H