#include "constant.h"
/*API:
coding the operands to image code
gets the image code array, the operands as string, the head of lebal list
return the current index after coding the operands to image code*/
int coding_operands(word [] , char [], lebal_node *,  int );

/*code the given operand into the code image
gets the instruction code image, the name of operand, the place of operand(first/second), the index in the code image array, the head of lebal list
return the index of the coding(current index)*/
int code_operand(word [],char [],operand_location, int, lebal_node * , int );

/*API:
return the code of a given lebal name
gets the lebal list head and the lebal name*/
int code_lebal(lebal_node *, char [],  int);

/*API:
update the lebal to be entry lebal
gets the lebal list head, the name of the lebal*/
void update_entry(lebal_node * ,char  [],int );
/*API:
check if lebal is a struct, if so- return true, otherwise return false
gets the head of lebal list and the lebal name*/
boolean lebal_is_struct(lebal_node * ,char []);
