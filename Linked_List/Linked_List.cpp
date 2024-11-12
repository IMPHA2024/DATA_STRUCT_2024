#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <vector>
using namespace std;
class Person
{
    friend void Change_Position();
    friend void Search_Person();
private:
    vector <char> Name;
    int Phone_Num[11] = { 0 };
public:
    void SetElme();
    void GetElme();
};
typedef struct table
{
    Person data;
    int num=0;
    table* Next_Pointer=NULL;
};
table* HEAD;
void Push_Elme(vector <char>& a, string b)
{
    int i = 0;
    char point = b[i];
    while (point != '\0') {
        a.push_back(point);
        point = b[++i];
    }
}
void Push_Elme(int* a, string b)
{
    int i = 0;
    char point = b[i];
    while (point != '\0') {
        a[i] = b[i] ^ 48;
        point = b[++i];
    }
}
void Init_Table(table* &HEAD)
{
    HEAD = NULL;
}
 void Add_Elme(table* &HEAD)
{
    table *a = new table;
    if (HEAD == NULL)
    {
        HEAD  = a;
        a->Next_Pointer = NULL;
        a->num = 1;
        a->data.SetElme();
        cout << "\033[37;46;1m已新建通信人\033[0m" << endl;
        Sleep(1500);
    }
    else
    {
        table* my = HEAD;
        while (my->Next_Pointer != NULL)
        {
            my = my->Next_Pointer;
        }
        my->Next_Pointer = a;
        a->Next_Pointer = NULL;
        a->num = my->num + 1;
        a->data.SetElme();
        cout << "\033[37;46;1m已新建通信人\033[0m" << endl;
        Sleep(1000);
    }
}
 void Insert_Elme()
 {
     table* a = new table;
     int left = 2, right = 3;
     cout <<endl<< "*说说要插入哪吧?!*" << endl;
     cout << "请输入插入哪两个通信人之间" << endl;
     cin >> left >> right;
     //判断
     table* my = HEAD;
     for (int i = 1; i < left; i++)
     {
         my = my->Next_Pointer;
     }
     table* go = my->Next_Pointer;
     my->Next_Pointer = a;
     a->Next_Pointer = go;
     a->num = my->num + 1;
     a->data.SetElme();
     my = a;
     while (go != NULL)
     {
         go->num = my->num+1;
         my = go;
         go = go->Next_Pointer;
     }
     cout << "\033[37;46;1m已插入通信人\033[0m" << endl;
     Sleep(1000);
 }
