
#include <iostream>
using namespace std;

// Create a node
struct Node {
    int number;
    Node* left;
    Node* right;

    Node(int value) {
        number = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;

    // Insert a number
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->number) {
            node->left = insert(node->left, value);
        }
        else if (value > node->number) {
            node->right = insert(node->right, value);
        }

        return node;
    }

    // Search for a number
    bool search(Node* node, int value) {
        if (node == nullptr) {
            return false;
        }

        if (node->number == value) {
            return true;
        }

        if (value < node->number) {
            return search(node->left, value);
        }

        return search(node->right, value);
    }

    // Find the smallest number
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }

        return node;
    }

    // Remove a number
    Node* remove(Node* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->number) {
            node->left = remove(node->left, value);
        }
        else if (value > node->number) {
            node->right = remove(node->right, value);
        }
        else {
            // Case 1: No children
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Case 2: One child
            else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Two children
            Node* temp = findMin(node->right);
            node->number = temp->number;
            node->right = remove(node->right, temp->number);
        }

        return node;
    }

    // Inorder traversal
    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->number << " ";
            inorder(node->right);
        }
    }

    // Preorder traversal
    void preorder(Node* node) {
        if (node != nullptr) {
            cout << node->number << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    // Postorder traversal
    void postorder(Node* node) {
        if (node != nullptr) {
            postorder(node->left);
            postorder(node->right);
            cout << node->number << " ";
        }
    }

    // Calculate height
    int height(Node* node) {
        if (node == nullptr) {
            return -1;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        if (leftHeight > rightHeight) {
            return leftHeight + 1;
        }

        return rightHeight + 1;
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insertNumber(int value) {
        root = insert(root, value);
    }

    bool searchNumber(int value) {
        return search(root, value);
    }

    void removeNumber(int value) {
        root = remove(root, value);
    }

    void showInorder() {
        inorder(root);
        cout << endl;
    }

    void showPreorder() {
        preorder(root);
        cout << endl;
    }

    void showPostorder() {
        postorder(root);
        cout << endl;
    }

    int getHeight() {
        return height(root);
    }
};

int main() {
    BinarySearchTree game;

    // Add 10 secret numbers
    game.insertNumber(50);
    game.insertNumber(30);
    game.insertNumber(70);
    game.insertNumber(20);
    game.insertNumber(40);
    game.insertNumber(60);
    game.insertNumber(80);
    game.insertNumber(10);
    game.insertNumber(35);
    game.insertNumber(65);

    int guess;
    int attempts = 0;

    cout << "       Guess The Number " << endl;
    cout << "-----------------------------------" << endl;

    cout << "Guess one of the 10 secret numbers!" << endl;
    cout << "Hint: Secret numbers are between 10 and 80." << endl;
    cout << "You have 5 attempts." << endl;

    // Play the game
    while (attempts < 5) {
        cout << "\nEnter your guess: ";
        cin >> guess;

        attempts++;

        if (game.searchNumber(guess)) {
            cout << "Congratulations! You found a secret number!" << endl;

            // Remove the guessed number
            game.removeNumber(guess);

            cout << "Number removed from the game." << endl;
        }
        else {
            cout << "Sorry! That number is not in the game." << endl;
        }

        cout << "Attempts left: " << 5 - attempts << endl;
    }

    cout << "\nGame Over!" << endl;

    // Show remaining numbers
    cout << "\nRemaining secret numbers: ";
    game.showInorder();

    // Show all traversals
    cout << "\nTree Traversals:" << endl;

    cout << "Inorder: ";
    game.showInorder();

    cout << "Preorder: ";
    game.showPreorder();

    cout << "Postorder: ";
    game.showPostorder();

    cout << "\nTree height: " << game.getHeight() << endl;

    // Demonstrate removal cases separately
    cout << "\nRemoval Tests:" << endl;

    BinarySearchTree test;

    test.insertNumber(50);
    test.insertNumber(30);
    test.insertNumber(70);
    test.insertNumber(20);
    test.insertNumber(40);
    test.insertNumber(60);
    test.insertNumber(80);
    test.insertNumber(10);
    test.insertNumber(35);
    test.insertNumber(65);

    cout << "\nOriginal numbers: ";
    test.showInorder();

    cout << "Removing 10 (leaf): ";
    test.removeNumber(10);
    test.showInorder();

    cout << "Removing 60 (one child): ";
    test.removeNumber(60);
    test.showInorder();

    cout << "Removing 70 (two children): ";
    test.removeNumber(70);
    test.showInorder();

    return 0;
}
