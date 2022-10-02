#ifndef CONSTANT
#define CONSTANT

#define LINESIZE (82)
#define MIN_FILE (2)
#define FILE_EXTENSION_SIZE (11)
#define MACRO_NAME_LENGTH (30)
/*It can be assumed that the macro content is no bigger than 10 lines
Also, each line is no bigger than 80
Therefore 800 character in macro content */
#define MACRO_CONTENT_LENGTH (800)



/*the max and min value of integer number in 10 bits*/
#define MAX_DATA_NUM 511
#define MIN_DATA_NUM -512

/*the max and min value of integer number in 8 bits*/
#define MAX_CODE_NUM 127
#define MIN_CODE_NUM -128

/*length of outside data names is 8*/
#define OUTSIDE_NAME 8

/*amount of outside data names is 2*/
#define AMOUNT_OUTSIDE 2	
	
/*max length of thirty_two_address is 2*/
#define MAX_LEN_32_ADD 3

/*max length of line is 80*/
#define MAX_LEN_LINE 81

/*max length of code image is 156*/
#define MAX_LEN_CODE_IMAGE 156

/*max length of type name is 8*/
#define MAX_LEN_TYPE_NAME 9


	


/*max length of lebal name is 30, with the colon - 31*/
#define MAX_LEN_LEBAL 31

/*length of opcode name is 3*/
#define NAME_LENGTH 4 

/*there are 16 opcodes*/
#define AMOUNT_OPCODE 16 

/*there ara 4 adresses*/
#define AMOUNT_ADRESS 4

/*length of largest adress name is 23*/
#define ADRESS_NAME 24

/*amount of encoding_type is 3*/
#define AMOUNT_ENCODE_TYPE 3

/*length of encodeing type name is 1*/
#define ENCODE_TYPE_NAME 2

/*amount of registers is 8*/
#define AMOUNT_REG 8

/*length of register name is 2*/
#define REG_NAME 3

/*length of directive name is 7*/
#define DIRECT_NAME 8

/*amount of directives is 3*/
#define AMOUNT_DIRECT 3

#define COLON ':'
#define MINUS '-'
#define PLUS '+'
#define QUOTATION '"'
#define HASHTAG '#'
#define DOT '.'
#define SPACE ' '
#define NOTE ';'
#define TAB '\t'
/*end of string*/
#define EOS '\0'

#define EOL "\n"
#define comma ","

#define STRUCT ".struct"
typedef enum {false, true} boolean;

typedef enum{A,E,R} ARE;

typedef enum{FIRST,SECOND} operand_location;

typedef struct macro_node {
	char* data;
	char* name;
	struct macro_node* next;
}macro_node;

typedef struct
	{
		char lebal [MAX_LEN_LEBAL];
		int decimal_address;
		char thirty_two_address [MAX_LEN_32_ADD];
		char operation [DIRECT_NAME];
		char operands [MAX_LEN_LINE];
		int binary_machine_code;
	}word;
	
typedef struct lebal_node
	{
		char name [MAX_LEN_LEBAL];
		int value;
		char type [MAX_LEN_TYPE_NAME];
		boolean entry;
		boolean is_struct;
		struct lebal_node * next;
		
	}lebal_node;



#endif
