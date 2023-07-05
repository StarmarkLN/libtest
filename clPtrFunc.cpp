#include "clPtrFunc.h"

void hello(void)
{
    printf("Hello, World \n");
}

void goodbye(void)
{
    printf("Good Bye, World \n");
}

int add(int x, int y)
{
    return x + y;
}

int subtract(int x, int y)
{
    return x - y;
}

int multiply(int x, int y)
{    
	return x * y;
}


void clPtrFunc::Test()
{
	message=hello;  	// message указывает на функцию hello
    message();      	// вызываем функцию hello, на которую указыывет указатель

	
    a = 10;
    b = 5;

	operation=add;
    result = operation(a, b);
    printf("add_result = %d \n", result);       // result=15
     
    operation = subtract;
    result = operation(a, b);
    printf("subtract_result = %d \n", result);  // result=5


	// массив указатеоей operations указывает на add, subtract, multiply
	int (*operations[3])(int, int) = {add, subtract, multiply};
	// получаем длину массива
    int length = sizeof(operations)/sizeof(operations[0]);
	// отрабатываеи в цикле эти функции     
    for(int i=0; i < length; i++)
    {
		// вызов функций по массиву указателей operations[]
        printf("res[%d] = %d \n", i, operations[i](a, b)); 
    }


	message = goodbye; 	// сменим функцию для message на goodbye
    message();
}
