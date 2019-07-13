#include <iostream>

using namespace std;

class BTS
{
public:
    BTS& insert_node(int var);
    BTS();
    ~BTS();



private:
    struct Node
    {
        Node(int val, Node *ls, Node *rs) : data{val}, pLeft{ls}, pRight{rs}{}
        ~Node() { cout << "Deletion of: " << this->data << endl; }
        int data;
        Node *pLeft;
        Node *pRight;
    };

    Node *pRoot_;
    Node* insert_as_subtree(Node *node, int var);
};

BTS& BTS::insert_node(int var) // insert root or go insert subtree
{
    if(pRoot_ == nullptr)
        pRoot_ = new Node(var,nullptr,nullptr);
    else
        insert_as_subtree(pRoot_,var);

    return *this;
}
BTS::Node* BTS::insert_as_subtree(Node *node, int var)// create subtree
{
    if(node == nullptr)
        return new Node(var,nullptr,nullptr);
    else
    {
        if(var <= node->data)
        {
            node->pLeft = insert_as_subtree(node->pLeft,var);
            return node;
        }
        else
        {
            node->pRight = insert_as_subtree(node->pRight,var);
            return node;
        }

     }

}
int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
