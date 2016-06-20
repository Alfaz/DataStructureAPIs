/*
*	A template based linked list API.
*	pushBack(T value) adds element at the end of the list.
*	pushFront(T value) adds at the beginning of the list.
*	print() prints the elements in space seperated manner.
*   getHead() returns pointer of type linkedListNode for traversal.
*
*	Author: Alfaz Ahmed (alfazahmed@gmail.com)
*/


template <class T>
class linkedListNode{
	public:
	T data;
	linkedListNode * next;

	public:
	linkedListNode(T value){
		this->data = value;
		this->next = NULL;
	}

	linkedListNode(){
	
	}
	
	void pushBack(T value){
		
	}
};

template <class T>
class linkedList{
	private:
	linkedListNode<T> * head;
	linkedListNode<T> * tail;
	
	public:
	linkedList(){
		this->head = NULL;
		this->tail = NULL;
	}
	
	linkedListNode<T> * getHead(){
		return this->head;
	}
	
	linkedListNode<T> * getTail(){
		return this->tail;
	}

	void pushBack(T value){
		linkedListNode<T> * newNode = new linkedListNode<T>(value);
		if(head == NULL){
			/*First element*/
			head = newNode;
			tail = newNode;
		}else{
			tail->next = newNode;
			tail = tail->next;
		}
		
	}
	void pushFront(T value){
		linkedListNode<T> * newNode = new linkedListNode<T>(value);
		if(head == NULL){
			/*First element*/
			head = newNode;
			tail = newNode;
		}else{
			newNode->next = head;
			head = newNode;
		}
	}

	void print(){
		linkedListNode<T> *ptr = this->head;
		while(ptr != NULL){
			std::cout << ptr->data <<" ";
			ptr=ptr->next;
		}
		std::cout << std::endl;
	}
};

/*Demo client calls

	linkedList<int> * myList = new linkedList<int>(); 
	myList->pushBack(2);
	myList->pushBack(6);
	myList->pushBack(9);
	myList->pushBack(12);
	myList->pushFront(99);
	myList->print();
	prints: 99 2 6 9 12
	
	linkedList<char> * charList = new linkedList<char>();
	charList->pushBack('A');
	charList->pushBack('L');
	charList->pushBack('F');
	charList->pushBack('A');
	charList->pushBack('Z');
	charList->print();
	prints: A L F A Z
*/
