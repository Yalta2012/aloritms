#include <iostream>
#include <limits>
#include "hashmap.h"

using namespace std;
using namespace curs;

int main()
{

    int menu_key;
    hash_map<string, int> map;
    string key;
    int val;
    do
    {
        cout << endl;
        cout << "Хеш-Таблица" << endl
             << "Ключ: std::string" << endl
             << "Значение: int" << endl
             << "1. Вставить" << endl
             << "2. Удалить" << endl
             << "3. Проверить наличие" << endl
             << "4. Количество элементов" << endl
             << "5. Размер таблицы" << endl
             << "6. Вывести все элементы" << endl
             << "7. Отчистить" << endl
             << "8. Вычислить хеш-код" << endl
             << "0. Выход" << endl
             << ">>";
        cin >> menu_key;
        if (cin.fail())
        {
            menu_key = -1;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (menu_key)
        {
        case 0:
            break;
        case 1:
            cout << "Введите ключ (std::string): ";
            cin >> key;
            cout << "Введие значение (int): ";
            cin >> val;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Значение должно быть числом" << endl;
            }
            else
            {
                map.put(key, val);
            }
            break;
        case 2:
            cout << "Введите ключ (std::string): ";
            cin >> key;
            map.remove(key);
            break;
        case 3:
            cout << "Введите ключ (std::string): ";
            cin >> key;
            if (map.contains(key))
            {
                cout << "\"" << key << "\" содержится в таблице" << endl;
            }
            else
            {
                cout << "\"" << key << "\" не содержится в таблице" << endl;
            }
            break;
        case 4:
            cout << "Количество элементов: " << map.size() << endl;
            break;
        case 5:
            cout << "Размер таблицы: " << map.total_buckets() << endl;
            break;
        case 6:
            if (map.empty())
            {
                cout << "Таблица пуста" << endl;
            }
            for (auto i : map)
            {
                cout << "\"" << i.key() << "\": " << i.value() << endl;
            }
            break;
        case 7:
            map.clear();
            break;
        case 8:
            cout << "Введите ключ (std::string): ";
            cin >> key;
            cout << "Хеш: " << map.hash(key, map.total_buckets()) << endl;
            break;
        default:
            cout << "Неизвестная команда" << endl;
            break;
        }

    } while (menu_key != 0);
}