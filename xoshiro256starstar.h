#ifndef XOSHIRO256STARSTAR_H
#define XOSHIRO256STARSTAR_H

#include <stdint.h>

uint64_t next(void);
void set_seed(void);
void jump(void);
void long_jump(void);

int64_t next_r(int64_t a, int64_t b);


double next_f(void);
double next_fr(double a, double b);

#endif