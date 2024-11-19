#include <iostream>
#include <algorithm>

using namespace std;

// Структура узла AVL-дерева
struct AVLNode {
    int data = 0; // Значение узла
    AVLNode* left = nullptr; // Указатель на левое поддерево
    AVLNode* right = nullptr; // Указатель на правое поддерево
    int balance = 0; // Разница высоты между левым и правым поддеревьями
};

// Функция для вычисления высоты узла
int HeightAVL(AVLNode* root) {
    if (root == nullptr) {
        return 0; // Высота пустого узла равна 0
    }
    // Возвращаем максимальную высоту между левым и правым поддеревом + 1 (для текущего узла)
    return max(HeightAVL(root->left), HeightAVL(root->right)) + 1;
}

// Функция для установки баланса узла
void bfactor(AVLNode* root) {
    if (root != nullptr) {
        // Вычисляем баланс узла как разницу высот левого и правого поддеревьев
        root->balance = HeightAVL(root->left) - HeightAVL(root->right);
    }
}

// Функция для вращения вправо
AVLNode* RotateRight(AVLNode* root) {
    AVLNode* newRoot = root->left; // Новый корень будет левым дочерним узлом
    root->left = newRoot->right; // Правое поддерево нового корня становится левым дочерним узлом старого корня
    newRoot->right = root; // Старый корень становится правым дочерним узлом нового корня
    bfactor(root); // Пересчитываем баланс старого корня
    bfactor(newRoot); // Пересчитываем баланс нового корня
    return newRoot; // Возвращаем новый корень
}

// Функция для вращения влево
AVLNode* RotateLeft(AVLNode* root) {
    AVLNode* newRoot = root->right; // Новый корень будет правым дочерним узлом
    root->right = newRoot->left; // Левое поддерево нового корня становится правым дочерним узлом старого корня
    newRoot->left = root; // Старый корень становится левым дочерним узлом нового корня
    bfactor(root); // Пересчитываем баланс старого корня
    bfactor(newRoot); // Пересчитываем баланс нового корня
    return newRoot; // Возвращаем новый корень
}

// Функция для вставки узла без балансировки
AVLNode* Insert(AVLNode* root, int value) {
    if (root == nullptr) {
        return new AVLNode{value}; // Создаем новый узел, если дерево пустое
    }
    if (value < root->data) {
        root->left = Insert(root->left, value); // Рекурсивно вставляем в левое поддерево
    } else if (value > root->data) {
        root->right = Insert(root->right, value); // Рекурсивно вставляем в правое поддерево
    }
    return root; // Возвращаем корень без балансировки
}

// Функция для балансировки узла
AVLNode* BalanceAVL(AVLNode* root) {
    bfactor(root); // Обновляем баланс узла

    // Проверка баланса и выполнение вращений
    if (root->balance > 1) {
        if (root->left->balance < 0) {
            root->left = RotateLeft(root->left); // Левый правый случай
        }
        return RotateRight(root); // Левый левый случай
    }
    
    if (root->balance < -1) {
        if (root->right->balance > 0) {
            root->right = RotateRight(root->right); // Правый левый случай
        }
        return RotateLeft(root); // Правый правый случай
    }

    return root; // Возвращаем (возможно) сбалансированный корень
}

// Функция для полной балансировки дерева
AVLNode* BalanceTree(AVLNode* root) {
    if (root == nullptr) return nullptr; // Если дерево пустое, возвращаем nullptr

    root->left = BalanceTree(root->left);   // Балансируем левое поддерево
    root->right = BalanceTree(root->right); // Балансируем правое поддерево
    return BalanceAVL(root);                // Балансируем текущий узел
}

// Функция для проверки сбалансированности дерева
bool IsBalanced(AVLNode* root) {
    if (root == nullptr) return true; // Пустое дерево считается сбалансированным

    int leftHeight = HeightAVL(root->left); // Высота левого поддерева
    int rightHeight = HeightAVL(root->right); // Высота правого поддерева

    // Проверяем, что разница высот не превышает 1 и рекурсивно проверяем поддеревья
    return (abs(leftHeight - rightHeight) <= 1) &&
            IsBalanced(root->left) &&
            IsBalanced(root->right);
}

int main() {
    system("chcp 65001"); // Устанавливаем кодировку консоли на UTF-8
    AVLNode* root = nullptr; // Инициализируем корень дерева как nullptr
    int value;

    cout << "Введите числа (нечисло для завершения): "; // Запрос ввода чисел
    while (cin >> value) {
        root = Insert(root, value); // Вставляем узлы без балансировки
    }

    // Проверка сбалансированности изначального дерева
    if (IsBalanced(root)) {
        cout << "дерево сбалансировано." << endl;
    } else {
        cout << "дерево не сбалансировано." << endl;
    }

    // Балансировка всего дерева
    root = BalanceTree(root);

    // Проверка сбалансированности после балансировки
    if (IsBalanced(root)) {
        cout << "После балансировки дерево сбалансировано." << endl;
    } else {
        cout << "После балансировки дерево несбалансировано." << endl;
    }

    return 0; // Завершение программы
}
