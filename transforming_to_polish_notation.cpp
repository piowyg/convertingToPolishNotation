// transforming_to_polish_notation.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//


#include <iostream>
#include <string>
#include<stack>
#include<algorithm>
#include<vector>
#include<list>
using namespace std;




/*

    Program to convert logic sentence into polish notation(prefix form).

  IN string s place's write your logic sentence to convert into polish notation(prefix form).
  Use that operations symbols:
  - Conjunction -> K,
  - Disjjunction -> A,
  - Implication-> C,
  - Equivalence -> E,
  -Negation - N

  Please remember about brackets in right places, fg

  N(pCq) != NpCq

  Also is important that for now you can use as variables in sentence only :
  -p
  -q
  -r
  -s
  -t


  Author: Piotr Wygocki
  */


bool isOperator(char c)
{
   return (!(c == 'p') && !(c == 'q') && !(c == 'r') && !(c == 's') && !(c == 't'));
}

int getPriority(char C)
{   /*
    C-> I
    A -> V
    K -> O
    E -> R
    */
    if (C == 'K' || C == 'A' || C == 'V' || C == 'O')
        return 1;
    else if (C == 'C' || C == 'E' || C == 'I' || C == 'R')
        return 2;
    return 0;
}

string infixToPrefix(string infix)
{
    stack<char> operators;
    stack<string> operands;

    for (int i = 0; i < infix.length(); i++) {

        if (infix[i] == 'N') continue;
        if (infix[i] == '(') {
            operators.push(infix[i]);
        }
        else if (infix[i] == ')') {
            while (!operators.empty() &&
                operators.top() != '(') {

                string op1 = operands.top();
                operands.pop();

                string op2 = operands.top();
                operands.pop();

                char op = operators.top();
                operators.pop();

                string tmp = op + op2 + op1;
                operands.push(tmp);
            }
            operators.pop();
        }
        else if (!isOperator(infix[i])) {
            operands.push(string(1, infix[i]));
        }
        else {
            while (!operators.empty() &&
                getPriority(infix[i]) <=
                getPriority(operators.top())) {

                string op1 = operands.top();
                operands.pop();

                string op2 = operands.top();
                operands.pop();

                char op = operators.top();
                operators.pop();

                string tmp = op + op2 + op1;
                operands.push(tmp);
            }

            operators.push(infix[i]);
        }
    }
    while (!operators.empty()) {
        string op1 = operands.top();
        operands.pop();

        string op2 = operands.top();
        operands.pop();

        char op = operators.top();
        operators.pop();

        string tmp = op + op2 + op1;
        operands.push(tmp);
    }
    return operands.top();
}

int main()
{   /*
    
    IN string s place's write your logic sentence to convert into polish notation(prefix form).
    Use that operations symbols:
    - Conjunction -> K,
    - Disjjunction -> A,
    - Implication-> C,
    - Equivalence -> E,
    -Negation - N

    Please remember about brackets in right places, fg

    N(pCq) != NpCq

    Also is important that for now you can use as variables in sentence only :
    -p
    -q
    -r
    -s
    -t

    */
    string s = "(N(pCq)C((qCr)C(pCr)))";
    vector <pair<char, int>> wp;
    int var = 0;
    int var2 = 0;
    int temp = 0;
    for (int i = 0; i < s.length(); i++)
    {
        var = 0;
        var2 = 0;
        if (s[i] == 'N') {
            i++;
            if (s[i] > 'a' && s[i] < 'z')
            {

                for (int j = 0; j <= i; j++)
                {
                    if (s[i] == s[j])
                    {
                        var++;
                    }
                }
                wp.push_back(make_pair(s[i], var));
                i--;
            }
            else if (s[i] == 'N') continue;
            else if (s[i] == '(') {
                var2++;
                i++;
                temp = i;
                if (s[temp] == 'N') continue;
                while (s[temp] == '(') {
                    temp++;
                    var2++;
                }
                i--;
                for (int j = i; j < s.length(); j++)
                {

                    if (s[j] == 'C' || s[j] == 'K' || s[j] == 'A' || s[j] == 'E')
                    {
                        var2--;
                        if (var2 == 0)
                        {
                            switch (s[j])
                            {
                            case 'C':
                                s[j] = 'I';
                                break;
                            case 'E':
                                s[j] = 'R';
                                break;
                            case 'K':
                                s[j] = 'O';
                                break;
                            case 'A':
                                s[j] = 'V';
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    string prefix = infixToPrefix(s);
    int length = prefix.length();
    list<char> mylist;
    for (int i = 0; i < length; i++)
    {
        mylist.push_back(prefix[i]);
    }
    int number = 0;
    for (int i = 0; i < wp.size(); i++)
    {

        number = 0;
        for (list<char>::iterator it = mylist.begin(); it != mylist.end(); ++it)
        {
            if (wp[i].first == *it)
            {

                number++;
                if (number == wp[i].second)
                {

                    mylist.insert(it, 'N');

                    break;
                }
            }
        }

    }
    int counter = 0;
    for (list<char>::iterator it = mylist.begin(); it != mylist.end(); ++it)
    {
        switch (*it)
        {
        case 'I':
            *it = 'C';
            if (counter == 0)
            {
                mylist.push_front('N');
            }
            else {

                mylist.insert(it, 'N');

            }
            break;
        case 'R':
            *it = 'E';
            if (counter == 0)
            {
                mylist.push_front('N');
            }
            else {

                mylist.insert(it, 'N');

            }
            break;
        case 'O':
            *it = 'K';
            if (counter == 0)
            {
                mylist.push_front('N');
            }
            else {

                mylist.insert(it, 'N');

            }
            break;
        case 'V':
            *it = 'A';
            if (counter == 0)
            {
                mylist.push_front('N');
            }
            else {

                mylist.insert(it, 'N');

            }
            break;
        }
        counter++;
    }

    for (auto x : mylist)
    {
        cout << x;
    }
    cout << "\n\n";
    return 0;
}
