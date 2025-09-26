/**
* This program finds the highest odd-level leaf, transforms a binary tree into a binary
* search tree without changing its structure, and identifies two swapped nodes in a BST.
*
* @author  Frode Haug, NTNU (Original)
* @author Johannes Nupen Theigen (Modifier)
* @version 26.09.2025
* @since 26.09.2025
*/
#include <iostream>
using namespace std;

/**
 *  Node (with ID/key/data, level og left/right pointer to the children of the node).
 */
struct Node {
    char ID; // The node's ID/key/name (a char).
    Node *left, *right; // Pointer to both subtrees, possibly nullptr
    Node(char id) {
        ID = id;
        left = right = nullptr;
    }
};

Node *gRoot = nullptr; // Root pointer to the entire tree.
Node *gNoder[10]; // Used to create and process the tree/nodes.
Node *gNode1 = nullptr, // First node in the wrong position.
     *gNode2 = nullptr, // Second node in the wrong position.
     *gPrevious = nullptr; // Helper pointer to find 'gNode1/2'.
int gMaxHOB = -1; // Highest odd-level leaf node.
int gLevel = -1; // Current node level.
char gKeys[101]; // Array with space for ALL tree IDs.
int gNr = 0; // Current index in 'gKeys'.


Node *buildTree();
void findNodes(Node *node);
void insertionSort(char arr[], int N);
void traverseInorder(const Node *node);
void traverseInorder2(Node *node);
void traverseA(const Node *node);
void traverseB(const Node *node);

/**
* Builds a binary tree
*
* @return Points to the root of the tree that has been built
*/
Node *buildTree() {
    gNoder[1] = new Node('A');
    gNoder[2] = new Node('G');
    gNoder[3] = new Node('E');
    gNoder[4] = new Node('O');
    gNoder[5] = new Node('S');
    gNoder[6] = new Node('A');
    gNoder[7] = new Node('R');
    gNoder[8] = new Node('N');
    gNoder[9] = new Node('L');
    gNoder[1]->left = gNoder[2];
    gNoder[1]->right = gNoder[3];
    gNoder[2]->right = gNoder[4];
    gNoder[3]->left = gNoder[5];
    gNoder[3]->right = gNoder[6];
    gNoder[5]->left = gNoder[7];
    gNoder[6]->left = gNoder[8];
    gNoder[6]->right = gNoder[9];
    return gNoder[1];
}


/**
 * Finds and sets pointers to two swapped nodes in a binary search tree.
 *
 *Node *gNode1 = nullptr,      ///<  Node no.1 in the wrong place.
 *Node *gNode2 = nullptr,      ///<  Node no.2 in the wrong place.
 *Node *gPrevious = nullptr;    ///<  Helper pointer for finding gNode1/2
 *
 * @param   node  -  Current node to process
 */
void findNodes(Node *node) {
    if (node) {
        findNodes(node->left);
        if (gPrevious && node->ID < gPrevious->ID) {
            if (!gNode1) {
                gNode1 = gPrevious;
            }
            gNode2 = node;
        }
        gPrevious = node;
        findNodes(node->right);
    }
}

/**
* Sorts 'arr' in ascending order.
*
* @param arr - Array to be sorted ascending
* @param N - Number of elements to sort in the array
*/
void insertionSort(char arr[], const int N) {
    int i, j;
    char v;
    for (i = 2; i <= N; i++) {
        v = arr[i];
        j = i;
        while (arr[j - 1] > v) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = v;
    }
}

/**
* Recursively traverses a binary tree inorder and writes its contents.
*
* @param node - Current node to process
*/
void traverseInorder(const Node *node) {
    if (node) {
        traverseInorder(node->left);
        cout << ' ' << node->ID; //  = 'besok'
        traverseInorder(node->right);
    }
}

/**
 * Recursively inorders the nodes' consecutively sorted IDs,
 * so that the tree becomes a binary search tree.
 *
 * @param node - Current node to process
*/
void traverseInorder2(Node *node) {
    if (node) {
        traverseInorder2(node->left);
        node->ID = gKeys[++gNr];
        traverseInorder2(node->right);
    }
}

/**
 * Recursively find the max level for any odd leaf node(s).
 *
 * @param node - Current node to process
*/
void traverseA(const Node *node) {
    if (node) {
        gLevel++;
        traverseA(node->left);
        traverseA(node->right);
        if (!node->left && !node->right && gLevel % 2 && gLevel > gMaxHOB) {
            gMaxHOB = gLevel;
        }
        gLevel--;
    }
}

/**
 * Converts an arbitrary binary tree into a binary search tree
 * without changing the structure/shape of a tree,
 *
 * @param node - Current node to process
*/
void traverseB(const Node *node) {
    if (node) {
        traverseB(node->left);
        traverseB(node->right);
        gKeys[++gNr] = node->ID;
    }
}

/**
 *  Main Program:
 */
int main() {
    char ch;

    gRoot = buildTree(); // Initializes the tree
    traverseInorder(gRoot); // Output

    cout << "\n\nFinding the max level for odd leaf nodes:\n";
    traverseA(gRoot);
    cout << "Highest level for odd terminal node is: " << gMaxHOB << '\n';

    cout << "\nConvert to binary search tree:\n";
    gNr = 0;
    traverseB(gRoot); // Retrieves the tree's IDs.
    gKeys[0] = '\0';
    insertionSort(gKeys, gNr); // Alphabetically sorts the tree's IDs

    gNr = 0; // Sets all the tree's IDs again, so you get a
    traverseInorder2(gRoot); // binary search tree. This MUST be done inorder!

    cout << "Binary search tree, traversed inorder (i.e. alphabetical print):\n";
    traverseInorder(gRoot); // Prints new search tree contents (sorted).

    cout << "\n\n\nTesting task C - Finding two swapped nodes:\n";
    cout << "Swaps 'G' and 'S'. \n";
    ch = gNoder[7]->ID;
    gNoder[7]->ID = gNoder[9]->ID;
    gNoder[9]->ID = ch;
    traverseInorder(gRoot);

    findNodes(gRoot);

    cout << "\nSwapping back 'node1' and 'node2'. \n";
    ch = gNode1->ID;
    gNode1->ID = gNode2->ID;
    gNode2->ID = ch;
    traverseInorder(gRoot);

    gNode1 = gNode2 = gPrevious = nullptr;
    cout << "\n\nBytter 'E' (rota) og 'O'. \n";
    ch = gNoder[1]->ID;
    gNoder[1]->ID = gNoder[8]->ID;
    gNoder[8]->ID = ch;
    traverseInorder(gRoot);

    findNodes(gRoot);

    cout << "\nSwapping back 'node1' and 'node2'. \n";
    ch = gNode1->ID;
    gNode1->ID = gNode2->ID;
    gNode2->ID = ch;
    traverseInorder(gRoot);

    cout << "\n\n";
    return 0;
}