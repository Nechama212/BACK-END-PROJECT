#include "main.h"
void second_pass(word i_code_image [],word d_code_image [], lebal_node ** lebal_list, FILE * file)
{
	char source_line [MAX_LEN_LINE];
	char line [MAX_LEN_LINE];
	char * token;
	char white_space [12] = " \n\r\t\v\f";
	char * operands;
	int counter_lines = 0;
	/*1. in algorithm*/
	IC = 0;
	
	
	/*2. in algorithm*/
	while (fgets(source_line, sizeof(source_line), file))
	{
		counter_lines++;
		
		/*if empty or comment (;) -ignore*/
   		if(source_line == NULL || source_line[0] == NOTE || source_line[0] == '\n')
   			continue;
   		
   		arrange_line(source_line,line);
   		if(line[0] == EOS)
   			continue;

		
   		/* get the first token - always by white space */
   		token = strtok(line, white_space);

   		/*3. in algorithm*/
   		if(is_lebal(token) == true)
   		{
   			/*skip - read the operation token*/
   			token = strtok(NULL, white_space);
   		
   		}
   		/*4. in algorithm*/
   		/*if the operation is .data/.string/.struct or .extern*/
   		if(is_directive_data(token) != -1 || strcmp(token, outside[0]) ==0)
   		{
   			continue;
   		}
   		/*5. in algorithm*/
   		/*if the operation is .entry*/
   		if(strcmp(token, outside[1]) ==0)
   		{
   			/*6. in algorithm*/
   			/*take the rest of the string*/
   			operands = strtok(NULL,EOL);
   			update_entry(* lebal_list,operands,counter_lines);
 
   			continue;
   		}
   		/*7.8. in algorithm*/
   		/*take the rest of the string*/
   		operands = strtok(NULL,EOL);

   		IC = coding_operands(i_code_image, operands, *lebal_list,counter_lines );
   		
   		IC++;
   			
	}
	/*10. in algorithm*/
   	/*if we have errors - stop*/
   	/*11. in algorithm*/
   	/*make the output files*/
}
