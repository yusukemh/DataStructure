#include <stdio.h>
#include <cstddef>
#include <assert.h>


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

        

    public:
        bool verbose;
        bool insert(int key) {
            /*
            Does NOT insert if dublicate key.
            returns true if success, false if failure (duplicate key)
            */
            //printf("insert is called for %i\n", key);
            Node* node = new Node;
            node->key = key;
            
            Node* curr = this->root;
            Node* parent = nullptr;

            // printf("I bet you can see me\n");
            // //printf("%i\n", parent->key);
            // printf("But not me!\n");
            
            // if(this->root) {
            //     printf("The root exists\n");
            // } else {
            //     printf("The root dne\n");
            // }

            // if(curr) {
            //     printf("curr exists\n");
            // } else {
            //     printf("curr dne\n");
            // }


            while (curr) {
                //printf("I am inside the while loop!\n");
                parent = curr;
                if(node->key < curr->key) {
                    curr = curr->left;
                } else if(node->key > curr->key){
                    curr = curr->right;
                } else {
                    //printf("The key already exists.\n");
                    return false;
                }
            }

            //printf("the key of the node being inserted: %i\n", node->key);

            node->parent = parent;
            //printf("%i\n", parent->key);
            if(!parent) {
                //printf("Yes, tree was empty!\n");
                this->root = node; //Tree was empty
            } else if(node->key < parent->key) {
                //printf("No, tree was not empty-1!\n");
                parent->left = node;
            } else {
                parent->right = node;
                //printf("No, tree was not empty-2!\n");
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
                //return ret;
            } else {
                if(verbose) printf("Tree.min = %i\n", minHelper(this->root)->key);
                //return 0;
            }
        }

        void max() {
            if(isEmpty()) {
                printf("This tree contains no keys.\n");
            } else {
                printf("Tree.max = %i\n", maxHelper(this->root)->key);
            }
        }

        void deleteKey(int key) {
            Node* node = searchHelper(this->root, key);
            if(!node) {
                printf("The key does not exist.\n");
            } else {
                deleteKeyHelper(node);
            }
        }

        void set_verbose(bool boolean) {
            this->verbose = boolean;
        }

        

};

int main(int argc, char* argv[]){
    BST tree;
    tree.set_verbose(true);
    tree.min();
    assert(tree.insert(1));
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(10);
    tree.insert(1);
    tree.inorder();
    tree.postorder();
    tree.preorder();
    tree.search(10);
    tree.min();
    tree.max();
    tree.deleteKey(1);
    tree.inorder();
}





/*
struct Node{
    int value;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
};

int main(int argc, char * argv[]) {
    printf("Hello World\n");
    struct Node node;
    node.value = 1;

    if(node.parent){
        printf("hello");
    }

}

struct BST{
    struct Node root;

    
    
};
*/