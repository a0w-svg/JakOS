#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include "../include/stdio.h"
#include "../include/string.h"
#include "../../drivers/include/screen.h"
#include <stdint.h>
#include <stddef.h>

static bool print(const char* data, size_t length, uint8_t Color) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i], Color) == 0)
			return false;
	return true;
}

int printf(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);
	uint8_t color;
	int c;
	char buf[20];
	int written = 0;
	while ((c = *format) != '\0') {
		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount)
				// TODO: Set errno to EOVERFLOW.
				return -1;
			if (!print(format, amount, color))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format++;
		
		if (c == 'c') {
			format++;
			char ch = (char) va_arg(parameters, int);
			if (!maxrem)
				// TODO: Set errno to EOVERFLOW.
				return -1;
			if (!print(&ch, sizeof(ch), color))
				return -1;
			written++;
		} 
		else if (*format == 's') {
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len)
				// TODO: Set errno to EOVERFLOW.
				return -1;
			if (!print(str, len, color))
				return -1;
			written += len;
		} 
		else if(*format == 'x')
		{
			format++;
			int a = va_arg(parameters, int);
			if(!maxrem)
				// TODO: Set errno to EOVERFLOW
				return -1;
			int_to_ascii(buf, 'x', a);
			print("0x", 2, color);
			size_t len = strlen(buf);
			if(!print(buf, len, color))
				return -1;
			written =+ len+2;
		}
		else if(*format == 'd')
		{
			format++;
			int a = va_arg(parameters, int);
			if(!maxrem)
				// TODO: Set errno to EOVERFLOW
				return -1;
			int_to_ascii(buf, 'd', a);
			size_t len = strlen(buf);
			if(!print(buf, len, color))
				return -1;
			written =+ len;
		}
		else if(*format == 'z')
		{
			format++;
			color = va_arg(parameters, int);
		}
		else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len)
				// TODO: Set errno to EOVERFLOW.
				return -1;
			if (!print(format, len, color))
				return -1;
			written += len;
			format += len;
		}
	}

	va_end(parameters);
	return written;
}
