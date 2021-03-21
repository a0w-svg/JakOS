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
	// declare a va_list (list arguments)
	va_list parameters;
	// creates the va_list with the total length stored in the format variable
	va_start(parameters, format);
	uint8_t color = 0;
	// buffer used to convert numbers to strings.
	char buf[20];
	// The Variable written stored number of characters written out.
	int written = 0;
	while ( *format != '\0') {
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
			// add the amount variable to the format variable
			format += amount;
			// add the amount variable to the written variable.
			written += amount;
			// continue executing instructions in the loop
			continue;
		}

		const char* format_begun_at = format++;
		// displays the character from the va_list argument type int
		if (*format == 'c') {
			// increment the format variable by 1.
			format++;
			// get a char value from the va_arg type int argument
			char ch = (char) va_arg(parameters, int);
			// if maxrem is never equal 0
			if (!maxrem)
				// TODO: Set errno to EOVERFLOW.
				return -1;
			// print a character on the screen with color (background + foreground) form color variable
			if (!print(&ch, sizeof(ch), color))
				return -1;
			// if everything went well, increment the written variable by 1
			written++;
		} 
		// displays the string from the va_list argument type const char*
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
		// displays the hexadecimal number from the va_list argument type int
		else if(*format == 'x')
		{
			format++;
			int a = va_arg(parameters, int);
			if(!maxrem)
				// TODO: Set errno to EOVERFLOW
				return -1;
			//convert
			int_to_ascii(buf, 'x', a);
			print("0x", 2, color);
			size_t len = strlen(buf);
			if(!print(buf, len, color))
				return -1;
			written =+ len+2;
		}
		// displays the decimal number from the va_list argument type int
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
			written += len;
		}
		// set color 
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
