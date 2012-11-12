#include <algorithm>
using namespace std;
#define maxn 610000
#define NEGATIVE_VALUE_INF 1<<31
#define POSITIVE_VALUE_INF 0x7fffffff
struct node {
	int ch[2],father; int data,size; int sum,add,dmax,mask;
	bool rev,clr;
} sp[maxn];  //sp[0] is sentinel
int top;
struct Splay {
	int root;
	/*************** fundamental code ***************/
	Splay() { // constructor
		root = newnode(NEGATIVE_VALUE_INF);
		sp[root].ch[1] = newnode(POSITIVE_VALUE_INF);
		sp[sp[root].ch[1]].father = root; //2 special nodes indicate boundary
		push_up(root);
	} // another construct, called by split(), can be delete when not necessary.
	Splay(int add_r) {
		root = newnode(NEGATIVE_VALUE_INF);
		sp[root].ch[1] = newnode(POSITIVE_VALUE_INF);
		sp[sp[root].ch[1]].father = root;
		sp[sp[root].ch[1]].ch[0] = add_r;
		sp[add_r].father = sp[root].ch[1];
		push_up(sp[root].ch[1]);
		push_up(root);
	} //return the index of the pos-th element or 0 if it doesn't exist.
	int select(int pos) {
		if (pos<1 || pos>sp[root].size) return 0;
		int res = root;
		push_down(root);
		while (sp[sp[res].ch[0]].size+1!=pos) {
			if (pos>sp[sp[res].ch[0]].size) {
				pos-=sp[sp[res].ch[0]].size+1;
				res = sp[res].ch[1];
			} else res = sp[res].ch[0];
			push_down(res);
		}
		return res;
	} //right rotate if op==0 or left rotate otherwise.
	void rotate(int r, int op) {
		int pre = sp[r].father;
		push_down(pre); push_down(r);
		sp[pre].ch[op] = sp[r].ch[!op];
		sp[sp[r].ch[!op]].father = pre;
		sp[r].ch[!op]=pre;
		sp[r].father = sp[pre].father;
		sp[pre].father = r;
		sp[sp[r].father].ch[pre==sp[sp[r].father].ch[1]]=r;
		push_up(pre);
	}  //lift the given node beneath the node goal. Lift to root if goal==0.
	void splay(int r, int goal) {
		push_down(r);
		while (sp[r].father!=goal) {
			if (sp[sp[r].father].father==goal)
				rotate(r, sp[sp[r].father].ch[1]==r);
			else {
				int y = sp[r].father, z = sp[y].father, f = (sp[z].ch[1] == y);
				if(sp[y].ch[f] == r) {
					rotate(y, f); rotate(r, f);
				} else {
					rotate(r, !f); rotate(r, f);
				}
			}
		}
		push_up(r);
		if (goal == 0) root = r;
	} //select the pos-th node and lift it beneath the node goal.
	void lift(int pos,int goal) {
		int np = select(pos+1); //be careful with the index
		if (np==0) return;
		splay(np,goal);
	}
	/**** functions over ordered structure, can be deleted if not necessary ****/
	int order_find(int data, int &rank) {  // binary-search a element
		int add = root, res = 0;
		push_down(root);
		rank = 0;
		while (add!=0) {
			if (data == sp[add].data) res = add;
			if (data >= sp[add].data) {
				rank += sp[sp[add].ch[0]].size+1;
				add = sp[add].ch[1];
			} else add = sp[add].ch[0];
			if (add!=0) push_down(add);
		}
		rank--;
		return res;
	}
	void order_remove(int data) { // remove an element
		int rank;
		if (order_find(data,rank) != 0)
			split(rank,rank);
	}
	void order_insert(int data) { // insert an element
		int rank;
		order_find(data,rank);
		int temp[1]; temp[0] = data;
		insert(rank,temp,0,0);
	}
	/***functions for interval-maintenances in sequence, add them if necessary*/
	int maketree(int *num, int s, int t) { // build a tree from num[s] to num[t]
		int m = (s+t) >> 1;
		int res = newnode(*(num+m));
		if (s<m) sp[res].ch[0]=maketree(num,s,m-1); sp[sp[res].ch[0]].father=res;
		if (m<t) sp[res].ch[1]=maketree(num,m+1,t); sp[sp[res].ch[1]].father=res;
		push_up(res);
		return res;
	} // traverse the tree, for debug or output.
	void traverse(int r) {
		push_down(r);
		if (sp[r].ch[0]!=0) traverse(sp[r].ch[0]);
		if (sp[r].ch[1]!=0) traverse(sp[r].ch[1]);
		push_up(r);
	} // insert numbers from num[s] to num[t] after the pos-th element
	void insert(int pos,int *num, int s, int t) {
		int r = maketree(num, s,t);
		lift(pos, 0);
		lift(pos+1,root);
		sp[sp[root].ch[1]].ch[0] = r;
		sp[r].father=sp[root].ch[1];
		push_up(sp[root].ch[1]);
		push_up(root);
	} // concat another splay after the pos-th element
	void concat(int pos, Splay *p) {
		lift(pos, 0);
		lift(pos+1,root);
		p->lift(0,0);
		p->lift(sp[p->root].size-1,p->root);
		int r = sp[sp[p->root].ch[1]].ch[0];
		sp[sp[root].ch[1]].ch[0] = r;
		sp[r].father = sp[root].ch[1];
		push_up(sp[root].ch[1]);
		push_up(root);
	} // split all numbers in interval [s, t] and return as a new splay
	Splay *split(int s, int t) {
		lift(s-1, 0);
		lift(t+1, root);
		int r = sp[sp[root].ch[1]].ch[0];
		sp[sp[root].ch[1]].ch[0] = 0;
		sp[r].father = 0;
		push_up(sp[root].ch[1]);
		push_up(root);
		return new Splay(r);
	}
	/**** Operations/Queries, add or modify them according to problem **/
	int get_sum(int s, int t) { // get sum of numbers in interval [s, t]
			lift(s-1, 0);
			lift(t+1, root);
			int r = sp[sp[root].ch[1]].ch[0];
			return sp[r].sum;
	} // get maximum in interval [s, t]
	int get_max(int s, int t) {
		lift(s-1, 0);
		lift(t+1, root);
		int r = sp[sp[root].ch[1]].ch[0];
		return sp[r].dmax;
	} // add all numbers in [s, t] with delta
	void opt_add(int s, int t, int delta) {
		lift(s-1, 0);
		lift(t+1, root);
		int x = sp[sp[root].ch[1]].ch[0];
		if (sp[x].clr)
			sp[x].mask+=delta;
		else
			sp[x].add += delta;
		sp[x].data += delta;
		sp[x].sum += delta*sp[x].size;
		sp[x].dmax += delta;
		push_up(sp[root].ch[1]);
		push_up(root);
	} // change all numbers in [s, t] with delta
	void opt_clr(int s,int t,int delta) {
		lift(s-1,0);
		lift(t+1,root);
		int x = sp[sp[root].ch[1]].ch[0];
		sp[x].add = 0;
		sp[x].clr = true;
		sp[x].mask = delta;
		sp[x].data = delta;
		sp[x].sum = delta*sp[x].size;
		sp[x].dmax = delta;
		push_up(sp[root].ch[1]);
		push_up(root);
	} // reverse all numbers in [s, t]
	void opt_rev(int s,int t) {
		lift(s-1, 0);
		lift(t+1, root);
		int x = sp[sp[root].ch[1]].ch[0];
		sp[x].rev ^= 1;
		swap(sp[x].ch[0],sp[x].ch[1]);
	}
	/**** Basic functions. Modify the fields of nodes according to problem ****/
	int newnode(int d) { // generate a new node
		++top;
		sp[top].father = sp[top].ch[0] = sp[top].ch[1] = 0;
		sp[top].data = d;
		sp[top].add = 0;
		sp[top].rev = false;
		sp[top].clr = false;
		push_up(top);
		return top;
	} // handle the marks and maintain data downward
	void push_down(int r) {
		for (int i=0;i<2;++i) { //be careful with interaction of multiple marks
			int x = sp[r].ch[i];
			if (x==0) continue;
			if (sp[r].add!=0) {//mark ADD
				if (sp[x].clr)
					sp[x].mask+=sp[r].add;
				else
					sp[x].add+=sp[r].add;
				sp[x].data+=sp[r].add;
				sp[x].sum+=sp[r].add*sp[x].size;
				sp[x].dmax+=sp[r].add;
			}
			if (sp[r].clr) {//CLEAR
				sp[x].clr = 1;
				sp[x].mask = sp[r].mask;
				sp[x].add = 0;
				sp[x].data = sp[r].mask;
				sp[x].sum = sp[r].mask*sp[x].size;
				sp[x].dmax = sp[r].mask;
			}
			if (sp[r].rev) { //REVERSE
				sp[x].rev^=1;
				swap(sp[x].ch[0],sp[x].ch[1]);
			}
		}
		sp[r].add = 0;
		sp[r].clr = false;
		sp[r].rev = false;
	} // maintain data upward
	void push_up(int r) {
		sp[r].size = 1 + sp[sp[r].ch[0]].size + sp[sp[r].ch[1]].size;
		sp[r].sum = sp[r].data+sp[sp[r].ch[0]].sum+sp[sp[r].ch[1]].sum;
		sp[r].dmax = max(sp[r].data,
				max(sp[sp[r].ch[0]].dmax, sp[sp[r].ch[1]].dmax));
	}
};
void init() { // initalize the memory pool and some data
	top = 0;
	sp[0].dmax = NEGATIVE_VALUE_INF; //sp[0] is sentinel
}