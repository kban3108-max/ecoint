project('ecoint', 'c',
  license: 'LGPL-2.1-only',
  meson_version: '>=1.1.0')

cc = meson.get_compiler('c')
libm = cc.find_library('m', required: false)
inc = include_directories('.')

library_type = get_option('library_type')

if library_type == 'static'
  static_library('ecoint', 'ecoint.c',
    include_directories: inc,
    dependencies: libm,
    install: true)

  static_library('ecoint_freestanding', 'ecoint_freestanding.c',
    include_directories: inc,
    c_args: ['-ffreestanding'],
    install: true)

elif library_type == 'dynamic'
  shared_library('ecoint', 'ecoint.c',
    include_directories: inc,
    dependencies: libm,
    install: true)

  shared_library('ecoint_freestanding', 'ecoint_freestanding.c',
    include_directories: inc,
    c_args: ['-ffreestanding'],
    install: true)

else # 'all'
  both_libraries('ecoint', 'ecoint.c',
    include_directories: inc,
    dependencies: libm,
    install: true)

  both_libraries('ecoint_freestanding', 'ecoint_freestanding.c',
    include_directories: inc,
    c_args: ['-ffreestanding'],
    install: true)
endif


header_template = '''/*
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

#ifndef GUARD_PLACEHOLDER
#define GUARD_PLACEHOLDER

#define ECOINT_OK 0
#define ECOINT_NOTGOOD -1

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

double getthres(double K, double M, double P, double Pool);
double getelo(double K, double M, double P, double Pool, double T, double* Tthres);
bool checkthres(double K, double M, double P, double Pool, double* Tthres);
int winnings(double* p_a, double* p_b, double* Pool, double* win, double K, double M, double P, double D, double DC, int MR, int MP, double* Tthres);

#ifdef __cplusplus
}
#endif

#endif
'''

sh = find_program('sh', required: false)

if sh.found()
  foreach spec : [['ecoint.h', 'ECOINT_H'],
                  ['ecoint_freestanding.h', 'ECOINT_FREESTANDING_H']]
    configure_file(
      output: spec[0],
      command: [sh, '-c', 'printf \'%s\' "$0" > "$1"',
                header_template.replace('GUARD_PLACEHOLDER', spec[1]),
                '@OUTPUT@'],
      install: true,
      install_dir: get_option('includedir'))
  endforeach
else
  warning('sh not found: headers will not be generated or installed')
endif
