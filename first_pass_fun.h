#include "constant.h"

/*API:
coding the first word of instruction sentence to the image code
gets the image code, the operands of instruction sentence
return L - the number of additional words*/
int coding_code(word [], char [],int );

/*API:
calculate L- additional words for two operands
gets the first operand and the second operand
return L- the addditional words*/	
int additional_words(char [],char []);

/*API:
return the amount of operands that should be according to operation name
gets the operation name*/
int find_amount_operand(char []);

/*API:
arange the given line, without white spaces, leave one space in a place of spaces
in a comma place clean all spaces before and after the comma, dont treat the edges of the line
gets the line that need to arrange*/
void remove_white_spaces(char* );

/*API:
arange the given line, without white spaces, in the edges
gets the line that need to arrange its edges*/
void remove_white_space_edges(char* );

/*API:
arange the given line, without white spaces, leave one space in a place of spaces
in a comma place clean all spaces before and after the comma
gets the line that need to arrange*/
void arrange_line(char* , char* );

/*API:
check if there is two consecutive commas, if so - return true, otherwise return false
gets the line*/
boolean two_commas(char [], int );
