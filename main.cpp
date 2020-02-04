//HW2 by Dane Brazinski
//SU Net ID: dbbrazin SUID: 533140379
//Due: Wednesday (Feb. 5) at 11:59PM
#include <iostream>

using namespace std;
int m = 50;
class Node {
public:
    int value;
    Node* l_child;
    Node* r_child;
    Node* parent;
    Node() : l_child(nullptr), r_child(nullptr), parent(nullptr) {}
    Node(int i) :value(i), l_child(nullptr), r_child(nullptr), parent(nullptr) {}
};

class Tree { //an n-level full binary tree of 2^n - 1 nodes
public:
    Node* root;
    int level;
    Tree() : root(nullptr), level(0) {}
    Node* makeTree(int n);
    void printTree1(Node* p);
    void printTree2(Node* p);
    void printTree3(Node* p);
    //*************
    //Implement the following 4 member functions using recursion.
    int numOdds(Node* p);//Return the number of odd numbers in the subtree rooted at node pointed by p

    Node* SymCopy(Node* p);//Create a tree symmetric to the subtree rooted at node pointed by p

    bool Find(Node* p, int k);//Return true if value k exists in the subtree rooted at node pointed by p
    //else return false

    int LeftHeavy(Node* p);//For all nodes in the subtree rooted by a node pointed by p,
    //re-structure the tree such that
    //sum of left child branch is >= sum of right child branch.
    //In addition, return the sum of all nodes in the subtree rooted by the node pointed by p.

    //***********
    //Implement the following function.
    //You are not required to use recursion for this implementation.
    void makeMaxHeap(Node* p);
    //Re-structure the subtree rooted at a node pointed by p such that
    //the subtree is a max heap.
    //Remember that a tree is a max heap if all nodes in the tree satisfy the property
    //that (value of left child <= value of parent) and (value of right child <= value of parent).



};
void Tree::makeMaxHeap(Node* p) {
    //Need to implement this function
    Node* temp;
    if(p == nullptr){
        return;
    }
    else if(p->l_child == nullptr && p->r_child == nullptr){
        return;
    }
    else if(p->r_child == nullptr){
        makeMaxHeap(p->l_child);
        return;
    }
    else if(p->l_child == nullptr){
        makeMaxHeap(p->r_child);
        return;
    }
    int lValue =p->l_child->value;
    int rValue =p->r_child->value;
    int pValue =p->value;
    if(lValue <= pValue && rValue <= pValue){

    }
    else if(lValue > rValue) {
        p->l_child->value = pValue;
        p->value = lValue;
    }
    else {
        p->r_child->value = pValue;
        p->value = rValue;
    }
    makeMaxHeap(p->l_child);
    makeMaxHeap(p->r_child);
}

int Tree::LeftHeavy(Node* p) {
    //Need to implement this funciton.
    Node* temp;
    if(p == nullptr){
        return 0;
    }
    else if(p->l_child == nullptr && p->r_child == nullptr){
        return p->value;
    }
    else if(p->r_child == nullptr){
        return p->value + LeftHeavy(p->l_child);
    }
    else if(p->l_child == nullptr){
        return p->value + LeftHeavy(p->r_child);
    }

    int lValue =p->l_child->value;
    int rValue =p->r_child->value;
    if(lValue > rValue) {
        temp = p->l_child;
        p->l_child = p->r_child;
        p->r_child = temp;
    }
    return p->value + LeftHeavy(p->l_child) + LeftHeavy(p->r_child);
}

bool Tree::Find(Node* p, int k) {
    //Need to implement this funciton.
    if(p == nullptr){
        return false;
    }
    else if(p->value == k){
        return true;
    }
    else {
        return Find(p->l_child, k) || Find(p->r_child, k);
    }
}

Node* Tree::SymCopy(Node* p) {
    //Need to implement this funciton.
    Node* temp;
    if(p == nullptr){
        return nullptr;
    }
    else{
        temp = p->l_child;
        p->l_child = SymCopy(p->r_child);
        p->r_child = SymCopy(temp);
        return p;
    }
}

int Tree::numOdds(Node* p) {
    //Need to implement this funciton.
    if(p == nullptr){
        return 0;
    }
    else if(p->value % 2 != 0){
        return 1 + numOdds(p->l_child) + numOdds(p->r_child);
    }
    else {
        return numOdds(p->l_child) + numOdds(p->r_child);
    }
}


Node* Tree::makeTree(int n) { //Create an n-level full binary tree with
    //with random values between 0 ... m-1
    Node* p = new Node(rand() % m);
    if (n == 1) return p;
    p->l_child = makeTree(n - 1);
    p->l_child->parent = p;
    p->r_child = makeTree(n - 1);
    p->r_child->parent = p;
    return p;
}

void Tree::printTree1(Node* p) { //in-order printing
    if (p == nullptr) return;
    printTree1(p->l_child);
    cout << p->value << " ";
    printTree1(p->r_child);
}

void Tree::printTree2(Node* p) { //pre-order printing

    if (p == nullptr) return;
    cout << p->value << " ";
    printTree2(p->l_child);
    printTree2(p->r_child);
}
void Tree::printTree3(Node* p) { //post-order printing
    if (p == nullptr) return;
    printTree3(p->l_child);
    printTree3(p->r_child);
    cout << p->value << " ";
}


int main() {
    Tree T1;
    T1.root = T1.makeTree(4);
    T1.printTree1(T1.root);
    cout << endl;
    T1.printTree2(T1.root);
    cout << endl;
    T1.printTree3(T1.root);
    cout << endl;
    cout << T1.numOdds(T1.root) << endl;
    Tree T2;
    T2.root = T1.SymCopy(T1.root);
    T2.printTree1(T2.root);
    cout << endl;
    T2.printTree2(T2.root);
    cout << endl;
    T2.printTree3(T2.root);
    cout << endl;
    cout << T2.Find(T2.root, 9) << endl;
    cout << T2.LeftHeavy(T2.root) << endl;
    T2.printTree1(T2.root);
    cout << endl;
    T2.printTree2(T2.root);
    cout << endl;
    T2.printTree3(T2.root);
    cout << endl;
    T2.makeMaxHeap(T2.root);
    T2.printTree1(T2.root);
    cout << endl;
    T2.printTree2(T2.root);
    cout << endl;
    T2.printTree3(T2.root);

    return 0;
}