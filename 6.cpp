#include <iostream>
#include <string>

using namespace std;

// Определение структуры узла для хеш-таблицы
struct Node {
    char key;           // Символ, который мы будем хранить в узле
    int index;         // Индекс символа в строке
    Node* next;        // Указатель на следующий узел

    // Конструктор структуры для инициализации узла с символом и его индексом
    Node(char k, int idx) : key(k), index(idx), next(nullptr) {}
};

// Определение класса хеш-таблицы
class Hash {
public:
    static const int size = 256;   // Определяем размер хеш-таблицы (256, чтобы вместить все символы ASCII)
    Node* table[size];             // Массив указателей на узлы (представляет хеш-таблицу)

    // Конструктор хеш-таблицы
    Hash() {
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;     // Инициализируем все элементы таблицы значением nullptr
        }
    }

    // Хеш-функция, которая принимает символ и возвращает индекс
    int hash(char key) {
        return key; // Используем значение символа как индекс
    }

    // Метод для вставки символа в хеш-таблицу
    bool insert(char key, int index) {
        int idx = hash(key); // Получаем индекс для данного символа

        // Проверка на наличие символа в таблице
        Node* current = table[idx]; // Доступ к списку узлов по индексу
        while (current != nullptr) {
            if (current->key == key) {
                if (current->index < index) {
                    current->index = index; // Обновляем индекс, если он меньше
                }
                return false; // Если символ уже существует в списке, возвращаем false
            }
            current = current->next; // Переходим к следующему узлу в списке
        }

        // Если символ не найден, добавляем новый узел
        Node* newNode = new Node(key, index); // Создаем новый узел с данным символом
        newNode->next = table[idx]; // Указываем, что следующий узел нового узла - текущая голова списка
        table[idx] = newNode; // Устанавливаем новую голову списка на новый узел
        return true; // Возвращаем true, так как символ успешно добавлен
    }

    // Метод для получения индекса символа
    int getIndex(char key) {
        int idx = hash(key); // Получаем индекс для данного символа
        Node* current = table[idx]; // Доступ к списку узлов по индексу
        while (current != nullptr) {
            if (current->key == key) {
                return current->index; // Возвращаем индекс символа
            }
            current = current->next; // Переходим к следующему узлу в списке
        }
        return -1; // Если символ не найден, возвращаем -1
    }

    // Метод для очистки хеш-таблицы и освобождения памяти
    void clear() {
        for (int i = 0; i < size; i++) { // Проходим по всем индексам в таблице
            Node* current = table[i]; // Доступ к списку узлов по текущему индексу
            while (current != nullptr) { // Пока есть узлы в списке
                Node* temp = current; // Сохраняем текущий узел во временную переменную
                current = current->next; // Переходим к следующему узлу
                delete temp; // Освобождаем память, занятую текущим узлом
            }
            table[i] = nullptr; // Устанавливаем указатель на пустоту для текущего индекса
        }
    }

    // Деструктор для автоматической очистки хеш-таблицы при уничтожении объекта
    ~Hash() {
        clear(); // При уничтожении объекта очищаем хеш-таблицу
    }
};

int main() {
    string s; // Объявляем строку для хранения пользовательского ввода
    cout << "Введите строку: ";
    getline(cin, s); // Читаем строку, включая пробелы

    Hash hashTable; // Создаем экземпляр хеш-таблицы для хранения уникальных символов
    int maxLength = 0; // Переменная для хранения максимальной длины подстроки
    string longestSubstring; // Переменная для хранения самой длинной подстроки
    int start = 0; // Начальный индекс текущей подстроки

    // Проходим по строке
    for (int end = 0; end < s.length(); ++end) {
        char currentChar = s[end];

        // Если символ уже встречался, перемещаем начальный индекс
        int index = hashTable.getIndex(currentChar);
        if (index != -1) {
            start = max(start, index + 1); // Обновляем стартовый индекс
        }

        // Вставляем текущий символ в хеш-таблицу
        hashTable.insert(currentChar, end);

        // Проверяем длину текущей подстроки
        if (end - start + 1 > maxLength) {
            maxLength = end - start + 1; // Обновляем максимальную длину
            longestSubstring = s.substr(start, maxLength); // Обновляем самую длинную подстроку
        }
    }

    // Выводим результат
    cout << maxLength << " (" << longestSubstring << ")" << endl;

    return 0;
}

