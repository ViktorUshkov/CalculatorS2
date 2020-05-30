#include "calcitself.h"
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

double calculate(char* expression) {
	clear_spaces(expression);
	unsigned position = 0; // ïåðåìåííàÿ äëÿ îáðàáîòêè ñèìâîëîâ â âûðàæåíèè
	return add_and_sub(expression, &position);
}

void clear_spaces(char* expression) {
	int i = 0, j = 0;                          
	while ((expression[i] = expression[j++]) != '\0') 
		if (expression[i] != ' ' && expression[i] != '\n' && expression[i] != '\t')
			i++;
}

double add_and_sub(char* expression, unsigned *position) {
	double answer = mult_and_div(expression, position);
	while (expression[*position] == '+' || expression[*position] == '-') {
		switch (expression[*position])
		{
		case '+':
			++*position;
			answer += mult_and_div(expression, position);
			break;
		case '-':
			++*position;
			answer -= mult_and_div(expression, position);
			break;
		}
	}
	return answer;
}

double mult_and_div(char* expression, unsigned *position) {
	double answer = power_and_brackets(expression, position);
	double divide = 0.0; // ïåðåìåííàÿ äëÿ ïðîâåðêè äåëåíèÿ íà íîëü
	while (expression[*position] == '*' || expression[*position] == '/') {
		switch (expression[*position])
		{
		case '*':
			++*position;
			answer *= power_and_brackets(expression, position);
			break;
		case '/':
			++*position;
			divide = power_and_brackets(expression, position);
			if (divide == 0.0) puts("ERROR: Division by 0\n"); // ïðîâåðêà äåëåíèÿ íà íîëü
			else answer /= divide;
			break;
		}
	}
	return answer;
}


double power_and_brackets(char* expression, unsigned *position) {
	double answer;
	int sign = 1; 
	if (expression[*position] == '-') {
		++*position;
		sign = -1;
	}
	if (expression[*position] == '(') { // ïîèñê ïîäâûðàæåíèé â ñêîáêàõ
		++*position;
		answer = add_and_sub(expression, position);
		/*if (expression[*position] != ')') puts(" ERROR: Brackets");*/
		++*position;
	}
	else answer = get_numbers(expression, position);
	if (expression[*position] == '^') {
		++*position;
		answer = pow(answer, power_and_brackets(expression, position));
	}
	return answer * sign;
}

double get_numbers(char* expression, unsigned *position) {
	double answer = 0.0;
	double decimal_part = 10.0; 
	int sign = 1;
	if (expression[*position] == '-') {
		++*position;
		sign = -1;
	}
	while (isdigit(expression[*position])) {
		answer = answer * 10.0 + (expression[*position] - 48); //ïîëó÷åíèå ÷èñëà 
		++*position;
	}
	if (expression[*position] == '.') { //ïîëó÷åíèå äåñÿòè÷íîé ÷àñòè ÷èñëà
		++*position;
		while (isdigit(expression[*position])) {
			answer = answer + (expression[*position] - 48) / decimal_part;
			decimal_part *= 10.0;
			++*position;
		}
	}
	return sign * answer;
}
