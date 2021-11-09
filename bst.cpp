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

    public:
        void insert(int key) {
            Node* node = new Node;
            node->key = key;

            if(!this->root) {//root D.N.E. => set the new node as the root
                this->root = node;
            } else {//If the root exists, find the appropriate location
                Node* parent;
                Node* curr = this->root;
                while (curr) {
                    parent = curr;
                    if(key < curr->key) {
                        curr = curr->left;
                    } else if (key > curr->key) {
                        curr = curr->right;
                    } else {
                        printf("The key already exists.\n");
                        break;
                    }
                }
                node->parent = parent;
                if(key < parent->key) {
                    parent->left = node;
                } else {
                    parent->right = node;
                }
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

};

int main(int argc, char* argv[]){
    BST tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.inorder();
    tree.postorder();
    tree.preorder();
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