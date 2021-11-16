#include <stdio.h>
#include <cstddef>
#include <assert.h>
#include <stdlib.h>
#define MAX(a,b) (((a)>(b))?(a):(b))

struct Node{
    int key;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
};

class BST {
    private:
        Node* root;

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

        Node* search_helper(Node* curr, int key) {
            while (curr && curr->key != key) {
                if (key < curr->key) {
                    curr = curr->left;
                } else {
                    curr = curr->right;
                }
            }

            if(!curr) {
                return curr;
            }

            while(curr != this->root) {
                //printf("Iamin\n");
                curr = splay(curr);
                //break;
                //printf("I am okay\n");
                //printf("%i\n", curr->key);
                //printf("%i, %i", curr->left->key, curr->right->key);
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

        void left_rotate_helper(Node* x){
            Node* y = x->right;
            if(!y) {
                //printf("ME?\n");
                return;
            }
            //printf("not you buddy\n");
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
        }

        void right_rotate_helper(Node* x) {
            Node* y = x-> left;
            if(!y) return;
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

        Node* splay(Node* x){
            //printf("inside splay\n");
            if(!x->parent) {
                //printf("parent dne\n");
            }

            if(!x->parent->parent) {
                //printf("grant parent dne\n");
            }

            if (x->parent == this->root) {// if the parent is the root
                // zig
                //printf("ZIG\n");
                if(x == x->parent->left) {
                    right_rotate_helper(x->parent);
                } else {
                    //printf("right child\n");
                    left_rotate_helper(x->parent);
                    //printf("rotate completed\n");
                }
            } else if (x->parent->parent->left && x == x->parent->parent->left->right) {// if zig-zag (left, right)
                // zig-zag
                //printf("ZIG-ZAG-1\n");
                left_rotate_helper(x->parent);
                right_rotate_helper(x->parent);
            } else if (x->parent->parent->right && x == x->parent->parent->right->left) {// if zig-zag (right, left)
                //zig-zag
                //printf("ZIG-ZAG-2\n");
                right_rotate_helper(x->parent);
                left_rotate_helper(x->parent);
            } else if(x->parent->parent->left && x == x->parent->parent->left->left) {// if zig-zig (left, left)
                //printf("ZIG-ZIG-1\n");
                right_rotate_helper(x->parent->parent);
                right_rotate_helper(x->parent);
            } else if(x->parent->parent->right && x == x->parent->parent->right->right) {// if zig-zig (right, right)
                //printf("ZIG-ZIG-2\n");
                left_rotate_helper(x->parent->parent);
                left_rotate_helper(x->parent);
            }
            //printf("no match\n");
            // if(x) {
            //     printf("%i\n", x->key);
            // }
            return x;
        }
        
    public:
        bool verbose;
        bool insert(int key) {
            /*
            Does NOT insert if dublicate key.
            returns true if success, false if failure (duplicate key)
            */

            Node* node = new Node;
            node->key = key;
            
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
            Node* ret = search_helper(this->root, key);
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
            Node* node = search_helper(this->root, key);
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
            Node* x = search_helper(this->root, key);
            left_rotate_helper(x);
        }

        void right_rotate(int key) {
            Node* x = search_helper(this->root, key);
            right_rotate_helper(x);
        }

        int height() {
            return height_helper(this->root) - 1;
        }

        

        

};

int main(int argc, char* argv[]){
    BST tree;
    tree.set_verbose(true);

    for (int i = 0; i < 10; i ++) {
        int r = rand() % 100;
        // printf("%i", r);
        tree.insert(r);
        printf("Inserting %i\n", r);
    }
    printf("BEFORE\n");
    tree.preorder();
    tree.inorder();
    tree.postorder();
    printf("height: %i\n", tree.height());
    printf("============\n");
    printf("search 49\n");
    tree.search(49);
    printf("height: %i\n", tree.height());
    printf("AFTER\n");
    tree.preorder();
    tree.inorder();
    tree.postorder();
    printf("============\n");

}



