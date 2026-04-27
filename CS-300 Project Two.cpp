//============================================================================
// Name        : CoursePlanner.cpp
// Author      : Grant Prokopis
// Institution : Southern New Hampshire University
// Course      : CS-300 DSA: Analysis and Design
// Description : Advising assistance software using a Binary Search Tree
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//============================================================================
// Course and Node Structures
//============================================================================

/**
 * Structure to hold course information
 */
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

/**
 * Structure for Binary Search Tree nodes
 */
struct Node {
    Course course;
    Node* left;
    Node* right;

    // Default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Initialize with a course
    Node(Course aCourse) : Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree Class Definition
//============================================================================

class BinarySearchTree {
private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void destroyTree(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(Course course);
    void PrintInOrder();
    void SearchAndPrint(string courseNumber);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    destroyTree(root);
}

/**
 * Recursively deletes nodes to free memory
 */
void BinarySearchTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

/**
 * Insert a course into the tree
 */
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        addNode(root, course);
    }
}

/**
 * Recursive helper method for insertion
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    if (course.courseNumber.compare(node->course.courseNumber) < 0) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            addNode(node->left, course);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            addNode(node->right, course);
        }
    }
}

/**
 * Traverse the tree in order to print the alphanumeric list
 * Prints only the Course ID and Title (with double space format)
 */
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.courseNumber << ",  " << node->course.title << endl;
        inOrder(node->right);
    }
}

/**
 * Public method to trigger in-order printing
 */
void BinarySearchTree::PrintInOrder() {
    if (root == nullptr) {
        cout << "The course catalog is currently empty. Please load data first." << endl;
        return;
    }

    cout << "Here is a sample schedule:\n" << endl;
    inOrder(root);
}

/**
 * Search for a course and print its details
 * Prints Course ID, Title, AND Prerequisites
 */
void BinarySearchTree::SearchAndPrint(string courseNumber) {
    Node* current = root;

    while (current != nullptr) {
        // Node match found
        if (current->course.courseNumber == courseNumber) {
            cout << current->course.courseNumber << ", " << current->course.title << endl;

            // Iterate through and format prerequisite vector
            if (!current->course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (size_t i = 0; i < current->course.prerequisites.size(); ++i) {
                    cout << current->course.prerequisites[i];
                    if (i != current->course.prerequisites.size() - 1) {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
            else {
                cout << "Prerequisites: None" << endl;
            }
            return;
        }
        // Traverse left
        else if (courseNumber.compare(current->course.courseNumber) < 0) {
            current = current->left;
        }
        // Traverse right
        else {
            current = current->right;
        }
    }

    cout << "Error: Course " << courseNumber << " not found." << endl;
}

//============================================================================
// Helper Functions 
//============================================================================

/**
 * Utility to trim carriage returns (\r) and whitespace from strings.
 */
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \r\n\t");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \r\n\t");
    return str.substr(first, (last - first + 1));
}

/**
 * Load courses from a CSV file into the Binary Search Tree
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {
    ifstream file(csvPath);
    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string currentLine;

    // Read file line by line
    while (getline(file, currentLine)) {
        stringstream ss(currentLine);
        string token;
        vector<string> rowTokens;

        // Split line by commas
        while (getline(ss, token, ',')) {
            rowTokens.push_back(trim(token));
        }

        // Validate minimum required parameters
        if (rowTokens.size() < 2) continue;

        Course course;
        course.courseNumber = rowTokens[0];
        course.title = rowTokens[1];

        // Append any subsequent tokens as prerequisites
        for (size_t i = 2; i < rowTokens.size(); ++i) {
            if (!rowTokens[i].empty()) {
                course.prerequisites.push_back(rowTokens[i]);
            }
        }

        bst->Insert(course);
    }
    file.close();
}

/**
 * Convert string to uppercase to standardize user input
 */
string toUpperCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

//============================================================================
// Main Application Loop
//============================================================================

int main() {
    BinarySearchTree* bst = new BinarySearchTree();
    int choice = 0;
    string filename;
    string searchTarget;

    // ----------------------------------------------------------------------
    // Initialize Binary Search Tree with default course catalog data
    // ----------------------------------------------------------------------
    // Introductory classes (No prerequisites)
    bst->Insert({ "CSCI100", "Introduction to Computer Science", {} });
    bst->Insert({ "MATH201", "Discrete Mathematics", {} });

    // CSCI Progression
    bst->Insert({ "CSCI101", "Introduction to Programming in C++", {"CSCI100"} });
    bst->Insert({ "CSCI200", "Data Structures", {"CSCI101"} });
    bst->Insert({ "CSCI301", "Advanced Programming in C++", {"CSCI101"} });
    bst->Insert({ "CSCI300", "Introduction to Algorithms", {"CSCI200", "MATH201"} });
    bst->Insert({ "CSCI350", "Operating Systems", {"CSCI301"} });
    bst->Insert({ "CSCI400", "Large Software Development", {"CSCI301", "CSCI350"} });

    // Computer Science Courses
    bst->Insert({ "CS-230-10400-M01", "Operating Platforms", {"CSCI100"} });
    bst->Insert({ "CS-250-12292-M01", "Software Development Lifecycle", {"CSCI101"} });
    bst->Insert({ "CS-255-10443-M01", "System Analysis and Design", {"CS-250-12292-M01"} });
    bst->Insert({ "CS-300-12444-M01", "DSA: Analysis and Design", {"CS-230-10400-M01", "CS-255-10443-M01"} });
    // ----------------------------------------------------------------------

    cout << "Welcome to the course planner.\n" << endl;

    while (choice != 4) {
        cout << "  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  4. Exit" << endl;
        cout << "\nWhat would you like to do? ";

        // Input validation to prevent infinite loops on string input
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
        }

        switch (choice) {
        case 1:
            cout << "Enter the file name to load (e.g., courses.csv): ";
            cin >> filename;
            loadCourses(filename, bst);
            cout << "\n";
            break;

        case 2:
            bst->PrintInOrder();
            cout << "\n";
            break;

        case 3:
            cout << "What course do you want to know about? ";
            cin >> searchTarget;

            // Remove trailing commas if the user accidentally copy/pasted one
            if (!searchTarget.empty() && searchTarget.back() == ',') {
                searchTarget.pop_back();
            }

            // Standardize casing before passing to the search logic
            searchTarget = toUpperCase(searchTarget);
            bst->SearchAndPrint(searchTarget);
            cout << "\n";
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option.\n" << endl;
            break;
        }
    }

    // Free memory upon exit
    delete bst;
    return 0;
}