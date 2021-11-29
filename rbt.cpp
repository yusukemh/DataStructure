/***
ICS621 Final Project
Fall 2021
Reference: CLRS, 2009
***/
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
            if(this->root == TNIL) {
                return true;
            } else {
                return false;
            }
        }

        Node* min_aux(Node* x) {
            /***
            Returns the pointer to the node with the smallest key in the subtree rooted at [Node* x]
            ***/
            while(x->left != TNIL) {
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
            if(u->parent == TNIL) {//if u is the root
                this->root = v;
            } else if(u == u->parent->left) {
                u->parent->left = v;
            } else {
                u->parent->right = v;
            }
            v->parent = u->parent;
        }

        void delete_key_aux(Node* z) {
            /***
            Performs deletion of node [Node* z]
            ***/
            Node* x;
            Node* y = z;
            int y_original_color = y->color;
            if(z->left == TNIL) {
                x = z->right;
                transplant(z, z->right);
            } else if(z->right == TNIL) {
                x = z->left;
                transplant(z, z->left);
            } else {
                y = min_aux(z->right);
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
                delete_fixup(x);
            }
        }

        void delete_fixup(Node* x) {
            /***
            Performs set of operations to restore RB property after deletion of a node.
            ***/
            while(x != this->root && x->color == 0) {
                Node* w;
                if(x == x->parent->left) {
                    w = x->parent->right;
                    if(w->color == 1) {
                        w->color = 0;
                        x->parent->color = 1;
                        left_rotate_aux(x->parent);
                        w = x->parent->right;
                    }
                    if(w->left->color == 0 && w->right->color == 0) {
                        w->color = 1;
                        x = x->parent;
                    } else {
                        if(w->right->color == 0) {
                            w->left->color = 0;
                            w->color = 1;
                            right_rotate_aux(w);
                            w = x->parent->right;
                        }
                        w->color = x->parent->color;
                        x->parent->color = 0;
                        w->right->color = 0;
                        left_rotate_aux(x->parent);
                        x = this->root;
                    }
                } else {
                    w = x->parent->left;
                    if(w->color == 1) {
                        w->color = 0;
                        x->parent->color = 1;
                        right_rotate_aux(x->parent);
                        w = x->parent->left;
                    }
                    if(w->right->color == 0 && w->left->color == 0) {
                        w->color = 1;
                        x = x->parent;
                    } else {
                        if(w->left->color == 0) {
                            w->right->color = 0;
                            w->color = 1;
                            left_rotate_aux(w);
                            w = x->parent->left;
                        }
                        w->color = x->parent->color;
                        x->parent->color = 0;
                        w->left->color = 0;
                        right_rotate_aux(x->parent);
                        x = this->root;
                    }
                }
            }
            x->color = 0;
        }

        void left_rotate_aux(Node* x){
            /***
            Performs left rotate on [Node* x]
            ***/
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

        void right_rotate_aux(Node* x) {
            /***
            Performs right rotate on [Node* x]
            ***/
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
            /***
            Creates a new node with [int key] and inserts it in the tree.
            If there is already a node with [int key] then insertion will not take place, 
            in which case false is returned, true otherwise.
            ***/
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
            /***
            Performs set of operations to restore RB property after insertion of a node.
            ***/
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
                            left_rotate_aux(z);
                        }
                        z->parent->color = 0;
                        z->parent->parent->color = 1;
                        right_rotate_aux(z->parent->parent);
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
                            right_rotate_aux(z);
                        }
                        z->parent->color = 0;
                        z->parent->parent->color = 1;
                        left_rotate_aux(z->parent->parent);
                    }
                } else {    
                }
            }
            this->root->color = 0;
        }

        void inorder(){
            /***
            Performs inorder travevrsal from the root
            ***/
            if (verbose) printf("Inorder traversal\n");
            if (this->root == TNIL) {
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
            if (this->root == TNIL) {
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
            if (this->root == TNIL) {
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
                if(verbose) printf("The key exists in the tree.\n");
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
                if(verbose) printf("deletion completed\n");
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
                printf("\n");
                inspect(x->right);
            }
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
            /***
            Counts the number of black node from [Node* x] to TNIL
            ***/
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
    tree.set_verbose(false);

    printf("file_name =  %s\n", argv[1]);
    FILE* file = fopen(argv[1], "r");
    if(!file) {
        printf("Unable to open file\n");
        exit(-1);
    }
    char line[64];
    char* str_num;
    int num;
    while(fgets(line, sizeof(line), file)) {
        //printf("line: %s", line);
        str_num = &line[2];
        num = strtol(str_num, NULL, 10);
        switch(line[0]) {
            case 'i':
                //printf("insert %i\n", num);
                tree.insert(num);
                break;
            case 'd':
                //printf("delete %i\n", num);
                tree.delete_key(num);
                break;
            case 's':
                //printf("serach %i\n", num);
                tree.search(num);
                break;
        }
    }
    printf("%i\n", tree.height());
    printf("complete\n");

    /*
    for (int i = 0; i < 10; i ++) {
        int r = rand() % 100;
        printf("Inserting %i\n", r);
        tree.insert(r);
    }

    tree.inspect(tree.root);
    tree.delete_key(49);
    */
}



