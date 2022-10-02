#include "main.h"
char * conv_32base(int val)
{
	static char conv[3] = { 0 };
	char base[] = "!@#$%^&*<>abcdefghijklmnopqrstuv\0";
	int first, second;
	first = val & 31; /*First 5 bits*/
	second = ((val & ~31) >> 5) & 31; /*second 5 bits*/

	conv[0] = base[second];
	conv[1] = base[first];
	return conv;
}
void print_error(int counter_line, char error [])
{
	fprintf(stderr, "file number: %d, line number: %d - %s\n", file_number, counter_line, error);
	is_error = true;
}
