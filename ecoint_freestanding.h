/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2026 kban3108-max
*/
#ifndef ECOINT_ANTIOS_H
#define ECOINT_ANTIOS_H

#define ECOINT_OK 0
#define ECOINT_NOTGOOD -1

#include <stdbool.h>

static inline double fmax(int limiter, double num)
{
    if (num < limiter)
        return limiter;

    return num;
}

static inline double fabs(double num) {
    if (num < 0)
        return num * -1;
    return num;
}

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
