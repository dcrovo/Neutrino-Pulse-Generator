#ifndef NPG_CHANNEL_H_
#define NPG_CHANNEL_H_

#include <math.h>
#include <vector>

#include "utils.h"
#include "lut.h"
#include "pixel.h"
#include "squid.h"

class Channel{ 
  public: 
  Channel(UserInput user_input, Lut& lut);
  ~Channel();
  void run_channel();
  std::vector<double> get_signal();
  

  private:
  static int id_count_;
  int id_;
  Pixel pixel_;
  Squid squid_;
  Lut lut_;
  std::vector<double> signal_;
};

#endif