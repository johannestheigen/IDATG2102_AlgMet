/**
* This program analyzes binary trees using recursive functions. The functions
* in this version includes:
*
* buildTree() -> builds a binary tree.
* isBST() -> checks whether a subtree is a binary search tree (BST) or not.
* findMax() -> finds the highest value (ID)
* findMin() -> finds the lowest value (ID)
*
* @author  Frode Haug, NTNU (Original)
* @author Johannes Nupen Theigen (Modifier)
*/


#include <iostream>
using namespace std;

/**
 *  Node (with ID/key/data og left/right pointer to the node's children).
 */
struct Node {
    int ID; //  Node's ID/key/key/name (a number).
    Node *left; // Pointer to left subtree, 'nullptr' if empty
    Node *right; // Pointer to right subtree, 'nullptr' if empty
    //  Constructor:
    Node(const int id, Node *l, Node *r) {
        ID = id;
        left = l, right = r;
    }
};

Node *buildTree();

bool isBST(Node *node);
int findMax(Node *node);
int findMin(Node *node);


Node *gRoot = nullptr; ///<  Pointer to the entire tree's root.
const int MIN = 0, ///<  Values less/greater than all ID's within the tree.
        MAX = 9999;


/**
 *  Main program
 */
int main() {
    gRoot = buildTree();

    cout << "\n\nTesting minimum and maximum value within the tree:\n";
    cout << "Minimum value within the tree is:  " << findMin(gRoot) << '\n'; //   3
    cout << "Maximum value within the tree is:  " << findMax(gRoot) << '\n'; //  82


    cout << "The tree is " << (isBST(gRoot) ? "" : "NOT ") //  Is not
            << "is binary search tree\n\n";
    return 0;
}


/**
 *  Builds a binary test tree.
 *
 *  @return Pointer to the root of the tree that is built
 */
Node *buildTree() {
    //          Building the test tree:                //
    //                       17                       //
    //                  /          \                  //
    //                 33           11                //
    //               /    \       /    \              //
    //              7      35   82      5             //
    //            /   \           \    /              //
    //           27     13        31  34              //
    //                   \        /                   //
    //                   10      57                   //
    //                          /  \                  //
    //                         3   30                 //
    auto n3 = new Node(3, nullptr, nullptr),
            n30 = new Node(30, nullptr, nullptr),
            n10 = new Node(10, nullptr, nullptr),
            n57 = new Node(57, n3, n30),
            n27 = new Node(27, nullptr, nullptr),
            n13 = new Node(13, nullptr, n10),
            n31 = new Node(31, n57, nullptr),
            n34 = new Node(34, nullptr, nullptr),
            n7 = new Node(7, n27, n13),
            n35 = new Node(35, nullptr, nullptr),
            n82 = new Node(82, nullptr, n31),
            n5 = new Node(5, n34, nullptr),
            n33 = new Node(33, n7, n35),
            n11 = new Node(11, n82, n5),
            n17 = new Node(17, n33, n11);
    return n17;
}


/**
 * Finds out if a binary tree is a binary search tree (BST).
 *
 * @param    node  -  Node to process
 * @return   If the subtree is a binary search tree (BST) or not
 * @see      findMax(...)
 * @see      findMin(...)
 */
bool isBST(Node *node) {
    if (node) {
        const int left_max = findMax(node->left);
        const int right_min = findMin(node->right);
        if (left_max < node->ID && right_min > node->ID) { return isBST(node->left) && isBST(node->right); }
        return false;
    }
    return true;
}


/**
 * Find the greatest value (ID) within a binary tree.
 *
 *  @param    node  -  Node to be processed
 *  @return   The highest value (ID) found in the binary tree.
 */
int findMax(Node *node) {
    if (node) {
        int max = node->ID;
        const int left_max = findMax(node->left);
        const int right_max = findMax(node->right);
        if (left_max > max) max = left_max;
        if (right_max > max) max = right_max;
        return max;
    }
    return MIN;
}

/**
 * Finds the lowest value (ID) within a binary tree.
 *
 *  @param    node  -  Node to be processed
 *  @return   The lowest value (ID) found in the binary tree.
 */
int findMin(Node *node) {
    if (node) {
        int min = node->ID;
        const int left_min = findMin(node->left);
        const int right_min = findMin(node->right);
        if (left_min < min)min = left_min;
        if (right_min < min) min = right_min;
        return min;
    }
    return MAX;
}
