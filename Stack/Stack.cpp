#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <string>
using namespace std;

double change_double(vector<char> in)
{
	int i = 0, j = 0, num = 0;
	double out = 0;
	for (i;i < in.size() && in[i] != '.';i++);
	j = i + 1;
	i = i - 1;
	for (i;i >= 0;i--)
	{
		out += pow(10, num) * (in[i] ^ 48);
		num++;
	}
	num = 1;
	for (j;j < in.size();j++)
	{
		out += pow(0.1, num) * (in[j] ^ 48);
		num++;
	}
	return out;
};

int real_len(string in)
{
	int i = 0,j=0;
	while (in[i] !='\0')
	{
		if (in[i] > '9' || in[i] < '0')
		{
			if (in[i] != '.' && in[i] != ' ')
			{
				j++;
			}
		}
		i++;
	}
	i = 0;
	j = 2 * j + 1;
	while (in[i] != '\0')
	{
		if (in[i]=='[' || in[i] == '{'  || in[i] == '(')
		{
			j -= 2;
		}
		i++;
	}
	return j;
};

//dispose the raw string
class new_char
{
public:
	double num=0;
	char process = 'a';
	char fin = 'n';
};

class new_string
{
public:
	new_char* s = nullptr;
	void create(string a, int len)
	{
		s = new new_char[len];
		int i = 0, j = 0, k = 0;
		vector<char> temp;
		while (a[i] != '\0')
		{
			if (a[i] > '9' || a[i] < '0')
			{
				if (a[i] != ' ')
				{
					s[k].process = a[i];
					s[k++].fin = 'p';
				}
				i++;
			}
			else
			{
				j = i;
				for (j;a[j] != ' ';j++)
				{
					if (a[j] > '9' || a[j] < '0')
					{
						if (a[j] != '.')
						{
							break;
						}
					}
					temp.push_back(a[j]);
				}
				i = j;
				s[k++].num = change_double(temp);
				temp.clear();
			}
		}
	}
};
//make stack without data type (using variation)
class node
{
public:
	double operand=0;
	char sign='\0';
	node* next=nullptr;
};

