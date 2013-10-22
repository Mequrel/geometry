#ifndef SHEWCHUK_H
#define SHEWCHUK_H

#ifdef __cplusplus
extern "C"{
#endif 

double orient2dfast(double*, double*, double*);
double orient2dexact(double*, double*, double*);
double orient2dslow(double*, double*, double*);

#ifdef __cplusplus
}
#endif

#endif