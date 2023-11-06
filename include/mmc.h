#ifndef NPG_MMC_H_
#define NPG_MMC_H_

#include <math.h>
#include <stdint.h>

#include <random>
#include <vector>

#include "lut.h"
#include "utils.h"

class Mmc {
 public:
  Mmc(UserInput user_input, Lut& lut);
  ~Mmc();
  std::vector<int32_t> generate_pulses();

 private:
  double total_time_;
  double tau_;
  double activity_;
  int num_points_;

  double time_step_;
  double amplitude_;
  double noise_amplitude_;

  std::vector<double> time_points_;
  std::vector<int32_t> signal_;
  std::vector<double> trigger_times_;
  Lut& lut_;
  std::mt19937 generator_;

  void generate_time_points(void);
  void generate_trigger_times(void);
  void generate_pulse_shapes();
  void add_noise();
};
#endif  // NPG_MMC_H_