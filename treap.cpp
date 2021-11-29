/***
ICS621 Final Project
Fall 2021
Reference: CLRS, 2009
***/
#include <stdio.h>
#include <cstddef>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#define MAX(a,b) (((a)>(b))?(a):(b))

struct Node{
    int key;
    int priority;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
};

/***
TODO: do rotate have to return pointer????
Add treap-insert to the latex
***/

class Treap {
    /***
    the priority is represented by strictly negative number.
    0 therefore indicates infinite priority (least prioritized)
    ***/
    private:
        void inorder_aux(Node* x) {
            /***
            Performs inorder traversal from [Node* x]
            ***/
            if (x) {
                inorder_aux(x->left);
                printf("%i ", x->key);
                inorder_aux(x->right);
            }
        }

        void preorder_aux(Node* x) {
            /***
            Performs preorder traversal from [Node* x]
            ***/
            if (x) {
                printf("%i ", x->key);
                preorder_aux(x->left);
                preorder_aux(x->right);
            }
        }

        void postorder_aux(Node* x) {
            /***
            Performs postorder traversal from [Node* x]
            ***/
            if (x) {
                postorder_aux(x->left);
                postorder_aux(x->right);
                printf("%i ", x->key);
            }
        }

        Node* search_aux(Node* x, int key) {
            /***
            Performs search on [int key] in the subtree rooted at [Node* x].
            ***/
            while (x && x->key != key) {
                if (key < x->key) {
                    x = x->left;
                } else {
                    x = x->right;
                }
            }
            return x;
        }

        bool is_empty() {
            /***
            Returns true if the tree is empty, false otherwise
            ***/
            if(!root) {
                return true;
            } else {
                return false;
            }
        }

        Node* min_aux(Node* x) {
            /***
            Returns the pointer to the node with the smallest key in the subtree rooted at [Node* x]
            ***/
            while(x->left) {
                x = x->left;
            }
            return x;
        }

        Node* max_aux(Node* x) {
            /***
            Returns the pointer to the node with the maximum key in the subtree rooted at [Node* x]
            ***/
            while(x->right) {
                x = x->right;
            }
            return x;
        }

        void transplant(Node* u, Node* v) {
            /***
            Transplant the subtree rooted at [Node* v] in the replace of [Node* u]
            ***/
            if(!u->parent) {
                this->root = v;//if u is the root
            } else if(u == u->parent->left) {
                u->parent->left = v;
            } else {
                u->parent->right = v;
            }

            if(v) {
                v->parent = u->parent;
            }
        }

        void delete_key_aux(Node* z) {
            /***
            Performs deletion of node [Node* z]
            ***/
            z = increase_priority(z);
            if(z == z->parent->left){
                z->parent->left = nullptr;
            } else {
                z->parent->right = nullptr;
            }
            delete(z);
        }

