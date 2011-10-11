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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifdef _WIN32
    #include "radop.h"
#else
    #include "src\radop.h"
#endif

void radop_radcharset(char **charset, enum radix_t rad)
{
	*charset = calloc(rad + 1, 1);
	if(*charset == NULL)
		exit(-1);
	switch(rad)
	{
	case BIN:
		strcpy(*charset, "01");
		break;
	case OCT:
		strcpy(*charset, "01234567");
		break;
	case HEX:
		strcpy(*charset, "0123456789ABCDEFabcdef");
		break;
	default:
		strcpy(*charset, "0123456789");
	}
}

void radop_backwdstr(const char* str, const int len, char** backwd)
{
	int i;
	*backwd = calloc(len, sizeof(char));
	if(*backwd == NULL)
		exit(-1);
	for(i = 0; i < len + 1; i++)
	{
		(*backwd)[i] = str[len - i - 1];
	}
	(*backwd)[len] = 0;
}

double radop_radtodec(const char* src, const int len, enum radix_t rad)
{
	int counter;
	char curdigit;
	double dec = 0;
	int curnum;
	for(counter = len - 1; counter >= 0; --counter)
	{
		curdigit = src[counter];
		curnum = radop_hexchrtoint(curdigit);
		dec += curnum * pow(rad, (double) len - counter - 1);
	}
	return dec;
}

int radop_hexchrtoint(const char hex)
{
	int numlist[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 13, 14, 15};
	return numlist[(int) hex - 48]; /* 48 = '0' ASCII code */
}

char radop_inttohexchr(const int num)
{
	char *charset;
	char result;
	radop_radcharset(&charset, HEX);
	if(num < 0 || num > 15)
	{
		return '0';
	}
	result = charset[num];
	return result;
}


void radop_dectorad(char** dest, const double num, const enum radix_t radix)
{
	double dividen = num;
	double remainder;
	char* curdigit;
	int digitcount = 0;
	char* sorted;
	curdigit = calloc(2, sizeof(char));
	if(curdigit == NULL)
		exit(-1);
	*dest = calloc(digitcount+100, sizeof(char));
	if(*dest == NULL)
		exit(-1);
	while(dividen > radix - 1)
	{
		remainder = fmod(dividen,radix);
		dividen = floor(dividen / radix);
		if(radix == HEX)
		{
			*curdigit = radop_inttohexchr((int)remainder);
		}
		else
		{
			sprintf(curdigit, "%d", (int)remainder);
		}
		(*dest)[digitcount] = curdigit[0];
		digitcount++;
	}

	if(radix == HEX)
	{
		*curdigit = radop_inttohexchr((int)dividen);
	}
	else
	{
		sprintf(curdigit, "%.0f", dividen);
	}
	(*dest)[digitcount] = curdigit[0];
	(*dest)[digitcount + 1] = 0; /* end string with NULL */
	radop_backwdstr(*dest, strlen(*dest), &sorted);
	free(*dest);
	*dest = sorted;
	free(curdigit);
}

void radop_convrad(char** result, const char* src, const int srclen, const enum radix_t srcrad, const enum radix_t destrad)
{
	double num = 0;
	num = radop_radtodec(src, srclen, srcrad);
	radop_dectorad(result, num, destrad);
}
