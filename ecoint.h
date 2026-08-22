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

static inline int winnings(double* p_a, double* p_b, double* Pool, double* win, double K, double M, double P, double D, int MR, int MP, double* Tthres) {
	double diff = fabs(*p_a - *p_b);
	if (win == p_a) {
		double eb = fmax(MR, *p_b - diff);
		double loss = fabs(*p_b - eb);
		*p_b = eb;
		*Pool = fmax(MP, *Pool - loss);
		*p_a = *p_a * (1 - D);
	} else if (win == p_b) {
		double ea = fmax(MR, *p_a - diff);
		double loss = fabs(*p_a - ea);
		*p_a = ea;
		*Pool = fmax(MP, *Pool - loss);
		*p_b = *p_b * (1 - D);
	} else {
		return ECOINT_NOTGOOD;
	}
	*Tthres = getthres(K,M,P,*Pool);
	return ECOINT_OK;
}

#endif