void Del_Elme(table* &HEAD)
{
    int n;
    cout << "删除第几个通信人？";
    cin >> n;
    table* sur = HEAD;
    if (n == 1)
    {
        HEAD = sur->Next_Pointer;
        delete sur;
    }
    else
    {
        for (int i = 1; i < n - 1; i++)
        {
            sur = sur->Next_Pointer;
        }
        table* temp = sur->Next_Pointer->Next_Pointer;
        delete sur->Next_Pointer;
        sur->Next_Pointer = temp;
    }
    table* go = HEAD;
    int i = 1;
    while(go!=NULL)
    {
        go->num = i;
        go = go->Next_Pointer;
        i++;
    }
    cout << "\033[37;46;1m已删除通信人\033[0m" << endl;
}
void Delet_Table(table* &HEAD)
{
    char flag;
    cout << "\033[37;41m确认清空通信录？（y/n）\033[0m";
    cin >> flag;
    if (flag == 'n' || flag == 'N'){}
    else if(flag == 'y' || flag == 'Y')
    {
        table* sur = HEAD;
        table* del = HEAD;
        while (sur!= NULL)
        {
            sur = sur->Next_Pointer;
            delete del;
            del = sur;
        }
        HEAD = NULL;
        cout << "\033[37;46;1m已清空通信录\033[0m" << endl;
    }
}
void Change_Position()
{
    int n;
    table* sur = HEAD;
    while (sur->Next_Pointer != NULL)
    {
        sur = sur->Next_Pointer;
    }
    n = sur->num;
    Person* temp = new Person[n];
    table* go = HEAD;
    for (int i = 0; i < n; i++)
    {
        temp[i] = go->data;
        go = go->Next_Pointer;
    }
    go = HEAD;
    int* len = new int[n];
    cout << "\033[37;46m请输入调整后的编号顺序\033[0m";
    for (int i = 0; i < n; i++)
    {
        cin >> len[i];
    }
    for (int i = 0; i < n; i++)
    {
        go->data = temp[len[i] - 1];
        go = go->Next_Pointer;
    }
    delete[]len;
    delete[]temp;
}
void Search_Person()
{
    string aaa = " \033[37;46;1m*-----------------------------------------------------*\033[0m";
    string bbb = "\033[37;46;1m+\t\t\t\t\t\t\t+\033[0m";
    cout << aaa << endl;
    for (int i = 0; i < 3; i++)
    {
        if (i == 1) { cout<<"\033[37;46;1m+\033[0m"<<"\t\t\t查找模式\t\t\t" <<"\033[37;46;1m+\033[0m"<< endl; }
        else { cout << bbb << endl; }
    }
    cout << aaa << endl;
    string a;
    cout << "输入通信人姓名"<<endl;
    cin >> a;
    vector <char> b;
    Push_Elme(b, a);
    table* temp=HEAD;
    while (temp!=NULL)
    {
        if (b != temp->data.Name)
        {
            temp = temp->Next_Pointer;
        }
        else
        {
            break;
        }
    }
    if (temp == NULL)
    {
        cout << "未找到通信人"<< endl;
    }
    else
    {
        temp->data.GetElme();
    }
    system("pause");
}
void Draw_Graph(int status)
{
    string set = "1.新建通信人";
    string ins = "2.插入通信人";
    string get = "3.查寻通信人";
    string del = "4.删除通信人";
    string tab = "5.清空通信录";
    string pos = "6.调整通信录顺序";
    string sur = "Q查找模式";
    if (status == 1) { set = "\033[36;47m1.新建通信人\033[0m"; }
    if (status == 2) { ins= "\033[36;47m2.插入通信人\033[0m"; }
    if (status == 3) { get = "\033[36;47m3.查寻通信人\033[0m"; }
    if (status == 4) { del = "\033[36;47m4.删除通信人\033[0m"; }
    if (status == 5) { tab = "\033[36;47m5.清空通信录\033[0m"; }
    if (status == 6) { pos = "\033[36;47m6.调整通信录顺序\033[0m"; }
    string a = " \033[37;46;1m*-----------------------------------------------------*\033[0m";
    string b = "\033[37;46;1m+\t\t\t\t\t\t\t+\033[0m";
    cout << a << endl;
    for (int i = 0; i < 15; i++)
    {
        if (i==2) { cout << "\033[37;46;1m+\033[0m\t\t\t"<<set<<"\033[37;46;1m\t\t\t+\033[0m"<<endl; }
        else if(i==4) {cout<<"\033[37;46;1m+\033[0m\t\t\t" <<ins<< "\033[37;46;1m\t\t\t+\033[0m" <<endl; }
        else if (i==6) { cout<<"\033[37;46;1m+\033[0m\t\t\t"<<get<<"\033[37;46;1m\t\t\t+\033[0m"<<endl;}
        else if (i==8) { cout<<"\033[37;46;1m+\033[0m\t\t\t"<<del<<"\033[37;46;1m\t\t\t+\033[0m"<<endl;}
        else if (i==10) { cout<<"\033[37;46;1m+\033[0m\t\t\t"<<tab<<"\033[37;46;1m\t\t\t+\033[0m"<<endl;}
        else if (i==12){cout<<"\033[37;46;1m+\033[0m\t\t\t"<<pos<<"\033[37;46;1m\t\t+\033[0m"<<endl;}
        else if (i==14){cout <<"\033[37;46;1m+\033[0m\t\t\t\t\t      "<<sur<<" \033[37;46;1m+\033[0m"<<endl;}
        else { cout << b << endl; }
    }
    cout << a << endl;
}
void Get_Event(table* &HEAD)
{
    int len=0;
    table* sur = HEAD;
    if (sur != NULL)
    {
        while (sur->Next_Pointer != NULL)
        {
            sur = sur->Next_Pointer;
        }
        len = sur->num;
    }
    char n=0;
    table* temp = HEAD;
    cin >> n;
    switch (n)
    {
    case '1':
        system("cls");
        Draw_Graph(1);
        Add_Elme(HEAD);
        break;
    case '2':
        system("cls");
        Draw_Graph(2);
        if (HEAD == NULL || HEAD->Next_Pointer == NULL)
        {
            cout << "现在还插入不了噢！！" << endl;
            system("pause");
        }
        else
        {
            for (int i = 0; i < len; i++)
            {
                cout << temp->num << "号通信人." << endl;
                temp->data.GetElme();
                temp = temp->Next_Pointer;
            }
            Insert_Elme();
        }
        break;
    case '3':
        system("cls");
        Draw_Graph(3);
        if (HEAD == NULL)
        {
            cout << "通信录是空的欸 QAQ "<<endl;
        }
        else
        {
            for (int i = 0; i < len; i++)
            {
                cout << temp->num<<"号通信人."<<endl;
                temp->data.GetElme();
                temp = temp->Next_Pointer;
            }
        }
        system("pause");
        break;
    case '4':
        system("cls");
        Draw_Graph(4);
        if (HEAD == NULL)
        {
            cout << "通信录是空的欸 QAQ " << endl;
        }
        else
        {
            for (int i = 0; i < len; i++)
            {
                cout << temp->num << "号通信人." << endl;
                temp->data.GetElme();
                temp = temp->Next_Pointer;
            }
            Del_Elme(HEAD);
        }
        system("pause");
        break;
    case '5':
        system("cls");
        Draw_Graph(5);
        Delet_Table(HEAD);
        break;
    case '6':
        system("cls");
        Draw_Graph(6);
        for (int i = 0; i < len; i++)
        {
            cout << temp->num << "号通信人."<<endl;
            temp->data.GetElme();
            temp = temp->Next_Pointer;
        }
        Change_Position();
        break;
    case 'Q':
    case 'q':
        system("cls");
        Search_Person();
        break;
    default:
        cout << "无效操作" << endl;
        system("pause");
        break;
    }
}
void Person::SetElme()
{
    string a, b;
    cout << "输入通信人姓名"<<endl;
    cin >> a;
    cout << "通信人手机号"<<endl;
    cin >> b;
    Push_Elme(Name, a);
    Push_Elme(Phone_Num, b);
}
void Person::GetElme()
{
    cout << "通信人姓名：";
    for (char x : Name) {
        cout << x;
    }
    cout << endl;
    cout << "通信人手机号：";
    for (int i = 0; i < 11; i++) {
        cout << Phone_Num[i];
    }
    cout << endl;
};
int main()
{
    Init_Table(HEAD);
    bool running = true;
    while (running)
    {
        system("cls");
        Draw_Graph(0);
        Get_Event(HEAD);
    }
}

