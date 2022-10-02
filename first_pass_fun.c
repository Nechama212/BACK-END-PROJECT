#include "main.h"
/*IC is global*/
/*API:
coding the first word of instruction sentence to the image code
gets the image code, the operands of instruction sentence
return L - the number of additional words*/
int coding_code(word i_code_image [], char operands [],  int counter_line)
{

	char * first;
	char * second;
	char * temp;
	
	
	int amount_operand;	
	
	
	
	/*enter the first 4 bits - the instruction value*/
	i_code_image[IC].binary_machine_code = opcode_code(i_code_image[IC].operation);

	/*shift 2 bits - to put the instruction value in the left 4 bits*/
	i_code_image[IC].binary_machine_code = i_code_image[IC].binary_machine_code << 2;

	if(operands != NULL && operands[strlen(operands)-1] == ',' )
	{
		print_error( counter_line, "comma in end of line");
        	return 0;
	}

	first = strtok(operands, ",\n");
    	second = strtok(NULL, EOL);
    	

    	
    	amount_operand = find_amount_operand(i_code_image[IC].operation);
    	

    	
	if(amount_operand == 2)
	{
		if(first == NULL)
		{
			print_error( counter_line, "missing operands");
        		return 0;
		}
		if(second == NULL)
		{
			print_error( counter_line, "missing comma");
        		return 0;
		}	
		temp = (char *)malloc(strlen(second));
		if(temp == NULL)
		{
			fprintf(stderr, "Error allocation faild!\n");
			exit(-1);
		}
    		temp = strcpy(temp, second);
    		
    		if(strcmp(second, strtok(temp, comma)) != 0)
    		{
    			print_error( counter_line, "There are more arguments than allowed");
        		return 0;
    		}
		
		free (temp);
		
		/*FIRST*/
			
		if(adress_mathod(first) == -1)
		{
			print_error( counter_line, "unlegal operand");
        		return 0;
		}
			
			
		/*operation is 6(lea) legal adress method for first is 1,2*/
		if(i_code_image[IC].operation == opcode[6] && (adress_mathod(first) == 0 || adress_mathod(first) == 3))
		{
			print_error( counter_line, "unlegal operand- unlegal adress method");
        		return 0;
		}
		
		
		i_code_image[IC].binary_machine_code += adress_mathod(first);
		

		/*shift the source operand (2 bits)*/
		i_code_image[IC].binary_machine_code = i_code_image[IC].binary_machine_code << 2;
		
		/*SECOND*/
    		
    		if(adress_mathod(second) == -1)
		{
			print_error( counter_line, "unlegal operand");
        		return 0;
		}	
		/*if the second is not cmp and the address method is 0-error*/
		if((strcmp(i_code_image[IC].operation, opcode[1]) != 0) && adress_mathod(second) == 0)
		{
			print_error( counter_line, "unlegal operand - unlegal adress method");
        		return 0;
		}	
		
		i_code_image[IC].binary_machine_code += adress_mathod(second);
		

		
		/*shift the destination operand (2 bits)*/
		i_code_image[IC].binary_machine_code = i_code_image[IC].binary_machine_code << 2;
		
		/*return L*/
		return additional_words(first,second);
	}
	
	if(amount_operand == 1)
	{
		if(first == NULL)
		{
			print_error( counter_line, "missing operands");
        		return 0;
		}
		if(second != NULL)
		{
			print_error( counter_line, "There are more arguments than allowed");
        		return 0;
		}
		if(adress_mathod(first) == -1)
		{
			print_error( counter_line, "unlegal operand");
			return 0;
		}
				
		/*if the operation is prn - the adress method can be 0,1,2,3*/	
		
		if(strcmp(i_code_image[IC].operation,opcode[12]) != 0 && adress_mathod(first) == 0)
		{
			print_error( counter_line, "unlegal operand - unlegal adress method");
			return 0;
		}
		
		/*shift the source operand (2 bits)*/
		i_code_image[IC].binary_machine_code = i_code_image[IC].binary_machine_code << 2;
		i_code_image[IC].binary_machine_code += adress_mathod(first);
		
		/*shift the destination operand (2 bits)*/
		i_code_image[IC].binary_machine_code = i_code_image[IC].binary_machine_code << 2;
		
		/*return L*/
		if(adress_mathod(first) == 2)
			return 2;
		else
			return 1;
	}
	if(amount_operand == 0)
	{
		if(first != NULL)
		{
			print_error( counter_line, "There are more arguments than allowed");
		}
		
		/*shift the source operand (2 bits)*/
		i_code_image[IC].binary_machine_code = i_code_image[IC].binary_machine_code << 2;
		/*shift the destination operand (2 bits)*/
		i_code_image[IC].binary_machine_code = i_code_image[IC].binary_machine_code << 2;	
		/*return L*/
		return 0;
	}
	return 0;
	
}

