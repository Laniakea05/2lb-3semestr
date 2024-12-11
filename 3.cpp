#include <iostream>
#include <string>

using namespace std;

// Определение структуры узла для связного списка
struct Node {
    string value; // Значение элемента
    Node* next;   // Указатель на следующий узел
};

// Определение структуры для множества
struct Set {
    Node* head; // Указатель на голову списка

    // Конструктор для инициализации множества
    Set() : head(nullptr) {}

    // Деструктор для освобождения памяти
    ~Set() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Метод для добавления элемента в множество
    void add(const string& value) {
        if (!contains(value)) { // Проверяем, существует ли элемент в множестве
            Node* newNode = new Node{value, nullptr}; // Создаем новый узел
            if (head == nullptr) { // Если список пуст
                head = newNode; // Новый узел становится головой списка
            } else {
                Node* current = head;
                while (current->next != nullptr) { // Находим последний узел
                    current = current->next;
                }
                current->next = newNode; // Добавляем новый узел в конец списка
            }
        }
    }

    // Метод для проверки наличия элемента в множестве
    bool contains(const string& value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                return true; // Элемент найден
            }
            current = current->next;
        }
        return false; // Элемент не найден
    }

    // Метод для вывода множества
    void print() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Метод для пересечения множеств
    Set intersectionWith(const Set& other) const {
        Set result;
        Node* current = head;
        while (current != nullptr) {
            if (other.contains(current->value)) {
                result.add(current->value); // Добавляем элемент, если он есть в другом множестве
            }
            current = current->next;
        }
        return result;
    }

    // Метод для разности множеств
    Set differenceWith(const Set& other) const {
        Set result;
        Node* current = head;
        while (current != nullptr) {
            if (!other.contains(current->value)) {
                result.add(current->value); // Добавляем элемент, если его нет в другом множестве
            }
            current = current->next;
        }
        return result;
    }

    // Метод для объединения множеств
    Set unionWith(const Set& other) const {
        Set result = *this; // Начинаем с текущего множества
        Node* current = other.head;
        while (current != nullptr) {
            result.add(current->value); // Добавляем элементы из другого множества
            current = current->next;
        }
        return result;
    }
};

int main() {
    Set set1;
    Set set2;

    // Добавляем элементы в первое множество
    set1.add("1");
    set1.add("2");
    set1.add("3");
    set1.add("4");
    set1.add("5");

    // Добавляем элементы во второе множество
    set2.add("3");
    set2.add("4");
    set2.add("5");
    set2.add("6");
    set2.add("7");

    cout << "Первое множество: ";
    set1.print();

    cout << "Второе множество: ";
    set2.print();

    // Пересечение множеств
    Set intersectionSet = set1.intersectionWith(set2);
    cout << "Пересечение множеств: ";
    intersectionSet.print();

    // Разность множеств
    Set differenceSet = set1.differenceWith(set2);
    cout << "Разность множеств (set1 - set2): ";
    differenceSet.print();

    // Объединение множеств
    Set unionSet = set1.unionWith(set2);
    cout << "Объединение множеств: ";
    unionSet.print();

    return 0;
}
