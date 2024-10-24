#pragma once

struct Items {
    int id;
    string name;
};

struct inventory {
    vector<Items> items;

    void add(int id, string name) {
        Items i;
        i.id = id;
        i.name = name;
        items.push_back(i);
        cout << "Add done" << endl;
    }

    void get(int id) {
        bool found = false;
        for (int i = 0; i < items.size(); i++) {
            if (items[i].id == id) {
                cout << "Item name: " << items[i].name << " item id: " << items[i].id << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Item not found" << endl;
        }
    }
};

