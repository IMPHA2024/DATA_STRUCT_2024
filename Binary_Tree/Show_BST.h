#ifndef Show_BST_H
#define Show_BST_H
#include <iostream>
using namespace std;

class BT_Node
{
public:
	int floor = 0;
	char data = '\0';
	BT_Node* left_ptr = nullptr;
	BT_Node* right_ptr = nullptr;
};

void Draw_BST(const BT_Node* raw, int height);//由于使用static，若树有所改变，不可二次调用。
string Get_Array(string & data, string  & floor);
BT_Node* Inject_BT(const BT_Node* root, BT_Node* re);
BT_Node* Create_Perfect(int height);
string Floororder(const BT_Node* root);//height<=9
#endif
