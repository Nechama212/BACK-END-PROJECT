#include "main.h"
/*API:
go on the image code and put the data in the output files
get the two images code arrays, the head of lebal list, the ob. file, the ent. file and the ext. file, the names of ext. file name and ent. file name*/
void third_pass(word i_code_image [],word d_code_image [], lebal_node ** lebal_list, FILE * object, FILE * externals, FILE * entries, char externals_file_name [], char entries_file_name [])
{
	boolean ext_flag = false;
	boolean ent_flag = false;
	lebal_node * current = *lebal_list;
	int i = 0;

	char image[3];
	
	fprintf(object, "%s\t",conv_32base(IC));
	fprintf(object, "%s\n",conv_32base(DC));
	
	for(i = 0; i< IC;i++)
	{
		strcpy(i_code_image[i].thirty_two_address, conv_32base(i_code_image[i].decimal_address));
		
		strcpy(image,conv_32base(i_code_image[i].binary_machine_code));
		fprintf(object, "%s\t%s\n", i_code_image[i].thirty_two_address, image);
		
		/*externals*/
		if((i_code_image[i].binary_machine_code & E) == E)
		{
			fprintf(externals, "%s\t%s\n", i_code_image[i].operands, i_code_image[i].thirty_two_address);
			ext_flag = true;
		}
	}
	
		
	for(i = 0; i< DC;i++)
	{
		strcpy(d_code_image[i].thirty_two_address, conv_32base(d_code_image[i].decimal_address + IC));

		strcpy(image,conv_32base(d_code_image[i].binary_machine_code));
		fprintf(object, "%s\t%s\n",d_code_image[i].thirty_two_address , image);
	}
	
	/*entries*/
	
	
	while (current != NULL)
	{
		if(current->entry == true)
		{
			fprintf(entries, "%s\t%s\n",current->name , conv_32base(current->value));
			ent_flag = true;
		}
		current = current->next;
	}
	if(ext_flag == false)
	{
		remove(externals_file_name);
	}
	if(ent_flag == false)
	{
      		remove(entries_file_name);
      	}
	
}
