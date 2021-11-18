#include <stdio.h>
#include <cstddef>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#define MAX(a,b) (((a)>(b))?(a):(b))

/*
TODO
implement insert
implement decrease-key
implement delete
*/

struct Node{
    /***
        structure for a Red-Black-Tree Node.
        properties:
    ***/
    int key;
    int priority;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
};

class Treap {
    private:
        //Node* root;

        void inorderHelper(Node* curr) {
            if (curr) {
                inorderHelper(curr->left);
                printf("%i ", curr->key);
                inorderHelper(curr->right);
            }
        }

        void preorderHelper(Node* curr) {
            if (curr) {
                printf("%i ", curr->key);
                preorderHelper(curr->left);
                preorderHelper(curr->right);
            }
        }

        void postorderHelper(Node* curr) {
            if (curr) {
                postorderHelper(curr->left);
                postorderHelper(curr->right);
                printf("%i ", curr->key);
            }
        }

        Node* searchHelper(Node* curr, int key) {
            while (curr && curr->key != key) {
                if (key < curr->key) {
                    curr = curr->left;
                } else {
                    curr = curr->right;
                }
            }
            return curr;
        }

        bool isEmpty() {
            if(!root) {
                return true;
            } else {
                return false;
            }
        }

        Node* minHelper(Node* curr) {
            /*
            Returns the pointer to the node with the smallest key in the dubtree rooted at curr
            */
            while(curr->left) {
                curr = curr->left;
            }
            return curr;
        }

        Node* maxHelper(Node* curr) {
            /*
            Returns the pointer to the node with the maximum key in the subtree rooted at curr
            */
            while(curr->right) {
                curr = curr->right;
            }
            return curr;
        }

        void transplant(Node* u, Node* v) {
            if(!u->parent) {
                this->root = v;//if u is the root
            } else if(u == u->parent->left) {
                u->parent->left = v;
            } else {
                u->parent->right = u;
            }

            if(!v) {
                v->parent = u->parent;
            }
        }

        void deleteKeyHelper(Node* z) {
            if(!z->left) {
                transplant(z, z->right);
            } else if(!z->right) {
                transplant(z, z->left);
            } else {
                Node* y = minHelper(z->right);
                if (y->parent) {
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
            }
        }

        Node* left_rotate_helper(Node* x){
            /*return the pointer to the node closer to the root*/
            Node* y = x->right;
            if(!y){
                printf("You are not supposed to call left_rotate\n");
                return nullptr;
            }
            x->right = y->left;
            if (y->left) {
                y->left->parent = x;
            }
            y->parent = x->parent;
            if (!x->parent) {
                this->root = y;
            } else if (x == x->parent->left) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }
            y->left = x;
            x->parent = y;
            return y;
        }

