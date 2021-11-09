#include <stdio.h>
#include <cstddef>

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

        Node* minHelper() {
            /*
            Returns the pointer to the node with the smallest key
            */
            Node* curr = this->root;
            while(curr->left) {
                curr = curr->left;
            }
            return curr;
        }

        Node* maxHelper() {
            /*
            Returns the pointer to the node with the maximum key
            */
            Node* curr = this->root;
            while(curr->right) {
                curr = curr->right;
            }
            return curr;
        }

        

    public:
        void insert(int key) {
            Node* node = new Node;
            node->key = key;
            
            Node* curr = this->root;
            Node* parent;
            
            while (curr) {
                parent = curr;
                if(node->key < curr->key) {
                    curr = curr->left;
                } else if(node->key > curr->key){
                    curr = curr->right;
                } else {
                    printf("The key already exists.\n");
                    return;
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
            
        }

        void inorder(){
            printf("Inorder traversal\n");
            inorderHelper(this->root);
            printf("\n");
        }

        void postorder(){
            printf("Post-order traversal\n");
            postorderHelper(this->root);
            printf("\n");
        }

        void preorder() {
            printf("Pre-order traversal\n");
            preorderHelper(this->root);
            printf("\n");
        }

        void search(int key) {
            /*
            Returns the pointer to the node whose key mathes the query.
            */
            Node* ret = searchHelper(this->root, key);
            if (!ret) {
                printf("The key does not exist in the tree.\n");
            } else {
                printf("The key exists in the tree.\n");
            }
        }

        void min() {
            if(isEmpty()) {
                printf("This tree contains no keys.\n");
            } else {
                printf("Tree.min = %i\n", minHelper()->key);
            }
        }

        void max() {
            if(isEmpty()) {
                printf("This tree contains no keys.\n");
            } else {
                printf("Tree.max = %i\n", maxHelper()->key);
            }
        }

};

int main(int argc, char* argv[]){
    BST tree;
    tree.insert(1);
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