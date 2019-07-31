#include <iostream>

using namespace std;

class BTS
{
public:
    BTS& insert_node(int var);

    BTS(): pRoot_{nullptr} {}
    ~BTS();
    void show_data();
    void print_min();
    void print_max();
    void print_depth();
    void find_node(int x);
    void delete_node(int x);



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
    int depth_of_tree(Node* pNode);
    int delete_node(Node* pNode, int x);
    void search_for_node(Node* pNode, int var);


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
    if(pNode != nullptr)
    {
        while(pNode->pLeft != nullptr)
        {
            pNode = pNode->pLeft;
        }

    cout << "Mininimum is: " << pNode->data << endl;
    }


}

void BTS::print_min()
{
    search_for_min(pRoot_);
}

void BTS::search_for_max(Node* pNode)
{
    if(pNode != nullptr)
    {

        while(pNode->pRight != nullptr)
        {
            pNode = pNode->pRight;
        }

    cout << "Maximum is: " << pNode->data << endl;
    }


}
void BTS::print_max()
{
    search_for_max(pRoot_);
}
int BTS::depth_of_tree(Node* pNode)
{
    if(pNode == nullptr)
    {
        return 0;
    }
    int l_depth = depth_of_tree(pNode->pLeft);
    int r_depth = depth_of_tree(pNode->pRight);
    if(l_depth > r_depth)
    {
        int h = 1 + l_depth;
        return h;
    }
    else
    {
        int h = 1 + r_depth;
        return h;
    }

}
void BTS::print_depth()
{

    cout << "Depth of tree is: " << depth_of_tree(pRoot_)<<endl;
}

void BTS::search_for_node(Node* pNode, int var)
{
    if(pNode != nullptr)
    {

        if(var == pNode->data)
        {
            cout << "The node is: "<< pNode->data <<endl;
        }
        else
        {
            if(var <= pNode->data)
            {
                search_for_node(pNode->pLeft,var);
            }
            else
            {
                search_for_node(pNode->pRight,var);
            }

        }
    }
    else
    {
        cout <<"Node " << var << " does not exist"<<endl;
    }
}
void BTS::find_node(int x)
{
    search_for_node(pRoot_,x);

}
int BTS::delete_node(Node* pNode, int x)
{
    if(pNode != nullptr)
    {

        if(x == pNode->data)
        {
            if(pNode == pRoot_)
            {
                Node* temp_right = pNode->pRight; // to save right saubtree
                if(pNode->pLeft != nullptr) // both subtree or only left
                {


                    Node* temp_left = pNode->pLeft; // we must achieve leaf of left subtree to put there temp_right
                    pRoot_ = temp_left; // this is new root

                    while(temp_left->pRight != nullptr) // moving to leaf
                    {
                        temp_left = temp_left->pRight;
                    }

                    temp_left->pRight = temp_right;// adding old right subtree
                    delete(pNode); // deleting node
                }
                else if (pNode->pLeft == nullptr && pNode->pRight != nullptr) // only right subtree
                {
                    Node* temp_right = pNode->pRight; // to save right saubtree
                    pRoot_ = temp_right;
                    delete(pNode);

                }
                else // only root exists
                {
                    delete(pNode);
                    pRoot_ = nullptr;
                }

            }

        }
        else
        {
            if(x <= pNode->data)
            {
                search_for_node(pNode->pLeft,x);
            }
            else
            {
                search_for_node(pNode->pRight,x);
            }

        }
    }
    else
    {

        cout <<"Tree does not exist"<<endl;
    }


}

void BTS:: delete_node(int x)
{
    delete_node(pRoot_,x);
}
int main()
{
    cout << "Hello World!" << endl;
    BTS first;
    first.insert_node(15);
    first.insert_node(16);
    first.insert_node(18);
    first.insert_node(14);
    first.insert_node(1);
    first.show_data();
    first.delete_node(15);
    first.show_data();






    return 0;
}
