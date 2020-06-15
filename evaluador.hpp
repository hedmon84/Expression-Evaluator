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
void evaluate_expressions();
void stackchecker();
void print_posfix();
int operation(int a, int b, char opr);
int num_size(string number);
int is_operator(string symbol);
bool is_number(string number);
int precedence(string symbol);
double answer();

#endif /*EVALUADOR_HPP*/