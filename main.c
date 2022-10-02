#include "main.h"

char opcode [AMOUNT_OPCODE][NAME_LENGTH]= {
"mov",
"cmp",
"add",
"sub",
"not",
"clr",
"lea",
"inc",
"dec",
"jmp",
"bne",
"get",
"prn",
"jsr",
"rts",
"hlt"
};

char address [AMOUNT_ADRESS][ADRESS_NAME] = {
"Immediate address",
"Direct address",
"Address access",
"Direct register address"
};

char encoding_type [AMOUNT_ENCODE_TYPE][ENCODE_TYPE_NAME] ={
"A",
"E",
"R"
};

char registers [AMOUNT_REG][REG_NAME] = {
"r0",
"r1",
"r2",
"r3",
"r4",
"r5",
"r6",
"r7"
};

char directive [AMOUNT_DIRECT][DIRECT_NAME] = {
".data",
".string",
".struct"
};

char outside [AMOUNT_OUTSIDE][OUTSIDE_NAME] ={
".extern",
".entry"
};
	
int main(int argc, char* argv[])
{
	
	
   	word d_code_image [MAX_LEN_CODE_IMAGE];
   	word i_code_image [MAX_LEN_CODE_IMAGE];
   	
   	
   	
   	FILE * file;
   	FILE * input_file;
	FILE * object;
	FILE * externals;
	FILE * entries;
	char * externals_file_name;
	char * entries_file_name;
	char * object_file_name;
   	char * source_file_name;
   	char * macro_return;
   	int j;
	
	
   	if (argc < MIN_FILE)
	{
		fprintf(stderr, "missing file name\n");
		exit(-1);
	}
	
	
	for (j = 1; j < argc; j++)
	{
		
		
		lebal_node * lebal_list = NULL;
		file_number = j;
		if (!(source_file_name = (char*)realloc(source_file_name,(strlen(argv[j]) + 1) * sizeof(char) + FILE_EXTENSION_SIZE)))
		{
			fprintf(stderr, "Error allocation faild!\n");
			exit(-1);
		}
		
	
		strcpy(source_file_name, argv[j]);
		strcat(source_file_name, ".as");
		input_file = fopen(source_file_name, "r");
		if (input_file == NULL)
		{
			fprintf(stderr, "%s Could not open file named %s!\n,", argv[0], argv[j]);
			exit(-1);
		}
		
 
   	
	
		/*object_file*/
		if (!(object_file_name = (char*)realloc(object_file_name,(strlen(argv[1]) + 1) * sizeof(char) + FILE_EXTENSION_SIZE)))
		{
			fprintf(stderr, "Error allocation faild!\n");
			exit(-1);
		}
		strcpy(object_file_name, argv[1]);
		strcat(object_file_name, ".ob");	
		
	
		object = fopen(object_file_name, "w");
		
		/*externals_file*/
		if (!(externals_file_name = (char*)realloc(externals_file_name,(strlen(argv[1]) + 1) * sizeof(char) + FILE_EXTENSION_SIZE)))
		{
			fprintf(stderr, "Error allocation faild!\n");
			exit(-1);
		}
		strcpy(externals_file_name, argv[1]);
		strcat(externals_file_name, ".ext");	
		
	
		externals = fopen(externals_file_name, "w");
	
		/*entries_file*/
		if (!(entries_file_name = (char*)realloc(entries_file_name,(strlen(argv[1]) + 1) * sizeof(char) + FILE_EXTENSION_SIZE)))
		{
			fprintf(stderr, "Error allocation faild!\n");
			exit(-1);
		}
		strcpy(entries_file_name, argv[1]);
		strcat(entries_file_name, ".ent");	

	
		entries = fopen(entries_file_name, "w");

		/*the file name return from macro retirement*/
		macro_return = (char*)realloc(macro_return,(strlen(argv[j]) + 1) * sizeof(char) + FILE_EXTENSION_SIZE);
					
		strcpy(macro_return,macro_retirement(input_file, argv[j]));
	
		/*CALL TO MACRO*/
	
	
		file = fopen(macro_return,"r");	
		/*return the pointer on file to the start*/
		fseek(file, 0, SEEK_SET);
	
		if(is_error == true)
		{
			fclose(file);
			fclose(object);
			fclose(externals);
			fclose(entries);
			remove(object_file_name);
      			remove(externals_file_name);
      			remove(entries_file_name);
			remove(macro_return);
			freelist(&lebal_list);
			is_error = false;
			continue;
		}



	
		/*CALL TO FIRST PASS*/	
	
		first_pass(i_code_image,d_code_image,&lebal_list, file);

		if(is_error == true)
		{
			fclose(file);
			fclose(object);
			fclose(externals);
			fclose(entries);
		
			freelist(&lebal_list);
		
			remove(object_file_name);
      			remove(externals_file_name);
      			remove(entries_file_name);
      			is_error = false;
			continue;
		}
	
		/*return the pointer on file to the start*/
		fseek(file, 0, SEEK_SET);
	

		/*CALL TO SECOND PASS*/
	
		second_pass(i_code_image,d_code_image,&lebal_list, file);
	
		if(is_error == true)
		{
		
			fclose(file);
			fclose(object);
			fclose(externals);
			fclose(entries);
		
			freelist(&lebal_list);
		
			remove(object_file_name);
      			remove(externals_file_name);
      			remove(entries_file_name);
      			is_error = false;
			continue;
		}
	
		/*CALL TO THIRD PASS*/
		third_pass(i_code_image, d_code_image, &lebal_list,object,externals,entries,externals_file_name,entries_file_name);
	
	
	
		fclose(file);
		fclose(object);
		fclose(externals);
		fclose(entries);
		
		
		freelist(&lebal_list);
		is_error = false;
		
	}

		
	free(object_file_name);
	free(externals_file_name);
	free(entries_file_name);
		
	free(macro_return);
	free(source_file_name);
	return 0;
}