        Node* right_rotate_helper(Node* x) {
            /*return the pointer to the node closer to the root*/
            Node* y = x-> left;
            if(!y){
                printf("You are not supposed to call left_rotate\n");
                return nullptr;
            }
            x->left = y->right;
            if (y->right) {
                y->right->parent = x;
            }
            y->parent = x->parent;
            if(!x->parent) {
                this->root = y;
            } else if (x == x->parent->left) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }
            y->right = x;
            x->parent = y;
            return y;
        }

        int height_helper(Node* x) {
            int left = 0;
            int right = 0;
            if(x -> left) {
                left = height_helper(x->left);
            }
            if(x -> right) {
                right = height_helper(x->right);
            }

            return MAX(left, right) + 1;

        }
        
    public:
        Node* root;
        bool verbose;
        bool insert(int key) {
            /*
            Does NOT insert if dublicate key.
            returns true if success, false if failure (duplicate key)
            */

            Node* node = new Node;
            node->key = key;
            node->priority = rand();
            printf("priority: %i\n", node->priority);
            
            Node* curr = this->root;
            Node* parent = nullptr;

            while (curr) {
                parent = curr;
                if(node->key < curr->key) {
                    curr = curr->left;
                } else if(node->key > curr->key){
                    curr = curr->right;
                } else {
                    return false;
                }
            }

            node->parent = parent;
            if(!parent) {
                this->root = node; //Tree was empty
            } else if(node->key < parent->key) {
                parent->left = node;
            } else {
                parent->right = node;
            }

            /*
            fix the tree to maintian the heap property, using priority
            */
            while(node->parent && node->priority < node->parent->priority){
                if(node == node->parent->right){// if I am the right child
                    node = left_rotate_helper(node->parent);
                } else if (node == node->parent->left){// if I am the left child
                    node = right_rotate_helper(node->parent);
                } else {
                    printf("something is wrong");
                }
            }

            return true;
        }

        void inorder(){
            if (verbose) printf("Inorder traversal\n");
            inorderHelper(this->root);
            printf("\n");
        }

        void postorder(){
            if (verbose) printf("Post-order traversal\n");
            postorderHelper(this->root);
            printf("\n");
        }

        void preorder() {
            if (verbose) printf("Pre-order traversal\n");
            preorderHelper(this->root);
            printf("\n");
        }

        bool search(int key) {
            /*
            Returns true if the key exists, false if not.
            */
            Node* ret = searchHelper(this->root, key);
            if (!ret) {
                if(verbose) printf("The key does not exist in the tree.\n");
                return false;
            } else {
                if(verbose) printf("The key exists in the tree.\n");
                return true;
            }
        }

        void min() {
            if(isEmpty()) {
                if(verbose) printf("This tree contains no keys.\n");
            } else {
                if(verbose) printf("Tree.min = %i\n", minHelper(this->root)->key);
            }
        }

        void max() {
            if(isEmpty()) {
                printf("This tree contains no keys.\n");
            } else {
                printf("Tree.max = %i\n", maxHelper(this->root)->key);
            }
        }

        bool deleteKey(int key) {
            Node* node = searchHelper(this->root, key);
            if(!node) {
                if(verbose) printf("The key does not exist.\n");
                return false;
            } else {
                deleteKeyHelper(node);
                return true;
            }
        }

        void set_verbose(bool boolean) {
            this->verbose = boolean;
        }

        void left_rotate(int key) {
            /*
            Rotates the tree aound the node with the key.
            Calls the private helper function after checking validity of the input.
            */
            Node* x = searchHelper(this->root, key);
            left_rotate_helper(x);
        }

        void right_rotate(int key) {
            Node* x = searchHelper(this->root, key);
            right_rotate_helper(x);

        }

        int height() {
            return height_helper(this->root) - 1;
        }

        void inspect(Node* x) {
            if(x) {
                if(x==this->root) {
                    printf("root key: %i\n", x->key);
                }
                inspect(x->left);
                printf("key: %3i ", x->key);
                printf("priority: %10i ", int(x->priority/100000));
                if(x->left) {
                    printf("left: %4i ", x->left->key);
                } else {
                    printf("left: none ");
                }
                if(x->right) {
                    printf("right: %4i ", x->right->key);
                } else {
                    printf("right: none");
                }
                printf("\n");
                inspect(x->right);
            }
        }

        bool assert_tree(Node* x) {
            /*
            Make sure the tree property is maintained in every node
            */
            if(x) {
                // check left subtree
                if(!assert_tree(x->left)) return false;
                // check left child
                if (x->left) {
                    if (x->key < x->left->key) return false;
                    if (x->priority > x->left->priority) return false;
                }
                // check right child
                if (x->right) {
                    if (x->key > x->right->key) return false;
                    if (x->priority > x->right->priority) return false;
                }
                // check right subtree
                if (!assert_tree(x->right)) return false;
            }
            return true;
        }
        

        

};

int main(int argc, char* argv[]){
    Treap tree;
    srand (time(NULL));
    tree.set_verbose(true);

    for (int i = 0; i < 1000; i ++) {
        int r = rand() % 10000;
        // printf("%i", r);
        tree.insert(r);
        printf("Inserting %i\n", r);
    }
    printf("=========\n");
    tree.inspect(tree.root);
    // tree.preorder();
    // tree.inorder();
    // tree.postorder();
    // printf("height: %i\n", tree.height());
    // tree.inspect(tree.root);
    // // printf("++++++++++++\n");
    // // tree.left_rotate(49);
    // // tree.inspect(tree.root);

    // printf("++++++++++++\n");
    // tree.right_rotate(49);
    // tree.inspect(tree.root);
    // tree.left_rotate(7);
    // printf("%i\n", tree.root->key);
    assert(tree.assert_tree(tree.root));

}



