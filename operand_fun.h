#include "constant.h"
/*API
return the CODE of a given opcode name, if not exist return -1
*/
int opcode_code(char []);

/*API
return true if the operand is a leagal LEBAL
*/
boolean is_lebal(char []);

/*API
convert the LEBAL to legal and clean lebal, when given CORRECT lebal
change the given lebal! 
(assume the input is correct)
*/

void convert_lebal(char []);

/*API
return true if the word is a reserved word
*/
boolean is_reserved_word(char []);

/*API
return true if the operand is a leagal NUMBER
*/
boolean is_num(char []);

/*API
return int for legal number, change the given num!
(assume the input is correct)
*/
int convert_num(char []);

/*API
return the code of register if the operand is a leagal REGISTER, else return -1.
*/
int register_code(char []);

/*API
return true if the operand is a leagal STRING
*/
boolean is_string(char []);

/*API
convert string to a leagal and clean STRING, change the given str!
(assume the input is correct)
*/
void convert_string(char []);

/*API
return the INDEX of a given directive data name, if not a directive data name return -1
*/
int is_directive_data(char []);

/*API
return the INDEX of a given outside data name, if not a outside data name return -1
*/
int is_outside_data(char []);

