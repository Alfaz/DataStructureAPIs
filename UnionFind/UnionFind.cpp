/*
The tree based implementation of the Union Find DS, generally a lot faster than the array based implementation.
g++ UnionFindQuick.cpp
Author: Alfaz Ahmed
*/

#include<iostream>
#include<vector>
using namespace std;
class UnionFind{
	private:
	int root(int node);
	vector<int> *array;
	public:
	UnionFind(int n);
	void Union(int a, int b);
	bool Find(int a, int b);
	void printData();
	~UnionFind();

};
int UnionFind::root(int node){
	int i=node;	
	while(this->array->at(i) != i){
		i = this->array->at(i);
	}
	return i;
}
void UnionFind::printData(){
	for(vector<int>::iterator it = array->begin();it != array->end();it++){
		cout << *it << " ";
	}
	cout << endl;
}
UnionFind::~UnionFind(){
	delete this->array;
}
UnionFind::UnionFind(int n){
	this->array = new vector<int>(n);
	for(vector<int>::iterator it = array->begin();it != array->end();it++){
		*it = it - this->array->begin(); //put index of the cell as initial value
	}
}

void UnionFind::Union(int a, int b){
	int root_a = this->root(a);
	int root_b = this->root(b);
	this->array->at(root_a) = this->array->at(root_b);
}

bool UnionFind::Find(int a, int b){
	int root_a = this->root(a);
	int root_b = this->root(b);
	return this->array->at(root_a) == this->array->at(root_b);
}

int main(){
	UnionFind *uf = new UnionFind(10);
	uf->printData();
	cout << "Union(1,2)"<<endl;
	uf->Union(1,2);
	uf->printData();
	cout << "Union(4,2)"<<endl;
	uf->Union(4,2);
	uf->printData();
	cout << "Union(7,8)"<<endl;
	uf->Union(7,8);
	uf->printData();
	cout << "Union(1,9)"<<endl;
	uf->Union(1,9);
	uf->printData();
	cout << "Find(1,4) -> "<< uf->Find(1,4)<<endl;
	cout << "Find(8,7) -> "<< uf->Find(8,7)<<endl;
	cout << "Find(9,6) -> "<< uf->Find(9,6)<<endl;
	cout << "Find(1,9) -> "<< uf->Find(1,9)<<endl;
return 0;
}
