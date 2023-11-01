#ifndef NPG_LUT_H_
#define NPG_LUT_H_

#include <stdint.h>
#include <math.h>
#include <vector>
#include "utils.h"

class Lut{ 
    
    public: 
    Lut();
    Lut(UserInput  user_input);
    ~Lut();


    void calculate_exponential(UserInput user_input);
    void set_amplitude(double amplitude);
    void set_taus(double taus[]);
    void set_taus(std::vector<double> taus);
    void set_nsamples(int n_samples);
    void set_time_step(double time_step);

    double get_amplitude(void);
    double get_taus(void);
    int get_nsamples(void);
    int get_time_step(void);
    std::vector<uint16_t> get_lut(void);
       
    private: 
    
    double amplitude; 
    double taus[4];
    int num_samples;
    double time_step;
    std::vector<uint16_t> lut[];



};



#endif // NPG_LUT_H