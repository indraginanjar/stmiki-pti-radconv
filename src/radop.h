/*
Mata Kuliah Pengantar Teknologi Informasi
Kelas Mandiri
Semester I, 2010
Kelompok 2:
101100195 Desi Putri Dewi
101100180 Indra Ginanjar
101100034 Muhammad Kadri
101100052 Overson Oscar Manalu
101100015 Reza Parisol
101100162 Yendrizal

Program Studi Sistem Informasi
SMIK Indonesia
Padang, Desember 2010
*/

#ifndef __RADOP__H_
#define __RADOP__H_




enum radix_t {BIN = 2, OCT = 8, DEC = 10, HEX = 16};

/* get valid character set of radix for filtering user input */
void radop_radcharset(char **charset, enum radix_t rad);

/* turn string backward */
void radop_backwdstr(const char* str, const int len, char** backwd);

/* convert a hexadecimal character to integer (decimal) */
int radop_hexchrtoint(const char hex);

/* convert integer (decimal) to hexadecimal character */
char radop_inttohexchr(const int num);

/* convert integer to specified radix number */
void radop_inttoradix(char** dest, const int src, const enum radix_t radix);

/* convert number to other radix */
void radop_convrad(char** result, const char* src, const int srclen, const enum radix_t srcradix, const enum radix_t destradix);

/* convert a string number from a certain radix to integer (decimal) */
double radop_radtodec(const char* src, const int len, enum radix_t rad);

#endif
