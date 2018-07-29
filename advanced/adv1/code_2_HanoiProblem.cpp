/*
牛客算法进阶班第一课第二题(视频00:46:00)
汉诺塔1及2改进版本：不能在最左和最右之间直接移动。

@2018/1/6

*/

#include <iostream>
#include <string>
#include <climits>
#include <stack>
#include <vector>
#include <time.h>

using namespace std;

//递归实现汉诺塔问题，返回步数
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
		if (n % 2 == 0) {//n个圆盘
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
	//非递归实现汉诺塔，发现规律：圆盘1总是被有规律的移动，每次移动其他盘后，必移动1
	//所以尝试以圆盘1为每一次循环的开始
	//n为奇数时，第一步移动到R，偶数时第一步移动到M，所以将两个杆互换位置，保证第一步圆盘1移动到它的next
	//next通过next+1并对3取模得到
	
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
		//cout <<从右到左计算各项的值，在从左到右输出。
		sticks.others(others_two);
		if ((*others_two)[0]->stack_name->empty()|| (*others_two)[1]->stack_name->empty())
		{//如果两个有一个为空，则把另一个上面的数弹出压入空栈
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
		else {//如果两个栈都不为空，则把较小的压入较大的
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
		//两个条件：上一个动作不能是被禁止的（与本次相反的），且from栈顶值小于to栈顶值
		// 如果上一次的动作与本次相同，必然不满足第二个条件
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
	for (int i = n; i > 0; --i) {//从最左侧的栈开始，将圆盘压入栈
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