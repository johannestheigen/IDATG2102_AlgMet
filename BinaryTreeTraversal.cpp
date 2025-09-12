/** Program example nr 8 - Traverses a binary tree in three/four different ways .
 *
 * The examples show traversal of a binary three using stack/queue
 *
 * @author Frode Haug, NTNU (Original)
 * @author Johannes Nupen Theigen (Modifier)
 * @version 12.09.2025
 * @since 12.09.2025
*/
#include <iostream>                  //  cout
#include <stack>                     //  stack from STL
#include <queue>                     //  queue from STL
using namespace std;


/**
 *  Node (with ID/key/data og left/right pointers to the node's children,
 *        including a 'seenBefore' that can be used if needed).
 */
struct Node {
    char ID;
    bool seenBefore;                     //  'seenBefore' used for postorder traversal.
    Node *left, *right;               //  Initializing constructor:
    Node(char id)  {  ID = id;  left = right = nullptr;   seenBefore = false;  }
};


void  visit(const Node* node);
Node* buildTree();
void  traverseInorder(Node* node);
void  traverseLevelorder(Node* node);
void  traversePostorder(Node* node);
void  traversePreorder(Node* node);


stack <Node*> gStack;                      //  Stack with Node-pointers.
queue <Node*> gQueue;                         //  Queue with Node-pointers.


/**
 *  Main program:
 */
int main()  {
    Node*  root;

    root = buildTree();

    cout << "\n\nPreorder traversal:\n\t";
    traversePreorder(root);

    cout << "\n\nLevelorder traversal:\n\t";
    traverseLevelorder(root);

    cout << "\n\nInorder traversal:\n\t";
    traverseInorder(root);

    cout << "\n\nPostorder traversal:\n\t";
    traversePostorder(root);

    cout << "\n\n";
    return 0;
}


/**
 *  Visits a node and writes out its ID, key and data
 *
 *  @param node - Current node to visit
 */
void  visit(const Node* node) {
    cout << ' ' << node->ID;
}


/**
 *  Builds a binary example-three.
 *
 *  @return Pointer to the built three's root
 */
Node* buildTree() {
/*   Builds the three:                                 A
                                              /                 \
                                         B                          C
                                    /         \                  /
                                  D             E              F
                              /       \           \          /
                            G           H           I      J
                              \        / \         /        \
                               K      L   M       N          O
*/
    Node*  nodes[15];
    for (int i = 0; i < 15; i++)
        nodes[i] = new Node(static_cast <char> ('A' + i));

    nodes[0]->left = nodes[1];  nodes[0]->right = nodes[2];
    nodes[1]->left = nodes[3];  nodes[1]->right = nodes[4];
    nodes[2]->left = nodes[5];
    nodes[3]->left = nodes[6];  nodes[3]->right = nodes[7];
                                nodes[4]->right = nodes[8];
    nodes[5]->left = nodes[9];
                                nodes[6]->right = nodes[10];
    nodes[7]->left = nodes[11]; nodes[7]->right = nodes[12];
    nodes[8]->left = nodes[13];
                                nodes[9]->right = nodes[14];
    return nodes[0];
}


/**
 * Traverses a three using an inorder method using stack.
 *
 *   @param node - Current node to process
 *   @see visit(...)
 */
void traverseInorder(Node* node) {
   while (node  ||  !gStack.empty()) { //  Real node OR something on the stack:
        if (node) {                    //  Real node:
           gStack.push(node);          //  Pushed onto the stack.
           node = node->left;          //  Go to the left.
        } else {                       //  'node' == nullptr:
           node = gStack.top();  gStack.pop();  //  Pop a node
           visit(node);                         //  Visit
           node = node->right;                  //  Go to the right
        }
   }
}

/**
 *  Traverses a three using an LEVELORDER method using queue.
 *
 *   @param node - Current node to process
 *   @see visit(...)
 */
void traverseLevelorder(Node* node) {
    if (node) {                                  //  Real node:
        gQueue.push(node);                          //  Put the root in the queue.
        while (!gQueue.empty()) {                   //  Still nodes left:
            node = gQueue.front();   gQueue.pop();     //  Take out the first node.
            visit(node);                         //  Visit it.
            if (node->left)  gQueue.push(node->left);  //  Add left subtree (if any)
            if (node->right) gQueue.push(node->right); //  and right subtree to the back.
        }
    }
}

/**
 *  Traverses a three using an POSTORDER method using stack.
 *
 *   @param node - Current node to visit
 *   @see visit(...)
 */
void traversePostorder(Node* node) {
    if (node) {                                  //  Real node:
        gStack.push(node);                       //  Push the root onto the stack.
        while (!gStack.empty()) {                //  Still nodes left:
            node = gStack.top();                 //  Get the top node (without removing it)
            if (node->seenBefore) {              //  Check if the node has been seen before
                visit(node);                     //  Visit the node if it has been seen before
                gStack.pop();                    //  Remove the node if it has been seen before
            } else {
                node->seenBefore = true;
            }
            if (node->right && !node->right->seenBefore)
                gStack.push(node->right);        //  Push right subtree if it exists and hasn't been seen
            if (node->left && !node->left->seenBefore)
                gStack.push(node->left);         //  Push left subtree if it exists and hasn't been seen
        }
    }
}

/**
 *  Traverses a three using an PREORDER method using stack.
 *
 *   @param node - Current node to visit
 *   @see visit(...)
 */
void traversePreorder(Node* node) {
    if (node) {                                  //  Real node:
        gStack.push(node);                       //  Push the root onto the stack.
        while (!gStack.empty()) {                //  Still nodes left:
            node = gStack.top();   gStack.pop(); //  Remove the top node.
            visit(node);                         //  Visit it.
            if (node->right)  gStack.push(node->right); //  Push right subtree if it exists
            if (node->left)   gStack.push(node->left);  //  Push left subtree if it exists.
        }
    }
}