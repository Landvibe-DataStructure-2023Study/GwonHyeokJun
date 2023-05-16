#include <iostream>
#include <string>

using namespace std;

struct Entry {
    int key;
    bool available;

    Entry() {
        key = 0;
        available = true;
    }

};

class HashTable {
public:
    Entry *table;
    int maxSizeA;
    int maxSizeB;
    int curA;
    int curB;
    bool doubleRotate;

    HashTable(int maxSizeA, int maxSizeB) {
        this->maxSizeA = maxSizeA;
        this->maxSizeB = maxSizeB;
        curA = curB = 0;
        table = new Entry[maxSizeA + 1];
        doubleRotate = false;
    }

    int hashFunction(int laps, bool clock, bool isA) {

        if (isA) {
            if (!clock) {
                return (curA + (laps % maxSizeA)) % maxSizeA;
            } else {
                return (curA + maxSizeA - (laps % maxSizeA)) % maxSizeA;
                if (curA >= (laps % maxSizeA)) {
                    return curA - (laps % maxSizeA);
                } else {
                    return maxSizeA + (curA - (laps % maxSizeA));
                }
            }
        } else {
            if (!clock) {
                return (curB + (laps % maxSizeB)) % maxSizeB;
            } else {
                return (curB + maxSizeB - (laps % maxSizeB)) % maxSizeB;
                if (curB >= (laps % maxSizeB)) {
                    return curB - (laps % maxSizeB);
                } else {
                    return maxSizeB + (curB - (laps % maxSizeB));
                }
            }
        }
    }

    void rotateA(int laps) {
        // �ݽð� -> ���� ����

//        cout << "�ؽ� �� curA : " << curA + 1 << " curB : " << curB + 1 << '\n';
        curA = hashFunction(laps, false, true);
        curB = hashFunction(laps, true, false);
//        cout << "�ؽ� �� curA : " << curA + 1 << " curB : " << curB + 1 << '\n';
        if (table[curA].available) {

            table[curA].available = false;
            cout << curA + 1 << ' ';
            if (doubleRotate) {
//                cout << "2������ �ذ� ";
//                cout << "curA : " << curA + 1 << " curB : " << curB + 1 << '\n';
            } else {
//                cout << "1������ �ذ� ";
//                cout << "curA : " << curA + 1 << " curB : " << curB + 1 << '\n';
            }
            doubleRotate = false;
            return;
        } else {
            if (doubleRotate) {
                rotateB();
            } else {
                doubleRotate = true;
                rotateA(curB + 1);

            }
        }
    }

    void rotateB() {
//        cout << "B�ؽ� �� curA : " << curA + 1 << " curB : " << curB + 1 << '\n';
        while (!table[curA].available) {
            curA = hashFunction(1, true, true);
            curB = hashFunction(1, false, false);
        }

        table[curA].available = false;
        cout << curA + 1 << ' ';
//        cout << "3������ �ذ� ";
//        cout << "B �ؽ� �� curA : " << curA + 1 << " curB : " << curB + 1 << '\n';
        doubleRotate = false;
    }


};

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int n, m, cnt;
        cin >> n >> m >> cnt;
        HashTable hst(n, m);
        for (int i = 0; i < cnt; i++) {
            int k;
            cin >> k;
            hst.rotateA(k);
        }
        cout << '\n';
    }
}

