#include <iostream>

using namespace std;

class BTS
{
public:




private:
    struct Node
    {
        Node(int val, Node *ls, Node *rs) : data{val}, pLeft{ls}, pRight{rs}{}
        ~Node() { cout << "Deletion of: " << this->data << endl; }
        int data;
        Node *pLeft;
        Node *pRight;
    };
};
int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
