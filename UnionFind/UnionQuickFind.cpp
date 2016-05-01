/*
Array based implementation of Union Find data structure. In this implementation, the union operation is costly while the find is very quick, hence the quiry naming.
g++ UnionQuickFind.cpp
Author: Alfaz Ahmed
*/

#include<iostream>
#include<vector>
using namespace std;
class UnionFind{
	private:
	vector<int> *array;
	public:
	UnionFind(int n);
	void Union(int a, int b);
	bool Find(int a, int b);
	void printData();
	~UnionFind();

};
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
	int val_at_a = this->array->at(a);
	for(vector<int>::iterator it = this->array->begin();it!=this->array->end();it++){
		if(*it == val_at_a){
			*it = b;
		}
	}
}

bool UnionFind::Find(int a, int b){
	return this->array->at(a) == this->array->at(b);
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
