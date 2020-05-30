#include "calcitself.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void CheckExpressions(FILE* in); // функция для анализа введенных выражений
	
int main(int argc, char** argv) {
	if (argc > 2) { // проверка на корректное кол-во аргументов
		puts("ERROR: Too much input arguments");
		return -1;
	}
	if (argv[1] == NULL) // если не передано аргументов
		CheckExpressions(stdin); // работать со стандартным потоком
	else { // если передано имя файла в качестве аргумента
		FILE* input;
		fopen_s(&input, argv[1], "r");
		if (input == NULL) {
			puts("ERROR: Invalid file");
			return -2;
		}
		else {
			CheckExpressions(input); // работать с файлом
			fclose(input);
		}
	} 
	return 0;
}

void CheckExpressions(FILE* in) { 
	char symbol; // переменная для обработки потока
	char* buffer = (char*)malloc(sizeof(char)); // строка, куда записываются выражения
	int status = 1; // переменная, определяющая формат строки (0 - выражение, 1 - пустая строка/комментарий)
	int i = 0; // счетчик
	while ((symbol = (char)fgetc(in)) != EOF) {
		// условие для поиска комментариев
		if (symbol == '/') {
			putc(symbol, stdout);
			buffer[i] = symbol;
			buffer = realloc(buffer, (i + 2) * sizeof(char)); //увеличение размера строки
			if (buffer == NULL) {
				puts("ERROR: Not enough memory\n");
				free(buffer);
			}
			i++;
			symbol = (char)fgetc(in);
			if (symbol == '/') {
				putc(symbol, stdout);
				while ((symbol = (char)fgetc(in)) != '\n')
					putc(symbol, stdout);
				i = 0;
				buffer = realloc(buffer, sizeof(char));
			}
			else {
				status = 0;
			}
		}

		// условие для поиска пустых строк
		if (!isspace(symbol)) status = 0;

		// условие на конец выражения
		if (symbol == '\n' && status == 0)
		{
			buffer[i] = '\0';
			printf(" == %g", calculate(buffer));
			status = 1;
			i = 0;
			buffer = realloc(buffer, sizeof(char));
		}

		putc(symbol, stdout); // вывод символа после проверки всех условий
		buffer[i] = symbol; // запись в строку
		buffer = realloc(buffer, (i + 2) * sizeof(char)); //увеличение размера строки
		if (buffer == NULL) {
			puts("ERROR: Not enough memory\n");
			free(buffer);
		}
		i++;
	}
	// для последнего выражения
	buffer[i] = '\0';
	if (status == 0) printf(" == %g", calculate(buffer));
	free(buffer);
}