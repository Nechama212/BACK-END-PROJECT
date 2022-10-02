#include "main.h"
/*API
add a lebal on the front of lebal list, if there is error - print to the error file.
*/
void add_lebal_list(lebal_node ** head,char lebal [], char type [], int VC, int counter_lines)
{
	 /* 1. allocate node */
	 lebal_node * new_node;
	if(!(new_node = (lebal_node *)malloc(sizeof(lebal_node))))
	{	
		fprintf(stderr, "Error allocation faild!\n");
		exit(-1);
	
	}
	
	
	/* 2. put in the data  */
	strcpy(new_node->name, lebal);
	strcpy(new_node->type, type);
	new_node->value = VC;
	new_node->entry = false;
	new_node->is_struct = false;
	/*check if the node IN list already*/
	if(search_lebal_list(*head, new_node) != -1)
	{
		print_error(counter_lines, "The label was previously defined");
        	return;
	}

	/* 3. Make next of new node as head */
	new_node->next = (*head);

	/* 4. move the head to point to the new node */
	(*head) = new_node;
		
}

/*API
search a node in list, return the value if found, atherwise - -1.
*/
int search_lebal_list(lebal_node * head, lebal_node * node)
{
	
	lebal_node * current = head;
			
	while (current != NULL)
	{
		if(strcmp(node->name, current->name) == 0)
		{
			return current->value;
		}
		

		current = current->next;
	}
	return -1;
}
/*API
free the lebal_list
*/
void freelist(lebal_node ** head)
{
	lebal_node * p = *head;
	if(*head == NULL)
		return;
	while (*head != NULL)
	{
		p = (*head)->next;
		free(*head);
		*head = p;
	}
	
}
/*API
print the lebal_list
*/
void printlist(lebal_node ** head)
{
	lebal_node * current = *head;
	
	while (current)
	{
		printf("%s,\t%s,\t%d, \t%d, \t%d\n", current->name, current->type, current->value, current->entry, current->is_struct);
		current = current->next;
	}
}
/*API
update the data symbols to be + IC- 16. in first_pass algorithm*/
void update_data_symbols(lebal_node * head)
{
	lebal_node * current = head;
	while(current != NULL)
	{
     		if(strcmp(current->type, "data") == 0)
     			current->value = current->value + IC;
     		current= current->next;
	}
}
