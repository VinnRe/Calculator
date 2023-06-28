#include <iostream>
using namespace std;

bool isNan(double num) {
    return num != num;  // NaN is the only value that is not equal to itself
}

class Calculation {
public:
    string expression;
    double result;
    Calculation* next;

    Calculation(const string& exp, double res) : expression(exp), result(res), next(nullptr) {}
};

class History {
private:
    const int MAX_SIZE = 100;
    Calculation* head;
    Calculation* tail;
    int count;

public:
    History() : head(nullptr), tail(nullptr), count(0) {}

    void addToHistory(Calculation* calc) {
        if (count >= MAX_SIZE) {
            Calculation* oldestCalc = head;
            head = head->next;
            delete oldestCalc;
            count--;
        }

        if (head == nullptr) {
            head = calc;
            tail = calc;
        }
        else {
            tail->next = calc;
            tail = calc;
        }

        count++;
        cout << "Added to history. Address: " << calc << endl;
    }

    void showHistory() {
        cout << "[ ======== History ======== ]" << endl;
        Calculation* current = head;
        while (current != nullptr) {
            cout << "Equation: " << current->expression << " = " << current->result << " Address: " << current << endl;
            current = current->next;
        }
    }

    void clearHistory() {
        Calculation* current = head;
        while (current != nullptr) {
            Calculation* temp = current;
            current = current->next;
            delete temp;
        }

        head = nullptr;
        tail = nullptr;
        count = 0;
    }
};

class Calculator {
private:
    History history;

    double calcBrain(const string& expression) {
        double result = 0.0;
        double number = 0.0;
        char op = '+';
        int i = 0;

        while (i < expression.length()) {
            if (expression[i] >= '0' && expression[i] <= '9') {
                number = 0.0;
                while (i < expression.length() && expression[i] >= '0' && expression[i] <= '9') {
                    number = number * 10 + (expression[i] - '0');
                    i++;
                }

                switch (op) {
                    case '+':
                        result += number;
                        break;
                    case '-':
                        result -= number;
                        break;
                    case '*':
                        result *= number;
                        break;
                    case '/':
                        if (number != 0.0)
                            result /= number;
                        else
                            return 0.0 / 0.0;  // Return NaN if there is a division by zero
                        break;
                }
            }
            else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
                op = expression[i];
                i++;
            }
            else {
                return 0.0 / 0.0;  // Return NaN if an invalid character is encountered
            }
        }

        return result;
    }

public:
    void mainCalc() {
        string expression;
        cout << "Enter an expression: ";
        getline(cin, expression);

        double result = calcBrain(expression);
        if (!isNan(result)) {
            cout << "Result: " << result << endl;

            Calculation* calc = new Calculation(expression, result);
            history.addToHistory(calc);
        }
        else {
            cout << "Invalid input or mathematical error." << endl;
        }
    }

    void run() {
        bool continueCalc = true;

        while (continueCalc) {
            mainCalc();

            char choice;
            cout << "Do you want to input a new expression? ( Y | N ): ";
            cin >> choice;
            cin.ignore();
            while (true) {
                if (choice == 'Y' || choice == 'y') {
                    break;
                }
                else if (choice == 'N' || choice == 'n') {
                    continueCalc = false;
                    cout << "Ending program.\n";
                    break;
                }
                else {
                    cout << "Invalid input. Please input 'Y' or 'N'.\n";
                }
            }

            if (continueCalc) {
                history.showHistory();
            }
        }
    }
};

int main() {
    Calculator calculator;
    calculator.run();

    return 0;
}
