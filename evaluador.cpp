#include "evaluador.hpp"
int sizes;
double result = 0;
stack<string> s;          // stack2
stack<double> s2;         // numbers stacl
vector<string> g1;        //posfix
vector<double> numscheck; //numscheck
int precedence1 = 0;      // precedence saver
bool isdenominatorz = false;
string inf;
// (6+2)*3/2^2-4            pass
// (6+10(10+1))*2           pass
// 1^2/(5*3)+10             pass
// ((8+(1+2)/15))           pass
//8^(5*(5*2)+(18/2))/1000   pass
//(1+1.5)*(2+300)           pass
//(pi+pi)*pi/pi^pi-pi       pass
//(e+e)*e/e^e-e             pass
// (e+pi)*e/pi^2-4          pass
// 5*(6+2)-12/4             pass
//1^2*20/2+(3+4)*3^2-6+15   pass
//---------------error Test-------------------------
// 1+1//(1-1)1              pass
// 11+11(1-1)1-             pass
// (1+1/(1-1)1              pass
// +11+11(1-1)1             pass
// 11+11(1-1-)1             pass
// 11+11(-1-1)1             pass
// 11/11(1-1)1              pass
// 11%0(1-1)1               pass
// evaluador machine
//---------Features-------------
// c++ 14 Template
// c++ 14 function auto
// c++14 Return type deduction
// c++14 [[deprecated]] attribute
//c++ 11 stod
//c++11 auto variables
// c++ 11 Automatic Type Deduction en (auto i = g1.begin(); i != g1.end() feature c++ 11
// C++11 stack
// c++ 11 nullptr
// C++17 consexpr
// c++ 17 [[fallthrough]]
// c++ 17 inline
//c++17 lambda expresion

struct errors
{

    inline static string error102 = "\033[1;31m Error#102 (Character not allowed) \033[0m\n";
    inline static string error103 = "\033[1;31m Error#103 (Character not allowed) \033[0m\n";
    inline static string error104 = "\033[1;31m Error#104 (Few Arguments) \033[0m\n";
    inline static string error101 = "\033[1;31m Error#101 (Parentheses Mismatched) \033[0m\n";
    inline static string pass = "\033[1;31m Pass \033[0m\n";

} handle;

//[[deprecated("Esta funcion tendra una nueva version 2.0 mas compacta")]]
void evaluador(string infix)
{
    inf = infix;
    // string c[100];
    string numbers;
    // num size count

    sizes = infix.size();

    valid_expresion(inf);
    for (int i = 0; i < sizes; i++)
    {
        //gets every character of the string
        string exp = infix.substr(i, 1);

        //operator evaluation
        if (1 == is_operator(exp))
        {
            cout << "is operator" << endl;

            //validations

            stack2(exp);
        }

        //number evaluation
        else if (is_number(exp))
        {

            numbers += exp;
            //numbers += infix.substr(i + 1, 1);

            cout << "is number" << endl;
            //infix.substr(i + 1, 1)) if the next is "" or a operator
            if (is_operator(infix.substr(i + 1, 1)) || infix.substr(i + 1, 1) == "")
            {
                g1.push_back(numbers);
                numbers.clear();
            }
        }
        else
        {
            cout << "error no valid" << endl;
            break;
        }
    }
    while (!s.empty())
    {
        if (s.top() == "(" || s.top() == ")")
        {
            s.pop();
        }

        g1.push_back(s.top());

        cout << '\t' << s.top();
        s.pop();
    }
}

//stack machine
void stack2(string operators)
{
    //precedence check

    if (operators == ")")
    {

        while (s.top() != "(")
        {

            if (s.top() == "(" || s.top() == ")")
            {
                s.pop();
            }
            if (s.top() == "^" || s.top() == "*" || s.top() == "/" || s.top() == "%" || s.top() == "+" || s.top() == "-")
            {
                g1.push_back(s.top());
            }

            cout << '\t' << s.top();
            s.pop();
        }

        cout
            << '\n'
            << "empty stack";
        s.pop();
    }

    else if (operators == "(")
    {
        s.push(operators);
        precedence1 = 0;
    }

    else if (precedence(operators) == precedence1)
    {

        g1.push_back(s.top());

        cout << '\t' << s.top();
        s.pop();

        cout << '\n'
             << "precedence update" << endl;
        s.push(operators);
        precedence1 = precedence(operators);
    }
    else if (precedence(operators) > precedence1)
    {

        s.push(operators);
        precedence1 = precedence(operators);
    }
    else if (precedence(operators) < precedence1)
    {

        while (!s.empty())
        {

            if (s.top() == "(")
            {
                break;
            }

            g1.push_back(s.top());

            cout << '\t' << s.top();
            s.pop();
        }

        cout << '\n'
             << "precedence update" << endl;
        s.push(operators);
        precedence1 = precedence(operators);
    }
}

