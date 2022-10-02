#include "constant.h"



/*API
add a lebal to the lebal list, if there is error - print to the error file.
*/	
void add_lebal_list(lebal_node **, char [], char [], int,  int);


/*API
free the lebal_list
*/
void freelist(lebal_node **);

/*API
print the lebal_list
*/
void printlist(lebal_node **);

/*API
search a node in list, return value if found, atherwise - -1.
*/
int search_lebal_list(lebal_node *, lebal_node * );

/*API
update the data symbols to be + IC- 16. in first_pass algorithm*/
void update_data_symbols(lebal_node *);
