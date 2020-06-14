#include "evaluador.hpp"

int sizes;
stack<string> s;   // stack2
vector<string> g1; //posfix
int precedence1 = 0;
int precedence2;
string inf;
// (6+2)*3/2^2-4

void evaluador(string infix)
{
    inf = infix;
    string c[100];

    sizes = infix.size();

    for (int i = 0; i < infix.size(); i++)
    {
        c[i] = infix[i];
    }

    for (int i = 0; i < sizes; i++)
    {
        string exp = c[i];

        if (1 == is_operator(exp))
        {
            cout << "is operator" << endl;

            if (exp == ")" || exp == "(")
            {
                if (exp == ")")
                {

                    while (!s.empty())
                    {
                        if (s.top() == "+")
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
            else
            {
                stack2(exp);
            }
        }

        else if (is_number(exp))
        {
            cout << "is number" << endl;
            g1.push_back(exp);
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

void stack2(string operators)
{
    //precedence check

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
int is_operator(string symbol)
{
    if (symbol == "(" || symbol == ")" || symbol == "^" || symbol == "*" || symbol == "/" || symbol == "%" || symbol == "+" || symbol == "-" || symbol == "p" || symbol == "i" || symbol == "e")
    {
        return 1;
    }
    else
        return 0;
}

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
    cout << endl
         << endl;
    cout << "posfix form: ";
    for (auto i = g1.begin(); i != g1.end(); ++i)
        cout << *i << " ";

    cout << endl;
}
