#include "calcitself.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void CheckExpressions(FILE* in); // ������� ��� ������� ��������� ���������
	
int main(int argc, char** argv) {
	if (argc > 2) { // �������� �� ���������� ���-�� ����������
		puts("ERROR: Too much input arguments");
		return -1;
	}
	if (argv[1] == NULL) // ���� �� �������� ����������
		CheckExpressions(stdin); // �������� �� ����������� �������
	else { // ���� �������� ��� ����� � �������� ���������
		FILE* input;
		fopen_s(&input, argv[1], "r");
		if (input == NULL) {
			puts("ERROR: Invalid file");
			return -2;
		}
		else {
			CheckExpressions(input); // �������� � ������
			fclose(input);
		}
	} 
	return 0;
}

void CheckExpressions(FILE* in) { 
	char symbol; // ���������� ��� ��������� ������
	char* buffer = (char*)malloc(sizeof(char)); // ������, ���� ������������ ���������
	int status = 1; // ����������, ������������ ������ ������ (0 - ���������, 1 - ������ ������/�����������)
	int i = 0; // �������
	while ((symbol = (char)fgetc(in)) != EOF) {
		// ������� ��� ������ ������������
		if (symbol == '/') {
			putc(symbol, stdout);
			buffer[i] = symbol;
			buffer = realloc(buffer, (i + 2) * sizeof(char)); //���������� ������� ������
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

		// ������� ��� ������ ������ �����
		if (!isspace(symbol)) status = 0;

		// ������� �� ����� ���������
		if (symbol == '\n' && status == 0)
		{
			buffer[i] = '\0';
			printf(" == %g", calculate(buffer));
			status = 1;
			i = 0;
			buffer = realloc(buffer, sizeof(char));
		}

		putc(symbol, stdout); // ����� ������� ����� �������� ���� �������
		buffer[i] = symbol; // ������ � ������
		buffer = realloc(buffer, (i + 2) * sizeof(char)); //���������� ������� ������
		if (buffer == NULL) {
			puts("ERROR: Not enough memory\n");
			free(buffer);
		}
		i++;
	}
	// ��� ���������� ���������
	buffer[i] = '\0';
	if (status == 0) printf(" == %g", calculate(buffer));
	free(buffer);
}