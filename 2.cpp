#include <iostream>
#include <fstream>
#include <string>

using namespace std; // Используем стандартное пространство имен

// Структура для узла в хеш-таблице
struct Node {
    string data;     // Данные, хранящиеся в узле (строка)
    Node* next;      // Указатель на следующий узел (для реализации связного списка)
};

// Структура для хеш-таблицы
struct Set {
    Node** table;    // Массив указателей на узлы (таблица для хеширования)
    int size;        // Размер хеш-таблицы

    // Конструктор для хеш-таблицы
    Set(int tableSize) : size(tableSize) {
        table = new Node*[size](); // Инициализируем массив указателей, устанавливая их в nullptr
    }

    // Хеш-функция для вычисления индекса в таблице
    int hash(const string& value) const {
        // Обрабатываем строку для получения целого значения
        int hashValue = 0;
        for (char c : value) {
            hashValue += c; // Суммируем ASCII-коды символов
        }
        return hashValue % size; // Возвращаем остаток от деления на размер таблицы
    }

    // Добавление элемента в хеш-таблицу
    void add(const string& value) {
        // Проверяем, существует ли уже значение в множестве
        if (contains(value)) {
            cout << "Значение уже есть в множестве: " << value << endl; // Выводим сообщение
            return; // Выходим из функции
        }

        int index = hash(value); // Вычисляем индекс для нового значения
        Node* newNode = new Node{value, nullptr}; // Создаем новый узел с данным значением

        // Если в таблице по вычисленному индексу нет узлов
        if (table[index] == nullptr) {
            table[index] = newNode; // Устанавливаем новый узел в таблицу
        } else {
            // Если узел уже существует, добавляем новый узел в начало связного списка
            newNode->next = table[index]; // Устанавливаем указатель на текущий узел
            table[index] = newNode; // Обновляем указатель на первый узел
        }
    }

    // Удаление элемента из хеш-таблицы
    void remove(const string& value) {
        int index = hash(value); // Вычисляем индекс для значения
        Node** current = &table[index]; // Указатель на указатель узла по индексу
        while (*current != nullptr) { // Пока текущий узел не пустой
            if ((*current)->data == value) { // Если нашли узел с нужным значением
                Node* toDelete = *current; // Сохраняем указатель на узел для удаления
                *current = (*current)->next; // Перенаправляем указатель на следующий узел
                delete toDelete; // Удаляем узел
                return; // Выходим из функции
            }
            current = &((*current)->next); // Переходим к следующему узлу
        }
    }

    // Проверка наличия элемента в хеш-таблице
    bool contains(const string& value) const {
        int index = hash(value); // Вычисляем индекс для значения
        Node* current = table[index]; // Получаем указатель на первый узел по индексу
        while (current) { // Пока текущий узел не пустой
            if (current->data == value) { // Если значение найдено
                return true; // Возвращаем true
            }
            current = current->next; // Переходим к следующему узлу
        }
        return false; // Если значение не найдено, возвращаем false
    }

    // Деструктор для хеш-таблицы
    ~Set() {
        for (int i = 0; i < size; ++i) { // Проходим по всем индексам в таблице
            Node* current = table[i]; // Получаем указатель на первый узел по индексу
            while (current) { // Пока текущий узел не пустой
                Node* toDelete = current; // Сохраняем узел для удаления
                current = current->next; // Переходим к следующему узлу
                delete toDelete; // Удаляем узел
            }
        }
        delete[] table; // Освобождаем память, занятую массивом указателей
    }

    // Сохранение хеш-таблицы в файл
    void saveToFile(const char* filename) const {
        ofstream file(filename); // Открываем файл для записи
        for (int i = 0; i < size; ++i) { // Проходим по всем индексам в таблице
            Node* current = table[i]; // Получаем указатель на первый узел по индексу
            while (current) { // Пока текущий узел не пустой
                file << current->data << endl; // Записываем данные узла в файл
                current = current->next; // Переходим к следующему узлу
            }
        }
        file.close(); // Закрываем файл
    }

    // Загрузка хеш-таблицы из файла
    void loadFromFile(const char* filename) {
        ifstream file(filename); // Открываем файл для чтения
        string value; // Переменная для хранения считываемого значения
        while (file >> value) { // Читаем значения из файла, пока это возможно
            add(value); // Добавляем считанное значение в хеш-таблицу
        }
        file.close(); // Закрываем файл
    }
};

// Функция для выполнения команды
void executeCommand(Set& set, const string& command, const string& value) {
    if (command == "SETADD") { // Если команда - добавление
        set.add(value); // Добавляем значение
    } else if (command == "SETDEL") { // Если команда - удаление
        set.remove(value); // Удаляем значение
    } else if (command == "SET_AT") { // Если команда - проверка наличия
        cout << (set.contains(value) ? "ДА" : "НЕТ") << endl; // Выводим результат проверки
    }
}

int main(int argc, char* argv[]) {
    // Проверяем количество аргументов командной строки
    if (argc != 6) {
        cerr << "Использование: " << argv[0] << " --file <путь к файлу> --query <команда> <значение>" << endl;
        return 1; // Выход с ошибкой, если аргументов недостаточно
    }

    const char* filename = argv[2]; // Получаем путь к файлу из аргументов
    const string command = argv[4]; // Получаем команду из аргументов
    string value = argv[5]; // Получаем значение как строку

    Set set(100); // Создаем хеш-таблицу размером 100
    set.loadFromFile(filename); // Загружаем данные из файла в хеш-таблицу

    // Выполнение команды
    executeCommand(set, command, value); // Выполняем соответствующую команду

    set.saveToFile(filename); // Сохраняем обновленную хеш-таблицу в файл

    return 0;
}
