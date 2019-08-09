#include <iostream>

using namespace std;

template <typename T>
class BTS
{
public:
    BTS& insert_node(T var);

    BTS(): pRoot_{nullptr} {}
    ~BTS();
    void show_data();
    void print_min();
    void print_max();
    void print_depth();
    void find_node(T x);
    void delete_node(T x);



private:
    struct Node
    {
        Node(T val, Node *ls, Node *rs) : data{val}, pLeft{ls}, pRight{rs}{}
        ~Node() { cout << "Deletion of: " << this->data << endl; }
        T data;
        Node *pLeft;
        Node *pRight;
    };


    Node *pRoot_;
    //some functions
    Node* insert_as_subtree(Node* node, T var);
    void show(Node* pNode);
    void delete_from(Node* pNode); // clear data started from choosen node
    void delete_all();
    void search_for_min(Node* pNode);
    Node* return_min(Node* pNode);
    void search_for_max(Node* pNode);
    int depth_of_tree(Node* pNode);
    Node* delete_node(Node* pNode, T x);
    void search_for_node(Node* pNode, T var);


};

template <typename T>
BTS<T>& BTS<T>::insert_node(T var) // insert root or go insert subtree
{
    if(pRoot_ == nullptr)
        pRoot_ = new Node(var,nullptr,nullptr);
    else
        insert_as_subtree(pRoot_,var);

    return *this;
}
template <typename T>
typename BTS<T>::Node* BTS<T>::insert_as_subtree(Node* node, T var)// create subtree
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

template <typename T>
void BTS<T>::show(Node* pNode)
{
    if(pNode != nullptr)
    {
        show(pNode->pLeft);
        cout << pNode->data<<endl;
        show(pNode->pRight);
    }

}

template <typename T>
BTS<T>::~BTS()
{
    delete_all();
}

template <typename T>
void BTS<T>:: delete_from(Node* pNode)
{
    if(pNode != nullptr)
    {
        delete_from(pNode->pLeft);
        delete_from(pNode->pRight);
        delete pNode;
    }
}

template <typename T>
void BTS<T>::delete_all()
{
    delete_from(pRoot_);
    pRoot_ = nullptr;
}

template <typename T>
void BTS<T>::show_data()
{
    show(pRoot_);
}

template <typename T>
void BTS<T>::search_for_min(Node* pNode)
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

template <typename T>
void BTS<T>::print_min()
{
    search_for_min(pRoot_);
}

template <typename T>
void BTS<T>::search_for_max(Node* pNode)
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

template <typename T>
void BTS<T>::print_max()
{
    search_for_max(pRoot_);
}

template <typename T>
int BTS<T>::depth_of_tree(Node* pNode)
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

template <typename T>
void BTS<T>::print_depth()
{

    cout << "Depth of tree is: " << depth_of_tree(pRoot_)<<endl;
}

template <typename T>
void BTS<T>::search_for_node(Node* pNode, T var)
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

template <typename T>
void BTS<T>::find_node(T x)
{
    search_for_node(pRoot_,x);

}

template <typename T>
typename BTS<T>::Node* BTS<T>::return_min(Node* pNode)
{
    if(pNode != nullptr)
    {
        while(pNode->pLeft != nullptr)
        {
            pNode = pNode->pLeft;
        }
           return pNode;
    }
    else
    {
        return nullptr;
    }

}

template <typename T>
typename BTS<T>::Node* BTS<T> ::delete_node(Node* pNode, T x)
{
    if(pNode == nullptr)
    {
        return pNode;
    }
    if(x < pNode->data)
    {
        pNode->pLeft = delete_node(pNode->pLeft,x);
        return pNode;

    }
    if(x > pNode->data)
    {
        pNode->pRight = delete_node(pNode->pRight,x);
        return pNode;
    }
    else // x = pNode->data, so this is node to delete
    {

        if(pNode->pRight == nullptr) // node is leaf, or has only one child
        {

            Node* temp = pNode->pLeft;
            delete(pNode);
            return temp;

        }
        else if (pNode->pLeft == nullptr)
        {

            Node* temp = pNode->pRight;
            delete(pNode);
            return temp;
        }
        else // two children
        {

            Node* temp = return_min(pNode->pRight); // searching for min value of right subtree
            pNode->data = temp->data; // assign min value to chosen node
            pNode->pRight = delete_node(pNode->pRight,temp->data); // deleting min of right subtree
            return pNode;
        }

    }

}

template <typename T>
void BTS<T>:: delete_node(T x)
{
    (void)delete_node(pRoot_,x);
}
int main()
{
    cout << "Hello World!" << endl;
    BTS<int> first;
    first.insert_node(15);
    first.insert_node(7);
    first.insert_node(5);
    first.insert_node(6);
    first.insert_node(22);
    first.insert_node(68);
    first.insert_node(45);
    first.insert_node(18);
    first.show_data();
    first.delete_node(22);
    first.show_data();

    /*BTS<double> second;
    second.insert_node(1.5);
    second.insert_node(2.5);
    second.insert_node(0.7);
    second.insert_node(1.9);
    second.insert_node(1.6);
    second.insert_node(2.7);
    second.show_data();
    second.print_max();
    second.print_min();
    second.print_depth();

    second.delete_node(2.5);
    second.show_data();*/

    return 0;
}
