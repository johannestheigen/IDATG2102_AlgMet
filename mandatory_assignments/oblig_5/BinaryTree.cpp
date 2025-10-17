/**
* This program builds a binary tree and
* has a recursive function that prints the IDs
* of the predecessors of a given node.
*
* @author Johannes Nupen Theigen
* @version 17.10.2025
* @since 17.10.2025
*/
#include <iostream>
#include <iomanip>
using namespace std;

struct Node {
    int ID; // The node's ID/key/name (a unique number).
    Node *left, *right; // Pointers to both subtrees (possibly 'nullptr').
    Node(const char id, Node *l, Node *r) {
        ID = id;
        left = l;
        right = r;
    }
};

Node *buildTree();

bool writeAllPredecessors(Node *node, int id);

/**
 * Builds an example binary tree
 *
 * Det binære treet:
 *          18
 *        /    \
 *      33      47
 *     /  \    /  \
 *   60   27  93   62
 *  /    /    / \
 * 91   83   94 21
 *
 * @return Pointer to the root node (18)
 */
Node *buildTree() {
    auto n94 = new Node(94, nullptr, nullptr),
            n21 = new Node(21, nullptr, nullptr),
            n83 = new Node(83, nullptr, nullptr),
            n91 = new Node(91, nullptr, nullptr),
            n60 = new Node(60, nullptr, nullptr),
            n62 = new Node(62, n94, n21),
            n93 = new Node(93, n83, nullptr),
            n27 = new Node(27, n91, nullptr),
            n47 = new Node(47, n93, n62),
            n33 = new Node(33, n60, n27),
            n18 = new Node(18, n33, n47);
    return n18;
}

/**
* Prints the ID of all nodes that are predecessors of the node with ID equal to id.
*
* @param node starts at the root of the tree.
* @param id The ID or key of the node for which the predecessors should be printed.
* @return true if the ID or key exists, false if the ID or key
* does not exist.
*/
bool writeAllPredecessors(Node *node, int id) {
    if (node) {
        if (node->ID == id) {
            // Checks if the ID being searched for is the same as the current node's ID
            return true;
        }

        bool foundLeft = writeAllPredecessors(node->left, id);
        // Checks if the ID being searched for is in the left subtree
        bool foundRight = writeAllPredecessors(node->right, id);
        // Checks if the ID being searched for is in the right subtree

        if (foundLeft || foundRight) {
            cout << " " << node->ID; // Prints the predecessor of the ID being searched for
            return true;
        }
    }
    return false; // The ID being searched for does not exist
}

/**
 * Main program
 */
int main() {
    Node *root = buildTree();
    writeAllPredecessors(root, 1);
    return 0;
}