#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
#include <stdexcept>

class RPNCalculator {
private:
    std::stack<double> stack;

public:
    void push(double value) {
        stack.push(value);
    }

    double pop() {
        if (stack.empty()) {
            throw std::runtime_error("错误：栈为空");
        }
        double top = stack.top();
        stack.pop();
        return top;
    }

    void calculate(const std::string& op) {
        if (op == "+") {
            double b = pop(), a = pop();
            push(a + b);
        } else if (op == "-") {
            double b = pop(), a = pop();
            push(a - b);
        } else if (op == "*") {
            double b = pop(), a = pop();
            push(a * b);
        } else if (op == "/") {
            double b = pop(), a = pop();
            if (b == 0) throw std::runtime_error("错误：除零");
            push(a / b);
        } else {
            throw std::invalid_argument("错误：未知操作符");
        }
    }

    void clear() {
        while (!stack.empty()) stack.pop();
    }

    void display() {
        std::stack<double> temp = stack;
        std::cout << "当前栈: ";
        while (!temp.empty()) {
            std::cout << temp.top() << " ";
            temp.pop();
        }
        std::cout << std::endl;
    }

    bool isEmpty() const {
        return stack.empty();
    }

    double getTop() const {
        return stack.top();
    }
};

int main() {
    RPNCalculator calc;
    std::string input;
    std::cout << "C++ RPN 计算器\n输入表达式(例: '5 5 +'), 或 'q' 退出, 'c' 清空栈, 'd' 显示栈\n> ";

    while (std::getline(std::cin, input)) {
        if (input == "q") break;
        if (input == "c") {
            calc.clear();
            std::cout << "栈已清空\n> ";
            continue;
        }
        if (input == "d") {
            calc.display();
            std::cout << "> ";
            continue;
        }

        std::istringstream iss(input);
        std::string token;
        try {
            while (iss >> token) {
                if (token == "+" || token == "-" || token == "*" || token == "/") {
                    calc.calculate(token);
                } else {
                    // 尝试转换为数字
                    double num = std::stod(token);
                    calc.push(num);
                }
            }
            if (!calc.isEmpty()) {
                std::cout << "结果: " << calc.getTop() << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << "> ";
    }
    return 0;
}
