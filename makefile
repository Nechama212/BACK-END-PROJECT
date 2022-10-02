run: main.o operand_fun.o adr_method_fun.o first_pass.o lebal_list_fun.o first_pass_fun.o directive_coding.o general_func.o second_pass_fun.o second_pass.o third_pass.o pre_assembler.o
	gcc -g -ansi -pedantic -Wall main.o operand_fun.o adr_method_fun.o first_pass.o lebal_list_fun.o first_pass_fun.o directive_coding.o general_func.o second_pass_fun.o second_pass.o third_pass.o pre_assembler.o -o run
main.o: first_pass.c adr_method_fun.c operand_fun.c lebal_list_fun.c main.c main.h first_pass_fun.c directive_coding.c general_func.c second_pass_fun.c second_pass.c third_pass.c pre_assembler.c
	gcc -c -ansi -pedantic -Wall main.c -o main.o
operand_fun.o: first_pass.c adr_method_fun.c operand_fun.c lebal_list_fun.c main.c main.h first_pass_fun.c directive_coding.c general_func.c second_pass_fun.c second_pass.c third_pass.c pre_assembler.c
	gcc -c -ansi -pedantic -Wall operand_fun.c -o operand_fun.o
adr_method_fun.o: first_pass.c adr_method_fun.c operand_fun.c lebal_list_fun.c main.c main.h first_pass_fun.c directive_coding.c general_func.c second_pass_fun.c second_pass.c third_pass.c pre_assembler.c
	gcc -c -ansi -pedantic -Wall adr_method_fun.c -o adr_method_fun.o
first_pass.o: first_pass.c adr_method_fun.c operand_fun.c lebal_list_fun.c main.c main.h first_pass_fun.c directive_coding.c general_func.c second_pass_fun.c second_pass.c third_pass.c pre_assembler.c
	gcc -c -ansi -pedantic -Wall first_pass.c -o first_pass.o
lebal_list_fun.o: first_pass.c adr_method_fun.c operand_fun.c lebal_list_fun.c main.c main.h first_pass_fun.c directive_coding.c general_func.c second_pass_fun.c second_pass.c third_pass.c pre_assembler.c
	gcc -c -ansi -pedantic -Wall lebal_list_fun.c -o lebal_list_fun.o
first_pass_fun.o: first_pass.c adr_method_fun.c operand_fun.c lebal_list_fun.c main.c main.h first_pass_fun.c directive_coding.c general_func.c second_pass_fun.c second_pass.c third_pass.c pre_assembler.c
	gcc -c -ansi -pedantic -Wall first_pass_fun.c -o first_pass_fun.o
directive_coding.o: first_pass.c adr_method_fun.c operand_fun.c lebal_list_fun.c main.c main.h first_pass_fun.c directive_coding.c general_func.c second_pass_fun.c second_pass.c third_pass.c pre_assembler.c
	gcc -c -ansi -pedantic -Wall directive_coding.c -o directive_coding.o
general_func.o: first_pass.c adr_method_fun.c operand_fun.c lebal_list_fun.c main.c main.h first_pass_fun.c directive_coding.c general_func.c second_pass_fun.c second_pass.c third_pass.c pre_assembler.c
	gcc -c -ansi -pedantic -Wall general_func.c -o general_func.o
second_pass.o: first_pass.c adr_method_fun.c operand_fun.c lebal_list_fun.c main.c main.h first_pass_fun.c directive_coding.c general_func.c second_pass_fun.c second_pass.c third_pass.c pre_assembler.c
	gcc -c -ansi -pedantic -Wall second_pass.c -o second_pass.o
second_pass_fun.o: first_pass.c adr_method_fun.c operand_fun.c lebal_list_fun.c main.c main.h first_pass_fun.c directive_coding.c general_func.c second_pass_fun.c second_pass.c third_pass.c pre_assembler.c
	gcc -c -ansi -pedantic -Wall second_pass_fun.c -o second_pass_fun.o
third_pass.o: first_pass.c adr_method_fun.c operand_fun.c lebal_list_fun.c main.c main.h first_pass_fun.c directive_coding.c general_func.c second_pass_fun.c second_pass.c third_pass.c pre_assembler.c
	gcc -c -ansi -pedantic -Wall third_pass.c -o third_pass.o
pre_assembler.o: first_pass.c adr_method_fun.c operand_fun.c lebal_list_fun.c main.c main.h first_pass_fun.c directive_coding.c general_func.c second_pass_fun.c second_pass.c third_pass.c pre_assembler.c
	gcc -c -ansi -pedantic -Wall pre_assembler.c -o pre_assembler.o
