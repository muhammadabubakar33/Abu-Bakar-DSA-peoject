#include <iostream>
#include <string>

// --- Node for Book Tree (Binary Search Tree) ---
struct BookNode {
    int bookID;
    std::string title;
    std::string author;
    bool isAvailable;
    
    BookNode* left;
    BookNode* right;

    BookNode(int id, std::string t, std::string a)
        : bookID(id), title(t), author(a), isAvailable(true), left(nullptr), right(nullptr) {}
};

// --- Node for Borrow Queue / History (Singly Linked List) ---
struct RequestNode {
    int userID;
    std::string userName;
    RequestNode* next;

    RequestNode(int uID, std::string name)
        : userID(uID), userName(name), next(nullptr) {}
};

// --- Library System Logic ---
class LibrarySystem {
private:
    BookNode* root;

    // Helper: Insert book into BST
    BookNode* insertBook(BookNode* node, int id, std::string title, std::string author) {
        if (!node) return new BookNode(id, title, author);
        if (id < node->bookID)
            node->left = insertBook(node->left, id, title, author);
        else if (id > node->bookID)
            node->right = insertBook(node->right, id, title, author);
        return node;
    }

    // Helper: Search book in BST
    BookNode* searchBook(BookNode* node, int id) {
        if (!node || node->bookID == id) return node;
        if (id < node->bookID) return searchBook(node->left, id);
        return searchBook(node->right, id);
    }

    // Helper: In-order traversal for printing catalog
    void displayInOrder(BookNode* node) {
        if (!node) return;
        displayInOrder(node->left);
        std::cout << "ID: " << node->bookID 
                  << " | Title: " << node->title 
                  << " | Author: " << node->author 
                  << " | Status: " << (node->isAvailable ? "Available" : "Checked Out") << "\n";
        displayInOrder(node->right);
    }

public:
    LibrarySystem() : root(nullptr) {}

    void addBook(int id, std::string title, std::string author) {
        root = insertBook(root, id, title, author);
    }

    void displayCatalog() {
        if (!root) {
            std::cout << "Library is empty.\n";
            return;
        }
        displayInOrder(root);
    }

    void checkoutBook(int id) {
        BookNode* book = searchBook(root, id);
        if (!book) {
            std::cout << "Book ID " << id << " not found.\n";
        } else if (!book->isAvailable) {
            std::cout << "Book is already checked out.\n";
        } else {
            book->isAvailable = false;
            std::cout << "Successfully checked out: " << book->title << "\n";
        }
    }
};

int main() {
    LibrarySystem lib;
    
    // Adding books (no arrays used)
    lib.addBook(102, "Data Structures via Nodes", "A. Author");
    lib.addBook(101, "C++ Without Arrays", "B. Coder");
    lib.addBook(105, "Algorithm Analysis", "C. Scientist");

    std::cout << "--- Library Catalog ---\n";
    lib.displayCatalog();

    std::cout << "\n--- Check Out Process ---\n";
    lib.checkoutBook(101);

    std::cout << "\n--- Updated Catalog ---\n";
    lib.displayCatalog();

    return 0;
}