        Node* left_rotate_aux(Node* x){
            /***
            Performs left rotate on [Node* x]
            ***/
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

        Node* right_rotate_aux(Node* x) {
            /***
            Performs right rotate on [Node* x]
            ***/
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

        int height_aux(Node* x) {
            /***
            Returns the maximum length of path from [Node* x] to any leaf node in the subtree rooted at [Node* x].
            ***/
            int left = 0;
            int right = 0;
            if(x -> left) {
                left = height_aux(x->left);
            }
            if(x -> right) {
                right = height_aux(x->right);
            }

            return MAX(left, right) + 1;

        }

        Node* increase_priority(Node* x) {
            /***
            Increases node x's priority to 0 (lowest priority)
            so that x becomes a leaf node.
            Returns the pointer to x
            ***/
            x->priority = 0;
            while(x->left || x->right) {
                if(!x->left) {//if only right child exists
                    left_rotate_aux(x);
                } else if (!x->right) {//if only left child exists
                    right_rotate_aux(x);
                } else {//if both child exists
                    if(x->left->priority < x->right->priority) {
                        right_rotate_aux(x);
                    } else {
                        left_rotate_aux(x);
                    }
                }
            }
            return x;
        }
        
    public:
        Node* root;
        bool verbose;
        bool insert(int key) {
            /***
            Creates a new node with [int key] and inserts it in the tree.
            If there is already a node with [int key] then insertion will not take place, 
            in which case false is returned, true otherwise.
            ***/

            Node* node = new Node;
            node->key = key;
            node->priority = - (rand() + 1);//shift by one to make sure 0 never occurs
            
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

            //fix the tree to maintian the heap property, using priority
            while(node->parent && node->priority < node->parent->priority){
                if(node == node->parent->right){// if I am the right child
                    node = left_rotate_aux(node->parent);
                } else if (node == node->parent->left){// if I am the left child
                    node = right_rotate_aux(node->parent);
                } else {
                    printf("something is wrong");
                }
            }

            return true;
        }

        void inorder(){
            /***
            Performs inorder travevrsal from the root
            ***/
            if (verbose) printf("Inorder traversal\n");
            if (is_empty()) {
                if (verbose) printf("The tree is empty\n");
            } else {
                inorder_aux(this->root);
                printf("\n");
            }
        }

        void postorder(){
            /***
            Performs preorder travevrsal from the root
            ***/
            if (verbose) printf("Postorder traversal\n");
            if (is_empty()) {
                if (verbose) printf("The tree is empty\n");
            } else {
                postorder_aux(this->root);
                printf("\n");
            }
        }

        void preorder(){
            /***
            Performs postorder travevrsal from the root
            ***/
            if (verbose) printf("Preorder traversal\n");
            if (is_empty()) {
                if (verbose) printf("The tree is empty\n");
            } else {
                preorder_aux(this->root);
                printf("\n");
            }
        }

        bool search(int key) {
            /***
            Performs search of a node with [int key].
            Returns true if the key exists, false if not.
            ***/
            Node* ret = search_aux(this->root, key);
            if (!ret) {
                if(verbose) printf("The key does not exist in the tree.\n");
                return false;
            } else {
                if(verbose) printf("The key %i exists in the tree.\n", key);
                return true;
            }
        }

        int min() {
            /***
            Returns the minimum key that exists in the tree
            ***/
            if(is_empty()) abort_program("min() on an empty tree");
            return min_aux(this->root)->key;
        }

        int max() {
            /***
            Returns the maximum key that exists in the tree
            ***/
            if(is_empty()) abort_program("max() on an empty tree");
            return min_aux(this->root)->key;
        }

        bool delete_key(int key) {
            /***
            Deletes the node with [int key] if it exists, in which case
            true is returned, false otherwise.
            ***/
            Node* node = search_aux(this->root, key);
            if(!node) {
                if(verbose) printf("The key does not exist.\n");
                return false;
            } else {
                delete_key_aux(node);
                return true;
            }
        }

        void abort_program(const char* error){
            /***
            Auxiliary function to abort program after printing an error message.
            ***/
            printf("ERROR: ");
            printf("%s\n", error);
            printf("*****Aborting the program*****\n");
            exit(1);
        }

        int height() {
            /***
            Calculates the height of the tree
            ***/
            return height_aux(this->root) - 1;
        }

        void set_verbose(bool boolean) {
            /***
            Sets the verbosity setting of the tree
            ***/
            this->verbose = boolean;
        }

        void inspect(Node* x) {
            /***
            Inspect the tree in in-order manner by printing out the information on each node
            ***/
            if(x) {
                if(x==this->root) {
                    printf("root key: %i\n", x->key);
                    printf("height: %i\n", this->height());
                }
                if(!x) {
                    return;
                }
                inspect(x->left);
                printf("key: %i ", x->key);
                if(!x->left) {
                    printf("left: none ");
                } else {
                    printf("left: %i ", x->left->key);
                }

                if(!x->right) {
                    printf("right: none");
                } else {
                    printf("right: %i ", x->right->key);
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
    tree.set_verbose(true);


    for (int i = 0; i < 10000; i ++) {
        int r = rand() % 1000000;
        // printf("%i", r);
        tree.insert(r);
        //printf("Inserting %i\n", r);
    }
    printf("=========\n");
    tree.inspect(tree.root);
    tree.assert_tree(tree.root);

}



