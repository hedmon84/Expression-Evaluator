#ifndef EVALUADOR_HPP
#define EVALUADOR_HPP
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <bits/stdc++.h>
#include <cmath>
#include <fstream>
#include <stdio.h>
#include <string>
#include <ctype.h>
#include <iomanip>
using namespace std;

// namespace variables
void evaluador(string);
void stack1(string digits);
void stack2(string operators);
void evaluate_expressions();
void stackchecker();
void print_posfix();
void valid_expresion(string infix);
double operation(double y, double x, string opr);
int num_size(string number);
int is_operator(string symbol);
auto operators_check(string symbol);
bool is_number(string number);
int precedence(string symbol);
void Pruebas(string operation, double p1);
void Tests_TDD();

#endif /*EVALUADOR_HPP*/