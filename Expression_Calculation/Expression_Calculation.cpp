
#include <iostream>
#include <stack>

int priority(const char& symbol);
bool is_digit(const char& symbol);
bool is_operator(const char& symbol);

std::string makeReverseNotation(const std::string& s);
int calculate(const std::string& reverseNotation);



int priority(const char& symbol)
{
    if (symbol == '+' || symbol == '-') {
        return 1;
    }
    else if (symbol == '*' || symbol == '/') {
        return 2;
    }
    else if (symbol == '^') {
        return 3;
    }
    else {
        return 0;
    }
}

bool is_digit(const char& symbol)
{
    return (symbol >= '0' && symbol <= '9');
}

bool is_operator(const char& symbol)
{
    return (symbol == '+' || symbol == '-' ||
        symbol == '*' || symbol == '/' ||
        symbol == '^');
}

std::string makeReverseNotation(const std::string& s)
{
    std::stack<char> st;
    std::string result = "";

    for (int i = 0; i < s.length(); ++i) {
        if (is_digit(s[i])) {
            result += s[i];
        }
        else if (s[i] == '(') {
            st.push(s[i]);
        }
        else if (s[i] == ')') {
            while (st.top() != '(') {
                result += st.top();
                st.pop();
            }
            st.pop();
        }
        else if (is_operator(s[i])) {
            while (!st.empty() && priority(st.top()) >= priority(s[i])) {
                result += st.top();
                if (st.top() == '-') {
                    st.pop();
                    break;
                }
                st.pop();
            }
            if (s[i] == '-' && (i == 0 || s[i - 1] == '(')) {
                result += '0';
                st.push(s[i]);
            }
            else if (s[i] == '-') {
                st.push(s[i]);
                st.push('+');
                result += '0';
            }
            else {
                st.push(s[i]);
            }
        }
        else {
            while (!st.empty()) {
                if (s[i] == '-' && i > 0 && s[i - 1] == '(') {
                    st.push(s[i]);
                }
                else if (s[i] == '-') {
                    st.push('+');
                    st.push(s[i]);
                }
                else {
                    st.push(s[i]);
                }
            }
            st.push(s[i]);
        }
    }
    while (!st.empty()) {
        char temp = st.top();
        st.pop();
        if (!st.empty() && st.top() != '-') {
            result += temp;
        }
        else if (!st.empty() && st.top() == '-') {
            result += st.top();
            result += temp;
            st.pop();
        }
        else {
            result += temp;
        }
    }

    return result;
}

int calculate(const std::string& reverseNotation)
{
    std::stack<int> st;
    
    for (int i = 0; i < reverseNotation.length(); ++i) {
        if (!is_operator(reverseNotation[i])) {
            st.push(reverseNotation[i] - 48);
        }
        else {
            int temp;
            if (reverseNotation[i] == '+') {
                temp = st.top();
                st.pop();
                temp += st.top();
                st.pop();
                st.push(temp);
            }
            else if (reverseNotation[i] == '-') {
                temp = st.top();
                st.pop();
                st.top() -= temp;
            }
            else if (reverseNotation[i] == '*') {
                temp = st.top();
                st.pop();
                temp *= st.top();
                st.pop();
                st.push(temp);
            }
            else if (reverseNotation[i] == '/') {
                temp = st.top();
                st.pop();
                temp = st.top() / temp;
                st.pop();
                st.push(temp);
            }
            else if (reverseNotation[i] == '^') {
                temp = st.top();
                st.pop();
                temp = pow(st.top(), temp);
                st.pop();
                st.push(temp);
            }
        }
    }
    return st.top();
}
