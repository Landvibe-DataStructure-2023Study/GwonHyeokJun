#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Compare {
    bool operator()(const int &i1, const int &i2) {
        return i1 < i2;
    }
};

class Heap { // �ּ� heap
public:
    Heap() {
        arr.push_back(0);
    } // vector ��� ���� 0�� �ε����� ������� �ʱ� ������ ������ �� �̻�� ���� �־��ش�
    int size() {
        return arr.size() - 1;
    }

    bool empty() {
        return arr.size() == 1;
    }

    void insert(int e) { // ���� �������� ���Ҹ� �����ϰ� �������������� ������ �����Ѵ�.
        arr.push_back(e);
        upHeap(size());
    }

    int min() { // �ּұ�� ���̱� ������ arr[1]�� ���� �ּҰ��� ����ִ�.
        if (empty()) return -1;
        return arr[1];
    }

    void removeMin() { // �ּҰ��� arr[1]�� ���� ������ ���� ������ ������. �׸��� idx=1 �������� �ٿ��� ����
        if (empty()) return;
        swap(1, size());
        arr.pop_back();
        downHeap(1);
    }

    void isEmpty(){
        if(empty()){
            cout << 1 << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
    void print(){
        if(empty()){
            cout << -1 << '\n';
            return;
        }
        for(int i = 1; i < arr.size(); i++){
            cout << arr[i] << ' ';
        }
        cout << '\n';
    }
private:
    vector<int> arr;
    Compare C;

    void swap(int idx1, int idx2) {
        int temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }

    void upHeap(int idx) {
        if (idx == 1) return;

        int parentIDX = idx / 2;
        if (C(arr[idx], arr[parentIDX])) {
            swap(idx, parentIDX);
            upHeap(parentIDX);
        }
    }

    void downHeap(int idx) {
        int left = 2 * idx;
        int right = 2 * idx + 1;
        int child;

        // ���� ���� Ʈ���� ���� �̿�
        if (left > size()) { // �ڽ��� ���� ���
            return;
        } else if (left == size()) { // ���� �ڽĸ� �ִ� ���
            child = left;
        } else { // �� �ڽ��� ��� ������ ������ �� �ڽ��� �� ���� �ڽ��� �ε����� child�� ����
            if (arr[left] <= arr[right]) { child = left; }
            else child = right;
        }

        if(C(arr[child], arr[idx])){
            swap(child, idx);
            downHeap(child);
        }
    }
};

int main() {
    int tc;
    cin >> tc;
    Heap h;
    while(tc--){
        string query;
        cin >> query;

        if(query == "insert"){
            int n;
            cin >> n;
            h.insert(n);
        } else if (query == "size"){
            cout << h.size() << '\n';
        } else if (query == "isEmpty"){
            h.isEmpty();
        } else if (query == "pop"){
            cout << h.min() << '\n';
            h.removeMin();
        } else if (query == "top"){
            cout << h.min() << '\n';
        } else if (query == "print"){
            h.print();
        }
    }
}