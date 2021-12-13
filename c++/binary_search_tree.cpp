/// Name: BinarySearchTree
/// Description: Implementation of bst
/// Detail: Balanced Tree, Binary Tree
/// Guarantee: // BinarySearchTree

struct node
{
    int val;
    struct node *left, *right;
    node(int value)
    {
        val = value;
        left = right = nullptr;
    }
};

class BST
{
private:
    struct node* root = nullptr;
public:
    struct node* search(int val) {
        if(root == nullptr) {
            return nullptr;
        }
        
        else {
            return search_helper(root, val);
        }
    }

    void insert(int val) {
        if(root == nullptr) {
            root = new node(val);
        }
        else {
            if(root->val < val) {
                root->right = insert_helper(root->right, val);
            }
            else {
               root->left = insert_helper(root->left, val);
            }
        }
    }

    void erase(int val) {
        if(root == nullptr) return;

        if(root->val == val) {
            if(root->left && root->right) {
                if(root->right->left) {
                    struct node* next_min_node = next_min_leaf_node(root, root->right);
                    root->val = next_min_node->val;
                    delete next_min_node;
                }
                else {
                    root->val = root->right->val;
                    struct node* temp = root->right;
                    root->right = root->right->right;
                    delete temp;
                }
            }
            else if(root->left) {
                struct node* temp = root;
                root = root->left;
                delete temp;
            }
            else if(root->right) {
                struct node* temp = root;
                root = root->right;
                delete temp;
            }
            else {
                root = nullptr;
            }
        }
        else {
            if(root->val > val) {
                root->left = erase_helper(root->left, val);
            }
            else {
                root->right = erase_helper(root->right, val);
            }
        }
    }

    void inorder() {
        if(root != nullptr)
            inorder_traversal(root);
    }

private:
    struct node* search_helper(struct node* curr, int val) {
        if(curr == nullptr) return nullptr;
        if(curr->val == val) return curr;
        else if(curr->val > val) return search_helper(curr->left, val);
        return search_helper(curr->right, val);
    }

    struct node* insert_helper(struct node* curr, int val) {
        if(curr == nullptr) {
            return new node(val);
        }
        else if(curr->val < val) {
            curr->right = insert_helper(curr->right, val);
            return curr;
        }
        else {
            curr->left = insert_helper(curr->left, val);
            return curr;
        }
    }
    
    struct node* erase_helper(struct node* curr, int val) {
        if(curr == nullptr) return curr;

        if(curr->val == val) {
            if(curr->left && curr->right) {
                if(curr->right->left) {
                    struct node* next_min_node = next_min_leaf_node(curr, curr->right);
                    curr->val = next_min_node->val;
                    next_min_node = nullptr;
                    delete next_min_node;
                }
                else {
                    curr->val = curr->right->val;
                    struct node* temp = curr->right;
                    curr->right = curr->right->right;
                    temp = nullptr;
                    delete temp;
                }
                return curr;
            }
            else if(curr->left) {
                struct node* temp = curr->left;
                curr = nullptr;
                delete curr;
                return temp;
            }
            else if(curr->right) {
                struct node* temp = curr->right;
                curr = nullptr;
                delete curr;
                return temp;
            }
            else {
                delete curr;
                return nullptr;
            }
        }
        else if(curr->val > val) {
            curr->left = erase_helper(curr->left, val);
            return curr;
        }
        else {
            curr->right = erase_helper(curr->right, val);
            return curr;
        }
    }

    struct node* next_min_leaf_node(struct node* par, struct node* curr) {
        if(curr->left) {
            return next_min_leaf_node(curr, curr->left);
        }
        else if(curr->right) {
            par->left = curr->right;
            return curr;
        }
        return curr;
    }

    void inorder_traversal(struct node* curr) {
        if(curr->left != nullptr)
            inorder_traversal(curr->left);

        cout<<curr->val<<" ";

        if(curr->right != nullptr)
            inorder_traversal(curr->right);
    }
}; // BinarySearchTree
