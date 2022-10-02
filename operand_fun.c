#include "main.h"

/*API
return the CODE of a given opcode name, if not exist return -1
*/
int opcode_code(char opcode_name[])
{
	int i = 0;
	for(i = 0; i< AMOUNT_OPCODE; i++)
	{
		if(strcmp(opcode[i], opcode_name) == 0)
			return i;
	}
	return -1;
}
/*API
return the INDEX of a given outside data name, if not a outside data name return -1
*/
int is_outside_data(char outside_data [])
{
	int i = 0;
	for(i = 0; i< AMOUNT_OUTSIDE; i++)
	{
		if(strcmp(outside[i], outside_data) == 0)
			return i;
	}
	return -1;
	
}
/*API
return the INDEX of a given directive data name, if not a directive data name return -1
*/
int is_directive_data(char directive_name [])
{
	int i = 0;
	for(i = 0; i< AMOUNT_DIRECT; i++)
	{
		if(strcmp(directive[i], directive_name) == 0)
			return i;
	}
	return -1;
}

/*API
return the code of REGISTER if the operand is a leagal REGISTER, else return -1.
*/
int register_code(char register_name [])
{
	int i = 0;
	for(i = 0; i< AMOUNT_REG; i++)
	{
		if(strcmp(registers[i], register_name) == 0)
			return i;
	}
	
	return -1;
}


/*API
return true if the operand is a leagal LEBAL
*/
boolean is_lebal(char given_lebal[])
{
	int i = 0;
	char * lebal = (char *)malloc((strlen(given_lebal) + 1) * sizeof(char));
	if(lebal == NULL)
	{
		fprintf(stderr, "Error allocation faild!\n");
		exit(-1);
	}
	strcpy(lebal, given_lebal);
	
	
	if(strlen(lebal) > MAX_LEN_LEBAL)
	{
		free(lebal);
		return false;
	}
	
	/*first char has to be alpha letter*/
	if(isalpha(lebal[0]) == 0)
	{
		free(lebal);
		return false;
	}
	if(lebal[strlen(lebal) - 1] != COLON)
	{
		free(lebal);
		return false;	
	}	
	for(i = 0; i < strlen(lebal); i++)
	{
		
		if(lebal[i] != COLON)
		{

			/*if the char is not alpha and not digit, false*/
			if(isalpha(lebal[i]) == 0 && isdigit(lebal[i]) == 0)
			{		
				free(lebal);
				return false;
			}
		}
		/*if the char is COLON and it is not the last char - return false*/
		else if(i != strlen(lebal) - 1)
		{
			free(lebal);
			return false;	
		}	
	}
	/*delete the colon*/
	lebal[strlen(lebal)-1] = '\0';
	/*the name is not a reserved word*/
	if(is_reserved_word(lebal) == true)
	{
		free(lebal);
		return false;
	}
	free(lebal);
	return true;
	
}

/*API
convert the LEBAL to legal and clen lebal, when given CORRECT lebal
change the given lebal! 
(assume the input is correct)
*/

void convert_lebal(char lebal [])
{
	/*to convert the string to a lebal, need to delete only the COLON(last char)*/
	lebal[strlen(lebal)-1] = '\0';
}

/*API
return true if the word is a reserved word
*/
boolean is_reserved_word(char word[])
{
	int i = 0;
	for(i = 0; i< AMOUNT_OPCODE; i++)
	{
		if(strcmp(opcode[i], word) == 0)
			return true;
	}
	for(i = 0; i< AMOUNT_REG; i++)
	{
		if(strcmp(registers[i], word) == 0)
			return true;
	}
	for(i = 0; i< AMOUNT_DIRECT; i++)
	{
		if(strcmp(directive[i], word) == 0)
			return true;
	}
	for(i = 0; i< AMOUNT_OUTSIDE; i++)
	{
		if(strcmp(outside[i], word) == 0)
			return true;
	}
	if(strcmp("macro", word) == 0)
			return true;
	if(strcmp("endmacro", word) == 0)
			return true;
	return false;
}

/*API
return true if the operand is a leagal NUMBER
*/
boolean is_num(char num[])
{
	int i =0;
	int number;
	/*check the optional sign +/-*/
	if(num[0] != MINUS && num[0] != PLUS && isdigit(num[0]) == 0)
		return false;
	/*begin in second letter*/
	for(i = 1; i< strlen(num); i++)
	{
		if(isdigit(num[i]) == 0)
			return false;
	}
	number = convert_num(num);
	if(number > MAX_CODE_NUM || number < MIN_CODE_NUM)
		return false;
	return true;
}

/*API
return int for legal number, change the given num!
(assume the input is correct)
*/
int convert_num(char num [])
{
	if(num[0] == PLUS)
		memmove(num, num+1, strlen(num));
	return atoi(num);
}

/*API
return true if the operand is a leagal STRING
*/
boolean is_string( char str [])
{
	int i = 0;
	if(strlen(str) == 1)
		return false;
	if(str[0] != QUOTATION || str[strlen(str) -1] != QUOTATION)
		return false;
	/*loop without the edges*/
	for(i = 1; i< strlen(str)-1; i++)
	{
		if(isprint(str[i]) == 0)
			return false;
	}
	return true;
}
/*API
convert string to a leagal and clean STRING, change the given str!
(assume the input is correct)
*/
void convert_string(char str [])
{
	/*delete the first QUOTATION*/
	memmove(str, str+1, strlen(str));
	/*delete the last QUOTATION*/
	str[strlen(str)-1] = '\0';
	
}

