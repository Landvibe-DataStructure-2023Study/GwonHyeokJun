//���� Ž��Ʈ�� ����
//1. �� ��忡 �ߺ����� �ʴ� Ű(key)�� �ִ�.
//2. ��Ʈ����� ���� ���� Ʈ���� �ش� ����� Ű���� ���� Ű�� ���� ����� �̷���� �ִ�.
//3. ��Ʈ����� ������ ���� Ʈ���� �ش� ����� Ű���� ū Ű�� ���� ����� �̷���� �ִ�.
//4. �¿� ���� Ʈ���� ��� ���� Ž�� Ʈ������ �Ѵ�.


#include <iostream>
#include <string>

using namespace std;
int cnt = 0;

struct Node {

    int elem;
    Node *par;
    Node *left;
    Node *right;

    Node(int elem) {
        this->elem = elem;
        par = NULL;
        left = right = NULL;
    }
};

class BST {
private:

public:
    Node *root;
    int size;

    BST() {
        root = NULL;
        size = 0;
    }

    void insert(int e) {
        Node *newNode = new Node(e);
        if (size == 0) {
            root = newNode;
        } else {
            Node *cur = root;
            while (true) {
                if (e > cur->elem) {
                    if (cur->right == NULL) {
                        cur->right = newNode;
                        newNode->par = cur;
                        break;
                    } else {
                        cur = cur->right;
                    }
                } else {
                    if (cur->left == NULL) {
                        cur->left = newNode;
                        newNode->par = cur;
                        break;
                    } else {
                        cur = cur->left;
                    }
                }
            }
        }
        size++;
    }

    void traversal(Node* cur){
        if(cur == NULL){
            return;
        }

        traversal(cur->left);
        cout << cur->elem << ' ';
        traversal(cur->right);
    }

};

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cnt = 0;
        BST bst;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            bst.insert(k);
        }

        bst.traversal(bst.root);
        cout << '\n';
    }
}