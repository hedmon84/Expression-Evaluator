#include "evaluador.hpp"

int sizes;
stack<string> s;          // stack2
vector<string> g1;        //posfix
vector<double> numscheck; //numscheck
int precedence1 = 0;
int counter = 0;
int precedence2;
string inf;
string c_operator;

// (66+222)*3333/22222^222222-444444

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
            if (exp == ")" || exp == "(")
            {
                if (exp == ")")
                {

                    while (!s.empty())
                    {
                        if (s.top() == "^" || s.top() == "*" || s.top() == "/" || s.top() == "%" || s.top() == "+" || s.top() == "-" || s.top() == "pi" || s.top() == "e")
                        {
                            g1.push_back(s.top());
                        }

                        cout << '\t' << s.top();
                        s.pop();
                    }
                    cout << '\n'
                         << "empty stack";
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

void evaluate_expressions()
{
    //*i is has the result
    for (auto i = g1.begin(); i != g1.end(); ++i)
    {
        if (is_operator(*i))
        {
            cout << "operator found" << *i << endl;
        }
    }
}

int operation(int a, int b, char opr)
{
    switch (opr)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
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
