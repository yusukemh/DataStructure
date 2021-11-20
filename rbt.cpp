#include <stdio.h>
#include <cstddef>
#include <assert.h>
#include <stdlib.h>
#define MAX(a,b) (((a)>(b))?(a):(b))
/*
TODO
implement delete
*/

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
            Returns the pointer to the node with the smallest key in the subtree rooted at curr
            */
            while(curr->left != TNIL) {
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
            printf("You should see 9:%i\n", u->parent->key);
            if(u->parent == TNIL) {//if u is the root
                this->root = v;
            } else if(u == u->parent->left) {
                u->parent->left = v;
            } else {
                printf("wait...\n");
                u->parent->right = v;
            }
            v->parent = u->parent;
        }

        void deleteKeyHelper(Node* z) {
            Node* x;
            Node* y = z;
            int y_original_color = y->color;
            printf("my color: %i\n", y_original_color);
            if(z->left == TNIL) {
                printf("You must see me\n");
                x = z->right;
                transplant(z, z->right);
            } else if(z->right == TNIL) {
                x = z->left;
                transplant(z, z->left);
            } else {
                y = minHelper(z->right);
                y_original_color = y->color;
                x = y->right;
                if(y->parent == z) {
                    x->parent = y;
                } else {
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            delete(z);
            if(y_original_color == 0) {
                printf("You must also see me\n");
                delete_fixup(x);
            }
            printf("I've come here\n");
        }

        void delete_fixup(Node* x) {
            while(x != this->root && x->color == 0) {
                Node* w;
                if(x == x->parent->left) {
                    w = x->parent->right;
                    if(w->color == 1) {
                        w->color = 0;
                        x->parent->color = 1;
                        left_rotate_helper(x->parent);
                        w = x->parent->right;
                    }
                    if(w->left->color == 0 && w->right->color == 0) {
                        w->color = 1;
                        x = x->parent;
                    } else {
                        if(w->right->color == 0) {
                            w->left->color = 0;
                            w->color = 1;
                            right_rotate_helper(w);
                            w = x->parent->right;
                        }
                        w->color = x->parent->color;
                        x->parent->color = 0;
                        w->right->color = 0;
                        left_rotate_helper(x->parent);
                        x = this->root;
                    }
                } else {
                    w = x->parent->left;
                    if(w->color == 1) {
                        w->color = 0;
                        x->parent->color = 1;
                        right_rotate_helper(x->parent);
                        w = x->parent->left;
                    }
                    if(w->right->color == 0 && w->left->color == 0) {
                        w->color = 1;
                        x = x->parent;
                    } else {
                        if(w->left->color == 0) {
                            w->right->color = 0;
                            w->color = 1;
                            left_rotate_helper(w);
                            w = x->parent->left;
                        }
                        w->color = x->parent->color;
                        x->parent->color = 0;
                        w->left->color = 0;
                        right_rotate_helper(x->parent);
                        x = this->root;
                    }
                }
            }
            x->color = 0;
        }

        void left_rotate_helper(Node* x){
            Node* y = x->right;            
            if(y == TNIL) return;
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
            if(y == TNIL) return;
            x->left = y->right;
            if (y->right != TNIL) {
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
            TNIL->right = nullptr;
            TNIL->left = nullptr;
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

            insert_fixup(z);
            return true;
        }

        void insert_fixup(Node* z){
            // for any function call to this function, 
            // z->parent->parent exists and != TNIL
            Node* y;
            while(z->parent->color == 1) {
                if(z->parent == z->parent->parent->left){
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
                } else if(z->parent == z->parent->parent->right){
                    y = z->parent->parent->left;
                    if(y->color == 1) {
                        z->parent->color = 0;
                        y->color = 0;
                        z->parent->parent->color = 1;
                        z = z->parent->parent;
                    } else {
                        if (z == z->parent->left) {
                            z = z->parent;
                            right_rotate_helper(z);
                        }
                        z->parent->color = 0;
                        z->parent->parent->color = 1;
                        left_rotate_helper(z->parent->parent);
                    }
                } else {    
                }
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
                printf("I found the node: %i\n", node->key);
                deleteKeyHelper(node);
                printf("deletion completed\n");
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
                if(x==this->root) {
                    printf("root key: %i\n", x->key);
                    printf("height: %i\n", this->height());
                }
                if(x == TNIL) {
                    //printf("TNIL\n");
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
                if(x != TNIL) {
                    //printf("parents color %i ",x->parent->color);
                }
                if(x->parent == TNIL) {
                    //printf("I HAVE TNIL AS PARENT\n");
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

        bool assert_tree(Node* x) {
            /***
            Check if the following two properties are preserved:
            i) if node is red, then both its children are black
            ii) the # of black nodes from any node to its descendant leaves are equal
            ***/

            //check the color property
            if(x == TNIL || x == this->root) {//TNIL and root has to be black
                if (x->color != 0) {
                    return false;
                }
            } else {//if x is red, then both children have to be black
                if (x->right->color != 0) {
                    return false;
                } else if (x->left->color != 0) {
                    return false;
                }
            }

            if(count_black_node(x->left) != count_black_node(x->right)) {
                return false;
            }
            return true;
        }
        
        int count_black_node(Node* x) {
            if (x == TNIL){return 1;}

            int left = count_black_node(x->left);
            int right = count_black_node(x->right);
            int ret = x->color == 0 ? 1 : 0;

            if (left == -1 || right == -1 || left != right){
                return -1; 
            } else {
                return left + ret;
            }
        }
};

int main(int argc, char* argv[]){
    RBT tree;
    tree.set_verbose(true);

    /*
    for (int i = 0; i < 10; i ++) {
        int r = rand() % 100;
        printf("Inserting %i\n", r);
        tree.insert(r);
        assert(tree.assert_tree(tree.root));
    }
    tree.inspect(tree.root);
    tree.search(23);
    printf("Deleting 23\n");
    tree.deleteKey(23);
    tree.inspect(tree.root);
    */
    for (int i = 0; i < 1000; i ++) {
        int r = rand() % 1000;
        printf("Inserting %i\n", r);
        tree.insert(r);
        assert(tree.assert_tree(tree.root));
    }

    printf("switch up\n");
    for (int i = 0; i < 10; i ++) {
        int r = rand() % 100;
        //printf("Inserting %i\n", r);
        printf("Deleting %i\n", r);
        tree.deleteKey(r);
        tree.inspect(tree.root);
        assert(tree.assert_tree(tree.root));
    }
    tree.deleteKey(49);
    assert(tree.assert_tree(tree.root));
    tree.deleteKey(9);
    assert(tree.assert_tree(tree.root));

    tree.deleteKey(72);
    assert(tree.assert_tree(tree.root));

    tree.deleteKey(58);
    assert(tree.assert_tree(tree.root));
    tree.inspect(tree.root);
}



