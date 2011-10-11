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
#include <ctype.h>
#include <conio.h>
#ifdef _WIN32
    #include "main.h"
    #include "radop.h"
    #include <windows.h>
#else
    #include <dos.h>
    #define _getch() getch()
    #define Sleep(int) sleep(int)
    #define _kbhit() kbhit()
    #include "src\main.h"
    #include "src\radop.h"
#endif


int main()
{
	char *srcbuf;
	enum radix_t srcrad;
	char *resultbuf;
	enum radix_t destrad;
	char *charset;
	const int esc = 27;
	int inlen = 14; /* max safe digit of double */

	system("cls");
	printf("\n\n\n				 Radix Converter\n");
	printf("				 ---------------\n\n");
calculate:

	printf("\nInput radix (2,8,10,16) : ");
	srcrad = getusrrad();
	printf("\nInput number            : ");
	radop_radcharset(&charset, srcrad);
	inlen = inlen * DEC / srcrad;
	readkeyb(&srcbuf, 1, inlen, 1, charset);
	printf("\nOutput radix (2,8,10,16): ");
	destrad = getusrrad();
	radop_convrad(&resultbuf, srcbuf, strlen(srcbuf), srcrad, destrad);
	printf("\nOutput number           = %s\n", resultbuf);
	free(srcbuf);
	printf("\n\nTekan 'ESC' untuk mengakhiri atau tombol lainnya untuk mengulang kembali ...");
	printf("\n\n");
	if(_getch() != esc)
	{
		goto calculate;
	}
	prnmember();
	return 0;
}

void prnmember(void)
{
	system("cls");
	printf("\n\n\
			STMIK Indonesia\n\
			Sistem Informasi\n\
			Mata Kuliah Pengantar Teknologi Informasi\n\
			Kelas Mandiri\n\
			Semester I, 2010\n\n\
			Kelompok 2:\n\
			101100195 Desi Putri Dewi\n\
			101100180 Indra Ginanjar\n\
			101100034 Muhammad Kadri\n\
			101100052 Overson Oscar Manalu\n\
			101100015 Reza Parisol\n\
			101100068 Rizka Zewesti\n\
			101100162 Yendrizal\n\n");
    _getch();
}

void readkeyb(char **result, size_t minlen, size_t maxlen, int echo, const char* charset)
{
	const char bkspc = 8;
	const char enter = 13;
	size_t nbuf = 0;
	size_t nresult = 0;
	int curchr = 0;
	*result = calloc(maxlen + 1, sizeof(char));
	while(curchr != enter && nresult < maxlen)
	{
		Sleep(1);
		while(_kbhit() && nbuf < maxlen)
		{
			curchr = _getch();
			if(curchr == bkspc)
			{
				if(nresult > 0)
				{
					--nresult;
					*(*result + nresult) = 0;
					if(echo == 1)
					{
						printf("%c %c", bkspc, bkspc);
					}
				}
			}
			else if(curchr == enter && nresult < minlen)
			{
				curchr = 0;
			}
			else if(strchr(charset, curchr) != NULL)
			{
				*(*result + nresult) = (char) toupper(curchr);
				if(echo == 1)
				{
					printf("%c", *(*result + nresult));
				}
				++nresult;
			}
		}
		/* clear BIOS keyboard buffer if any */
		while(_kbhit())
		{
			_getch();
		}
	}
}

/* get radix number from user */
enum radix_t getusrrad(void)
{
	char *radstr;
	const char *charset = "01268";
	enum radix_t result;
	const int bkspc = 8;
userinput:
	readkeyb(&radstr, 1, 2, 1, charset);
	result = atoi(radstr);
	if(result == 2 ||
		result == 8 ||
		result == 10 ||
		result == 16)
	{
		free(radstr);
		return result;
	}
	if(strlen(radstr) == 1)
	{
		printf("%c %c", bkspc, bkspc);
	}
	else if(strlen(radstr) == 2)
	{
		printf("%c %c%c %c", bkspc, bkspc, bkspc, bkspc);
	}
	free(radstr);
	goto userinput;
}
