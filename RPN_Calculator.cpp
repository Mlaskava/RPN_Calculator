#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <set>

std::string securePop(std::stack<std::string> &stack) {
    if (!stack.empty()) {
        std::string temp = stack.top();
        stack.pop();
        return temp;
    } else {
        std::cout << "Stos pusty!" << std::endl;
        exit(EXIT_FAILURE);
    }

}

void calculate(std::stack<std::string> &stack) {

    std::string operation = securePop(stack);
    double l2 = stod(securePop(stack));
    double l1 = stod(securePop(stack));

    if (operation == "^") {
        stack.push(std::to_string(pow(l1, l2)));
    }

    if (operation == "*") {
        stack.push(std::to_string(l1 * l2));
    }

    if (operation == "/") {
        stack.push(std::to_string(l1 / l2));
    }

    if (operation == "+") {
        stack.push(std::to_string(l1 + l2));
    }

    if (operation == "-") {
        stack.push(std::to_string(l1 - l2));
    }
}

void pushAndCheck(std::stack<std::string> &stack, char c) {

    stack.push(std::string(1, c));
    std::set<char> set = {'+', '-', '*', '/', '^'};
    if (set.find(c) != set.end()) {
        calculate(stack);
    }
}

std::stack<std::string> convert(std::string &expr) {

    std::map<std::string, int> map = {{"+", 1},
                                      {"-", 1},
                                      {")", 1},
                                      {"*", 2},
                                      {"/", 2},
                                      {"^", 3}};

    std::stack<std::string> stack = {};
    std::stack<std::string> signs = {};
    std::string temp;
    for (std::string::iterator i = expr.begin(); i != expr.end(); ++i) {

        if (isdigit(*i)) {


            temp += *i;

            while (i + 1 != expr.end() && isdigit(*(i + 1))) {
                ++i;
                temp += *i;
            }
            stack.push(temp);
            temp.clear();

        } else if (*i == '(') {
            signs.push("(");

        } else if (*i == ')') {
            while (signs.top() != "(") {
                pushAndCheck(stack, signs.top().at(0));

                signs.pop();
            }
            signs.pop();
        } else if (map.find(std::string(1, *i)) != map.end()) {

            if (*i == '-') {
                if (i == expr.begin() || (!isdigit(*(i - 1)) && *(i - 1) != '(') && *(i - 1) != ')') {
                    temp += '-';
                    continue;
                }
            }

            int priority = map.find(std::string(1, *i))->second;

            if (signs.empty() || ((map.find(signs.top()) != map.end() && (map.find(signs.top())->second < priority)))) {

                signs.push(std::string(1, *i));

            } else {

                while (!signs.empty()) {
                    if (map.find(signs.top()) != map.end() && map.find(signs.top())->second >= priority) {
                        pushAndCheck(stack, signs.top().at(0));
                        signs.pop();
                    } else {
                        break;
                    }

                }
                signs.push(std::string(1, *i));
            }

        }

    }
    while (!signs.empty()) {
        pushAndCheck(stack, signs.top().at(0));
        signs.pop();
    }
    return stack;
}


int main() {
    std::string s;
    std::cin >> s;
    std::stack<std::string> stack = convert(s);
    std::cout << stack.top() << " ";

}
