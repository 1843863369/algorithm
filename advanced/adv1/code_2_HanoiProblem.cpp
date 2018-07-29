/*
ţ���㷨���װ��һ�εڶ���(��Ƶ00:46:00)
��ŵ��1��2�Ľ��汾�����������������֮��ֱ���ƶ���

@2018/1/6

*/

#include <iostream>
#include <string>
#include <climits>
#include <stack>
#include <vector>
#include <time.h>

using namespace std;

//�ݹ�ʵ�ֺ�ŵ�����⣬���ز���
int curHanoiTower1(int n, string& left, string& right, string& middle) {
	int a = 0;
	int b = 0;
	int c = 0;
	if (n) {
		a = curHanoiTower1(n - 1, left, middle, right);
		cout << "move "<< n << " from " << left << " to " << right << endl;
		b = curHanoiTower1(n - 1, middle, right, left);
		c = a + b + 1;
	}
	return c;
}

class Stick {
public:
	Stick() = default;
	Stick(const string& string_n, stack<int>* stack_n) :string_name(string_n), stack_name(stack_n) {}
	//Stick& operator=(Stick& rhs) {
	//	string_name = rhs.string_name;
	//	stack_name = rhs.stack_name;
	//	return *this;
	//}

	string string_name;
	stack<int>* stack_name;
};
class StickList {
public:
	StickList() = default;
	StickList(int n, Stick* right, Stick* left, Stick* middle) {// from  to  other
		if (n % 2 == 0) {//n��Բ��
			ss.push_back(right);
			ss.push_back(middle);
			ss.push_back(left);
		}
		else {
			ss.push_back(right);
			ss.push_back(left);
			ss.push_back(middle);
		}
	}
	
	Stick* current() {
		//cout << get_cur()<< " cur    ";
		return ss[get_cur()];
	}
	Stick* next() {
		++cur;
		//cout << get_cur() << " next  ";
		return ss[get_cur()];
	}
	vector<Stick*>* others(vector<Stick*>* other) {
		(*other)[0] = ss[(cur + 1) % 3];
		(*other)[1] = ss[(cur + 2) % 3];
		return other;
	}
	int get_cur() {
		return cur % 3;
	}
	void print(Stick* from_s, Stick* to_s) {
		cout << "move " << from_s->stack_name->top() << " from " << from_s->string_name
			<<" to " << to_s->string_name << endl ;
	}
private:
	vector<Stick*> ss;
	int cur=0;
	
};




int noCurHanoiTower1(int n,string& right,string& left,string& middle) { // from  to  other
	//�ǵݹ�ʵ�ֺ�ŵ�������ֹ��ɣ�Բ��1���Ǳ��й��ɵ��ƶ���ÿ���ƶ������̺󣬱��ƶ�1
	//���Գ�����Բ��1Ϊÿһ��ѭ���Ŀ�ʼ
	//nΪ����ʱ����һ���ƶ���R��ż��ʱ��һ���ƶ���M�����Խ������˻���λ�ã���֤��һ��Բ��1�ƶ�������next
	//nextͨ��next+1����3ȡģ�õ�
	
	stack<int> aa, bb, cc;
	stack<int>* a1 = &aa;
	stack<int>* b1 = &bb;
	stack<int>* c1 = &cc;
	Stick* from_stack, *other_stack, *to_stack;
	from_stack	= new Stick(right, a1);
	other_stack = new Stick(middle, b1);
	to_stack = new Stick(left, c1);	
	
	StickList sticks(n, from_stack, to_stack, other_stack);
	Stick* curstack_with_1 = sticks.current();
	Stick* nextstack_with_1 = sticks.current();
	for (int i = n; i > 0; --i) {
		from_stack->stack_name->push(i);
	}
	vector<Stick*> others_t(2,sticks.current() );
	vector<Stick*>* others_two = &others_t;
	int step = 0;
	while (1) {
		step += 1;
		curstack_with_1 = sticks.current();
		nextstack_with_1 = sticks.next();
		sticks.print(curstack_with_1, nextstack_with_1);
		nextstack_with_1->stack_name->push(curstack_with_1->stack_name->top());
		curstack_with_1->stack_name->pop();
		if (to_stack->stack_name->size() == n)
			break;
		//cout <<���ҵ����������ֵ���ڴ����������
		sticks.others(others_two);
		if ((*others_two)[0]->stack_name->empty()|| (*others_two)[1]->stack_name->empty())
		{//���������һ��Ϊ�գ������һ�������������ѹ���ջ
			if ((*others_two)[0]->stack_name->empty()) {
				sticks.print((*others_two)[1], (*others_two)[0]);
				++step;
				(*others_two)[0]->stack_name->push((*others_two)[1]->stack_name->top());
				(*others_two)[1]->stack_name->pop();
			}
			else {
				sticks.print((*others_two)[0], (*others_two)[1]);
				++step;
				(*others_two)[1]->stack_name->push((*others_two)[0]->stack_name->top());
				(*others_two)[0]->stack_name->pop();
			}
		}
		else {//�������ջ����Ϊ�գ���ѽ�С��ѹ��ϴ��
			++step;
			if ((*others_two)[0]->stack_name->top() < (*others_two)[1]->stack_name->top()) {
				sticks.print((*others_two)[0], (*others_two)[1]);	
				(*others_two)[1]->stack_name->push((*others_two)[0]->stack_name->top());
				(*others_two)[0]->stack_name->pop();
			}
			else {
				sticks.print((*others_two)[1], (*others_two)[0]);
				(*others_two)[0]->stack_name->push((*others_two)[1]->stack_name->top());
				(*others_two)[1]->stack_name->pop();
			}
		}

	}
	delete from_stack;
	delete other_stack;
	delete to_stack;
	return step;
}
int curHanoiTower2(int n, string& from, string& to) {
	if (1 == n) {
		if ("middle" == from || "middle" == to) {
			cout << "move "<<n<<" from " << from << " to " << to << endl;
			return 1;
		}
		else {
			cout << "move " << n << " from " << from << " to " << "middle" << endl;
			cout << "move " << n << " from " << "middle" << " to " << to << endl;
			return 2;
		}
	}
	if ("middle" == from || "middle" == to) {
		string other = ("left" == from) || ("left" == to) ? "right": "left";
		int part1 = curHanoiTower2(n - 1, from, other);
		cout << "move " << n << " from " << from << " to " << to << endl;
		int part2 = curHanoiTower2(n - 1, other, to);
		return part1 + part2 + 1;
	}
	else {
		int part1 = curHanoiTower2(n - 1, from, to);
		cout << "move " << n << " from " << from << " to " << "middle" << endl;
		int part2 = curHanoiTower2(n - 1, to, from);
		cout << "move " << n << " from " << "middle" << " to " << to << endl;
		int part3 = curHanoiTower2(n - 1, from, to);
		return part1 + part2 + part3 + 2;
	}
	
	
}

