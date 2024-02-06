//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Derek Spaulding
// Version     : 1.0
// Copyright   : Copyright © 2024 SNHU COCE
// Description : Binary Search Tree in C++
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) :
            Node() {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid* bid);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    void recursiveDestructor(Node* node);
    Node* removeNode(Node* node, string* bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void printNodeData(Node* node);
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    this->root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    if (this->root != nullptr) {
        this->recursiveDestructor(this->root);
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    if (this->root != nullptr) {
        this->inOrder(this->root);
    }
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    if (this->root != nullptr) {
        this->postOrder(this->root);
    }
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    if (this->root != nullptr) {
        this->preOrder(this->root);
    }
}

void BinarySearchTree::printNodeData(Node* node) {
    if (node != nullptr) {
        std::cout << "Bid ID: " << node->bid.bidId
            << " || Bid Title: " << node->bid.title
            << " || Bid Amount: " << node->bid.amount
            << " || Bid Fund: " << node->bid.fund << std::endl;
    }
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    if (this->root == nullptr) {
        Node* newNode = new Node(bid);
        this->root = newNode;
    }
    else {
        this->addNode(this->root, &bid);
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    Node* parentNode = nullptr;

    if (this->root != nullptr) {
        parentNode = this->removeNode(this->root, &bidId);
    }

    if (parentNode == nullptr) {
        cout << "Bid not found, returning..." << endl;
    }

    else {
        if (parentNode->left != nullptr) {
            if (parentNode->left->bid.bidId == bidId) {
                Node* nodeToDelete = parentNode->left;
                cout << "Deleting node: ";
                this->printNodeData(nodeToDelete);
                cout << endl;
                parentNode->left = nodeToDelete->left;
                parentNode->right = nodeToDelete->right;
                delete nodeToDelete;
            }
        }
        else if (parentNode->right != nullptr) {
            if (parentNode->right->bid.bidId == bidId) {
                Node* nodeToDelete = parentNode->right;
                cout << "Deleting node: ";
                this->printNodeData(nodeToDelete);
                cout << endl;
                parentNode->left = nodeToDelete->left;
                parentNode->right = nodeToDelete->right;
                delete nodeToDelete;
            }
        }
    }
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    Node* currNode = this->root;

    while (currNode != nullptr) {
        if (currNode->bid.bidId == bidId) {
            return currNode->bid;
        }

        if (currNode->left != nullptr) {
            if (currNode->bid.bidId > bidId) {
                currNode = currNode->left;
                continue;
            }
        }

        if (currNode->right != nullptr) {
            if (currNode->bid.bidId < bidId) {
                currNode = currNode->right;
                continue;
            }
        }

        currNode = nullptr;
    }
    
    Bid emptyBid;
    return emptyBid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid* bid) {
    if (node->bid.bidId > bid->bidId) {
        if (node->left == nullptr) {
            Node* newNode = new Node(*bid);
            node->left = newNode;
        }
        else {
            this->addNode(node->left, bid);
        }
    }
    else {
        if (node->right == nullptr) {
            Node* newNode = new Node(*bid);
            node->right = newNode;
        }
        else {
            this->addNode(node->right, bid);
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {
      // FixMe (9): Pre order root
    if (node->left != nullptr) {
        this->inOrder(node->left);
    }

    this->printNodeData(node);

    if (node->right != nullptr) {
        this->inOrder(node->right);
    }
}
void BinarySearchTree::postOrder(Node* node) {

    if (node->left != nullptr) {
        this->postOrder(node->left);
    }

    if (node->right != nullptr) {
        this->postOrder(node->right);
    }

    this->printNodeData(node);

}

void BinarySearchTree::preOrder(Node* node) {

    this->printNodeData(node);

    if (node->left != nullptr) {
        this->preOrder(node->left);
    }

    if (node->right != nullptr) {
        this->preOrder(node->right);
    }
    
}

void BinarySearchTree::recursiveDestructor(Node* node) {
    if (node->left != nullptr) {
        this->recursiveDestructor(node->left);
    }
    else if (node->right != nullptr) {
        this->recursiveDestructor(node->right);
    }
    else {
        delete node;
        return;
    }
}

Node* BinarySearchTree::removeNode(Node* node, string* bidId)
{
    if (node->left != nullptr) {
        if (node->left->bid.bidId == *bidId) {
            return node;
        }

        if (node->bid.bidId > *bidId) {
            return this->removeNode(node->left, bidId);
        }

        if (node->right != nullptr) {
            if (node->right->bid.bidId == *bidId) {
                return node;
            }
            if (node->bid.bidId < *bidId) {
                return this->removeNode(node->right, bidId);
            }
        }

        return nullptr;
    }

    else if (node->right != nullptr) {
        if (node->right->bid.bidId == *bidId) {
            return node;
        }
        if (node->bid.bidId < *bidId) {
            return this->removeNode(node->right, bidId);
        }
    }

    else {
        return nullptr;
    }

    if (node != nullptr) {
        return node;
    }

    return nullptr;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98110";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
