#include <iostream>
#include <string>
#include "database.h"

// template<typename T>
// T getType(const T& value) {
//     return value;
// }

void arrayPrint(Array* array) {
    std::cout << "[";
    switch (array->type)
    {
        case INT:
            for (int i = 0; i < array->size -1; i++) {
                std::cout << (static_cast<int*>(array->items)[i]) << ", ";
            }
            std::cout << (static_cast<int*>(array->items)[array->size-1]);
            break;
        case DOUBLE:
            for (int i = 0; i < array->size -1; i++) {
                std::cout << (static_cast<double*>(array->items)[i]) << ", ";
            }
            std::cout << (static_cast<double*>(array->items)[array->size-1]);
            break;
        case STRING:
            for (int i = 0; i < array->size -1; i++) {
                std::cout << (static_cast<std::string*>(array->items)[i]) << ", ";
            }
            std::cout << (static_cast<std::string*>(array->items)[array->size-1]);
            break;
        case ARRAY:
            for (int i = 0; i < array->size -1; i++) {
                arrayPrint(&(static_cast<Array*>(array->items)[i]));
                std::cout << ", ";
            }
            arrayPrint(&(static_cast<Array*>(array->items)[array->size-1]));
            break;
    }
    std::cout << "]";
}

void getAllData(Database &database) {
    for (int i = 0; i < database.index; i++) {
        switch (database.entrys[i]->type) {
            case INT:
                std::cout << database.entrys[i]->key << ": " << *((int*)database.entrys[i]->value) << std::endl;
                break;
            case DOUBLE:
                std::cout << database.entrys[i]->key << ": " << *(double*)(database.entrys[i]->value) << std::endl;
                break;
            case STRING:
                std::cout << database.entrys[i]->key << ": " << *(std::string*)(database.entrys[i]->value) << std::endl;
                break;
            case ARRAY:
                std::cout << database.entrys[i]->key << ": " ;
                arrayPrint((static_cast<Array*>(database.entrys[i]->value)));
                std::cout << std::endl;
                break;
        }
    }
}

Array *addArray(Array *array = new Array()) {
    std::string type;
    void* value;
    std::cout << "type (int, double, string, array): ";
    std::cin >> type;
    std::cout << "size: ";
    std::cin >> array->size;
    
    if (type == "int") {
        array->type = INT;
        int* dump = new int[array->size];
        for (int i = 0; i < array->size; i++) {
            std::cout << "item[" << i << "]: " ;
            value = new int;
            std::cin >> *(static_cast<int*>(value));
            dump[i] = *((int*)value);
        }
        array->items = dump;
    } else if (type == "double") {
        array->type = DOUBLE;
        double* dump = new double[array->size];
        for (int i = 0; i < array->size; i++) {
            std::cout << "item[" << i << "]: " ;
            value = new double;
            std::cin >> *(static_cast<double*>(value));
            dump[i] = *((double*)value);
        }
        array->items = dump;
    } else if (type == "string") {
        array->type = STRING;
        std::string* dump = new std::string[array->size];
        for (int i = 0; i < array->size; i++) {
            std::cout << "item[" << i << "]: " ;
            value = new std::string;
            std::cin.ignore();
            std::getline(std::cin, *(static_cast<std::string*>(value)));
            dump[i] = *((std::string*)value);
        }
        array->items = dump;
    } else if (type == "array") {
        array->type = ARRAY;
        Array* dump = new Array[array->size];
        for (int i = 0; i < array->size; i++) {
            std::cout << "item[" << i << "]: " ;
            
            Array *newArray = addArray();

            if (newArray == nullptr) {
                std::cout << "invalid type";
            } else {
                dump[i] = *((Array*)newArray);
            }
        }
        array->items = dump;
    } else {
        return nullptr;
    }
    
    
    return array;
}

void addData(Database &database) {
    std::string key;
    std::string type;

    void* value;
    

    std::cout << "key: ";
    std::cin >> key;

    std::cout << "Type (int, double, string, array): ";
    std::cin >> type;
    std::cout << "Value: ";

    if (type == "int") {
        value = new int;
        std::cin >> *(static_cast<int*>(value));
        add(database, create(INT, key, value));
    } else if (type == "double") {
        value = new double;
        std::cin >> *(static_cast<double*>(value));
        add(database, create(DOUBLE, key, value));
    } else if (type == "string") {
        value = new std::string;
        std::cin.ignore();
        std::getline(std::cin, *(static_cast<std::string*>(value)));
        add(database, create(STRING, key, value));
    } else if (type == "array") {
        Array *array = new Array;
        array = addArray(array);
        if (array == nullptr) {
            std::cout << "invalid type" << std::endl;
        } else {
            add(database, create(ARRAY, key, array));
        }
    } else {
        std::cout << "invalid type";
    }
    return;
}

// command Mode, input text analyze
void commandMode(Database &database) {
    std::string command;
    std::string key;
    Entry *data;

    while (true) {
        std::cout << "command (list, add, get, del, exit): ";
        std::cin >> command;

        if (command == "list") {
            getAllData(database);
        } else if (command == "add") {
            addData(database);
        } else if (command == "get") {
            std::cout << "key: ";
            std::cin >> key;
            data = get(database, key);
            if (data == nullptr) {
                std::cout << "not found";
            } else {
                switch (data->type)
                {
                case INT:
                    std::cout << data->key << ": " << *((int*)data->value) << std::endl;
                    break;
                case DOUBLE:
                    std::cout << data->key << ": " << *((double*)data->value) << std::endl;
                    break;
                case STRING:
                    std::cout << data->key << ": " << *((std::string*)data->value) << std::endl;
                    break;
                case ARRAY:
                    std::cout << data->key << ": " << ((Array*)data->value) << std::endl;
                    break;
                default:
                    break;
                }
            }
        } else if (command == "del") {
            std::cout << "key: ";
            std::cin >> key;
            data = get(database, key);
            if (data == nullptr) {
                std::cout << "not found";
            } else {
                remove(database, key);
            }
        } else if (command == "exit") {
            return;
        } else {
            std::cout << "invalid command" << std::endl;
        }

        std::cout << std::endl;
    }
}

int main() {
    Database database;

    init(database);

    commandMode(database);

    destroy(database);

    return 0;
}

