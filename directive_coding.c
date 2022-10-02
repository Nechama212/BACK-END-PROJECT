#include "main.h"
void coding_data(word d_code_image[],char operands[], int counter_line)
{
	int num_list[80] = { 0 };
	int i;
	int number = 0;
	char * value;
	int amount_number = 0;
	
	if (strcmp(d_code_image[DC].operation, ".data") == 0)
	{
		   			   			
		if (operands == NULL) /*no numbers*/
		{
			print_error(counter_line, "missing numbers arguments");
			return;
		}
		if (operands[0] == ',')
		{
			print_error(counter_line, "Leading comma!");
			return;
		}
		if (operands[strlen(operands) - 1] == ',')
		{
			print_error(counter_line, "comma in the end of command");
			return;
		}

		if ((amount_number = make_numbers(operands, num_list)) != -1 )
		{
			for (i = 0; i < amount_number; i++)
			{
				d_code_image[DC].binary_machine_code = num_list[i];
				d_code_image[DC].decimal_address = DC +100;
				DC++;
			}
		}
		else
		{
			print_error(counter_line, "Invalid number has provided!");
			return;
		}



	}
	else if (strcmp(d_code_image[DC].operation, ".string")==0)
	{

		if (operands == NULL) /*no string*/
		{
			print_error(counter_line, "missing string argument");
			return;
		}
		if (is_string(d_code_image[DC].operands) == true)
		{
			convert_string(operands);
			
			for (i=0; i <= strlen(operands); i++)
			{
				
				d_code_image[DC].binary_machine_code = operands[i];
				d_code_image[DC].decimal_address = DC +100;
				DC++;
			}
			/*DC--; if we want the dc will point to the current*/
		}
		else
		{
			print_error(counter_line, "Invalid string has provided!");
			return;
		}

	}
	else if (strcmp(d_code_image[DC].operation, ".struct") == 0)
	{
		if (operands == NULL) /*no operands in struct*/
		{
			print_error(counter_line, "missing struct arguments");
			return;
		}
				
		if (operands[0] == ',')
		{
			print_error(counter_line, "Leading comma");
			return;
		}
		if (operands[strlen(operands) - 1] == ',')
		{
			print_error(counter_line, "comma in the end of command");
			return;
		}
		value = strtok(operands, ",");/* hold the first command-number*/
				
		if (is_num_data(value) == false)
		{
			print_error(counter_line, "Invalid number has provided!");
			return;
		}
		else
		{
			number = convert_num(value);/*Converts the string-number to real number*/
			d_code_image[DC].binary_machine_code = number;
			d_code_image[DC].decimal_address = DC +100;
			DC++;
		}

		value = strtok(NULL, "\n"); /*pointer to the rest ot the string*/
		if (is_string(value) == true)
		{
			convert_string(value);
					
			for (i = 0; i <= strlen(value); i++)
			{
				d_code_image[DC].binary_machine_code = value[i];
				d_code_image[DC].decimal_address = DC +100;
				DC++;
			}
			/*DC--; if we want the dc will point to the current*/
					
		}
		else
		{
			print_error(counter_line, "Invalid string has provided!");
			return;
		}
	}

}

int make_numbers(char str [], int num_list [])
{
	int i = 0;
	char* token = NULL;
	int number = 0;

	token = strtok(str, ",");
	while (token != NULL)
	{
		
		if (is_num_data(token) == false)
		{
			return -1;
		}

		number = convert_num(token);
			
		num_list[i] = number;
		i++;

		token = strtok(NULL, ",");
	}
	return i;
}




void coding_extern(lebal_node ** head, char operand [], int counter_line)
{
    char colon = COLON;
    
    if(operand == NULL)
    {
    	print_error(counter_line, "missing lebal operand");
        return;
    }
       				
    strncat(operand, &colon, 1);
    if (is_lebal(operand) == false)
    {
        print_error(counter_line, "Invalid lebal has provided!");
        return;
    }
    else
    {
    	
        operand[strlen(operand)-1] = '\0';
        /*add the lebal with type external and with NO value*/

        add_lebal_list(head, operand, "external", 0, counter_line);
        
    }
}

/*API
return true if the operand is a leagal NUMBER of data type
*/
boolean is_num_data(char num[])
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
	if(number > MAX_DATA_NUM || number < MIN_DATA_NUM)
		return false;
	return true;
}


		
