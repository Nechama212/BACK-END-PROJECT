
#include "main.h"
/*API:
coding the operands to image code
gets the image code array, the operands as string, the head of lebal list
return the current index after coding the operands to image code*/
int coding_operands(word i_code_image [] , char operands [], lebal_node * head, int counter_lines)
{
	
	char * first;
	char * second;
	int index = IC;
	first = strtok(operands, ",\n");
    	second = strtok(NULL, "\n");
    		

    	
    		/*edge case*/
    		if(first != NULL && second != NULL && adress_mathod(first) == 3 && adress_mathod(second) == 3)
		{
			index++;
			i_code_image[index].binary_machine_code += register_code(first);
			/*shift the first register operand (4 bits)*/
			i_code_image[index].binary_machine_code = i_code_image[index].binary_machine_code << 4;
			
			i_code_image[index].binary_machine_code += register_code(second);
			/*shift the first register operand (2 bits)*/
			i_code_image[index].binary_machine_code = i_code_image[index].binary_machine_code << 2;
			
			/*absolute*/
			i_code_image[index].binary_machine_code += A;
			
			i_code_image[index].decimal_address = index + 100;
			return index;
		}
		

		

    	index = code_operand(i_code_image, first, FIRST, index,head, counter_lines);

    	index = code_operand(i_code_image, second, SECOND, index,head, counter_lines);

    	/*return the current index - place in array*/
    	return index;
}

/*code the given operand into the code image
gets the instruction code image, the name of operand, the place of operand(first/second), the index in the code image array, the head of lebal list
return the index of the coding(current index)*/
int code_operand(word i_code_image [],char operand [],operand_location place, int index, lebal_node * head, int counter_lines)
{
	
	char * lebal;
	char * number;

	if(operand == NULL)
		return index;

		if(adress_mathod(operand) == 0)
		{
			index++;
			/*operand is a number*/
			/*delete the HAHSTAG*/
			memmove(operand, operand+1, strlen(operand));
			
			i_code_image[index].binary_machine_code += convert_num(operand);

			/*shift the num operand (2 bits)*/
			i_code_image[index].binary_machine_code = i_code_image[index].binary_machine_code << 2;
			
			/*absolute*/
			i_code_image[index].binary_machine_code += A;
			
			/*decimal_address*/
			i_code_image[index].decimal_address = index + 100;

		}
		if(adress_mathod(operand) == 1)
		{
			/*operand is a lebal*/
			index++;
			if(code_lebal(head,operand, counter_lines) == -1)
			{
				return index;
			}
			
			i_code_image[index].binary_machine_code += code_lebal(head,operand, counter_lines);
			
			i_code_image[index].binary_machine_code = i_code_image[index].binary_machine_code << 2;
			/*if value of lebal = 0 -> external. else - relocatble*/
			if(code_lebal(head,operand, counter_lines) == 0)
				i_code_image[index].binary_machine_code += E;
			else
				i_code_image[index].binary_machine_code += R;
			
			/*decimal_address*/
			i_code_image[index].decimal_address = index + 100;
			strcpy(i_code_image[index].operands,operand);
		}
		if(adress_mathod(operand) == 2)
		{
			/*take only the lebal*/
			lebal = strtok(operand, ".");
			

			
			/*take only the number*/
			number = strtok(NULL, "\0");
			

			
			
			
			/*operand is a lebal*/
			index++;
			/*if not legal (-1), skip the unlegal lebal- we already raise error!*/
			if(code_lebal(head,lebal, counter_lines) != -1)
			{	
				
				/*check if from type of struct*/
				
				if(lebal_is_struct(head,lebal) == false)
					print_error(counter_lines,"the lebal is not a struct type!");
				/*code the lebal*/
			
				i_code_image[index].binary_machine_code += code_lebal(head,lebal, counter_lines);
				
				i_code_image[index].binary_machine_code = i_code_image[index].binary_machine_code << 2;
				
				/*if value of lebal = 0 -> external. else - relocatble*/
				if(code_lebal(head,lebal, counter_lines) == 0)
					i_code_image[index].binary_machine_code += E;
				else
					i_code_image[index].binary_machine_code += R;
				
				/*decimal_address*/
				i_code_image[index].decimal_address = index + 100;
				strcpy(i_code_image[index].operands,lebal);
			}
			index++;
			/*code the number*/
			i_code_image[index].binary_machine_code += atoi(number);
			
			/*shift the number (2 bits)*/
			i_code_image[index].binary_machine_code = i_code_image[index].binary_machine_code << 2;
			
			/*absolute*/
			i_code_image[index].binary_machine_code += A;
			
			/*decimal_address*/
			i_code_image[index].decimal_address = index + 100;
		}
		if(adress_mathod(operand) == 3)
		{
			index++;
			/*operand is a register*/
			i_code_image[index].binary_machine_code += register_code(operand);
			
			if(place == FIRST)
			{
				/*shift the register operand (6 bits)*/
				i_code_image[index].binary_machine_code = i_code_image[index].binary_machine_code << 6;
			}
			if(place == SECOND)
			{
				/*shift the register operand (4 bits)*/
				i_code_image[index].binary_machine_code = i_code_image[index].binary_machine_code << 2;
			}
			
			
			
			/*absolute*/
			i_code_image[index].binary_machine_code += A;
			
			/*decimal_address*/
			i_code_image[index].decimal_address = index + 100;
			
		}
		
		return index;
		
}
/*API:
return the code of a given lebal name
gets the lebal list head and the lebal name*/
int code_lebal(lebal_node * head, char lebal [], int counter_lines)
{
	int result;
	lebal_node* new_node = (lebal_node *)malloc(sizeof(lebal_node));
	if(new_node == NULL)
	{
		fprintf(stderr, "Error allocation faild!\n");
		exit(-1);
	}
	
	strcpy(new_node->name, lebal );
	
	if(search_lebal_list(head, new_node) == -1)
	{
		print_error(counter_lines, "lebal not defined");
		free(new_node);
		return -1;
	}
	result = search_lebal_list(head,new_node);
	free(new_node);
	return result;
}
/*API:
check if lebal is a struct, if so- return true, otherwise return false
gets the head of lebal list and the lebal name*/
boolean lebal_is_struct(lebal_node * head,char lebal [])
{
	lebal_node * current = head;
	while (current)
	{
		
		if((strcmp(current->name,lebal) == 0 && current->is_struct == true))
		{
			return true;
		}
		/*if external - we dont know the type so retrn true, it can be struct*/
		if((strcmp(current->name,lebal) == 0) && (current->value == 0))
			return true;
		current = current->next;
	}
	return false;
}
/*API:
update the lebal to be entry lebal
gets the lebal list head, the name of the lebal*/
void update_entry(lebal_node * lebal_list,char operands [], int counter_lines)
{
	boolean exist_entry = false;
	lebal_node * current = lebal_list;
	if(operands == NULL)
	{
		print_error(counter_lines, "missing lebal operand");
		return;
	}
	while (current)
	{
		if(strcmp(current->name,operands) == 0)
		{
			exist_entry = true;
			if(strcmp(current->type,"external")==0)
				print_error(counter_lines, "can not define the same lebal as external and as entry");
			current->entry = true;
		}
		current = current->next;
	}
	if(exist_entry == false)
		print_error( counter_lines, "entry without definition");
}