enum Action{No,LToM,MToL,RToM,MToR};

int fStackToStack(Action pre_action[], Action pre_a, Action now_a, stack<int> &from_stack, stack<int> &to_stack, string &from, string &to) {
	if (pre_action[0] != pre_a && from_stack.top() < to_stack.top()) {
		//������������һ�����������Ǳ���ֹ�ģ��뱾���෴�ģ�����fromջ��ֵС��toջ��ֵ
		// �����һ�εĶ����뱾����ͬ����Ȼ������ڶ�������
		to_stack.push(from_stack.top());
		cout << "move " << from_stack.top() << " from " << from << " to " << to << endl;
		from_stack.pop();
		pre_action[0] = now_a;
		return 1;
	}
	return 0;
}
int noCurHanoiTower2(int n,string& left,string& middle,string& right) {
	stack<int> left_stack,mid_stack,right_stack;
	left_stack.push(INT_MAX);
	right_stack.push(INT_MAX);
	mid_stack.push(INT_MAX);
	for (int i = n; i > 0; --i) {//��������ջ��ʼ����Բ��ѹ��ջ
		left_stack.push(i);
	}
	Action record[] = { Action::No };
	int step = 0;
	while (right_stack.size()!=n+1) {
		step += fStackToStack(record, Action::LToM, Action::MToL, mid_stack, left_stack, middle, left);
		step += fStackToStack(record, Action::MToL, Action::LToM, left_stack, mid_stack, left, middle);
		step += fStackToStack(record, Action::RToM, Action::MToR, mid_stack, right_stack, middle, right);
		step += fStackToStack(record, Action::MToR, Action::RToM, right_stack, mid_stack, right, middle);


	}
	return step;
}



int main() {
	string left("left");
	string middle("middle");
	string right("right");

	clock_t cur_start = clock();
	int steps1 = curHanoiTower1(15, left, right, middle);
	clock_t cur_end = clock();
	cout << "running time of cur: " << (double)(cur_end - cur_start) << endl;
	cout << "==================================================="<< endl;
	clock_t nocur_start = clock();
	int steps2 = noCurHanoiTower1(15, left, right,middle);
	clock_t nocur_end = clock();
	//int step = curHanoiTower1(5, left, right, middle);
	cout << "running time of Nocur: " << (double)(nocur_end - nocur_start) << endl;
	cout << "running time of cur: " << (double)(cur_end - cur_start) << endl;
	cout << steps1 << " "<<steps2 << endl;
	
	system("pause");
	return 0;
}