/*API:
calculate L- additional words for two operands
gets the first operand and the second operand
return L- the addditional words*/	
int additional_words(char first [],char second [])
{
	int L = 0;
	if(adress_mathod(first) == 3 && adress_mathod(second)==3)
			return 1;
	if(adress_mathod(first) == 2)
		L+= 2;
	else
		L+= 1;
	if(adress_mathod(second) == 2)
		L+= 2;
	else
		L+= 1;
	return L;
}
/*API:
return the amount of operands that should be according to operation name
gets the operation name*/
int find_amount_operand(char operation [])
{
	int i;
	for(i = 0; i< AMOUNT_OPCODE; i++)
	{
		if(strcmp(operation, opcode[i]) == 0)
		{
			if((i >= 0 && i <= 3) || i == 6)
				return 2;
			if(i==4 || i== 5 ||(i >=7 && i<=13))
				return 1;
			if(i== 14 || i==15)
				return 0;
			break;
		}		
		
	}
	return -1;
}
/*API:
arange the given line, without white spaces, leave one space in a place of spaces
in a comma place clean all spaces before and after the comma
gets the line that need to arrange*/
void remove_white_spaces(char* line)
{
	if (line == NULL)
	{
		return;
	}

	/* When string is empty */
	if (line[0] == '\0')
		return;

	/* if the adjacent characters are same */
	if (((line[0] == ' ') && (line[1] == ' ')) ||
		((line[0] == '\t') && (line[1] == '\t')) ||
		((line[0] == ' ') && (line[1] == '\t')) ||
		((line[0] == '\t') && (line[1] == ' ')) ||
		((line[0] == ' ') && (line[1] == ',')) ||
		((line[0] == '\t') && (line[1] == ',')) ||
		((line[0] == ',') && (line[1] == ' ')) ||
		((line[0] == ',') && (line[1] == '\t')))
	{

		int i = 0;
		if (((line[0] == ',') && (line[1] == ' ')) ||
			((line[0] == ',') && (line[1] == '\t')))
		{
			i = 1;
		}

		/* Shift character by one to left */
		while (line[i] != '\0') {
			line[i] = line[i + 1];
			i++;
		}

		/* Check on Updated String line */
		remove_white_spaces(line);
	}

	/* If the adjacent characters are not same
	   Check from line+1 string address */
	remove_white_spaces(line + 1);
}

/*API:
arange the given line, without white spaces, in the edges
gets the line that need to arrange its edges*/
void remove_white_space_edges(char* str_line)
{
	char* temp = NULL;
	char* end = NULL;
	char* temp_str = str_line;
	/* Trim leading space */
	while ((*temp_str == ' ') || (*temp_str == '\t'))
	{
		temp_str++;
	}

	/* All spaces */
	if (*temp_str == '\0')
	{
		str_line[0] = '\0';
		return;
	}

	/* Trim trailing space */
	/*start before the '\n' character*/
	end = temp_str + strlen(temp_str) - 2;
	while ((end > temp_str) && ((*end == ' ') || (*end == '\t')))
	{
		end--;
	}

	/* Write new null terminator character */
	end[1] = '\0';

	temp = (char*)malloc(strlen(str_line) + 1);
	if (temp == NULL)
	{
		fprintf(stderr, "No free space!");
		exit(-1);
	}

	strcpy(temp, temp_str);
	strcpy(str_line, temp);

	free(temp);
}

/*API:
arange the given line, without white spaces, leave one space in a place of spaces
in a comma place clean all spaces before and after the comma
gets the line that need to arrange*/
void arrange_line(char* str_line, char* formatted_str_line)
{
	if ((str_line == NULL) || (formatted_str_line == NULL))
	{
		return;
	}

	strcpy(formatted_str_line, str_line);
	remove_white_space_edges(formatted_str_line);

	if (strlen(formatted_str_line) > 1)
	{
		remove_white_spaces(formatted_str_line);
	}

	if (formatted_str_line[strlen(formatted_str_line) - 1] == '\n')
	{
		formatted_str_line[strlen(formatted_str_line) - 1] = '\0';
	}

}
/*API:
check if there is two consecutive commas, if so - return true, otherwise return false
gets the line*/
boolean two_commas(char line [], int counter_lines)
{
	int i = 0;
	for(i = 0; i < strlen(line)-1; i++)
	{
		if(line[i] == ',' && line[i+1] == ',')
		{
			print_error(counter_lines,"There are two consecutive commas");
			return true;
		}
	}
	return false;
}
