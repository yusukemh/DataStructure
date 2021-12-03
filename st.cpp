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
#define BILLION 1000000000L

struct Node{
    int key;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
};

class SplayTree {
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
            Bring the node with [int key] to the root if exists.
            ***/
            while (x && x->key != key) {
                if (key < x->key) {
                    x = x->left;
                } else {
                    x = x->right;
                }
            }

            if(!x) {
                return x;
            }

            while(x != this->root) {
                //printf("SPLAY\n");
                //printf("%i\n", x->key);
                splay(x);
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
            Returns the pointer to the node with the smallest key in the subtree rooted at [Node* x]
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
            if(!z->left) {
                transplant(z, z->right);
            } else if(!z->right) {
                transplant(z, z->left);
            } else {
                Node* y = min_aux(z->right);
                if (y->parent != z) {
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
            }
        }

        void left_rotate_aux(Node* x){
            /***
            Performs left rotate on [Node* x]
            ***/
            Node* y = x->right;
            if(!y) return;
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

        void right_rotate_aux(Node* x) {
            /***
            Performs right rotate on [Node* x]
            ***/
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

        Node* splay(Node* x){
            /***
            Performs splay operation on [Node* x]
            ***/
            if (x->parent == this->root) {// if the parent is the root
                // zig
                if(x == x->parent->left) {
                    right_rotate_aux(x->parent);
                } else {
                    left_rotate_aux(x->parent);
                }
            } else if (x->parent->parent->left && x == x->parent->parent->left->right) {// if zig-zag (left, right)
                // zig-zag
                left_rotate_aux(x->parent);
                right_rotate_aux(x->parent);
            } else if (x->parent->parent->right && x == x->parent->parent->right->left) {// if zig-zag (right, left)
                //zig-zag
                right_rotate_aux(x->parent);
                left_rotate_aux(x->parent);
            } else if(x->parent->parent->left && x == x->parent->parent->left->left) {// if zig-zig (left, left)
                right_rotate_aux(x->parent->parent);
                right_rotate_aux(x->parent);
            } else if(x->parent->parent->right && x == x->parent->parent->right->right) {// if zig-zig (right, right)
                left_rotate_aux(x->parent->parent);
                left_rotate_aux(x->parent);
            } else {
                printf("Something is wrong\n");
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


            while(node != this->root) {
                //printf("SPLAY\n");
                //printf("%i\n", x->key);
                splay(node);
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

        bool deleteKey(int key) {
            /***
            Deletes the node with [int key] if it exists, in which case
            true is returned, false otherwise.
            Performs seach at the beginning, which in tern performs splay()
            ***/
            Node* node = search_aux(this->root, key);
            //printf("structure right before deletion\n");
            //inspect(this->root);
            //printf("===============================\n");
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
};

int main(int argc, char* argv[]){
    SplayTree tree;
    tree.set_verbose(false);

    //===============TIMER=====================
    uint64_t t_diff;
    double sec_diff;
    struct timespec t_start, t_end;
    // start timer
    clock_gettime(CLOCK_REALTIME, &t_start);
    //===============TIMER=====================

    printf("file_name =  %s\n", argv[1]);
    FILE* file = fopen(argv[1], "r");
    if(!file) {
        printf("Unable to open file\n");
        exit(-1);
    }
    char line[64];
    char* str_num;
    int num;

    int height;
    int max_height = 0;
    bool height_analysis = true;
    while(fgets(line, sizeof(line), file)) {
        //printf("line: %s", line);
        str_num = &line[2];
        num = strtol(str_num, NULL, 10);
        switch(line[0]) {
            case 'i':
                tree.insert(num);
                height = tree.height();
                if(height_analysis && height > max_height) {
                    max_height = height;
                }
                break;
            case 'd':
                tree.deleteKey(num);
                height = tree.height();
                if(height_analysis && height > max_height) {
                    max_height = height;
                }
                break;
            case 's':
                tree.search(num);
                height = tree.height();
                if(height_analysis && height > max_height) {
                    max_height = height;
                }
                break;
        }
    }

    //===============TIMER=====================
    // end timer
    clock_gettime(CLOCK_REALTIME, &t_end);
    // calculate time elapsed
    t_diff = BILLION * (t_end.tv_sec - t_start.tv_sec) + t_end.tv_nsec - t_start.tv_nsec;
    // convert from nanoseconds to seconds
    sec_diff = (double)t_diff / BILLION;
    printf("elapsed time = %.5f seconds\n", sec_diff);
    if(height_analysis) printf("Max height achieved: %i\n", max_height);
    return 0;

    
}



