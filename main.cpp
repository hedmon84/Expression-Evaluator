#include "evaluador.hpp"
#include <iostream>
#include <stdlib.h>
#include <string.h>
//compile
// g++ *.hpp *.cpp
using namespace std;

int main()
{

    string name;
    cout << "ingrese expresion infija\n";
    cin >> name;
    evaluador(name);
    // stackchecker();
    print_posfix();
    cout << "---------" << endl;
    evaluate_expressions();
    return 0;
}