/**
 * Weekly task number 6 of Algorithmic Methods
 *
 * BinaryTreeAnalyzer is able to find out different properties of binary tree
 * using a variety of different recursive functions.
 * The following functions include:
 *
 * buildTree() -> Builds a binary tree.
 * count() -> Counts all nodes.
 * countNullptrNodes() -> Counts all nullpointers.
 * countCompleteNodes -> Counts every nodes with two children.
 * findHeight -> Finds the total height of the tree.
 *
 *
 * @author Johannes Nupen Theigen
 * @version 06.09.2025
 * @since 05.09.2025
 */
#include <iostream>
using namespace std;

/**
 * Node with ID/key/data and left/right pointers to the child of the node,
 * including a 'seenBefore' variable indicating if the Node has been previously
 * seen.
 */
struct Node {
    char ID;
    Node *left, *right;

    explicit Node(char id) {
        ID = id;
        left = right = nullptr;
    }
};

Node *buildTree();


int gLevel = -1; // The initial value of gLevel set to -1 since the root level is defined as 0.
int gMaxLevel = -1; // The initial value of gMaxLevel set to -1 since the root level is defined as 0.
int totalNodeCount = 0;
int nullPointerCount = 0;
int completeNodeCounter = 0;

/**
 *  Builds a binary tree.
 *
 *  @return   Pointer to the root of the built tree
 */
Node *buildTree() {
    /*   Builds the tree:                                     A
                                                  /                 \
                                             B                          C
                                        /         \                  /
                                      D             E              F
                                  /       \           \          /
                                G           H           I      J
                                  \        / \         /        \
                                   K      L   M       N          O
    */
    Node *nodes[15];
    for (int i = 0; i < 15; i++)
        nodes[i] = new Node(static_cast<char>('A' + i));

    nodes[0]->left = nodes[1];
    nodes[0]->right = nodes[2];
    nodes[1]->left = nodes[3];
    nodes[1]->right = nodes[4];
    nodes[2]->left = nodes[5];
    nodes[3]->left = nodes[6];
    nodes[3]->right = nodes[7];
    nodes[4]->right = nodes[8];
    nodes[5]->left = nodes[9];
    nodes[6]->right = nodes[10];
    nodes[7]->left = nodes[11];
    nodes[7]->right = nodes[12];
    nodes[8]->left = nodes[13];
    nodes[9]->right = nodes[14];
    return nodes[0];
}

/**
 * Counts every node within given a binary tree.
 * @param root the entry point of the tree to be traversed
 * @return
 */
int count(const Node *root) {
    if (root) {
        totalNodeCount++;
        count(root->left);
        count(root->right);
    }
    return totalNodeCount;
}

/**
 * Counts every null pointer within a  given binary tree.
 * An alternative solution would that I discovered after implementation
 * would be to use third rule/property of trees '
 * (binary trees with N nodes have N+1 empty "children"/null(ptr)

 * @param root entry point of the tree to be traversed
 * @return counted null pointers
 */
int countNullptrNodes(const Node *root) {
    if (root) {
        if (root->left == nullptr)
            nullPointerCount++;
        if (root->right == nullptr)
            nullPointerCount++;
        countNullptrNodes(root->left);
        countNullptrNodes(root->right);
    }
    return nullPointerCount;
}

/**
 * Counts all complete nodes (nodes with both left and right children)
 * @param root entry point of the tree to be traversed
 */
void countCompleteNodes(const Node *root) {
    if (root) {
        gLevel++;
        if (root->left && root->right) {
            completeNodeCounter++;
            cout << root->ID << " at level " << gLevel
                  << " with children: " << root->left->ID << " and " << root->right->ID << '\n';
        }
        countCompleteNodes(root->left);
        countCompleteNodes(root->right);
        gLevel--;
    }
}

/**
 * Finds the height of a binary tree.
 * @param root entry point of the tree to be traversed
 */
int findHeight(const Node *root) {
    if (root) {
        gLevel++;
        findHeight(root->left);
        if (gLevel > gMaxLevel) {
            gMaxLevel = gLevel;
        }
        findHeight(root->right);
        gLevel--;
    }
    return gMaxLevel;
}

/**
 * Creates a tree to test out the different functions.
 * @return 0 to indicate that the program has successfully been executed
 */
int main() {
    Node *root = buildTree();

    cout << "\n";

    cout << "Counting all nodes: \n";
    totalNodeCount = 0;
    cout << count(root) << "\n";

    cout << "\n";

    cout << "Counting null pointers: \n";
    nullPointerCount = 0;
    cout << countNullptrNodes(root) << "\n";

    cout << "\n";

    cout << "Counting complete nodes: \n";
    completeNodeCounter = 0;
    countCompleteNodes(root);

    cout << "\n";

    cout << "Total height: \n";
    cout << findHeight(root);

    return 0;
}