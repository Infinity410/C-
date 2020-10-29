#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<iomanip>
#include <Windows.h>
using namespace std;

typedef struct Node {
	double num;//������
	char op;//������
	bool flag;//true��ʾ��������false��ʾ������
}node;
//�������ȼ�(ע��Ĭ�ϲ����������ȼ���ߣ����䲻��Ҫ��ջ����ջ�Ķ��������)
map<char, int> p;

void menu();
void change_into();
double calculate_back();
double calculate_medi();
char getPriority(char theta1, char theta2);
double calculate(double b, char theta, double a);
int getIndex(char theta);

vector<char> v1;//��׺���ʽ������
vector<char> v3;//��׺���ʽ������
int main()
{
	menu();
	return 0;
}

int times = 0;
void menu()//�˵�
{
	cout << "\t\t------------------------------------------------------" << endl;
	cout << "\t\t                       ���ʽ��ֵ                     " << endl;
	cout << endl;
	cout << "\t\t1. ��׺���ʽ����׺���ʽ��ת�� " << endl;
	cout << "\t\t2. ��׺���ʽ�ļ��� " << endl;
	cout << "\t\t3. ��׺���ʽ�ļ���" << endl;
	cout << "\t\t4. �˳� " << endl;
	cout << endl;
	cout << "\t\t------------------------------------------------------" << endl;
	char n;
	cin >> n;
	switch (n)
	{
	case '1':
		change_into();
		break;
	case '2':
		if (times == 0)
		{
			cout << "����ִ�й���1��5��󷵻ز˵�" << endl;
			Sleep(5 * 1000);    //������ʱ5s
			system("CLS");
			menu();
		}
		else
		{
			double ans;
			ans = calculate_back();
			cout << "��׺���ʽ��";
			for (int i = 0; i < v3.size(); i++)
			{
				cout << v3[i];
			}
			cout << endl;
			cout << "������Ϊ��" << ans << endl;
			cout << endl;
			cout << "����1���ز˵�������������������" << endl;
			char o;
			cin >> o;
			if (o == '1')
			{
				system("CLS");
				menu();
			}
			else
			{
				exit(0);
			}
		}
		break;
	case '3':
		cout << "��׺���ʽ��";
		for (int i = 0; i < v1.size(); i++)
		{
			cout << v1[i];
		}
		cout << endl;
		double ans;
		ans = calculate_medi();
		cout << "������Ϊ��" << ans << endl;
		cout << endl;
		cout << "����1���ز˵�������������������" << endl;
		char o;
		cin >> o;
		if (o == '1')
		{
			system("CLS");
			menu();
		}
		else
		{
			exit(0);
		}
		break;
	case '4':
		exit(0);
		break;
	default:
		system("CLS");
		menu();
		break;
	}
}

stack<node> s;//������ջ
queue<node> q;//��׺���ʽ����
void change_into()//��׺���ʽת��׺���ʽ
{
	char c;
	p['+'] = p['-'] = 1;//ͨ��hashmap��ֵ���ж�˳��
	p['*'] = p['/'] = 2;
	cout << "������׺���ʽ����#�Ž�����";
	cin >> c;
	char c1[100];	int string_num  = -1;//�ַ��������ڼ�¼��׺���ʽ
	vector<char> v2;	
	c1[++string_num] = c;
	while (c != '#')
	{
		cin >> c;
		c1[++string_num] = c;
	}
	string_num++;
	v2.push_back('#');//��#��ջ�жϽ�������
	int num = 0;
	node temp;
	//������̣������Ƹ�ʽ
	cout << setw(num + 1);
	for (int j = 0; j < string_num; j++)
	{
		cout << c1[j];
		v1.push_back(c1[j]);
	}
	cout.width(10);
	num++;
	for (int k = 0; k < v2.size(); k++)
	{
		cout << v2[k];
	}
	cout.width(10);
	for (int k = 0; k < v3.size(); k++)
	{
		cout << v3[k];
	}
	cout << endl;

	for (int i = 0; i < string_num;)
	{
		if (num != string_num)//�����׺���ʽ
		{
			cout << setw(num + 1);
			for (int j = num; j < string_num; j++)
			{
				cout << c1[j];
			}
			cout.width(10);
			num++;
		}
		else
		{
			cout << setw(string_num + 10);
		}
		if (c1[i] == '(')//���������ţ�������ջ
		{
			temp.flag = false;
			temp.op = c1[i];
			s.push(temp);
			v2.push_back(c1[i]);
			i++;
		}
		else if (c1[i] == ')')//���������ţ�ִ�г�ջ�������������׺���ʽ��ֱ����������������
		{
			while (!s.empty() && s.top().op != '(')
			{
				q.push(s.top());
				v3.push_back(s.top().op);
				s.pop();
				v2.pop_back();
			}
			s.pop();//����������
			v2.pop_back();
			i++;
		}
		else if (c1[i] >= '0' && c1[i] <= '9')//���������
		{
			temp.flag = true;
			temp.num = c1[i] - '0';
			v3.push_back(c1[i]);
			i++;
			q.push(temp);//�����������׺���ʽ
		}
		else//����ǲ�����
		{
			temp.flag = false;
			while (!s.empty() && p[s.top().op] >= p[c1[i]])//��������������������������ȼӴ��ڻ���ڸ��������ջ��Ԫ�أ�Ȼ�󽫸��������ջ
			{
				q.push(s.top());
				v3.push_back(s.top().op);
				s.pop();
				v2.pop_back();
			}
			temp.op = c1[i];
			s.push(temp);
			v2.push_back(temp.op);
			i++;
		}
		for (int k = 0; k < v2.size(); k++)
		{
			if (v2.front() == v2.back() && v2.size() != 1)
			{
				cout << " ";
			}
			else 
			{ 
				cout << v2[k]; 
			}
		}
		cout << setw(string_num - v2.size());
		for (int k = 0; k < v3.size(); k++)//��ջ���������ε�����׺���ʽ
		{
			cout << v3[k];
		}
		cout << endl;
	}
	cout << endl;
	cout << "����1���ز˵�������������������" << endl;
	char o;
	cin >> o;
	if (o == '1')
	{
		system("CLS");
		times++;
		menu();
	}
	else
	{
		exit(0);
	}
	
}

