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
            if (curr != nullptr) {
                inorderHelper(curr->left);
                printf("HEY:%i", curr->key);
                inorderHelper(curr->right);
            }
        }

    public:
        void insert(int key) {
            Node* node = new Node;
            node->key = key;
            node->left = nullptr;

            if(this->root == nullptr) {//if root does not exist
                this->root = node;
                printf("setting as root");
            } else {
                //Node curr = root;
                
            }
        }

        void inorder(){
            if(this->root->left != nullptr){
                printf("I have left child");
            }
            //printf("%s", this->root->left);
            inorderHelper(this->root);
        }

};

int main(int argc, char* argv[]){
    BST tree;
    tree.insert(1);
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