class stack
{
public:
	virtual void push(double in) = 0;
	void pop()
	{
		node* temp = HEAD->next;
		delete HEAD;
		HEAD = temp;

	};
	void clear()
	{
		while (!isempty())
		{
			pop();
		}
	}
	double top_operand()
	{
		return HEAD->operand;
	};
	char top_sign()
	{
		return HEAD->sign;
	};
	bool isempty()
	{
		if (HEAD == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	};
	int precede(char a) //a<=b -1 | a>b 1
	{
		if (isempty()) return 1;
		char b = HEAD->sign;
		int la, lb = 0;
		char arr[3][3] = { {'(','[','{'},{'+','-','}'}, {'*','/',']'} };
		for (int i = 0;i < 3;i++)
		{
			for (int j = 0;j < 3;j++)
			{
				if (arr[i][j] == a) la = i;
				if (arr[i][j] == b) lb = i;
			}
		}
		switch (la - lb)
		{
		case -1:
		case -2:
		case 0:
			return -1;
			break;
		case 1:
		case 2:
			return 1;
			break;
		default:
			return 0;
			break;
		}
	};
	int size()
	{
		node* temp = HEAD;
		int i = 0;
		while (temp != nullptr)
		{
			temp = temp->next;
			i++;
		}
		return i;
	};
	void reverse(node* head)
	{
		if (head->next== nullptr)
		{
			HEAD = head;
			return;
		}
		else
		{
			reverse(head->next);
			node* temp = head;
			temp->next->next = temp;
			temp->next = nullptr;
		}
	};
	void show()
	{
		node* temp = HEAD;
		int flag = 0;
		if (temp->sign == '\0');
		else flag = 1;
		while (temp != nullptr)
		{
			switch (flag)
			{
			case 0:
				cout << temp->operand << " ";
				cout << endl;
				break;
			case 1:
				cout << temp->sign << " ";
				cout << endl;
				break;
			default:
				break;
			}
			temp = temp->next;
		}
	};
	node* HEAD=nullptr;
};
class stack_double :public stack
{
public:
	virtual void push(double in)
	{
		node* fresh = new node;
		fresh->operand = in;
		if (HEAD == nullptr)
		{
			HEAD = fresh;
			fresh->next = nullptr;
		}
		else
		{
			node* temp = HEAD;
			HEAD = fresh;
			fresh->next = temp;
		}
		return;
	};
};
class stack_char :public stack
{
public:
	virtual void push(double in)
	{
		node* fresh = new node;
		fresh->sign = in;
		if (HEAD == nullptr)
		{
			HEAD = fresh;
			fresh->next = nullptr;
		}
		else
		{
			node* temp = HEAD;
			HEAD = fresh;
			fresh->next = temp;
		}
		return;
	};
};

new_char* make_RPN(string in ,int len)
{
	new_string s;
	int q = 0;
	new_char* RPN=new new_char[len];
	s.create(in, len);
	stack* cha = new stack_char;
	for (int i = 0;i < len;i++)
	{
		if (s.s[i].fin == 'n')
		{
			RPN[q].fin = s.s[i].fin;
			RPN[q++].num = s.s[i].num;
			if (i == len - 1)
			{
				while (!cha->isempty())
				{
					RPN[q].process = cha->top_sign();
					RPN[q++].fin = 'p';
					cha->pop();
				}
			}
		}
		else if(s.s[i].fin == 'p')
		{
			if (s.s[i].process == '(' || s.s[i].process == '[' || s.s[i].process == '{')
			{
				cha->push(s.s[i].process);
			}
			else if (s.s[i].process == ')' || s.s[i].process == ']' || s.s[i].process == '}')
			{
				RPN[q].process = cha->top_sign();
				RPN[q++].fin = 'p';
				cha->pop();
				cha->pop();
				if (i == len - 1)
				{
					while (!cha->isempty())
					{
						RPN[q].process = cha->top_sign();
						RPN[q++].fin = 'p';
						cha->pop();
					}
				}
			}
			else if (cha->isempty() || cha->precede(s.s[i].process) == 1)
			{
				cha->push(s.s[i].process);
			}
			else if (cha->precede(s.s[i].process) == -1)
			{
				while (cha->precede(s.s[i].process) == -1)
				{
					RPN[q].process = cha->top_sign();
					RPN[q++].fin = 'p';
					cha->pop();
				}
				cha->push(s.s[i].process);
			}
		}
	}
	return RPN;
};

double calculate_RPN(new_char* RPN,int len)
{
	stack* dou = new stack_double;
	for (int i = 0;i < len;i++)
	{
		if (RPN[i].fin == 'n')
		{
			dou->push(RPN[i].num);
		}
		else if(RPN[i].fin == 'p')
		{
			double a = 0, b = 0;
			switch (RPN[i].process)
			{
			case '+':
				a = dou->top_operand();
				dou->pop();
				b = dou->top_operand();
				dou->pop();
				dou->push(a + b);
				break;
			case '-':
				a = dou->top_operand();
				dou->pop();
				b = dou->top_operand();
				dou->pop();
				dou->push(b - a);
				break;
			case '*':
				a = dou->top_operand();
				dou->pop();
				b = dou->top_operand();
				dou->pop();
				dou->push(a * b);
				break;
			case '/':
				a = dou->top_operand();
				dou->pop();
				b = dou->top_operand();
				dou->pop();
				dou->push(b / a);
				break;
			default:
				break;
			}
		}
	}
	while (!(dou->HEAD->next == nullptr))
	{
		dou->pop();
	}
	return dou->top_operand();
};

int main()
{
	string in;
	double answer = 0;
	getline(cin, in);
	int len=real_len(in);
	answer = calculate_RPN(make_RPN(in, len), len);
	cout << answer;
	return 0;
}