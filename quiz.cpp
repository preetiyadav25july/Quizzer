#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Question {
    string question;
    string options[4];
    int correctOption;
};

// ---------- STACK IMPLEMENTATION ----------
#define MAX 10
struct Stack {
    int top;
    int arr[MAX];
};

void initStack(Stack &s) {
    s.top = -1;
}

void push(Stack &s, int value) {
    if (s.top == MAX - 1) {
        cout << "?? Stack Overflow! Cannot push more answers.\n";
        return;
    }
    s.top++;
    s.arr[s.top] = value;
}

int pop(Stack &s) {
    if (s.top == -1) {
        cout << "?? Stack Underflow! No answers to review.\n";
        return -1;
    }
    int value = s.arr[s.top];
    s.top--;
    return value;
}

void displayStack(Stack s) {
    if (s.top == -1) {
        cout << "\nNo answers stored in stack.\n";
        return;
    }

    cout << "\n--------------------------------------\n";
    cout << "?? Reviewing your answers (LIFO order):\n";
    cout << "--------------------------------------\n";

    int qNo = s.top + 1;
    while (s.top != -1) {
        cout << "Question " << qNo-- << " ? Your answer: " << s.arr[s.top] << endl;
        s.top--;
    }

    cout << "--------------------------------------\n";
}

// ---------- FUNCTION DECLARATIONS ----------
void startQuiz();
void viewScores();
void saveScore(const string &name, int score);

// ---------- MAIN MENU ----------
int main() {
    int choice;
    while (true) {
        cout << "\n===== ?? STACK QUIZ GAME =====\n";
        cout << "1. Start Quiz\n";
        cout << "2. View Previous Scores\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                startQuiz();
                break;
            case 2:
                viewScores();
                break;
            case 3:
                cout << "Thanks for playing! Goodbye ??\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

// ---------- FUNCTION DEFINITIONS ----------
void startQuiz() {
    cin.ignore();  
    string name;
    cout << "\nEnter your name: ";
    getline(cin, name);

    Question quiz[5] = {
        {"1?? What is the time complexity of push() in a stack (array)?",
         {"O(1)", "O(n)", "O(log n)", "O(n^2)"}, 1},

        {"2?? Which operation removes the top element of a stack?",
         {"push()", "pop()", "peek()", "insert()"}, 2},

        {"3?? Which data structure is used in function call management?",
         {"Queue", "Array", "Stack", "Tree"}, 3},

        {"4?? What happens if we pop from an empty stack?",
         {"Underflow", "Overflow", "Segmentation fault", "Creates new stack"}, 1},

        {"5?? Which of the following is NOT an application of stack?",
         {"Expression evaluation", "Recursion", "Undo operation", "Binary Search"}, 4}
    };

    int score = 0;
    int userChoice;

    Stack s;
    initStack(s);

    for (int i = 0; i < 5; i++) {
        cout << "\n" << quiz[i].question << "\n";
        for (int j = 0; j < 4; j++) {
            cout << j + 1 << ". " << quiz[i].options[j] << endl;
        }

        cout << "Enter your answer (1-4): ";
        cin >> userChoice;

        push(s, userChoice);

        if (userChoice == quiz[i].correctOption) {
            cout << "? Correct!\n";
            score += 10;
        } else {
            cout << "? Wrong! Correct answer: " << quiz[i].correctOption
                 << ". " << quiz[i].options[quiz[i].correctOption - 1] << "\n";
        }
    }

    // Wait before showing answers
    cin.ignore();
    cout << "\nPress Enter to review your answers...";
    cin.get();

    displayStack(s);

    cout << "\n?? " << name << ", your total score: " << score << " / 50\n";
    saveScore(name, score);
}

void saveScore(const string &name, int score) {
    ofstream file("stack_scores.txt", ios::app);
    if (file.is_open()) {
        file << name << " - " << score << " points\n";
        file.close();
        cout << "?? Your score has been saved successfully!\n";
    } else {
        cout << "?? Error: Unable to open file to save score.\n";
    }
}

void viewScores() {
    ifstream file("stack_scores.txt");
    if (!file) {
        cout << "\nNo previous scores found!\n";
        return;
    }

    cout << "\n---- ?? Previous Scores ----\n";
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    cout << "---------------------------\n";
    file.close();
}
