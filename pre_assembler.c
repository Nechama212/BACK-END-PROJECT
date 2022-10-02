#include "main.h"
/*API:
The function do the macro retirement
gets a pointer to input file, the input file name
if there is a macro in the file-return macro retirement file (.am)
else - return the source file.*/
char * macro_retirement(FILE* inputFile, char* input_file_name)
{
	FILE* outputFile = NULL;
	char* output_file_name = NULL;
	char line[LINESIZE] = {0};
	char* value = NULL;
	char* data = NULL;/*content of macro*/
	char* macroName = NULL;
	char* newMacroName = NULL;
	macro_node* h = NULL;
	unsigned long int sizeData = MACRO_CONTENT_LENGTH;
	char new_line[LINESIZE];
	int counter_line = 0;
	char c;

	
	
		if (!(output_file_name = (char*)malloc(((strlen(input_file_name) + 1) * sizeof(char) + FILE_EXTENSION_SIZE))))
		{
			fprintf(stderr, "Error allocation faild!\n");
			exit(-1);
		}

		strcpy(output_file_name, input_file_name);
		strcat(output_file_name, ".am");

		outputFile = fopen(output_file_name, "w");

		if ((outputFile == NULL))
		{
			fprintf(stderr, "Could not open file named %s!\n,", output_file_name);
			exit(0);
		}
	


	while (fgets(line, sizeof(line) - 1, inputFile))
	{
		/*check if line bigger than 80*/
		counter_line++;
		
		if((c = fgetc(inputFile)) != EOF)
		{	
			ungetc(c,inputFile);

			if (strchr(line, '\n') == NULL)
			{
				print_error(counter_line, "line is bigger than 80");
				while (((c = fgetc(inputFile)) != EOF) && (c != '\n'))
				{
					continue;
				}
				continue;
			}
		}
		else
			ungetc(c,inputFile);

		/*clean white spaces*/
		arrange_line(line, new_line);
		if(new_line[0] == EOS)
		{
			/*copy to the new file*/	
			fprintf(outputFile, "%s", line);
			continue;
		}
		/*The first word*/
		value = strtok(new_line, " \t\n");
		
		/*If we found "macro" it means that a new macro starts*/
		if (value != NULL && !(strcmp(value, "macro")))
		{

			macroName = (char*)calloc(MACRO_NAME_LENGTH, sizeof(char));

			if (!macroName)/*If there is no place in memory*/
			{
				fprintf(stderr, "memory allocation failed");
				exit(0);
			}

			newMacroName = (char*)calloc(FILE_EXTENSION_SIZE, sizeof(char));

			if (!newMacroName)/*If there is no place in memory*/
			{
				fprintf(stderr, "memory allocation failed");
				exit(0);
			}
			/*take the macro name*/
			value = strtok(NULL, " \t\n");
			
			if (!value)
			{
				print_error(counter_line, "Error! No macro name.");
				continue;
			}
			if (is_reserved_word(value) == true)
			{
				print_error(counter_line, "The name of the macro is reserved word");
				continue;
			}
			strcpy(macroName, value);/*The first word after "macro", the name of the macro*/
			
			strcpy(newMacroName, macroName);
			/*contant of macro*/
			data = (char*)calloc(sizeData + 1, sizeof(char));

			if (!data)/*If there is no place in memory*/
			{
				fprintf(stderr, "memory allocation failed");
				exit(0);
			}


			while (fgets(line, sizeof(line) - 1, inputFile))/*contant of macro*/
			{
				
				/*we found macro*/
				/*check if line bigger than 80*/
				counter_line++;
				if((c = fgetc(inputFile)) != EOF)
				{	
					ungetc(c,inputFile);

					if (strchr(line, '\n') == NULL)
					{
						print_error(counter_line, "line is bigger than 80");
						while (((c = fgetc(inputFile)) != EOF) && (c != '\n'))
						{
							print_error(counter_line, "line is bigger than 80");
							continue;

						}
						continue;
					}
				}
				else
					ungetc(c,inputFile);
				

				
				arrange_line(line, new_line);
				
				if(new_line[0] == EOS)
				{
					/*copy to the new file*/	
					fprintf(outputFile, "%s", line);
					continue;
				}
				/*The first word*/
				value = strtok(new_line, " \t\n");
				
				/*if we reach to the end of contant - endmacro*/
				if (!(strcmp(value, "endmacro")))
				{

					if ((find_macro_data(h, data)) == true)
					{
						print_error(counter_line, "error, double macro setup");
						continue;
					}
					else
						add_node(&h, data, newMacroName);/*add to list*/
					/*continue to read orginal file*/
					break;


				}
				/*add line to the data of the macro*/
				else
				{
					strcat(data, line);
				}
			}

		}
		/*The retirement of the macro - when we got macro name*/
		else if (find_macro_name(h, value) == true)
		{

			strcpy(data, give_macro_data(h, value));
			fprintf(outputFile, "%s", data);
		}
		/*regular line*/
		else
		{

			fprintf(outputFile, "%s", line);/*copy to the new file*/

		}
	}

	
	
	free_list_macro(h);
	free(macroName);
	free(newMacroName);
	free(data);
	fclose(inputFile);
	fclose(outputFile);
	return 	output_file_name;
}



/*API:
The method gets a node pointer and the node data and adds
the node to the last place in the list*/
void add_node(macro_node** head, char* str, char* macroName)

{
	macro_node* current, * new;

	new = (macro_node*)calloc(1, sizeof(macro_node));
	if (!new)
	{
		fprintf(stderr, "Error, no place in memmory");
		exit(0);
	}
	
	new->data = (char*)calloc(strlen(str) +1, sizeof(char));
	new->name = (char*)calloc(strlen(macroName) +1, sizeof(char));
	
	strcpy(new->name, macroName);
	strcpy(new->data, str);

	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;

		current->next = new;
	}

}

/*API:
The method gets tgets a pointer to the head of the list and frees up the memory*/
void free_list_macro(macro_node* head)
{
	macro_node* p = NULL;

	while (head)
	{
		p = head;
		head = head->next;
		
		free(p->data);
		free(p->name);
		
		free(p);
	}
}


/*API:
The function search if the given macro already defined
if so - return true, otherwise return false.
gets the head of macro list and a macro name*/
boolean find_macro_name(macro_node* head, char* macro_name)
{
	macro_node* current = head;
	if (!macro_name)
		return false;
	while (current != NULL)
	{
		if (!(strcmp(current->name, macro_name)))
			return true;
		else
		{
			current = current->next;
		}


	}
	return false;
}
/*API:
The function search if the given data of macro already defined with a another macro name
if so - return false, otherwise return true.
gets the head of macro list and a macro data*/
boolean find_macro_data(macro_node* head, char* data)
{
	macro_node* current = head;
	if (!data)
		return false;
	while (current != NULL)
	{
		if (!(strcmp(current->data, data)))
			return true;
		else
		{
			current = current->next;
		}
	}
	return false;

}
/*API:
The function returns the data macro by a given macro name
it gets the head of macro list and the macro name*/

char* give_macro_data(macro_node* head, char* macro_name)
{
	macro_node* current = head;

	while (current != NULL)
	{
		if (!(strcmp(current->name, macro_name)))
			return current->data;
		else
		{
			current = current->next;
		}


	}
	return NULL;

}

