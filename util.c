#include "prefix.h"

#include "util.h"

#include <ctype.h>
#ifdef TARGET_OS_WINDOWS
#include <windows.h>
#else
#include <sys/time.h>
#endif

void squeeze(char *str)
{
	int r; /* next character to be read */
	int w; /* next character to be written */

	r=w=0;
	while (str[r])
	{
		if (isspace((int)(str[r])) || iscntrl((int)(str[r])))
		{
			if (w > 0 && !isspace((int)(str[w-1])))
				str[w++] = ' ';
		}
		else
			str[w++] = str[r];
		r++;
	}
	str[w] = 0;
}

double time_sec(void)
{
#ifdef TARGET_OS_WINDOWS
	LARGE_INTEGER freq, ctr;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&ctr);
	return (double)ctr.QuadPart / (double)freq.QuadPart;
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (double)tv.tv_sec + ((double)tv.tv_usec / 1000000.0);
#endif
}
