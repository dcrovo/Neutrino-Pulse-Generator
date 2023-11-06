#ifndef NPG_SQUID_H_
#define NPG_SQUID_H_

#include "utils.h"

class Squid{
  public:
  Squid(UserInput user_input);
  ~Squid();
  std::vector<uint32_t> apply_squid();

  private: 
  double carrier_freq;
  double carrier_amp;
  double mod_coef;

};

#endif