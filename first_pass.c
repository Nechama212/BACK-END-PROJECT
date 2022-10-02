#include "main.h"
void first_pass(word i_code_image [],word d_code_image [], lebal_node ** lebal_list, FILE * file)
{
	char source_line [MAX_LEN_LINE]= {0};
	char line [MAX_LEN_LINE] = {0};
	char white_space [12] = " \n\r\t\v\f";
   	char * token = NULL;
   	boolean lebal_flag = false;
   	int counter_lines = 0;
   	int L = 0;
   	char curr_lebal[MAX_LEN_LEBAL] = {0};
   	char * operands = NULL;
   	IC = 0;
   	DC = 0;
   	while (fgets(source_line, sizeof(source_line)-1, file))
	{
		if(IC == MAX_LEN_CODE_IMAGE || DC ==MAX_LEN_CODE_IMAGE)
		{
			print_error(counter_lines,"the code image bigger than max length of code image!");
			return;
		}	
		counter_lines++;
		/*2. in algorithm*/
		
		
   		/*if empty or comment (;) -ignore*/
   		if(source_line == NULL || source_line[0] == NOTE || source_line[0] == '\n')
   			continue;
   		
   		arrange_line(source_line,line);
   		
   		if(line[0] == EOS)
   			continue;
		
   		
		if(two_commas(line, counter_lines) == true)
			continue;
   		
   		
   		/* get the first token - always by white space*/
   		token = strtok(line, white_space);
   		
   		
   		/*3. in algorithm*/
   		if(is_lebal(token) == true)
   		{
   			
   			convert_lebal(token);
   			
   			/*4. in algorithm*/
   			strcpy(curr_lebal,token);
   			lebal_flag = true;
   			/*read the operation token*/
   			token = strtok(NULL, white_space);
   			
   			if(token == NULL)
   			{
   				print_error(counter_lines,"lebal is empty");
   				continue;
   			}	

   		}
   		/*Checks if it's supposed to be a label and it's not correct*/
   		
   		else if(token[strlen(token)-1] == COLON)
   		{
   			print_error(counter_lines,"lebal is not legal");
   			continue;
   		}
   			
   		/*5. in algorithm*/
   		if(is_directive_data(token) != -1)
   		{
   			   			   			
   			/*enter DC + 100 to the decimal adress*/
   			d_code_image[DC].decimal_address = DC + 100;

   			/*6. in algorithm*/
   			if(lebal_flag == true)
   			{
   				
   			
   				/*enter the lebal to the lebal table*/
   				add_lebal_list(lebal_list ,curr_lebal, "data", DC+100, counter_lines);
   				/*now the new lebal is in the head of the list*/
   				if(strcmp(token, STRUCT) == 0)
   					(*lebal_list)->is_struct = true;
   					
   				/*enter the lebal name to d_code_image*/
   				strcpy(d_code_image[DC].lebal, curr_lebal);
   			}
   			/*7. in algorithm*/

   			strcpy(d_code_image[DC].operation, token);

   			/*take the rest of the string*/
   			operands = strtok(NULL,EOL);

   			if(operands != NULL)
   				strcpy(d_code_image[DC].operands,operands);

   			/*nechame function */
   			coding_data(d_code_image, operands, counter_lines);
   		}
   		
   		/*8. in algorithm*/
   		else if (is_outside_data(token) != -1)
   		{
   			
   			/*if was a lebal - skip*/
   			
   			/*9. in algorithm*/
   			/*if it is .extern*/
   			if(is_outside_data(token) == 0)
   			{
   				
   				/*take the rest of the string*/
   				operands = strtok(NULL,EOL);
   				   				
   				coding_extern(lebal_list, operands, counter_lines);

   			}

   		}
   		
   		/*10. in algorithm*/
   		else
   		{
   			
   			/*enter IC + 100 to the decimal adress*/
   			i_code_image[IC].decimal_address = IC + 100;
   			
   			
   			/*11. in algorithm*/
   			if(lebal_flag == true)
   			{
   			
   				/*enter the lebal to the lebal table*/
   				add_lebal_list(lebal_list ,curr_lebal, "code", IC + 100, counter_lines);
   				
   				
   				/*enter the lebal name to i_code_image*/
   				strcpy(i_code_image[IC].lebal, curr_lebal);
   			}
   			/*12. in algorithm*/
   			if(opcode_code(token) == -1)
   			{
   				print_error(counter_lines, "unlegal instruction name");
				continue;
   			}
   			
   			strcpy(i_code_image[IC].operation , token);

   			/*take the rest of the string*/

   			operands = strtok(NULL,EOL);
   			
   			if(operands != NULL)
				strcpy(i_code_image[IC].operands, operands);
				
			
   			
   			/*13. in algorithm*/
   			L = coding_code(i_code_image, operands, counter_lines);
   			   			
   			/*14. in algorithm*/
   			IC = IC +L;
   			IC++;
   		}
   		
   		lebal_flag = false;
   		
   	}
   	/*16. in algorithm*/
   	/*if we have errors - stop*/
   	/*17. in algorithm*/
   	/*update the data symbols in the symbol table. (add the IC to the current number) */
   	update_data_symbols(*lebal_list);
}