// if is operator
int is_operator(string symbol)
{
    if (symbol == "(" || symbol == ")" || symbol == "^" || symbol == "*" || symbol == "/" || symbol == "%" || symbol == "+" || symbol == "-")
    {
        return 1;
    }
    else
        return 0;
}

// is digit
bool is_number(string n)
{
    char *c = const_cast<char *>(n.c_str());
    // std::string::size_type sz; // alias of size_t
    // double number = std::stod(n, &sz);

    if (isdigit(*c))
    {
        return true;
    }
    else if (*c == '.')
        return true;

    else if (*c == 'p')
        return true;
    else if (*c == 'i')
        return true;
    else if (*c == 'e')
        return true;
    else
        return false;
}

//calculate precedence
int precedence(string symbol)
{

    if (symbol == "^") /* exponent operator, highest precedence*/
    {
        return (4);
    }
    else if (symbol == "*" || symbol == "/" || symbol == "%")
    {
        return (3);
    }
    else if (symbol == "+" || symbol == "-")
    {
        return (2);
    }
    else if (symbol == "pi" || symbol == "e") /* lowest precedence */
    {
        return (1);
    }
    else
        return 0;
}
void stackchecker()
{
    //     for (int i = 0; i < sizes; i++)
    //     {
    //         cout << c[i] << endl;
    //}

    // cout << "The stack is : ";

    // cout << "\ns.size() : " << s.size();
    // cout << "\ns.top() : " << s.top();

    // cout << "\ns.size() : " << s.size();
    // cout << "\ns.top() : " << s.top();

    cout << "The stack is : ";
    while (!s.empty())
    {
        cout << '\t' << s.top();
        s.pop();
    }
    cout << '\n';
}

//features c++ 14
template <typename T>
T pi = T(3.141592653589793238462643383);
template <typename T>
T e = T(2.71828);

void evaluate_expressions()
{
    //*i it has the result
    double x = 0;
    double y = 0;
    double digits = 0;
    string op;
    string::size_type sz;

    for (auto i = g1.begin(); i != g1.end(); ++i) // 2 feature en 1  (auto i = g1->cbegin(); i != g1.end() feature c++ 11
    {
        if (1 == is_number(*i))
        {

            if (*i == "pi")
            {
                s2.push(pi<double>);
            }
            else if (*i == "e")
            {
                s2.push(e<double>);
            }
            else
            {

                cout << "is number" << endl;
                digits = stod(*i, &sz); // c++ 11 stod
                s2.push(digits);
            }
        }
        else if (is_operator(*i))
        {

            op = *i;
            cout << '\n';
            cout << "operator: " << op << endl;
            // cout << '\t' << s.top();
            x = s2.top();
            // x = stod(s.top().substr(sz));
            s2.pop();
            y = s2.top();
            s2.pop();
            cout << '\n';
            cout << "variable in x : " << x << endl;
            // y = stod(s.top().substr(sz));
            cout << "variable in y : " << y << endl;
            cout << '\n';
            if (*i == "/" && y == 0 || *i == "%" && y == 0 || *i == "%" && x == 0 || *i == "/" && x == 0)
                isdenominatorz = true;

            result = operation(y, x, op);
            s2.push(result);
            cout << "result :" << result << endl;
            if (isdenominatorz == true)
                cout << "\033[1;31m Error#105 (Math Error Denominator undefined = 0) \033[0m\n";
        }
    }
}

double operation(double a, double b, string opr)
{

    char cstr[opr.size() - 1];
    strcpy(cstr, opr.c_str());

    switch (*cstr)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '%':
        return fmod(a, b);
    case '^':
        return pow(a, b);
    default:
        return 0;
    }
}

void print_posfix()
{
    cout << endl
         << endl;
    cout << "infix form: " << inf << endl
         << endl;
    cout << "posfix form: ";
    for (auto i = g1.begin(); i != g1.end(); ++i)
        cout << *i << " ";

    cout << endl;

    int *i = nullptr; //c++11 nullptr
}

//--------------------validate_expresion--------------------------//

// c++ 14 auto function
auto operators_check(string symbol)
{
    if (symbol == "^" || symbol == "*" || symbol == "/" || symbol == "%" || symbol == "+" || symbol == "-")
    {
        return 1;
    }

    else
        return 0; //Return type deduction
}

