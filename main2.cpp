#include<iostream>
using namespace std;

template <class T>
class SmarterArray {
private:
	T *A;
	int size;
public:
//Constructors
	SmarterArray(); //Implemented for You    done
	SmarterArray(const T*, const int&); //Deep copy of the argument    done
	SmarterArray(const SmarterArray<T>&); //Deep copy of the argument   done
//Assignment operator
	SmarterArray<T>& operator = (const SmarterArray<T>&); //Memory clean up and deep copy of the argument   done
//Destructor  
	~SmarterArray(); //Memory clean up   done
//Getters, Setters, operators and other functions
	int getSize() const; //Return the number of elements in the container  done
	T& operator[](const int&) const; //Assert index and then return the element at the given index done
	int find(const T&) const; //Return the index of the first element that is == to the argument.   done
//Return -1 if not found.
	void append(const T&); //Store the argument value after the last element  done
	void insert(const int &, const T&); //Assert the integer argument index >= 0 && index <= size and then
//Insert the T type argument into the calling object at the index.
//If the integer argument is equal to size, then perform append
	bool remove(const int&); //If the index is valid, then remove the element at the index argument
//from the calling object and return true. Otherwise return false. done
//You don't need to assert the index argument.
	bool operator == (const SmarterArray<T>&) const; //return true if sizes are equal and 
//elements at same indexes are equal done
	template <class T1>
	friend ostream& operator << (ostream&, const SmarterArray<T1>&); //Implemented for you
};

template <class T>
ostream& operator << (ostream& out, const SmarterArray<T>& L) {
	if (L.getSize() == 0)
		out << "[Empty List]";
	else {
		for (int i = 0; i < L.getSize()-1; i++)
		out << L[i] << endl;
		out << L[L.getSize()-1] << endl;
	}
	return out;
}

template<class T>
SmarterArray<T>::SmarterArray() {
	// constructor 
	this->size=0;
	this->A=NULL;
}
template<class T>
SmarterArray<T>::SmarterArray(const T* tekken, const int &size) {
	// copy constructor
	this->size=size;
	if(this->getSize()>0) {
		this->~SmarterArray();
		this->A = new T[this->getSize()];
		for(int i = 0 ; i<this->getSize() ; i++) {
			this->A[i] = &tekken[i];	
		}
	}
}

template<class T>
SmarterArray<T>::SmarterArray(const SmarterArray<T> &L) {
	this->size=L.getSize();
	if(this->getSize()>0) {
		this->A=new T [this->getSize()];
		for(int i=0;i<this->getSize();i++)
			this->A[i] = L[i];
	}
}
template<class T>
SmarterArray<T>::~SmarterArray() {
	// destructor
	if (this->getSize() > 0) {
		delete[] this->A;
		this->size = 0;
	}
}	

template<class T>
SmarterArray<T>& SmarterArray<T>::operator=(const SmarterArray<T> &L) {
	this->~SmarterArray();
	this->size=L.getSize();
	if(this->getSize()>0) {
		this->A = new T[this->getSize()];
		for(int i =0;i<this->getSize();i++) 
			this->A[i] = L[i];
	}
	return *this;
}

template<class T>
int SmarterArray<T>::getSize() const{
	return this->size;
} 

template<class T>
T& SmarterArray<T>::operator[](const int& index ) const {
	if(index>=0  && index<this->getSize()){
		return this->A[index];
	}
	else {
		cout<<"ERROR! ARRAY INDEX OUT OF BUONDS!";
		abort();
	}
}

template<class T>
int SmarterArray<T>::find(const T &n) const {
	for(int i=0;i<this->getSize();i++) 
		if(A[i]==n)
			return i+1;
	return -1;
}

template<class T>
void SmarterArray<T>::append(const T& e) {
	T *temp=new T [this->getSize()+1];
	
	for(int i=0;i<this->getSize();i++) 
		temp[i]=this->A[i];
		
	temp[this->getSize()]=e;
	
	if(this->getSize()>0)
		delete[] A;
		
	this->A=temp;
	this->size+=1;
}

template<class T>
void SmarterArray<T>::insert(const int &index, const T & element) {
	//Assert the integer argument index >= 0 && index <= size and then
	//Insert the T type argument into the calling object at the index.
	//If the integer argument is equal to size, then perform append

	if(index < 0 || index > this->getSize() )
		return;
	else if(index == this->getSize() ) {
		this->append(element);
	}
	else {
		T *temp=new T [this->getSize()+1];
		int i;
		for( i=0;i<index;i++) 
			temp[i]=this->A[i];
		
		temp[i]=element;
		i++;

		for(; i<this->getSize(); i++) 
			temp[i] = this->A[i-1];

		temp[i] = '\0';
	
		if(this->getSize()>0)
			delete[] A;
		
		this->A=temp;
		this->size+=1;
	}

}

template<class T>
bool SmarterArray<T>::remove(const int &index) {
	if(index > this->getSize()  || index < 0)
		return false;
	else {
		for(int i=0;i<this->getSize();i++) {
			if(this->A[i] == A[index]) {
				for(int j=i;j<(this->getSize()-1);j++) {
					this->A[j] = this->A[j+1];			
				}
				this->size = this->getSize()-1;
				return true;
			}
		}
	}
	return false;
}

template<class T>
bool SmarterArray<T>::operator == (const SmarterArray<T>& L) const {
	if(this->getSize() != L.getSize())
		return false;
	
	for(int i=0; i<this->getSize(); i++) {
		if(this->A[i] != L[i])
			return false;
	}
	return true;
}

