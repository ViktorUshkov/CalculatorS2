#pragma once

#define PI 3.14159265358979
#define E 2.718281828

double calculate(char* expression); //�������� ������� ������������
void clear_spaces(char* expression); //�������� ��������
double add_and_sub(char* expression, unsigned *position); //�������� � ���������
double mult_and_div(char* expression, unsigned *position); //��������� � �������
double power_and_brackets(char* expression, unsigned *position); //������� � ���������� ��������� � �������
double get_numbers(char* expression, unsigned *position); //���������� �����
