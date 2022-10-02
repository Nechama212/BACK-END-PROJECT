#include "constant.h"
void coding_data(word [], char [], int );

int make_numbers(char [] , int [] );
/*API
coding the extern command
gets the lebal list head, the operands of the command*/
void coding_extern(lebal_node ** , char [], int);

/*API
return true if the operand is a leagal NUMBER of data type
*/
boolean is_num_data(char []);
