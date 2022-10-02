#include "main.h"
/*API
return the ADRESS METHOD of a given operand, if not legal- return -1
*/
int adress_mathod(char operand [])
{

	if(adress_0(operand) != -1)
		return adress_0(operand);
	if(adress_1(operand) != -1)
		return adress_1(operand);
	if(adress_2(operand) != -1)
		return adress_2(operand);
	if(adress_3(operand) != -1)
		return adress_3(operand);
	return -1;
}

/*API
return the ADRESS METHOD 0 if a given operand have this address, otherwise, return -1
*/
int adress_0(char given_operand [])
{
	char * operand = malloc(strlen(given_operand)+1);
	if(operand == NULL)
	{
		fprintf(stderr, "Error allocation faild!\n");
		exit(-1);
	}
	strcpy(operand, given_operand);
	
	
	if(operand[0] ==  HASHTAG)
	{
		/*delete the HAHSTAG*/
		memmove(operand, operand+1, strlen(operand));
		if(is_num(operand))
			return 0;
	}
	
	free(operand);
	return -1;
}

/*API
return the ADRESS METHOD 1 if a given operand have this address, otherwise, return -1
*/
int adress_1(char given_operand [])
{
	/*linking COLON to the end of the operand
	(for the is_lebal method)*/
	char colon = COLON;
	
	char * operand = malloc(strlen(given_operand)+1);
	if(operand == NULL)
	{
		fprintf(stderr, "Error allocation faild!\n");
		exit(-1);
	}
	strcpy(operand, given_operand);
	
	strncat(operand, &colon, 1);
	if(is_lebal(operand))
	{
		return 1;
	}
	free(operand);
	return -1;
}

/*API
return the ADRESS METHOD 2 if a given operand have this address, otherwise, return -1*/

int adress_2(char given_operand [])
{
	int i = 0;
	int num_of_letters = 0;
	char lebal [MAX_LEN_LEBAL] = {0};
	char colon = COLON;
	
	char * operand = malloc(strlen(given_operand)+1);
	if(operand == NULL)
	{
		fprintf(stderr, "Error allocation faild!\n");
		exit(-1);
	}
	strcpy(operand, given_operand);
	
	for(i = 0; operand[i] != DOT && i< strlen(operand) && i < MAX_LEN_LEBAL; i++)
	{
		num_of_letters++;
	}

	/*copy the letters until the dot*/
	strncpy(lebal, operand, num_of_letters);
		
	/*linking COLON to the end of the lebal
	(for the is_lebal method)*/
	strncat(lebal, &colon, 1);

	if(is_lebal(lebal) && operand[i] == DOT)
	{
		if((operand[i+1] == '1' || operand[i+1] == '2') && operand[i+2] == '\0')
			return 2;
	}
	free(operand);
	return -1;
}

/*API
return the ADRESS METHOD 3 if a given operand have this address, otherwise, return -1
*/
int adress_3(char operand [])
{
	if(register_code(operand) != -1)
		return 3;
	return -1;
}


