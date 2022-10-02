#include "constant.h"


/*API:
The function do the macro retirement
gets a pointer to input file, the input file name
if there is a macro in the file-return macro retirement file (.am)
else - return the source file.*/
char * macro_retirement(FILE* , char*);

/*API:
The method gets tgets a pointer to the head of the list and frees up the memory*/
void free_list_macro(macro_node * );

/*API:
The function search if the given macro already defined
if so - return true, otherwise return false.
gets the head of macro list and a macro name*/
boolean find_macro_name(macro_node* , char* );

/*API:
The function returns the data macro by a given macro name
it gets the head of macro list and the macro name*/
char* give_macro_data(macro_node* , char* );

/*API:
The function search if the given data of macro already defined with a another macro name
if so - return false, otherwise return true.
gets the head of macro list and a macro data*/
boolean find_macro_data(macro_node* , char* );

/*API:
The method gets a node pointer and the node data and adds
the node to the last place in the list*/
void add_node(macro_node** , char* , char* );

