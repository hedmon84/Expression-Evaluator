#ifndef EVALUADOR_HPP
#define EVALUADOR_HPP
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <bits/stdc++.h>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
using namespace std;

void evaluador(string);
void stack1(string digits);
void stack2(string operators);
void evaluate_expressions(string expression);
int is_operator(string symbol);
bool is_number(string number);
int precedence(string symbol);
void stackchecker();
void print_posfix();
double answer();

#endif /*EVALUADOR_HPP*/