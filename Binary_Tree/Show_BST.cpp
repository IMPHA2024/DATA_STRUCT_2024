#include "Show_BST.h"
#include <iostream>
#include <math.h>
using namespace std;

//just be used paint
string pre(const BT_Node* root)
{
	static string out;
	if (root != nullptr)
	{
		out.push_back(root->data);
		pre(root->left_ptr);
		pre(root->right_ptr);
	}
	return out;
};

//Paint
void draw_interval(int h,int i)
{
	for (int q = 0;q < pow(2, h - i + 1) - 1;q++)
	{
		cout << " ";
	}
};
void draw_front_rear(int h, int i)
{
	for (int k = 0;k < pow(2, h - i) - 1;k++)
	{
		cout << " ";
	}
};

void Draw_BST(const BT_Node* raw,int height)
{
	BT_Node* done = Inject_BT(raw, Create_Perfect(height));
	string data= pre(done);
	string floor = Floororder(done);
	string a = Get_Array(data, floor);
	int len = a.length();
	int h = log(len + 1) / log(2) - 1;
	int index = 0;
	for (int i = 0;i <= h;i++)
	{
		draw_front_rear(h, i);
		cout << a[index++];
		for (int k = 0;k < pow(2, i) - 1;k++)
		{
			draw_interval(h, i);
			cout << a[index++];
		}
		draw_front_rear(h, i);
		cout << endl;
	}
};

//Array
BT_Node* Create_Perfect(int height)
{
	static int hi = height;
	BT_Node* root = nullptr;
	if (height == 0);
	else
	{
		root = new BT_Node();
		root->data = '#';
		root->floor = hi - height + 1;
		root->left_ptr = Create_Perfect(height - 1);
		root->right_ptr = Create_Perfect(height - 1);
	}
	return root;
};

BT_Node* Inject_BT(const BT_Node* root, BT_Node* re)
{
	if (root == nullptr);
	else
	{
		re->data = root->data;
		Inject_BT(root->left_ptr, re->left_ptr);
		Inject_BT(root->right_ptr, re->right_ptr);
	}
	return re;
};

string Floororder(const BT_Node* root)//height<10
{
	static string out;
	if (root != nullptr)
	{
		out.push_back(root->floor^48);
		Floororder(root->left_ptr);
		Floororder(root->right_ptr);
	}
	return out;
};

string Get_Array(string& data, string& floor)
{
	for (int i = 1;i < data.size() - 1;i++)
	{
		int j = i + 1;
		int flag = i;
		char temp1 = floor[j];
		char temp2 = data[j];
		floor[j] = floor[i];
		data[j] = data[i];
		while (temp1 < floor[flag])
		{
			floor[flag] = floor[flag - 1];
			data[flag] = data[flag - 1];
			flag--;
		}
		flag++;
		floor[flag] = temp1;
		data[flag] = temp2;
	}
	return data;
};
