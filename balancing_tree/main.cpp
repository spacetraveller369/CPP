#include <iostream>
#include <vector>
#include <algorithm> 
#include <random>    
#include <Windows.h>

using namespace std;


struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;
    int size;

    void inOrderPrint(Node* node) const {
        if (node == nullptr) return;
        inOrderPrint(node->left);
        cout << node->data << " ";
        inOrderPrint(node->right);
    }

    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void collectToVector(Node* node, vector<int>& vec) {
        if (node == nullptr) return;
        collectToVector(node->left, vec);
        vec.push_back(node->data);
        collectToVector(node->right, vec);
    }

    int getHeight(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

public:
    BinarySearchTree() : root(nullptr), size(0) {}

    ~BinarySearchTree() {
        clear(root);
    }

    void balanceByShuffling() {
        if (root == nullptr) return;

        vector<int> elements;
        collectToVector(root, elements);

        clear(root);
        root = nullptr;
        size = 0;

        random_device rd;
        mt19937 g(rd());
        shuffle(elements.begin(), elements.end(), g);

        for (int num : elements) {
            insertWithoutTrigger(num);
        }
    }

    void insertWithoutTrigger(int val) {
        Node* newNode = new Node(val);
        if (root == nullptr) {
            root = newNode;
            size++;
            return;
        }
        Node* current = root;
        Node* parent = nullptr;
        while (current != nullptr) {
            parent = current;
            if (val < current->data) current = current->left;
            else if (val > current->data) current = current->right;
            else { delete newNode; return; }
        }
        if (val < parent->data) parent->left = newNode;
        else parent->right = newNode;
        size++;
    }

    void insert(int val) {
        insertWithoutTrigger(val);

        if (size > 20 && getHeight(root) > size / 2) {
            cout << "Вырождение! Высота слишком большая (" << getHeight(root) << "). Балансируем перемешиванием...\n";
            balanceByShuffling();
            cout << "Готово! Дерево перестроено. Новая высота: " << getHeight(root) << "\n";
        }
    }

    void print() const {
        inOrderPrint(root);
        cout << "\n";
    }

    int getSize() const { return size; }
    int getTreeHeight() const { return getHeight(root); }
};

int main() {

    setlocale(LC_ALL, "Russian");

    BinarySearchTree bst;

    cout << " Тест простого алгоритма перемешивания \n";
    cout << "Добавляем числа от 1 до 5000 по порядку...\n\n";

    for (int i = 1; i <= 5000; ++i) {
        bst.insert(i);
    }

    cout << "\nФинальный размер дерева: " << bst.getSize() << "\n";
    cout << "Финальная высота дерева: " << bst.getTreeHeight() << "\n";

    cout << "\nЗапуск распечатки (первые элементы): \n";
    bst.print();

    cout << "\nУспешно! Стек не переполняется \n";

    return 0;
}