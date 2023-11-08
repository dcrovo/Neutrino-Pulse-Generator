#ifndef PIXEL_H_
#define PIXEL_H_

#include "mmc.h"

class Pixel {
public:
    Pixel(UserInput user_input, Lut& lut);

    std::vector<double> get_signal();
    void generate_signal();

private:
    Mmc mmc_pos_;
    Mmc mmc_neg_;
    std::vector<double> signal_;
    static int id_count_;
    int id_;

};

#endif  // PIXEL_H_
