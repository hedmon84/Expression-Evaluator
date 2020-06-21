#include "evaluador.hpp"

int sizes;
stack<string> s;          // stack2
stack<double> s2;         // numbers stacl
vector<string> g1;        //posfix
vector<double> numscheck; //numscheck
int precedence1 = 0;      // precedence saver
string inf;
// (6+2)*3/2^2-4            pass
// (6+10(10+1))*2           pass
// 1^2/(5*3)+10             pass
// ((8+(1+2)/15))           pass
//8^(5*(5*2)+(18/2))/1000  pass
//(1+1.5)*(2+300)           pass
//(pi+pi)*pi/pi^pi-pi       pass
//(e+e)*e/e^e-e             pass
// (e+pi)*e/pi^2-4          pass
// 5*(6+2)-12/4             pass
//---------------error Test-------------------------
// 1+1//(1-1)1             pass
// 11+11(1-1)1-            pass
// (1+1/(1-1)1             pass
// +11+11(1-1)1            pass
// 11+11(1-1-)1            pass
// 11+11(-1-1)1            pass
// 11/11(1-1)1              pass
// 11%0(1-1)1              pass
// evaluador machine
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

//features c++ 14/17
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
    double result = 0;
    string op;
    string::size_type sz;

    for (auto i = g1.begin(); i != g1.end(); ++i)
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
                digits = stod(*i, &sz);
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

            result = operation(y, x, op);
            s2.push(result);
            cout << "result :" << result << endl;
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

double answer()
{
    return 1;
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
}

//--------------------validate_expresion--------------------------//

int operators_check(string symbol)
{
    if (symbol == "^" || symbol == "*" || symbol == "/" || symbol == "%" || symbol == "+" || symbol == "-")
    {
        return 1;
    }
    else
        return 0;
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

        if (firstchar == "/" && nextchar == "0" || firstchar == "%" && nextchar == "0" || firstchar == "0" && nextchar == "/" || firstchar == "0" && nextchar == "%")
        {
            isdenominatorz = true;
            break;
        }
    }

    if (op == true)
    {
        cout << "pass" << endl;
    }
    else
    {
        cout << "\033[1;31m Error#102 (Character not allowed) \033[0m\n";
        exit(3);
    }

    if (op2 == true)
    {
        cout << "\033[1;31m Error#103 (Character not allowed) \033[0m\n";
        exit(3);
    }
    else
    {
        cout << "pass" << endl;
    }

    if (op3 == true)
    {
        cout << "\033[1;31m Error#104 (Few Arguments) \033[0m\n";
        exit(3);
    }
    else
    {
        cout << "pass" << endl;
    }

    if (isdenominatorz == true)
    {
        cout << "\033[1;31m Error#105 (Math Error Denominator is 0 ) \033[0m\n";
        exit(3);
    }
    else
    {
        cout << "pass" << endl;
    }

    if (c_parenthesis % 2 == 0)
    {
        cout << "pass" << endl;
    }
    else
    {
        cout << "\033[1;31m Error#101 (Parentheses Mismatched) \033[0m\n";
        exit(3);
    }
}