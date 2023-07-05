 /*---------------------------------------------------------------------------
Книга:
    Изучаем ядро Linux и библиотеки C
    Linux системное программирование
Автор:
    Роберт Лав

Пример программы, в которой используется буферизованный ввод-вывод

Сначала программа определяет структуру struct pirate , а потом определяет две
переменные такого типа. Программа инициализирует одну из переменных, а 
потом записывает ее на диск через поток данных вывода в файл data. 
В другом по­токе данных программа вновь считывает данные из файла data  
непосредственно в другой экземпляр struct pirate . 
Наконец, программа записывает содержимое структуры в стандартный вывод:
----------------------------------------------------------------------------*/
#include "clwrite_read.h"
#include <stdio.h>

int clWrite_Read::Test (void)
{
    FILE *in, *out;
    struct pirate {
        char  name[100];        /* настоящее имя */
        unsigned long booty;    /* вознаграждение в фунтах стерлингов */
        unsigned int beard_len; /* длина бороды в дюймах */
    } p, blackbeard = { "EdwardTeach", 950, 48 };

    printf("blackbeard:");
	printf ("name=\"%s\" booty=%lu beard_len=%u\n",
            blackbeard.name, blackbeard.booty, blackbeard.beard_len);

    out = fopen ("data", "w");
    if (!out) {
        perror ("fopen");
        return 1;
    }

    if (!fwrite (&blackbeard, sizeof (struct pirate), 1, out)) {
        perror ("fwrite");
        return 1;
    }

    if (fclose (out)) {
        perror ("fclose");
        return 1;
    }

    in = fopen ("data", "r");
    if (!in) {
        perror ("fopen");
        return 1;
    }

    if (!fread (&p, sizeof (struct pirate), 1, in)) {
        perror ("fread");
        return 1;
    }

    if (fclose (in)) {
        perror ("fclose");
        return 1;
    }

	printf("p:");
    printf ("name=\"%s\" booty=%lu beard_len=%u\n",
            p.name, p.booty, p.beard_len);

    return 0;
}
