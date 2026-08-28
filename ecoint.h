#ifndef ECOINT_H
#define ECOINT_H

#define ECOINT_OK 0
#define ECOINT_NOTGOOD -1

#include <math.h>
#include <stdbool.h>

static inline double getthres(double K, double M, double P, double Pool) {
	return ((P*P) * K * M) / Pool;
}

static inline double getelo(double K, double M, double P, double Pool, double T, double* Tthres) {
	*Tthres = getthres(K,M,P,Pool);
	return (Pool / K / M / P) * T;
}

static inline bool checkthres(double K, double M, double P, double Pool, double* Tthres) {
	double tmp = (Pool / K / M / P) * *Tthres;
	return fabs(tmp-P) < 1e-9;
}

static inline int winnings(double* p_a, double* p_b, double* Pool, double* win, double K, double M, double P, double D, double DC, int MR, int MP, double* Tthres) {
	double diff = fabs(*p_a - *p_b);
	if (win == p_a) {
    diff *= 1 - D;
    *p_a = fmax(MR, *p_a + (diff-(D*DC)));
    *Pool = fmax(MP, *Pool - (D*DC));
    *p_b = fmax(MR, *p_b - diff);
	} else if (win == p_b) {
    diff *= 1 - D;
		*p_a = fmax(MR, *p_a - diff);
		*Pool = fmax(MP, *Pool - (D*DC));
		*p_b = fmax(MR, *p_b + (diff-(D*DC)));
	} else {
		return ECOINT_NOTGOOD;
	}
	*Tthres = getthres(K,M,P,*Pool);
	return ECOINT_OK;
}

#endif
