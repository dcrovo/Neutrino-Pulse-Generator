#ifndef NPG_SQUID_H_
#define NPG_SQUID_H_

#include "utils.h"

class Squid {
 public:
  Squid();
  Squid(UserInput user_input, double time_step, std::vector<double> mmc_signal);
  //~Squid();
  void apply_squid();
  std::vector<double> get_signal();

 private:
  static int id_count_;
  int id_;
  double modulation_freq_;
  double modulation_amp_;
  double time_step_;
  std::vector<double> signal_;
  std::vector<double> pixel_signal_;
};

#endif