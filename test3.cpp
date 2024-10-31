#include <iostream>
using namespace std;

int a[2005], b[2005];

class chainNode {
public:
    int val;
    chainNode* next = NULL;
    chainNode(const int& num) {
        val = num;
    }
    chainNode(const int& num, chainNode* num_next) {
        val = num;
        next = num_next;
    }
};

class chain {
public:
    class chain_iterator {
    public:
        chain_iterator(chainNode* p = NULL) { node = p; }
        chainNode* node = NULL;
        int& operator*()const { return node->val; }
        chain_iterator& operator++() { node = node->next; return *this; }
        bool operator==(const chain_iterator& right) { return node == right.node; }
        bool operator!=(const chain_iterator& right) { return node != right.node; }
        //chain_iterator& operator=(chainNode* a) { node = a; return*this; }
    };
    void insert(int idx, int valx);
    void erase(int valx);
    void reserve();
    void search(int valx);
    void xorsum();
    void show();
    void operation(int theop) {
        if (theop == 1) {
            int idx, valx;
            cin >> idx >> valx;
            insert(idx, valx);
        }
        else if (theop == 2) {
            int valx;
            cin >> valx;
            erase(valx);
        }
        else if (theop == 3) {
            reserve();
        }
        else if (theop == 4) {
            int valx;
            cin >> valx;
            search(valx);
        }
        else {
            xorsum();
        }
    }
    int listSize = 0;
    chainNode* firstNode = NULL;
    //chainNode lastNode;

    void sort() {//插入排序
        if (listSize <= 1)
            return;

        chainNode* sorted = NULL;
        chainNode* current = firstNode;
        while (current != NULL) {
            chainNode* nextNode = current->next;

            // 在已排序的链表中找到插入位置
            if (sorted == NULL || current->val <= sorted->val) {
                current->next = sorted;
                sorted = current;
            }
            else {
                chainNode* searchNode = sorted;
                while (searchNode->next != NULL && searchNode->next->val < current->val) {
                    searchNode = searchNode->next;
                }
                current->next = searchNode->next;
                searchNode->next = current;
            }

            current = nextNode;
        }

        firstNode = sorted;
    }
};

void chain::insert(int idx, int valx) {//题目的索引是从零开始的
    if (idx > listSize) {
        throw"idx is illegal!";
        return;
    }
    if (idx == 0) {
        firstNode = new chainNode(valx, firstNode);
        listSize++;
    }
    else {
        chainNode* nowNode = firstNode;
        for (int i = 0; i < idx - 1; i++) {
            nowNode = nowNode->next;
        }
        nowNode->next = new chainNode(valx, nowNode->next);
        listSize++;
    }
}

void chain::erase(int valx) {
    chainNode* nowNode = firstNode;
    chainNode* preNode = firstNode;
    chainNode* delNode = firstNode;
    for (int i = 0; i < listSize; i++) {
        if (nowNode->val == valx) {
            if (i == 0) {
                delNode = firstNode;
                firstNode = firstNode->next;
                delete delNode;
                listSize--;
                return;
            }
            else {
                delNode = nowNode;
                nowNode = nowNode->next;
                preNode->next = nowNode;
                delete delNode;
                listSize--;
                return;
            }
        }
        preNode = nowNode;
        nowNode = nowNode->next;
    }
    cout << -1 << endl;
}

void chain::reserve() {
    if (listSize <= 1)
        return;

    chainNode* preNode = firstNode;
    chainNode* midNode = preNode->next;
    chainNode* nowNode = midNode->next;
    preNode->next = NULL;
    while (nowNode != NULL) {
        midNode->next = preNode;
        preNode = midNode;
        midNode = nowNode;
        nowNode = nowNode->next;
    }
    midNode->next = preNode;
    firstNode = midNode;
}

void chain::search(int valx) {
    chainNode* nowNode = firstNode;
    for (int i = 0; i < listSize; i++) {
        if (nowNode->val == valx) {
            cout << i << endl;
            return;
        }
        else
            nowNode = nowNode->next;
    }
    cout << -1 << endl;
}

void chain::xorsum() {
    chainNode* nowNode = firstNode;
    long long sum = 0;
    for (int i = 0; i < listSize; i++) {
        sum += (i ^ nowNode->val);
        nowNode = nowNode->next;
    }
    cout << sum << endl;
}

void chain::show() {
    chainNode* nowNode = firstNode;
    for (int i = 0; i < listSize; i++) {
        cout << nowNode->val << " ";
        nowNode = nowNode->next;
    }
    cout << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    int theval;
    chain listA, listB, listC;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        //listA.insert(i, theval);
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
        //listB.insert(i, theval);
    }

    int num_c = 0;

    for (int i = 0; i < n; i++, num_c++) {
        listA.insert(i, a[i]);
        listC.insert(num_c, a[i]);
    }
    for (int i = 0; i < m; i++, num_c++) {
        listB.insert(i, b[i]);
        listC.insert(num_c, b[i]);
    }
    //chain_iterator itA = listA.firstNode, itB = listB.firstNode;

    listA.sort();
    listB.sort();
    listC.sort();
    listA.xorsum();
    listB.xorsum();
    listC.xorsum();

    // 对链表listC进行排序
    //listC.sort();
    //listC.show();

    return 0;
}