#include <stdio.h>
#include <cstddef>
#include <assert.h>
#include <stdlib.h>
#define MAX(a,b) (((a)>(b))?(a):(b))

struct Node{
    int key;
    int color; // 0: black, 1: red
    struct Node* parent;
    struct Node* left;
    struct Node* right;
};

class RBT {
    private:
        //Node* root;
        //Special node tnull
        //Node* TNIL;

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

        void left_rotate_helper(Node* x){
            Node* y = x->right;            
            if(!y) return;
            x->right = y->left;
        

            if (y->left != TNIL) {
                y->left->parent = x;
            }

            y->parent = x->parent;
            if (x->parent == TNIL) {
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
            if(y != TNIL) return;
            x->left = y->right;
            if (y->right) {
                y->right->parent = x;
            }
            y->parent = x->parent;
            if(x->parent == TNIL) {
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
        
    public:
        Node* root;
        Node* TNIL;
        bool verbose;

        RBT(){
            TNIL = new Node;
            TNIL->color = 0;//all leaf nodes are black
            root = TNIL;
        }
        bool insert(int key) {
            /*
            Does NOT insert if dublicate key.
            returns true if success, false if failure (duplicate key)
            */

            //Initialize the node to be inserted
            Node* z = new Node;
            z->key = key;
            
            Node* y = TNIL;
            Node* x = this->root;
            
            while (x != TNIL) {
                y = x;
                if(z->key < x->key) {
                    x = x->left;
                } else if(z->key > x->key){
                    x = x->right;
                } else {//if already exists
                    delete(z);
                    return false;
                }
            }

            z->parent = y;

            if(y == TNIL) {
                this->root = z; //Tree was empty
            } else if(z->key < y->key) {
                y->left = z;
            } else if (z->key > y->key){
                y->right = z;
            } else {
                //something is wrong
            }

            z->left = TNIL;
            z->right = TNIL;
            z->color = 1;
            
            if (z->parent == TNIL) {
                //if the new node is the root, then no need fix
                //printf("I am the root\n");
                return true;
            }
            if (z->parent->parent == TNIL) {
                //printf("My parent is the root\n");
                //if the new node is the direct child of the root, then no need fix
                return true;
            }
            //printf("I need fix-up\n");
            insert_fixup(z);
            return true;
        }

        void insert_fixup(Node* z){
            // for any function call to this function, 
            // z->parent->parent exists and != TNIL
            Node* y;
            /*
            if(z->parent) {
                printf("parent exists\n");
            }
            if(z->parent->color) {
                printf("parent exists with color %i\n", z->parent->color);
            }
            */
            //printf("\n\n\n%i\n\n\n", z->key);
            while(z->parent->color == 1) {
                //printf("inside the while loop\n");
                if(z->parent == z->parent->parent->left){
                    //printf("Case A\n");
                    y = z->parent->parent->right;
                    if(y->color == 1) {
                        z->parent->color = 0;
                        y->color = 0;
                        z->parent->parent->color = 1;
                        z = z->parent->parent;
                    } else {
                        if (z == z->parent->right) {
                            z = z->parent;
                            left_rotate_helper(z);
                        }
                        z->parent->color = 0;
                        z->parent->parent->color = 1;
                        right_rotate_helper(z->parent->parent);
                    }
                } else {
                    //printf("Case B\n");
                    y = z->parent->parent->left;
                    if(y->color == 1) {
                        //printf("Case B-1\n");
                        z->parent->color = 0;
                        y->color = 0;
                        z->parent->parent->color = 1;
                        z = z->parent->parent;
                    } else {
                        //printf("Case B-2\n");
                        if (z == z->parent->left) {
                            //printf("Case B-2-a\n");
                            z = z->parent;
                            right_rotate_helper(z);
                            //printf("completed rotation-1\n");
                        }
                        z->parent->color = 0;
                        z->parent->parent->color = 1;
                        //inspect_node(z);
                        left_rotate_helper(z->parent->parent);
                        //printf("completed rotation-2\n");
                    }
                }
                /*
                if(z->parent->color){
                    printf("the parent's color is %i\n", z->parent->color);
                }
                if(z->parent->parent->left) {
                    printf("bet you can't see mee\n");
                }
                if (z->parent == TNIL) {
                    printf("break the loop\n");
                    break;
                } else {
                    this->inspect(this->root);
                    //printf("parent's key: %i\n", z->parent->key);
                }
                */
            }
            this->root->color = 0;
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
            /*inspect the tree in in-order manner*/
            if(x) {
                if(x == TNIL) {
                    printf("TNIL\n");
                    return;
                }
                inspect(x->left);
                printf("key: %i ", x->key);
                printf("color: %i ", x->color);
                if(x->left == TNIL) {
                    printf("left: TNIL ");
                } else {
                    printf("left: %i ", x->left->key);
                }

                if(x->right == TNIL) {
                    printf("right: TNIL");
                } else {
                    printf("right: %i ", x->right->key);
                }
                
                printf("\n");
                inspect(x->right);
            }
        }

        void inspect_node(Node *x) {
            printf("==============\n");
            printf("key: %i\n", x->key);
            printf("color: %i\n", x->color);
            if(x->left) {
                printf("Left child exists.");
                if(x->left == TNIL) {
                    printf(" which is TNIL\n");
                } else {
                    printf("\n");
                }
            }

            if(x->right) {
                printf("Right child exists.");
                if(x->right == TNIL) {
                    printf(" which is TNIL\n");
                } else {
                    printf("\n");
                }
            }
            printf("==============\n");
        }

        

        

};

int main(int argc, char* argv[]){
    RBT tree;
    tree.set_verbose(true);

    for (int i = 0; i < 10; i ++) {
        int r = rand() % 100;
        // printf("%i", r);
        printf("Inserting %i\n", r);
        tree.insert(r);
    }
    tree.preorder();
    tree.inorder();
    tree.postorder();
    printf("height: %i\n", tree.height());
    tree.inspect(tree.root);

    if (tree.root->parent == tree.TNIL) {
        printf("The root's parent is TNIL\n");
    }

    // printf("++++++++++++\n");
    // tree.left_rotate(49);
    // tree.inspect(tree.root);

    //printf("++++++++++++\n");
    //tree.right_rotate(49);
    //tree.inspect(tree.root);
    //tree.left_rotate(7);
    //printf("root: %i\n", tree.root->key);

}



