#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "adr_method_fun.h"
#include "first_pass.h"
#include "lebal_list_fun.h"
#include "operand_fun.h"
#include "constant.h"
#include "first_pass_fun.h"
#include "directive_coding.h"
#include "general_func.h"
#include "second_pass.h"
#include "second_pass_fun.h"
#include "third_pass.h"
#include "pre_assembler.h"
int IC;
int DC;

int file_number;
boolean is_error;

/*opcode names
the code is the index of each value*/
extern char opcode [][NAME_LENGTH];

/*adress of destination/source operand
the code is the index of each value*/
extern char address [][ADRESS_NAME];

/*encoding type ARE
the code is the index of each value*/

extern char encoding_type [][ENCODE_TYPE_NAME];

/*registers
the code is the index of each value*/
extern char registers [][REG_NAME];

/*directive*/

extern char directive [][DIRECT_NAME];

/*outside data names*/
extern char outside [][OUTSIDE_NAME];

