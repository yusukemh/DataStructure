#include <stdio.h>
#include <cstddef>

// class Node {
//     private:
//         int key;
//         Node* parent;
//         Node* left;
//         Node* right;
//     public:
//         int get_key() {
//             return this->key;
//         }

//         void set_key(int newKey) {
//             this->key = newKey;
//         }

//         void set_parent(Node* newParent) {
//             this->parent = newParent;
//         }

//         void set_left(Node* newLeft) {
//             this->left = newLeft;
//         }

//         void set_right(Node *newRight) {
//             this->right = newRight;
//         }
// };

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
            if(curr->left != NULL) {
                inorderHelper(curr->left);
            }
            printf("%i", curr->key);
            if(curr->right != NULL) {
                inorderHelper(curr->right);
            }
        }

    public:
        void insert(int key) {
            Node node;
            node.key = key;
            node.left = nullptr;

            if(this->root == NULL) {//if root does not exist
                this->root = &node;
            } else {
                //Node curr = root;
                
            }
        }

        void inorder(){
            //inorderHelper(this->root);
            printf("%i", root->key);
            if(root->left != nullptr){
                printf("I have left child");
            }
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