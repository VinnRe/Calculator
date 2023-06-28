// Kobe Andrew S. Capinpin
// CS - 1303

#include <iostream>
using namespace std;

bool isNan(double num) {
    return num != num;  // NaN is the only value that is not equal to itself
}


double calcBrain(const string& expression) { // The function for solving the mathematical expressions
    double result = 0.0;
    double number = 0.0;
    char op = '+';
    int i = 0;

    while (i < expression.length()) { 
        if (expression[i] >= '0' && expression[i] <= '9') { // if the character in the string is a number it goes through here
            // Extract the number
            number = 0.0;
            while (i < expression.length() && expression[i] >= '0' && expression[i] <= '9') {
                number = number * 10 + (expression[i] - '0');
                i++;
            }

            // Apply the previous operator to the current number
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
            // Update the operator
            op = expression[i];
            i++;
        }
        else {
            return 0.0 / 0.0;  // Return NaN if an invalid character is encountered
        }
    }

    return result;
}

struct Calculation { // This is for storing the expression and result
    string expression;
    double result;
};

void addToHistory(Calculation* calc);

void mainCalc() {
    string expression;
    cout << "Enter an expression: ";
    getline(cin, expression);

    double result = calcBrain(expression);
    if (!isNan(result)) {
        cout << "Result: " << result << endl;

        // Save to history
        Calculation* calc = new Calculation;
        calc->expression = expression;
        calc->result = result;
        addToHistory(calc);
    }
    else {
        cout << "Invalid input or mathematical error." << endl;
    }
}

// ------------------ HISTORY ----------------- //

const int MAX_SIZE = 100;
Calculation* history[MAX_SIZE];
int historyCount = 0;

void addToHistory(Calculation* calc) {
    Calculation* newCalc = new Calculation;  // Create a new Calculation object

    // Copy the values from the passed-in calc to the newCalc object
    newCalc->expression = calc->expression;
    newCalc->result = calc->result;

    if (historyCount < MAX_SIZE) {
        history[historyCount] = newCalc;
        historyCount++;
    }
    else {
        delete history[0];  // Remove the oldest entry
        for (int i = 0; i < MAX_SIZE - 1; i++) {
            history[i] = history[i + 1];
        }
        history[MAX_SIZE - 1] = newCalc;
    }
    cout << "Added to history. Address: " << newCalc << endl;
}

void showHistory() {
    cout << "[ ======== History ======== ]" << endl;
    for (int i = 0; i < historyCount; i++) {
        cout << "Equation: " << history[i]->expression << " = " << history[i]->result << " Address: " << history[i] << endl;
    }
}

void clearHistory() {
    for (int i = 0; i < historyCount; i++) {
        delete history[i];
        history[i] = nullptr;
    }
    historyCount = 0;
}

// --------------- MAIN ----------------- //
int main(){
    bool continueCalc = true;

    while(continueCalc){
        mainCalc();

        // Asks the user for continuation
        char choice;
        cout << "Do you want to input a new expression? ( Y | N ): ";
        cin >> choice;
        cin.ignore(); // Ignores new line character
        while(true){
            if(choice == 'Y' || choice == 'y'){
                break;
            }
            else if(choice == 'N' || choice == 'n'){
                continueCalc = false;
                cout << "Ending program. \n";
                break;
            }
            else{
                cout << "Invalid input. Please input 'Y' or 'N'.\n";
                
            }
        }
        if (continueCalc) {
            //clearHistory();
            showHistory();
        }
    }

    return 0;
}