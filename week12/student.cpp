#include <iostream>
#include <string>


using namespace std;

bool isRan = false;
int cnt = 0;

int stoi_(string s) {
    int t = 1;
    int a = 0;
    for (int i = 0; i < 6; i++, t *= 26) {
        a += (s[i] - 'a') * t;
    }
    return a;
}


struct Entry {

    int key;
    int valuekey;
    string value;
    int available;
    bool absent;
    int x;

    Entry() {
        key = 0;
        value = "";
        available = 0;
        valuekey = 0;
        absent = true;
        x = 0;
    }


    Entry(int key, string value) {
        this->key = key;
        this->value = value;
        valuekey = stoi_(value);
        available = 2;
        absent = true;
        x = key;
    }

    Entry(int key, string value, int x) {
        this->key = key;
        this->value = value;
        valuekey = stoi_(value);
        available = 2;
        absent = true;
        this->x = x;

    }

    void deletion() {
        key = 0;
        value = "";
        available = 1;
        absent = true;
        x = 0;
        valuekey = 0;

    }

};

class HashTable {

public:
    Entry *table;
    int maxSize;

    HashTable(int maxSize) {
        this->maxSize = maxSize;
        table = new Entry[maxSize + 1];
    }


    int LinearHash(int key) {
        return key % maxSize;
    }

    void add(int x, string s, int t) {
        put(x, s, t);
    }

    void name(int x) {
        find(x);
    }

    int present(string v) {
        int index = LinearHash(stoi_(v));
        int probe = 1;
        while (true) {
            if (table[index].available == 0) {
                cout << "Invalid" << '\n';
                break;
            }

            if (table[index].valuekey == stoi_(v)) {
                cout << table[index].x << '\n';
                if (table[index].absent == true) {
                    cnt++;
                }
                table[index].absent = false;

                return table[index].x;
            }
            index = LinearHash(++index);
            probe++;
            if (probe > maxSize) {
                cout << "Invalid" << '\n';
                break;
            }
        }
        return 0;

    }

    int absent(string v) {
        int index = LinearHash(stoi_(v));
        int probe = 1;
        while (true) {
            if (table[index].available == 0) {
                cout << "Invalid" << '\n';
                return 0;
            }

            if (table[index].valuekey == stoi_(v)) {
                cout << table[index].x << '\n';
                if (table[index].absent == false) {
                    cnt--;
                }
                table[index].absent = true;
                return table[index].x;
            }
            index = LinearHash(++index);
            probe++;

            if (probe > maxSize) {
                cout << "Invalid" << '\n';
                return 0;
            }
        }
    }

    int findIndex(int key) {
        int index = LinearHash(key);
        int probe = 1;
        while (true) {
            if (table[index].available == 0) {
                return 0;
            }

            if (table[index].key == key) {
                return index;
            }
            index = LinearHash(++index);
            probe++;

            if (probe > maxSize) {
                return 0;
            }
        }
    }




    void put(int key, string value, int t) {
        int index = LinearHash(key);

        int probe = 1;
        while (true) {
            if (table[index].available != 2) {
                if (t != 0) {
                    table[index] = Entry(key, value, t);
                } else {
                    table[index] = Entry(key, value);
                }
                return;
            }
            index = LinearHash(++index);
            probe++;
            if (probe > maxSize) {
                return;
            }
        }
    }

    void find(int key) {
        int index = LinearHash(key);

        while (true) {
            if (table[index].available == 0) {
                return;
            }
            if (table[index].key == key) {
                cout << table[index].value << '\n';
                return;
            }
            index = LinearHash(++index);
            if (index == LinearHash(key)) {
                return;
            }
        }
    }

    int erase(int key) {
        int index = LinearHash(key);

        int probe = 1;
        while (true) {
            if (table[index].available == 0) {
                return 0;
            }
            if (table[index].key == key) {
                if (table[index].absent == false) {
                    if (!isRan) {
                        cnt--;
                        isRan = true;
                    }

                }

                int tmp = table[index].valuekey;
                table[index].deletion();
                return tmp;
            }
            index = LinearHash(++index);
            probe++;
            if (probe > maxSize) {
                return 0;
            }

        }
    }
};

int main() {


    int tc;
    cin >> tc;
    HashTable hst(500000);
    HashTable hst2(500000);


    while (tc--) {

        string q;
        cin >> q;
        if (q == "add") {
            int x;
            string s;
            cin >> x >> s;
            int valuekey = stoi_(s);
            hst.add(x, s, 0);
            hst2.add(valuekey, s, x);
        } else if (q == "delete") {
            int x;
            cin >> x;
            int key = (hst.erase(x));
            hst2.erase(key);
            isRan = false;
        } else if (q == "name") {
            int x;
            cin >> x;
            hst.name(x);
        } else if (q == "present") {
            string v;
            cin >> v;
            int key = hst2.present(v);
            int hstIndex = hst.findIndex(key);
            hst.table[hstIndex].absent = false;
        } else if (q == "absent") {
            string v;
            cin >> v;
            int key = hst2.absent(v);
            int hstIndex = hst.findIndex(key);
            hst.table[hstIndex].absent = true;
        }
    }

    cout << cnt << '\n';
}

