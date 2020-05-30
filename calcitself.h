#pragma once

#define PI 3.14159265358979
#define E 2.718281828

double calculate(char* expression); //основная функция калькулятора
void clear_spaces(char* expression); //удаление пробелов
double add_and_sub(char* expression, unsigned *position); //сложение и вычитание
double mult_and_div(char* expression, unsigned *position); //умножение и деление
double power_and_brackets(char* expression, unsigned *position); //степень и нахождение выражений в скобках
double get_numbers(char* expression, unsigned *position); //извлечение чисел