void valid_expresion(string infix)
{

    int c_parenthesis = 0;
    bool op = false;
    bool op2;
    bool op3;
    bool isdenominatorz;
    for (int i = 0; i < sizes; i++)
    {
        string firstchar = infix.substr(i, 1);
        string nextchar = infix.substr(i + 1, 1);

        if (1 == operators_check(firstchar) && i == 0)
        {
            op3 = true;
            break;
        }

        if (firstchar == "(" || firstchar == ")")
        {
            if (firstchar == "(" && operators_check(nextchar))
            {
                op3 = true;
                break;
            }
            c_parenthesis++;
        }

        if (is_number(firstchar) || 1 == is_operator(firstchar))
        {
            op = true;
        }
        else
        {
            op = false;
            break;
        }

        if (1 == operators_check(firstchar) && 1 == operators_check(nextchar))
        {
            op2 = true;
            break;
        }
        if (1 == operators_check(firstchar) && nextchar == "" || 1 == operators_check(firstchar) && nextchar == ")")
        {
            op3 = true;
            break;
        }

        // if (firstchar == "/" && nextchar == "0" || firstchar == "%" && nextchar == "0" || firstchar == "0" && nextchar == "/" || firstchar == "0" && nextchar == "%")
        // {
        //     isdenominatorz = true;
        //     break;
        // }
    }

    if (op == true)
    {
        cout << "pass" << endl;
    }
    else
    {
        cout << handle.error102;
        exit(3);
    }

    if (op2 == true)
    {
        cout << handle.error103;
        exit(3);
    }
    else
    {
        cout << "pass" << endl;
    }

    if (op3 == true)
    {
        cout << handle.error104;
        exit(3);
    }
    else
    {
        cout << "pass" << endl;
    }

    // if (isdenominatorz == true)
    // {
    //     cout << "\033[1;31m Error#105 (Math Error Denominator is 0 ) \033[0m\n";
    //     exit(3);
    // }
    // else
    // {
    //     cout << "pass" << endl;
    // }

    if (c_parenthesis % 2 == 0)
    {
        [](string a) { cout << a << endl; }(handle.pass); //c++17 lambda expresion
    }
    else
    {

        cout << handle.error101;
        exit(3);
    }
}

void Pruebas(string op, double p1)
{

    evaluador(op);
    evaluate_expressions();

    if (p1 == result)
    {

        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl;

        cout << "TDD: "
             << "\033[1;32m  Passed \033[0m\n";
    }
    else
    {
        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl;

        cout << "TDD: "
             << "\033[1;31m  Failed \033[0m\n";
    }
}

void Tests_TDD()
{
    cout << "******************TDD********************" << endl;

    int eval = 0;

    cout << "Que opcion desea evaular ? " << endl;
    cin >> eval;

    if constexpr (0 || nullptr) //c++17 rite code that is instantiated depending on a compile-time condition.
    {
        cout << "test son de 1 en adelante;" << endl;
    }

    switch (eval)
    {
    case 1:
        Pruebas("10+(1+2)*2+2", 18); // el resultado tiene que ser 18
        cout << "Prueba : 1   operation: 10+(1+2)*2+2, input: 10" << endl;

        break;

    case 2:
        Pruebas("(6+2)*3/2^2-4", 10); // el resultado tiene que ser 2
        cout << "Prueba : 2   operation: 10+(1+2)*2+2, input: 10" << endl;
        break;
    case 3:
        Pruebas("(6+10(10+1))*2", 42); // el resultado tiene que ser 42
        cout << "Prueba : 3   operation: 10+(1+2)*2+2, input: 10" << endl;
        break;
    case 4:
        Pruebas("((8+(1+2)/15))", 8); // el resultado tiene que ser 8.2
        cout << "Prueba : 4   operation: 10+(1+2)*2+2, input: 10" << endl;
        break;
    case 5:
        Pruebas("2*(1+(4*(2+1)+3))", 32); // el resultado tiene que ser 32
        cout << "Prueba : 5   operation: 10+(1+2)*2+2, input: 10" << endl;
        break;
    case 6:
        Pruebas("2*20/2+(3+4)*3^2-6+15", 10); // el resultado tiene que ser 92
        cout << "Prueba : 6   operation: 10+(1+2)*2+2, input: 10" << endl;
        break;
    case 7:
        Pruebas("5*(6+2)-12/4", 10); // el resultado tiene que ser 37
        cout << "Prueba : 7   operation: 10+(1+2)*2+2, input: 10" << endl;
        break;
    case 8:
        Pruebas("1^2*20/2+(3+4)*3^2-6+15", 10); // el resultado tiene que ser 82
        cout << "Prueba : 8   operation: 10+(1+2)*2+2, input: 10" << endl;
        break;
    case 9:
        Pruebas("(e+pi)*e/pi^2-4", 10); // el resultado tiene que ser -2.38608
        cout << "Prueba : 9   operation: 10+(1+2)*2+2, input: 10" << endl;
        break;

    default:
        break; // [[fallthrough]]c++17 indicates to the compiler that falling through in a switch statement is intended behavior.
    }
}