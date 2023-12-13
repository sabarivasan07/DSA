#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

void updateHeight(Node* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* insert(Node* root, int key) {
    if (root == nullptr) {
        Node* newNode = new Node;
        newNode->key = key;
        newNode->left = newNode->right = nullptr;
        newNode->height = 1;
        return newNode;
    }

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root; 

    updateHeight(root);

    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp; 
            }

            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr)
        return root;

    updateHeight(root);

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

bool search(Node* root, int key) {
    if (root == nullptr)
        return false;
    if (root->key == key)
        return true;
    else if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

bool isAVLTree(Node* root) {
    if (root == nullptr)
        return true;

    int balance = getBalance(root);

    return (abs(balance) <= 1) && isAVLTree(root->left) && isAVLTree(root->right);
}

int getAVLTreeHeight(Node* root) {
    if (root == nullptr)
        return 0;
    return getHeight(root);
}

void inOrderTraversal(Node* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        cout << root->key << " ";
        inOrderTraversal(root->right);
    }
}

int main() {
    Node* root = nullptr;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "In-order traversal of AVL tree: ";
    inOrderTraversal(root);
    cout << endl;

    int keyToSearch = 30;
    if (search(root, keyToSearch))
                cout << keyToSearch << " found in the AVL tree." << endl;
    else
        cout << keyToSearch << " not found in the AVL tree." << endl;

    int keyToDelete = 30;
    root = deleteNode(root, keyToDelete);
    cout << "After deleting " << keyToDelete << ": ";
    inOrderTraversal(root);
    cout << endl;

    if (isAVLTree(root))
        cout << "The tree is an AVL tree." << endl;
    else
        cout << "The tree is not an AVL tree." << endl;

    cout << "Height of AVL tree: " << getAVLTreeHeight(root) << endl;

    return 0;
}
