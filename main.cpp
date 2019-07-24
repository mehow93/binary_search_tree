#include <iostream>

using namespace std;

class BTS
{
public:
    BTS& insert_node(int var);

    BTS(): pRoot_{nullptr} {}
    ~BTS();
    void show_data();
    void find_min();
    void find_max();



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
    //some functions
    Node* insert_as_subtree(Node* node, int var);
    void show(Node* pNode);
    void delete_from(Node* pNode); // clear data started from choosen node
    void delete_all();
    void search_for_min(Node* pNode);
    void search_for_max(Node* pNode);

};

BTS& BTS::insert_node(int var) // insert root or go insert subtree
{
    if(pRoot_ == nullptr)
        pRoot_ = new Node(var,nullptr,nullptr);
    else
        insert_as_subtree(pRoot_,var);

    return *this;
}
BTS::Node* BTS::insert_as_subtree(Node* node, int var)// create subtree
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

void BTS::show(Node* pNode)
{
    if(pNode != nullptr)
    {
        show(pNode->pLeft);
        cout << pNode->data<<endl;
        show(pNode->pRight);
    }

}

BTS::~BTS()
{
    delete_all();
}


void BTS:: delete_from(Node* pNode)
{
    if(pNode != nullptr)
    {
        delete_from(pNode->pLeft);
        delete_from(pNode->pRight);
        delete pNode;
    }
}
void BTS::delete_all()
{
    delete_from(pRoot_);
    pRoot_ = nullptr;
}

void BTS::show_data()
{
    show(pRoot_);
}
void BTS::search_for_min(Node* pNode)
{
    while(pNode->pLeft != nullptr)
    {
       pNode = pNode->pLeft;
    }

    cout << "Mininimum is: " << pNode->data << endl;
}

void BTS::find_min()
{
    search_for_min(pRoot_);
}

void BTS::search_for_max(Node* pNode)
{
    while(pNode->pRight != nullptr)
    {
       pNode = pNode->pRight;
    }

    cout << "Maximum is: " << pNode->data << endl;
}
void BTS::find_max()
{
    search_for_max(pRoot_);
}
int main()
{
    cout << "Hello World!" << endl;
    BTS first;
    first.insert_node(15);
    first.insert_node(1);
    first.insert_node(7);
    first.insert_node(22);
    first.show_data();
    first.find_min();
    first.find_max();




    return 0;
}
