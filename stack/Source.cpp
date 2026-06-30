#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <Windows.h>

using namespace std;

template <typename T>

class CustomStack {
private:
    list<T> data;

public:
    
    void push(const T& val) {
        data.push_back(val); 
    }

    void pop() {
        if (!empty()) {
            data.pop_back();
        }
    }

    T top() const {
        if (!empty()) {
            return data.back();
        }
        throw runtime_error("Стек пуст!");
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }


    // 1. 
    bool Contains(const T& val) const {
        
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (*it == val) return true;
        }
        return false;
    }

    // 2. 
    void Print() const {
        if (empty()) {
            cout << "[Стек пуст]";
            return;
        }
        
        for (auto it = data.begin(); it != data.end(); ++it) {
            cout << *it << " ";
        }
        cout << "(<- вершина)\n";
    }

    // 3. 
    void PushLessValue(const T& val) {
        if (empty() || val < top()) {
            push(val);
            cout << "Элемент " << val << " успешно добавлен (меньше вершины).\n";
        }
        else {
            cout << "Отказ: элемент " << val << " НЕ меньше вершины (" << top() << ").\n";
        }
    }

    // 4. 
    void PushUnique(const T& val) {
        if (!Contains(val)) {
            push(val);
            cout << "Элемент " << val << " успешно добавлен (уникальный).\n";
        }
        else {
            cout << "Отказ: элемент " << val << " уже есть в стеке.\n";
        }
    }
};


// 5.

bool checkBrackets(const string& expression) {
    CustomStack<char> stack; 

    for (char ch : expression) {
        
        if (ch == '(' || ch == '[' || ch == '{' || ch == '<') {
            stack.push(ch);
        }
        
        else if (ch == ')' || ch == ']' || ch == '}' || ch == '>') {
            if (stack.empty()) return false; 

            char topCh = stack.top();
            stack.pop();

            
            if ((ch == ')' && topCh != '(') ||
                (ch == ']' && topCh != '[') ||
                (ch == '}' && topCh != '{') ||
                (ch == '>' && topCh != '<')) {
                return false; 
            }
        }
    }

   
    return stack.empty();
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Проверка кастомных методов \n";
    CustomStack<int> intStack;

    cout << "Добавляем обычным push: 10, 20, 30\n";
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);

    cout << "Текущий стек: ";
    intStack.Print();

    cout << "\nПроверка Contains:\n";
    cout << "Содержит 20? " << (intStack.Contains(20) ? "Да" : "Нет") << "\n";
    cout << "Содержит 50? " << (intStack.Contains(50) ? "Да" : "Нет") << "\n";

    cout << "\nПроверка PushLessValue:\n";
    intStack.PushLessValue(15); 
    intStack.PushLessValue(40);
    intStack.PushLessValue(5);
    cout << "Стек после PushLessValue: ";
    intStack.Print();

    cout << "\nПроверка PushUnique:\n";
    intStack.PushUnique(20);
    intStack.PushUnique(99);
    cout << "Стек после PushUnique: ";
    intStack.Print();

    cout << "\nПроверка валидатора скобок\n";

    string expr1 = "{(5-[3+<9>])-4}";
    string expr2 = "{(>5-<[3+)9]-4}";
    string expr3 = "([<{}>])";
    string expr4 = "([)]";

    cout << "Выражение: " << expr1 << " -> " << (checkBrackets(expr1) ? "ПРАВИЛЬНОЕ" : "НЕПРАВИЛЬНОЕ") << "\n";
    cout << "Выражение: " << expr2 << " -> " << (checkBrackets(expr2) ? "ПРАВИЛЬНОЕ" : "НЕПРАВИЛЬНОЕ") << "\n";
    cout << "Выражение: " << expr3 << " -> " << (checkBrackets(expr3) ? "ПРАВИЛЬНОЕ" : "НЕПРАВИЛЬНОЕ") << "\n";
    cout << "Выражение: " << expr4 << " -> " << (checkBrackets(expr4) ? "ПРАВИЛЬНОЕ" : "НЕПРАВИЛЬНОЕ") << "\n";

    return 0;
}