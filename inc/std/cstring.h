#pragma once


#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <core/memory.h>
#include <std/ptr.h>

static inline int numlen(uint32_t num)
{
	int len = 0;
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return len;
}
static inline int strlen(const char* str)
{
	int len = 0;
	while (str[len] != '\0') len++;
	return len;
}
static inline char* strrev(char* str)
{
	int i = 0;
	int j = strlen(str) - 1;
	while (i < j)
	{
		char c = str[i];
		str[i] = str[j];
		str[j] = c;
		i++;
		j--;
	}
	return str;
}
static inline void numstr(uint32_t num, int base, char out[])
{
    int sz;
	if (num == 0) 
	{
		out[0] = '0';
		out[1] = '\0';
		return;
	}
	char* str = out;
	int i = 0;
	while (num > 0)
	{
		int r = num % base;
		if (r >= 10)
		{
			str[i] = r - 10 + 'a';
		}
		else
		{
			str[i] = r + '0';
		}
		num = num / base;
		i++;
	}
	str[i] = '\0';
	strrev(str);
}
static inline int strnum(char str[], int base)
{
	int ret = 0;
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			ret = ret * base + str[i] - '0';
		}
		else if (str[i] >= 'a' && str[i] <= 'z')
		{
			ret = ret * base + str[i] - 'a' + 10;
		}
		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			ret = ret * base + str[i] - 'A' + 10;
		}
		i++;
	}
	return ret;
}
static inline bool strcmp(const char *str1, const char *str2)
{
	int i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i]) return str1[i] - str2[i];
		i++;
	}
	return str1[i] - str2[i];
}
static inline bool strcmp_real(const char *str1, const char *str2)
{
	int i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i]) return false;
		i++;
	}
	return true;
}
static inline bool strcmpis(const char *str1, const char *str2, int ind1, int ind2, size_t sz)
{
	while (str1[ind1] && str2[ind2])
	{
		if (str1[ind1] != str2[ind2]) return str1[ind1] - str2[ind2];
		ind1++, ind2++;
	}
	return 0;
}
static inline char* itoa(int num, char* str, int base)
{
	int i = 0;
	bool isNegative = false;
	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}
	if (num < 0 && base == 10)
	{
		isNegative = true;
		num = -num;
	}
	while (num != 0)
	{
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}
	if (isNegative) str[i++] = '-';
	str[i] = '\0';
	strrev(str);
	return str;
}
static inline int vsprintf(char* str, const char* format, va_list args)
{
	int i = 0;
	int j = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 'd')
			{
				int num = va_arg(args, int);
				char* numstr = itoa(num, (char*)kalloc(100), 10);
				int k = 0;
				while (numstr[k] != '\0')
				{
					str[j++] = numstr[k++];
				}
				kfree(numstr);
			}
			else if (format[i] == 's')
			{
				char* str2 = va_arg(args, char*);
				int k = 0;
				while (str2[k] != '\0')
				{
					str[j++] = str2[k++];
				}
			}
			else if (format[i] == 'c')
			{
				char c = va_arg(args, int);
				str[j++] = c;
			}
			else if (format[i] == 'x')
			{
				int num = va_arg(args, int);
				char* numstr = itoa(num, (char*)kalloc(100), 16);
				int k = 0;
				while (numstr[k] != '\0')
				{
					str[j++] = numstr[k++];
				}
				kfree(numstr);
			}
			else if (format[i] == 'b')
			{
				int num = va_arg(args, int);
				char* numstr = itoa(num, (char*)kalloc(100), 2);
				int k = 0;
				while (numstr[k] != '\0')
				{
					str[j++] = numstr[k++];
				}
				kfree(numstr);
			}
			else if (format[i] == 'p')
			{
				void* ptr = va_arg(args, void*);
				char* numstr = itoa((uint32_t)ptr, (char*)kalloc(100), 16);
				int k = 0;
				while (numstr[k] != '\0')
				{
					str[j++] = numstr[k++];
				}
				kfree(numstr);
			}
			else if (format[i] == '%')
			{
				str[j++] = '%';
			}
		}
		else
		{
			str[j++] = format[i];
		}
		i++;
	}
	str[j] = '\0';
	return j;
}