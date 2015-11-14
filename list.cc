#include <iostream>
#include <cstdlib>
#include <exception>

using namespace std;

//------------------------------------
//NAME: Emiliyan Sokolov
//CLASS: 11b 
//NUMBER: 15
//PROBLEM: List
//FILE_NAME: Emiliqn_Sokolov_15.c
//FILE_PURPOSE: This file contains the program
//--------------------

template <class T> class List {
	struct Elem {
		T data_;
		Elem* next_;
		Elem* prev_;
		
		Elem(T val)
		: data_(val),
		  next_(0),
		  prev_(0)
		{}
		Elem()
		: next_(0),
		  prev_(0)
	    {}
	};
	Elem* head_;
	Elem* tail_;
	
public:
	//The constructor
	List()
	: head_(0),
	  tail_(0)
	{}
	//The destructor
	~List() {
		while(!empty()) {
			pop_front();
		}
	}
	
	//The copy constructor
	List(const List& other){
		head_ = 0;
		tail_ = 0;
		for(const_iterator it=other.begin(); it!=other.end(); ++it) {
			push_back(*it);
		}
	}
	
	//Assignment operator
	List& operator =(const List& other){
		//checks if the object is not the same
		if(this!=&other) {
			while(!empty()) {
				pop_front();
			}
			Elem* tmp = other.head_;
			while(tmp!=0){
				push_back(tmp->data_);
				tmp = tmp->next_;
			}
		}
		return *this;
	}
//------------------------------------
//FUNCTION: size
//This function returns the size of the list
//
//
//PARAMETERS: -
//-----------------------------------
	int size() const {
			Elem* tmp = head_;
			unsigned count = 0;
			while(tmp!= 0){
				count ++;
				tmp = tmp->next_;
			}
			
			return count;
	}
//------------------------------------
//FUNCTION: empty
//This function checks if the list is empty
//
//
//PARAMETERS: -
//-----------------------------------
	bool empty() const {
		return((head_ == 0) || (tail_ == 0));
	}
//------------------------------------
//FUNCTION: clear
//This function clears the elements in the list
//
//
//PARAMETERS: -
//-----------------------------------
	void clear() {
		while(!empty()) {
			pop_front();
		}
	}
//------------------------------------
//FUNCTION: swap
//This function swaps the elements of the two lists
//
//
//PARAMETERS: -other
//other is a reference to the other list
//-----------------------------------
	void swap(List& other) {
		Elem* temp_head = other.head_;
		Elem* temp_tail = other.tail_;
		other.head_ = head_;
		other.tail_ = tail_;
		head_ = temp_head;
		tail_ = temp_tail;
	}
//------------------------------------
//FUNCTION: push_back
//This function adds new element after the last element of the list
//
//
//PARAMETERS: x
//x parameter contains the element
//-----------------------------------	
	void push_back(const T& x) {
		Elem* newElem = new Elem(x);
		if(tail_ == 0) {
			head_ = tail_ = newElem;
			return;
		}
		newElem->prev_ = tail_;
		tail_->next_ = newElem;
		tail_ = newElem;
		
	}   
//------------------------------------
//FUNCTION: push_front
//This function adds new element before the first element of the list
//
//
//PARAMETERS: x
//x parameter contains the element
//-----------------------------------	
	void push_front(const T& x) {
		Elem* newElem = new Elem(x);
		if(head_ == 0) {
			head_ = tail_ = newElem;
			return;
		}
		newElem->next_ = head_;
		head_->prev_ = newElem;
		head_ = newElem;
	}
//------------------------------------
//FUNCTION: pop_back
//This function removes the last element of the list
//
//
//PARAMETERS: - 
//-----------------------------------	
	void pop_back() {
		if(empty()){
			throw exception();
		}
		Elem* ptr = tail_;
		tail_ = tail_->prev_;
		delete ptr;
	}
//------------------------------------
//FUNCTION: pop_front
//This function removes the first element of the list
//
//
//PARAMETERS: - 
//-----------------------------------	
	void pop_front() {
		if(empty()){
			throw exception();
		}
		Elem* ptr = head_;
		head_ = head_->next_;
		delete ptr;
	}
//------------------------------------
//FUNCTION: front
//This function returns a reference to the first element of the list
//
//
//PARAMETERS: - 
//-----------------------------------	
	T& front() {
		if(empty()) {
			throw exception();
		}
		return head_->data_;
	}
	
	const T& front() const {
		if(empty()) {
			throw exception();
		}
		return head_->data_;
	}
//------------------------------------
//FUNCTION: back
//This function returns a reference to the last element of the list
//
//
//PARAMETERS: - 
//-----------------------------------	
	T& back() {
		if(empty()){
			throw exception();
		}
		return tail_->data_; 
	}
	const T& back() const {
		if(empty()){
			throw exception();
		}
		return tail_->data_;
	}
	class iterator {
		Elem* ptr_;
		Elem* last;
		
		friend class List;
		
	public:
	//The constructor
		iterator(Elem* ptr)
		: ptr_(ptr)
		{}
	// Equals comparison operator
		bool operator==(const iterator& other) const {
			return ptr_ == other.ptr_;
		}
		// Not-equals comparison operator
		bool operator!=(const iterator& other) const {
			return ptr_!=other.ptr_;
		}
			//Increment operator
		iterator& operator++() {
			ptr_ = ptr_->next_;
			
			return *this;
		}
			//Increment operator
		iterator& operator++(int){
			iterator tmp(*this);
			ptr_ = ptr_->next_;
			
			return tmp;
		}
		//Dereference operator
     //return the value of the element this iterator is currently pointing at
		T& operator *() {
			return ptr_->data_;
		}
		T& operator ->() {
			return *(ptr_->data_);
		}
	};
	class const_iterator {
		Elem* ptr_;
		const_iterator(Elem* ptr)
		: ptr_(ptr)
		{}
		
		friend class List;
		
	public:
		bool operator==(const const_iterator& other) const {
			return ptr_ == other.ptr_;
		}
		bool operator!=(const const_iterator& other) const {
			return ptr_!=other.ptr_;
		}
		const_iterator& operator++() {
			ptr_ = ptr_->next_;
			
			return *this;
		}
		const_iterator& operator++(int){
			const_iterator i = *this;
			ptr_ = ptr_->next_;
			
			return i;
		}
		
		const T& operator *() {
			return ptr_->data_;
		}
		const T& operator ->() {
			return *(ptr_->data_);
		}
	};
	class reverse_iterator {
		Elem* ptr_;
		reverse_iterator(Elem* ptr)
		: ptr_(ptr)
		{}
		
		friend class List;
		
	public:
		bool operator==(const reverse_iterator& other) const {
			return ptr_ == other.ptr_;
		}
		bool operator!=(const reverse_iterator& other) const {
			return ptr_!=other.ptr_;
		}
		reverse_iterator& operator++() {
			ptr_ = ptr_->prev_;
			
			return *this;
		}
		reverse_iterator& operator++(int){
			reverse_iterator i = *this;
			ptr_ = ptr_->prev_;
			
			return i;
		}
		
		T& operator *() {
			return ptr_->data_;
		}
		T& operator ->() {
			return *(ptr_->data_);
		}
	};
	
	class const_reverse_iterator {
		Elem* ptr_;
		const_reverse_iterator(Elem* ptr)
		: ptr_(ptr)
		{}
		
		friend class List;
		
	public:
		bool operator==(const const_reverse_iterator& other) const {
			return ptr_ == other.ptr_;
		}
		bool operator!=(const const_reverse_iterator& other) const {
			return ptr_!=other.ptr_;
		}
		const_reverse_iterator& operator++() {
			ptr_ = ptr_->prev_;
			
			return *this;
		}
		const_reverse_iterator& operator++(int){
			const_reverse_iterator i = *this;
			ptr_ = ptr_->prev_;
			
			return i;
		}
		
		const T& operator *() {
			return ptr_->data_;
		}
		const T& operator ->() {
			return *(ptr_->data_);
		}
	};
//------------------------------------
//FUNCTION: begin
//This function returns the first element of the list
//
//
//PARAMETERS: -
//-----------------------------------	
	iterator begin() {
		return iterator(head_);
	}
//------------------------------------
//FUNCTION: end
//This function returns the last element of the list
//
//
//PARAMETERS: -
//-----------------------------------	
	iterator end() {
		return iterator(tail_->next_);
	}
	const_iterator begin() const {
		return const_iterator(head_);
	}
	const_iterator end() const {
		return const_iterator(tail_->next_);
	}
	reverse_iterator rbegin() {
		return reverse_iterator(tail_);
	}
	reverse_iterator rend() {
		return reverse_iterator(head_->prev_);
	}
	const_reverse_iterator rbegin() const {
		return const_reverse_iterator(tail_);
	}
	const_reverse_iterator rend() const {
		return const_reverse_iterator(head_->prev);
	}
//------------------------------------
//FUNCTION: insert
//This function adds new element in the specified position
//
//
//PARAMETERS: - pos,x
//-----------------------------------	
	iterator insert(iterator pos, const T& x){
				
		if (pos.ptr_ == 0)
		{  
		   push_back(x);
		} else{
			Elem* after = pos.ptr_;
			Elem* before = after->prev_;
			Elem* element = new Elem(x);
			element->prev_ = before;
			element->next_ = after;
			after->prev_ = element;
			if (before == 0) 
			  head_ = tail_ = element;
			else
			   before->next_ = element;
		}
		return pos;		
	}
//------------------------------------
//FUNCTION: erase
//This function removes the specified element
//
//
//PARAMETERS: - pos
//-----------------------------------	
	iterator erase(iterator pos){
		if(pos.ptr_ == 0){
			throw exception();
		}
		Elem* remove = pos.ptr_;
		Elem* before = remove->prev_;
		Elem* after = remove->next_;
		if(remove == head_){
			head_ = after;
		}
		else if(remove == tail_){
			tail_ = before;
		}
		else {
			before->next_ = after;
			after->prev_ = before;
		}
		return pos;
	}
	
	 iterator erase(iterator first, iterator last)
    {
        for(iterator itr = first; itr != last;)
			itr = erase(itr);

        return last;
    }
	
};

