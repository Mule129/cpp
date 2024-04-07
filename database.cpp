#include <string>
#include <iostream>

#include "database.h"


// 엔트리를 생성한다.
Entry *create(Type type, std::string key, void *value) {
    Entry *entry = new Entry;
    entry->type = type;
    entry->key = key;
    entry->value = value;

    return entry;
}


// 데이터베이스를 초기화한다.
void init(Database &database) {
    database.entrys = new Entry*[DEFALTSIZE];
    database.index = 0;
    database.maxSize = DEFALTSIZE;
}

// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry) {
    bool check = false;

    for (int i = 0; i < database.index; i++) {  // key duplication check
        if (database.entrys[i]->key == entry->key) {  
            database.entrys[i] = entry;
            check = true;
        }
    }
    
    if (check == true) {
        return;
    }

    database.entrys[database.index] = entry;
    database.index++;
    
    if (database.maxSize <= database.index-1) {
        database.maxSize = database.maxSize * 2;
        Entry** dump = new Entry*[database.maxSize];
        for (int i = 0; i < database.index; i++) {
            dump[i] = database.entrys[i];
        }
        delete[] database.entrys;
        database.entrys = dump;
    }
}

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry *get(Database &database, std::string &key) {
    for (int i = 0; i < database.index; i++) {
        if (database.entrys[i]->key == key) {
            return database.entrys[i];
        }
    }
    return nullptr;
}

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key) {
    for (int i = 0; i < database.index; i++) {
        if (database.entrys[i]->key == key) {
            delete database.entrys[i];
            database.index--;

            for (int j = i; j < database.index; j++) {
                database.entrys[j] = database.entrys[j+1];
            }
            return;
            
        }
    }
}

// 데이터베이스를 해제한다.
void destroy(Database &database) {
    delete database.entrys;
}
