/**
* @file prob1.cpp
* @brief This Cpp file is a program to add and multiply two ploynomial expressions using data structures.
*
* @author Prathamesh Katkar
*
* @date 02/10/2019
*/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
/**
* This method addExpression() will be used to add two polynomial expressions.
* @param map<int, int> expression1, map<int, int> expression2
* @date 02/10/2019
*/
map<int, int> addExpression(map<int, int> expression1, map<int, int> expression2)
{
    map<int, int> expression;
    expression.insert(expression1.begin(), expression1.end());
    map<int, int>::iterator it1;
    for (it1 = expression2.begin(); it1 != expression2.end(); ++it1)
    {
        int key = it1->first;
        auto it = expression.find(key);
        if (it == expression.end())
            expression[key] = it1->second;
        else
            it->second = it->second + it1->second;
    }
    return expression;
}
/**
* This method multiplyExpression() will be used to multiply two polynomial expressions.
* @param map<int, int> expression1, map<int, int> expression2
* @date 02/10/2019
*/
map<int, int> multiplyExpression(map<int, int> expression1, map<int, int> expression2)
{
    map<int, int> expression;
    map<int, int>::iterator it1, it2;
    for (it1 = expression1.begin(); it1 != expression1.end(); ++it1)
    {
        for (it2 = expression2.begin(); it2 != expression2.end(); ++it2)
        {
            int key = it1->first + it2->first;
            auto it = expression.find(key);
            if (it == expression.end())
                expression[key] = it1->second * it2->second;
            else
                it->second = it->second + (it1->second * it2->second);
        }
    }
    return expression;
}
/**
* This method printEpression() will be used to print the polynomial expression.
* @param map<int, int> expression1
* @date 02/10/2019
*/
void printEpression(map<int, int> expression)
{
    map<int, int>::iterator it;
    cout << "Coefficient\tPower" << endl;
    for (it = expression.end(); it != expression.begin();)
    {
        it--;
        cout << it->second << "\t\t" << it->first << endl;
    }
}
/**
* This method takeInput() will be used to take input of the polynomial expression.
* @param int expressionCount
* @date 02/10/2019
*/
map<int, int> takeInput(int expressionCount)
{
    string s = "";
    switch (expressionCount)
    {
    case 1:
        s = "first";
        break;
    case 2:
        s = "second";
        break;
    default:
        break;
    }
    cout << "Enter the number of terms in the " << s << " expression." << endl;
    int no_of_terms;
    cin >> no_of_terms;
    cout << "Enter the coefficients with their corresponding powers." << endl;
    map<int, int> expression;
    int key, value;
    for (int i = 0; i < no_of_terms; i++)
    {
        cin >> value;
        cin >> key;
        expression[key] = value;
    }
    return expression;
}

int main(int argc, char const *argv[])
{
    //Driver program
    map<int, int> expression1, expression2;
    expression1 = takeInput(1);
    expression2 = takeInput(2);
    while (true)
    {
        cout << "Enter the index values to perform the corresponding commands." << endl;
        cout << "1. Add the expressions." << endl;
        cout << "3. Multiply the expressions" << endl;
        cout << "3. Take new values" << endl;
        cout << "4. Exit" << endl;
        int commandIndex;
        cin >> commandIndex;
        switch (commandIndex)
        {
        case 1:
            printEpression(addExpression(expression1, expression2));
            break;
        case 2:
            printEpression(multiplyExpression(expression1, expression2));
            break;
        case 3:
            expression1 = takeInput(1);
            expression2 = takeInput(2);
            break;
        case 4:
            exit(0);
            break;
        default:
            break;
        }
    }
    return 0;
}