//-----------------------------------
//FUNCTION: main
//The main function of the program
//
//PARAMETERS: int argc, char* argv[]
//argc is the number of the arguments
//argv contains the arguments
//-----------------------------------
int main(int argc, char* argv[]) {
	unsigned equal_count = 0;
	unsigned list_count = 0;
	List<int> l[(argc-1)/2];
	if ((argc > 1) && ((argc-1)%2 == 0)) {
		for(int i = 1; i < argc; i+=2){
			for(int m = atoi(argv[i]); m < atoi(argv[i+1]); m++){
				l[list_count].push_back(m);
			}
			list_count++;
		}
	}
	else {
		cout << "Wrong number of arguments" << endl;
		exit(1);
	}
	for(int i = 0; i < (sizeof(l)/sizeof(l[0])); i++) {
		cout << "l" << i+1 << ":" << " " << "{";
		for(List<int>::iterator it = l[i].begin(); it!= l[i].end(); ++it) {
			cout << *it << ",";
		}
		cout << "}" << endl;
	}
	
	for(List<int>::iterator it1=l[0].begin(); it1 != l[0].end(); ++it1) {
		for(List<int>::iterator it2=l[1].begin() ; it2 != l[1].end(); ++it2) {
			if(*it1 == *it2){
				equal_count++;
			}
		}
	}
	cout << "equal element in l1 and l2: " << equal_count << endl;
	
	l[0].push_back(-100);
	l[1].push_back(-100);
	
	for(int i = 0; i < (sizeof(l)/sizeof(l[0])); i++) {
		cout << "l" << i+1 << ":" << " " << "{";
		for(List<int>::iterator it = l[i].begin(); it!= l[i].end(); ++it) {
			cout << *it << ",";
		}
		cout << "}" << endl;
	}
	List<int> ll(l[1]);
	cout << "l:" << " " << "{";
	for(List<int>::iterator it = ll.begin(); it!= ll.end(); ++it) {
			cout << *it << ",";
	}
	cout << "}" << endl;
	
	for(List<int>::reverse_iterator it=l[0].rbegin();it != l[0].rend(); ++it){
		ll.push_front(*it);
	}
	cout << "l:" << " " << "{";
	for(List<int>::iterator it = ll.begin(); it!= ll.end(); ++it) {
			cout << *it << ",";
	}
	cout << "}" << endl;
	
	
	for(List<int>::iterator it = ll.begin(); it!= ll.end(); ++it) {
			if(*it == -100){
				ll.erase(it);
				break;
			}
	}
	
	cout << "l:" << " " << "{";
	for(List<int>::iterator it = ll.begin(); it!= ll.end(); ++it) {
			cout << *it << ",";
	}
	cout << "}" << endl;
	cout << endl;
	
		return 0;
}



