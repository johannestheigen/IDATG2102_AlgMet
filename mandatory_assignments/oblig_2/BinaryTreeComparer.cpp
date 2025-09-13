/**
 *   Mandatory assignment number 2
 *
 *   This program generates binary trees and provides the following features:
 *   buildTree() -> builds a binart tree
 *   setAllIdsEqual() -> sets all the tree's IDs/keys
 *   isIdentical() -> checks if both trees are identical
 *   isSymmetric() -> checks if a binary tree is symmetric
 *
 *
 *   @author  Frode Haug, NTNU (Original author)
 *   @author Johannes Nupen Theigen (Modifier)
 */
#include <iostream>
using namespace std;


/**
 *  Node (with ID/key/data og left/right pointer to the node's children).
 */
struct Node {
    int ID; //  Nodes ID/key/name (a number).
    Node *left, *right; //  Points to both subtrees (possibly: 'nullptr').
    Node(int id) {
        ID = id;
        left = right = nullptr;
    }
};


Node *gRoot1 = nullptr, *gRoot2 = nullptr; ///< 2x root-pointers

Node *buildTree();

void setAllIdsEqual(Node *t);

bool isIdentical(Node *t1, Node *t2);

bool isSymmetric(Node *t1, Node *t2);


/**
 *  Main program:
 */
int main() {
    gRoot1 = buildTree();
    gRoot2 = buildTree();

    cout << "\n\nBoth trees are "
            << (!isIdentical(gRoot1, gRoot2) ? "NOT " : "") << "identical.";

    delete gRoot2->right->right->left;
    gRoot2->right->right->left = nullptr;
    cout << "\n\nBoth trees are "
            << (!isIdentical(gRoot1, gRoot2) ? "NOT " : "") << "identical.";

    delete gRoot1->right->right->left;
    gRoot1->right->right->left = nullptr;
    cout << "\n\nBoth trees are "
            << (!isIdentical(gRoot1, gRoot2) ? "NOT " : "") << "identical.";

    cout << "\n\nThe tree is "
            << (!isSymmetric(gRoot1, gRoot1) ? "NOT " : "") << "symmetric.";

    delete gRoot1->right->right->right; //  Sletter nr.11 i tre nr.1
    gRoot1->right->right->right = nullptr;
    cout << "\n\nThe tree is " //
            << (!isSymmetric(gRoot1, gRoot1) ? "NOT " : "") << "symmetric.";

    setAllIdsEqual(gRoot1);
    cout << "\n\nThe tree is "
            << (!isSymmetric(gRoot1, gRoot1) ? "NOT " : "") << "symmetric.";

    cout << "\n\n\n";
    return 0;
}


/**
 *  Builds a binary tree
 *
 *  @return   Pointer to the root of the tree that is built
 */
Node *buildTree() {
    Node *p[12];
    for (int i = 1; i <= 11; i++) p[i] = new Node(i); //  Builds the tree //
    p[1]->left = p[2];
    p[1]->right = p[3]; //            1             //
    p[2]->left = p[4];
    p[2]->right = p[5]; //        /       \         //
    p[3]->left = p[6];
    p[3]->right = p[7]; //       2         3        //
    p[5]->left = p[8]; //     /   \     /   \      //
    p[6]->right = p[9]; //    4     5   6     7     //
    p[7]->left = p[10];
    p[7]->right = p[11]; //         /     \   / \    //
    return p[1]; //        8       9 10 11   //
}


/**
 *  Goes through and sets all the tree's IDs/keys to '99'
 *
 *  @param  t  -  Pointer to the (sub)tree's root
 */
void setAllIdsEqual(Node *t) {
    if (t) {
        t->ID = 99;
        setAllIdsEqual(t->left);
        setAllIdsEqual(t->right);
    }
}

/**
 * Finds out and returns if two binary trees are completely identical.
 *
 *  @param   t1  -  Pointer to (sub)tree nr.1
 *  @param   t2  -  Pointer to (sub)tree nr.2
 *  @return  If the two (sub)trees are completely identical or not
 */
bool isIdentical(Node *t1, Node *t2) {
    if (t1 && t2) { // Checks if the nodes exists
        if (t1->ID == t2->ID) { // Checks the nodes' IDs are identical
            return isIdentical(t1->left, t2->left) && isIdentical(t1->right, t2->right); // Checks recursively if the subtrees are identical in both structure and ID
        }
        return false;
    }
    return t1 == t2; // The trees are identical
}


/**
 *  Finds out and returns if a binary tree is completely symmetric
 *
 *  @param   t1  -  Pointer to (sub)tree nr.1
 *  @param   t2  -  Pointer to (sub)tree nr.2
 *  @return  If the complete tree is symmetric around/under the root or not
 */
bool isSymmetric(Node* t1, Node* t2) {
    if (t1 && t2) {  // Checks if the nodes exists
        if (t1->ID == t2->ID) { // Checks the subtrees' nodes' IDs are identical
            return isSymmetric(t1->left, t2->right) && isSymmetric(t1->right, t2->left); // Recursively checks whether the subtree under the left child of t1 mirrors the subtree under the right child of t2, and vice versa.
        }
        return false; // The tree is not symmetric
    }
    return t1 == t2; //  The tree is symmetric
}