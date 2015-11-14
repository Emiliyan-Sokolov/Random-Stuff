#include <iostream>
#include <exception>

using namespace std;

template<typename T > 
class Vector {
	int capacity_;
	int size_;
	T* buffer_;
	
	void alloc_new() {
		capacity_ = size_*2;
		T* tmp = new T[capacity_];
		for(int i=0;i<size_;++i){
			tmp[i] = buffer_[i];
		}
		delete [] buffer_;
			
		buffer_ = tmp;
		
		cout << "Alloc new() Called" << endl;
	}
	void dealloc() {
		capacity_ = capacity_/2;
		T* tmp = new T[capacity_];
		for(int i=0;i<size_;++i){
			tmp[i] = buffer_[i];
		}
		delete [] buffer_;
		
		buffer_ = tmp;
		
		cout << "Dealloc new() Called" << endl;
		
	}	
	
public:
	Vector(int capacity)
	: capacity_(capacity),
	  size_(0),
	  buffer_ (new T[capacity_])
	{}
	
	Vector()
	: capacity_(1),
	  size_(0),
	  buffer_ (new T[capacity_])
	{}
	
	Vector(const Vector& other)	{
		capacity_ = other.capacity_;
		size_ = other.size_;
		buffer_ = new T[capacity_];
		for(int i = 0;i < other.size_; ++i){
			buffer_[i] = other.buffer_[i];
		}
	}
	
	~Vector () {
	delete [] buffer_;
	}
	
	bool empty() const {
		return size()==0;
	}
	
	int size() const {
		return size_;
	}
	
	int capacity() const {
		return capacity_;
	}
	
	void clear() {
		size_ = 0;
	}
	
	T& operator[](int n) {
		if(n > size_) {
			throw exception();
		}
		
		return buffer_[n];
	}
	const T& operator[](int n) const {
		
		if(n > size_) {
			throw exception();
		}
		
		return buffer_[n];
	}
	
	Vector& operator=(const Vector& other){
		
		//checks if the object is not the same
		if(this!=&other) {
			capacity_ = other.capacity_;
			size_ = other.size_;
			delete [] buffer_;
			buffer_ = new T[capacity_];
			for(int i = 0;i < other.size_; ++i)	{
				buffer_[i] = other.buffer_[i];
			}
		}
		return *this;
	}
	
	class iterator {
	 T* ptr_;
	 
	public :
		iterator(T* ptr)
		: ptr_(ptr)
		{}
		
		iterator operator ++() {
			ptr_++;
			return *this;
		}
		
		iterator operator ++(int) {
			iterator i = *this;
			ptr_++;
			return i;
		}
		bool operator ==(const iterator& other ) const {
			
			return ptr_ == other.ptr_;
		}
		bool operator !=(const iterator& other ) const {
			
			return ptr_ != other.ptr_;
		}
		
		T& operator *() {
			return *ptr_;
		}
		
		T* operator ->() {
			return ptr_; 
		}
		
	};
	class const_iterator {
		T* ptr_;
	 
	public :
		const_iterator(T* ptr)
		: ptr_(ptr)
		{}
		
		const_iterator operator ++() {
			ptr_++;
			return *this;
		}
		
		const_iterator operator ++(int) {
			iterator i = *this;
			ptr_++;
			return i;
		}
		
		bool operator ==(const const_iterator& other ) const {
			
			return ptr_ == other.ptr_;
		}
		bool operator !=(const const_iterator& other ) const {
			
			return ptr_ != other.ptr_;
		}
		
		const T& operator *() {
			return *ptr_;
		}
		
		const T* operator ->() {
			return ptr_; 
		}
	};
	
	class reverse_iterator {
		T* ptr_;
		
	public :
		reverse_iterator(T* ptr)
		: ptr_(ptr)
		{}
		
		reverse_iterator operator ++() {
			ptr_--;
			return *this;
		}
		
		reverse_iterator operator ++(int) {
			iterator i = *this;
			ptr_--;
			return i;
		}
		
		bool operator ==(const reverse_iterator& other ) const {
			
			return ptr_ == other.ptr_;
		}
		
		bool operator !=(const reverse_iterator& other ) const {
			
			return ptr_ != other.ptr_;
		}
		
		T& operator *() {
			return *ptr_;
		}
		
		T* operator ->() {
			return ptr_; 
		}
		
	};
	class const_reverse_iterator {
		T* ptr_;
	public :
		const_reverse_iterator(T* ptr)
		: ptr_(ptr)
		{}
		
		const_reverse_iterator operator ++() {
				ptr_--;
				return *this;
		}
		const_reverse_iterator operator ++(int) {
			iterator i = *this;
			ptr_--;
			return i;
		}
		
		bool operator ==(const const_reverse_iterator& other) const {
			
			return ptr_ == other.ptr_;
		}
		bool operator !=(const const_reverse_iterator& other) const {
			
			return ptr_ != other.ptr_;
		}
		
		const T& operator *() {
			return *ptr_;
		}
		
		const T* operator ->() {
			return ptr_; 
		}
		
	};
	
	iterator begin() {
		
		return iterator(buffer_);
	}
	iterator end() {
		
		 return iterator(buffer_ + size_);
	}
	const_iterator begin() const {
		
		 return const_iterator(buffer_);

	}
	const_iterator end() const {
		
		return const_iterator(buffer_ + size_);
	}
	
	reverse_iterator rbegin() {
		
		return reverse_iterator(buffer_-1 + size_);
	}
	reverse_iterator rend() {
		
		return reverse_iterator(buffer_ - 1);
	}
	const_reverse_iterator rbegin() const {
		
		return const_reverse_iterator(buffer_-1 + size_);
	}
	const_reverse_iterator rend() const {
		
		return const_reverse_iterator(buffer_ -1);
	}
	
	void push_back(T val) {
		if(size_+1 > capacity_ ) {
			alloc_new();
		}	
			buffer_[size_++] =  val;
	}
	
	void pop_back() {
		if(size_==0) {
			throw exception();
		}
		size_--;
		if(size_ < capacity_/2) {
			dealloc();
		}
	}
	
	T& front() {
		if(size_==0) {
			throw exception();
		}
		return buffer_[0];
	}
	
	const T& front() const {
			if(size_==0) {
			throw exception();
		}
		return buffer_[0];
	}
	
	T& back() {
		if(size_==0) {
			throw exception();
		}
		return buffer_[size_-1];
	}

	const T& back() const {
		if(size_==0) {
			throw exception();
		}
		return buffer_[size_-1];
	}
	
};

void command_args(int argc, char* argv[]) {
	Vector<int>*v = new Vector<int>[1];
	Vector<int>*tmp;
	size = 0;
	if ((argc-1)%2 == 0) {
		for(int i = 1; i < argc; i+=2){
			for(int m = argv[i]; m < argv[i+1]; m++){
				v[i-1].push_back(m);
			}
			if(argc > 3) {
				Vector<int>*tmp = new Vector<int>[i+1];
				tmp[i-1] = v[i-1];
				delete [] v;
				v = tmp;
			}
			cout << v[0].size() << endl;
		}
	}
}

int main(int argc, char* argv[]) {

	command_args(argc,argv[]);
		
	return 0;
}

