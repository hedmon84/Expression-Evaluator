#include "evaluador.hpp"

int sizes;
stack<string> s;          // stack2
stack<double> s2;         // numbers stacl
vector<string> g1;        //posfix
vector<double> numscheck; //numscheck
int precedence1 = 0;
int counter = 0;
int precedence2;
string inf;
string c_operator;

// revisar lo de los parentesis () presedencia maxima
// (6+2)*3/2^2-4      pass
// (6+10(10+1))*2     pass
// 1^2/(5*3)+10       pass
//((10+(6+2)*3)/((2^2)-4))
//8^((5*((5*2)+(18/2)))/1000)
// (8+(1+2)/15) res = 812+15/+

// evaluador machine
void evaluador(string infix)
{
    inf = infix;
    // string c[100];
    string numbers;
    // num size count

    sizes = infix.size();

    // for (int i = 0; i < infix.size() + 1; i++)
    // {

    //     c[i] = infix[i];
    //     if (is_number(c[i]))
    //     {
    //         numbers += c[i];
    //     }

    //     // if (is_operator(c[i]) || i >= sizes)
    //     // {

    //     //     if (c[i] == "(")
    //     //     {
    //     //     }
    //     //     if (counter >= 1)
    //     //     {
    //     //         numscheck.push_back(counter);
    //     //         counter = 0;
    //     //     }
    //     // }
    // }

    for (int i = 0; i < sizes; i++)
    {
        //gets every character of the string
        string exp = infix.substr(i, 1);

        //operator evaluation
        if (1 == is_operator(exp))
        {
            cout << "is operator" << endl;

            //validations
            if (exp == ")")
            {
                if (exp == ")")
                {

                    while (!s.empty())
                    {
                        if (s.top() == "^" || s.top() == "*" || s.top() == "/" || s.top() == "%" || s.top() == "+" || s.top() == "-" || s.top() == "pi" || s.top() == "e")
                        {
                            g1.push_back(s.top());
                        }

                        precedence1 = 0;
                        cout << '\t' << s.top();
                        s.pop();
                    }
                    cout << '\n'
                         << "empty stack";
                }

                else if (exp == "(")
                {
                }
                else
                    s.push(exp);
            }

            else if (exp == c_operator)
            {
                s.push(exp);
            }
            else
            {
                stack2(exp);
            }
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

        g1.push_back(s.top());

        cout << '\t' << s.top();
        s.pop();
    }
}

//stack machine
void stack2(string operators)
{
    //precedence check
    c_operator = operators;

    if (precedence(operators) == precedence1)
    {
        while (!s.empty())
        {

            g1.push_back(s.top());

            cout << '\t' << s.top();
            s.pop();
        }
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

        if (s.top() == "(")
        {
            s.pop();

            cout << '\n'
                 << "pop ( " << endl;

            cout << '\n'
                 << "( deleted and precedence update" << endl;
            s.push(operators);
            precedence1 = precedence(operators);
        }
        else
        {
            while (!s.empty())
            {

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

    else
    {
        s.push(operators);
        g1.push_back(s.top());
        s.pop();
        precedence1 = precedence(operators);
    }
}

// if is operator
int is_operator(string symbol)
{
    if (symbol == "(" || symbol == ")" || symbol == "^" || symbol == "*" || symbol == "/" || symbol == "%" || symbol == "+" || symbol == "-" || symbol == "pi" || symbol == "e")
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
    else
        return false;
}

//calculate precedence
int precedence(string symbol)
{

    if (symbol == "(") /* exponent operator, highest precedence*/
    {
        return (5);
    }

    else if (symbol == "^") /* exponent operator, highest precedence*/
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

void evaluate_expressions()
{
    //*i is has the result
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
            cout << "is number" << endl;
            digits = stod(*i, &sz);
            s2.push(digits);
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
    case 'p':
        return fmod(a, b);
    case 'e':
        return fmod(a, b);
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