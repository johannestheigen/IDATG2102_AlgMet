/**
* This program analyzes binary trees using recursive functions.
*
* @author  Frode Haug, NTNU (Original)
* @author Johannes Nupen Theigen (Modifier)
* @version 22.09.2025
* @since 22.09.2025
*/
#include <iostream>          //  cout
#include <cstdlib>           //  (s)rand
using namespace std;

/**
 *  Node (with ID/key/data, level og left/right pointer to the children of the node).
 */
struct Node {
    char ID; // The node's ID/key/name (a char).
    int level; // The node's level in the tree relative to its root.
    Node *left; // Pointer to the left subtree, possibly nullptr.
    Node *right; // Pointer to the right subtree, possibly nullptr.
    Node() {
        ID = '-';
        level = 0;
        left = right = nullptr;
    }
};

void visit(Node *node);
void findValues(const Node *node, int &sumLevel, int &amount);
Node *generate(int depth, int probability);
void setLevel(const Node *node);
void printParents(Node *node);
void traverseB(Node *node);

Node *gRoot; // Pointer to the root of the tree til treets rot.
int gNumber = 65; //  First node is 'A' (ASCII-symbol nr. 65).

/**
 * Main program:
 */
int main() {
    int levelSum = 0, amount = 0;

    srand(0);

    cout << "\nNodes in the starting tree:\n";
    //  Generate testtree (max. 5 levels)
    gRoot = generate(5, 80); // 80 % chance to make a subtree
    traverseB(gRoot); //  Traverses (and shows) the tree.
    getchar();

    cout << "\n\nThe nodes after level is set:\n";
    setLevel(gRoot); //  Sets the level of all nodes
    traverseB(gRoot); //  Traverses (and shows) the tree.
    getchar();

    cout << "\n\n Finds total levels and nodes:\n";
    findValues(gRoot, levelSum, amount); // Finds the sum of the nodes' level and amount.
    cout << "Sum level:  " << levelSum << "\tAmount: " << amount << '\n';

    cout << "Average level:  " // Calculate average level
            << static_cast<float>(levelSum) / amount;
    getchar();

    cout << "\n\nAll leaf nodes' predecessors:\n";
    printParents(gRoot); //  Prints of all predecessor of every leaf node.
    cout << "\n\n";
    return 0;
}


/**
 *  Visits/prints a node's content/data.
 *
 *  @param node - Node to print
 */
void visit(Node *node) {
    cout << ' ' << node->ID << ":  " << node->level << '\n';
}

/**
 * Recursively sums total amount of levels and nodes.
 *
 *  @param node - Node to process
 *  @param sumLevel - The sum of the nodes' total level
 *  @param amount - Total amount of nodes within the tree.
 */
void findValues(const Node *node, int &sumLevel, int &amount) {
    if (node) {
        sumLevel += node->level;
        amount++;

        findValues(node->left, sumLevel, amount);
        findValues(node->right, sumLevel, amount);
    }
}

/**
 * Recursive function that (if possible) generates a node
 * and possibly its left and/or right subtree.
 *
 * @param depth - The depth(level) within in the tree.
 * @param probability - Probability to generate a subtree-
 * @return Pointer to the generated (sub)tree.
 */
Node *generate(const int depth, const int probability) {
    Node *root = nullptr; // Pointer to the return value
    if (depth > 0) {
        if (rand() % 100 < probability) {
            root = new Node; //  New node
            root->left = generate(depth - 1, probability); // Possibly creates left subtree
            root->ID = static_cast<char>(gNumber++); //  Assigns its own ID
            root->right = generate(depth - 1, probability); // Possibly creates right subtree
        }
    }
    return root; //  Returns generated tree or nullptr
}


/**
 * Sets (recursively) all the tree's nodes' level relative to the level of the root.
 *
 *  @param node - Node to process
 */
void setLevel(const Node *node) {
    if (node) {
        if (node->left) {
            node->left->level = node->level + 1;
        }
        if (node->right) {
            node->right->level = node->level + 1;
        }
        setLevel(node->left);
        setLevel(node->right);
    }
}

/**
 * Helper function that recursively writes the node IDs in reverse order
 * along the path from 'node' to 'leaf'.
 *
 * @param node  The root of the current subtree
 * @param leaf  The leaf node to which the path is written
 */

void writePath(const Node *node, Node *leaf) {
    if (node == leaf) {
        cout << node->ID << " ";
    } else {
        if (leaf->ID < node->ID) {
            writePath(node->left, leaf);
        } else
            writePath(node->right, leaf);
        cout << node->ID << " ";
    }
}

/**
 * Recursively writes all leaf nodes' path from the root.
 *
 *  @param node - Node to process
 */
void printParents(Node *node) {
    if (node) {
        if (node->left == nullptr && node->right == nullptr) {
            writePath(gRoot, node);
            cout << "\n";
        }
        printParents(node->left);
        printParents(node->right);
    }
}

/**
 * Inorder traversal of a tree
 *
 *  @param node - Node to process
 *  @see visit(...)
 */
void traverseB(Node *node) {
    if (node) {
        traverseB(node->left);
        visit(node);
        traverseB(node->right);
    }
}