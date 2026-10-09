/*
 * ecoint - macroeconomy like rating system
 * Copyright (C) 2026 kban3108-max
 *
 * This file is part of ecoint.
 *
 * ecoint is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, version 2.1 only.
 *
 * ecoint is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ecoint. If not, see <https://www.gnu.org/licenses/>.
 */

#define ECOINT_OK 0
#define ECOINT_NOTGOOD -1

#include <math.h>
#include <stdbool.h>

double getthres(double K, double M, double P, double Pool) {
        return ((P*P) * K * M) / Pool;
}

double getelo(double K, double M, double P, double Pool, double T, double* Tthres) {
        *Tthres = getthres(K,M,P,Pool);
        return (Pool / K / M / P) * T;
}

bool checkthres(double K, double M, double P, double Pool, double* Tthres) {
        double tmp = (Pool / K / M / P) * *Tthres;
        return fabs(tmp-P) < 1e-9;
}

int winnings(double* p_a, double* p_b, double* Pool, double* win, double K, double M, double P, double D, double DC, int MR, int MP, double* Tthres) {
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
