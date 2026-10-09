# ecoint - EConomic pOINT

ecoint is a project that takes macroeconomics and turns it into a rating system

# Behavior

there are multiple variables that control the behavior of ecoint

P is the amount of points the user has (or in winnings() a controller)

K has no meaning but is a controller

M is like K

D also has no meaning but controls deflation (idk how to explain it)

DC means "D Controller" and it controls D in winnings (again idk how to explain it just read the code)

Pool is the total amount of points across all users (like how many dollars are printed, or else it wouldn't be an economy)

T is like M and K

Tthres is the threshold between where T negates and T adds, if T = Tthres then the output should be equal to P

MP means 'Minimum Pool' (wow finally a meaning), which is the minimum amount of points Pool can have

MR means 'Minimum Rating', it's like MP but for P instead of Pool

ECOINT_OK is equal to 0 and is what the program returns when it's good

ECOINT_NOTGOOD is equal to -1 and is what the program returns when it's well not good

# Usage

1. RTFS (read the fucking source)

2. Include the header (or compile the .a or .so for usage, go to Usage (.a/.so) for that)
```C
#include "ecoint.h"
```

3. Use the functions

getelo (it's not elo but I named it getelo for clarity):
```c
double newelo = getelo(K, M, P, Pool, T, &Tthres);
```
getthres:
```c
double newTthres = getthres(K, M, P, Pool);
```
checkthres:
```c
bool isThres = checkthres(K, M, P, Pool, &Tthres);
```
winnings (oh boy):
```c
// for p_a winning
int whoWins = winnings(&p_a, &p_b, &Pool, &p_a, K, M, P, D, DC, MR, MP, &Tthres);
// for p_b winning
int whoWins = winnings(&p_a, &p_b, &Pool, &p_b, K, M, P, D, DC, MR, MP, &Tthres);
```
Note from developer: winnings returns the status code (if it's 0 it ran successfully if it's -1 fix it), it mutates the variables you input.

4. Compile the code

# Usage (.a/.so)

this section is for compiling ecoint to .a or .so to be used dynamically or with ffi (like JNI or cffi)
1. run the commands below
```shell
# for all types
meson setup build
# for .a only
meson setup build -Dlibrary_type=static
# for .so/.dll/.dylib only
meson setup build -Dlibrary_type=dynamic

# build
ninja -C build
```

# License

This project is licensed under the GNU Lesser General Public License v2.1 only
(LGPL-2.1-only). See the LICENSE file for the full license text.

[LICENSE](LICENSE)