stack<node> s1;//��Ų������ģ�Ϊ�˼����׺���ʽ��ֵ
double calculate_back()
{
	cout << endl;
	double num_a, num_b;//������a,b
	node cur, temp;
	vector<char> b1;
	b1 = v3;
	vector<int> b2;
	int num = 1;
	int string_num = b1.size();
	//�����׺���ʽ�����Ƹ�ʽ
	cout.setf(ios::right);
	for (int j = 0; j < b1.size(); j++)
	{
		cout << b1[j];
	}
	cout << endl;

	while (!q.empty())//��׺���зǿ�
	{
		if (num != string_num)
		{
			cout << setw(num + 1);
			cout.setf(ios::right);
			for (int j = num; j < b1.size(); j++)
			{
				
				cout << b1[j];
			}
			cout.width(10);
			num++;
		}
		else
		{
			for (int j = 0; j < b1.size(); j++)
			{
				cout << " ";
			}
		}
		cur = q.front();//��¼����Ԫ��
		q.pop();
		if (cur.flag == true)//�ǲ���������ջ
		{
			s1.push(cur);
			b2.push_back(cur.num);
		}
		else//�ǲ�����������
		{
			num_b = s1.top().num;//�����ڶ�������
			s1.pop();
			b2.pop_back();
			num_a = s1.top().num;//������һ������
			s1.pop();
			b2.pop_back();
			temp.flag = true;
			if (cur.op == '+')
			{
				temp.num = num_a + num_b;
			}
			else if (cur.op == '-')
			{
				temp.num = num_a - num_b;
			}
			else if (cur.op == '*')
			{
				temp.num = num_a * num_b;
			}
			else
			{
				if (num_b == 0)//��������Ϊ0
				{
					cout << "����Ϊ0,���ܼ��㣬��������" << endl;
					exit(-1);
				}
				temp.num = num_a / num_b;
			}
			s1.push(temp);//�Ѽ����Ľ���ٴ�ѹջ
			b2.push_back(temp.num);
		}
		cout.setf(ios::right);
		cout.width(10);
		cout << setw(string_num - b2.size());
		for (int k = 0; k < b2.size(); k++)
		{
			cout << b2[k];
		}
		cout << endl;
	}
	return s1.top().num;
}

int getIndex(char theta)   //��ȡtheta����Ӧ������
{
	int index = 0;
	switch (theta)
	{
	case '+':
		index = 0;
		break;
	case '-':
		index = 1;
		break;
	case '*':
		index = 2;
		break;
	case '/':
		index = 3;
		break;
	case '(':
		index = 4;
		break;
	case ')':
		index = 5;
		break;
	case '#':
		index = 6;
		break;
	default:
		break;
	}
	return index;
}

char getPriority(char theta1, char theta2)   //��ȡtheta1��theta2֮������ȼ�
{
	const char priority[][7] =     //���������ȼ���ϵ
	{
		{ '>','>','<','<','<','>','>' },
		{ '>','>','<','<','<','>','>' },
		{ '>','>','>','>','<','>','>' },
		{ '>','>','>','>','<','>','>' },
		{ '<','<','<','<','<','=','0' },
		{ '>','>','>','>','0','>','>' },
		{ '<','<','<','<','<','0','=' },
	};

	int index1 = getIndex(theta1);
	int index2 = getIndex(theta2);
	return priority[index1][index2];
}

double calculate(double b, char theta, double a)   //����b theta a
{
	switch (theta)
	{
	case '+':
		return b + a;
	case '-':
		return b - a;
	case '*':
		return b * a;
	case '/':
		return b / a;
	default:
		break;
	}
}

double calculate_medi()//��׺���ʽ��ֵ
{
	stack<char> opter;    //�����ջ
	stack<double> opval;  //������ջ
	opter.push('#');      //���Ƚ�'#'��ջopter
	int i = 0;
	char c = v1[i];
	while (c != '#' || opter.top() != '#')
	{
		if (isdigit(v1[i]))
		{
			opval.push(v1[i] - '0');
			c = v1[++i];
		}
		else
		{
			switch (getPriority(opter.top(), v1[i]))   //��ȡ�����ջopterջ��Ԫ����c֮������ȼ�����'>'��'<'��'='��ʾ
			{
			case '<':
				opter.push(v1[i]);
				c = v1[++i];
				break;
			case '=':               //=��opterջ��Ԫ�ص������������ŵĴ���
				opter.pop();
				c = v1[++i];
				break;
			case '>':               //>�����
				char theta = opter.top();
				opter.pop();
				double a = opval.top();
				opval.pop();
				double b = opval.top();
				opval.pop();
				opval.push(calculate(b, theta, a));
			}
		}
	}
	return opval.top();
}
