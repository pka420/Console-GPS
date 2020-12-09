#include<iostream>
#include<fstream>
using namespace std;

class CMPT135_String {
private:
	char *buffer;
public:
	CMPT135_String(); //The buffer is initialized to nullptr value    done
	CMPT135_String(const char *); //A null terminated char array    done
	CMPT135_String(const CMPT135_String &); //Deep copy constructor   done
	~CMPT135_String(); //Delete any heap memory and assign buffer nullptr value   done
	CMPT135_String& operator = (const CMPT135_String &); //Deep copy assignment    done
	int length() const; //Return the number of printable characters   done
	bool empty() const; //Return true if length is 0. Otherwise return false    done
	char& operator [] (const int &) const; //Assert index and then return the char at the index  done  
	CMPT135_String operator + (const char &) const; //See assignment 1		done
	CMPT135_String& operator += (const char &); //See assignment 1			done
	bool operator == (const CMPT135_String &) const; //See assignment 1		done
	bool operator != (const CMPT135_String &) const; //See assignment 1		done
	friend istream& operator >> (istream &, CMPT135_String &); //Implemented for you   done
	friend ostream& operator << (ostream &, const CMPT135_String &); //Implemented for you    done
};

int getLength(const char *str) {
	// return legnth of the null terminated character array
	// helper function for the class
	if (str == nullptr)
		return 0;
	else {
		int len = 0;
		while (str[len] != '\0')
			len++;
		return len;
	}
}



CMPT135_String::CMPT135_String()
{
// init a very empty string
	buffer = nullptr;
}

CMPT135_String::CMPT135_String(const CMPT135_String &str)
{
//constructs a CMPT135_String object which is a copy of the string str
// deep-copier
	int len = str.length();
	if(len>0) {
		this->buffer = new char[len+1];
		int i;
		for(i = 0; i<len; i++)
			this->buffer[i] = str[i];
		this->buffer[i] = '\0';
	}
}

CMPT135_String::CMPT135_String(const char *c) 
{
// a null terminated character array to CMPT135_String
	int len = getLength(c);
	if (len == 0)
		buffer = nullptr;
	else {
		buffer = new char[len+1];
		for (int i = 0; i < len; i++)
			buffer[i] = c[i];

		buffer[len] = '\0';
	}
}

CMPT135_String::~CMPT135_String()
{
// destructoir
	if (buffer != nullptr) {
		delete[] buffer;
		buffer = nullptr;
	}
}

CMPT135_String& CMPT135_String::operator = (const CMPT135_String &s)
{
// assignment operator

	this->~CMPT135_String();
	int len = s.length();
	if(len==0)
		return *this;

	this->buffer = new char[len+1];
	for(int i=0;i<len;i++) {
		this->buffer[i] = s.buffer[i];
	}
	this->buffer[len] = '\0';
	return *this;

}


int CMPT135_String::length() const
{
// returns length of the string
	return getLength(buffer);
}

bool CMPT135_String::empty() const {
	// return true if the string is empty (size = 0) false otherwise
	if(this->length() == 0)
		return true;
	return false;
}

char& CMPT135_String::operator[](const int &index) const
{
	// index operator
	if(index >=0 && index <this->length())
		return this->buffer[index];
	else {
		cout<<"\nERROR! Index out of bounds."<<endl;
		abort();
	}
}

CMPT135_String& CMPT135_String::operator += (const char &c) {
//	This function appends a copy of the character c to the calling object and 
//	returns the calling object
	//char *temp = new char;
	//*temp = c;
	*this = *this+c;
	return *this;
}

bool CMPT135_String::operator == (const CMPT135_String &str) const {
	// checks if the calling object is exactly equal to the string str
	int len = this->length();
	if (len != str.length())
		return false;
	else {
		for (int i = 0; i < len; i++) {
			if (buffer[i] != str[i])
				return false;
		}
	return true;
	}
}

bool CMPT135_String::operator != (const CMPT135_String &str) const {
	// bassicaly opposite of operator==
	return !(*this == str);
}

CMPT135_String CMPT135_String::operator + (const char &s) const {
	// adds	character s to the calling object
	int len = this->length()+ 1;
	CMPT135_String temp = new char[len+1];
	int i;
	for(i=0;i<this->length();i++) {
		temp.buffer[i] = this->buffer[i];
	}
	temp.buffer[i] = s;
	i++;
	temp.buffer[i] = '\0';
	return temp;
}

istream& operator >> (istream &in, CMPT135_String &s) {
//This function reads from keyboard or file characters until either a TAB, EOL, or EOF is reached
//The function ignores any leading or trailing spaces.
//Define some useful constant values
	#define SPACE ' '
	#define TAB '\t'
	#define EOL '\n'
//Delete the old value of s
	s.~CMPT135_String();
//Skip leading spaces, tabs, and empty lines
	char ch;
	while (!in.eof())	{
		in.get(ch);
		if (ch == SPACE || ch == TAB || ch == EOL)
		continue;
		break;
	}
//Append the value in ch to s
	if (ch != SPACE && ch != TAB && ch != EOL)
		s += ch;
		//Read characters into s until a TAB or EOL or EOF is reached
		while (!in.eof()) {
			in.get(ch);
			if (ch == TAB || ch == EOL || in.eof())
				break;
			else
				s += ch;
		}
//Remove any trailing spaces
	int trailingSpacesCount = 0;
	for (int i = s.length()-1; i >= 0; i--) 	{
		if (s[i] != SPACE)
			break;
			trailingSpacesCount++;
	}
	CMPT135_String temp;
	for (int i = 0; i < s.length()-trailingSpacesCount; i++)
		temp += s[i];
	
	s = temp;
	return in;
}
ostream& operator << (ostream &out, const CMPT135_String &s) {
	for (int i = 0; i < s.length(); i++)
	out << s[i];
	return out;
}















































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














































struct Edge
{
	int desVertexIndex; //the index (in the graph) of the destination vertex of this edge
	double cost; //cost of an edge
};


class Vertex {
private:
	CMPT135_String name; //name of the vertex
	SmarterArray<Edge> E; //edges emanating from this vertex. All the elements of E have the same origin
//vertex which is the this object. But they have different destination vertices which are given by the
//desVertexIndex member variable of each element
public:
	Vertex(); //Assign name = "N/A" and initialize E to an empty container done
	Vertex(const CMPT135_String &); //Assign name = the argument and initialize E to an empty container done 
	CMPT135_String getName() const; //Return the name done
	SmarterArray<Edge> getEdgeSet() const; //Return E done
	int getEdgeSetSize() const; //Return the size of E done
	Edge getEdge(const int &) const; //Assert an edge whose destination vertex index is equal to the
	//argument exists in E and then return it done
	double getEdgeCost(const int &desVertexIndex) const; //Assert an edge whose destination vertex index
	//is equal to the argument exists in E and then return its cost done
	void appendEdge(const int &desVertexIndex, const double &cost); //Assert there is no existing edge
	//whose destination vertex index and cost are equal to the argument values and then
	//append a new element whose destination vertex index and cost are initialized with the
	//argument values to E done
	friend ostream& operator << (ostream &, const Vertex &); //Implemented for you
};

ostream& operator << (ostream &out, const Vertex &vertex) {
	out << "Name = " << vertex.name << endl;
	out << "Edge Set" << endl;
	for (int i = 0; i < vertex.E.getSize(); i++)
		out << "\t to ---> " << vertex.E[i].desVertexIndex << ", cost = " << vertex.E[i].cost << endl;
	return out;
}

Vertex::Vertex() {
	name = "N/A";
	// E is automatically defined empty by default constructor.
}

Vertex::Vertex(const CMPT135_String &str) {
	name = str;
	// E is automatically defined empty by default constructor.
}

CMPT135_String Vertex::getName() const{
	return name;
}

SmarterArray<Edge> Vertex::getEdgeSet() const {
	return E;
}

int Vertex::getEdgeSetSize() const {
	return E.getSize();
}

Edge Vertex::getEdge(const int &index) const {
	//Assert an edge whose destination vertex index is equal to the index and exists in E and then return it
	for(int i=0; i<this->E.getSize(); i++)
		if(index == E[i].desVertexIndex)
			return E[i];

	Edge temp;
	return temp;
}

double Vertex::getEdgeCost(const int &desVertexIndex) const {
	for(int i=0;i<E.getSize();i++) {
		if(E[i].desVertexIndex == desVertexIndex)
			return E[i].cost;
	}
	// if not found.
	return 0.0;
}

void Vertex::appendEdge(const int &desVertexIndex, const double &cost) {
	//Assert there is no existing edge
	//whose destination vertex index and cost are equal to the argument values and then
	//append a new element whose destination vertex index and cost are initialized with the
	//argument values to E
	int i=0;
	for(;i<this->E.getSize();i++) {
		if(E[i].desVertexIndex == desVertexIndex)
			return;
	}

	Edge temp;
	temp.desVertexIndex = desVertexIndex;
	temp.cost = cost;
	E.append(temp);
}








































class Graph {
private:
	SmarterArray<Vertex> V;
public:
	Graph();//Construct empty graph
	Graph(const char *); //Construct a graph from a text file whose path is given by the argument
	//The text file input will consist in every line a pair of cities and the cost to go from one to
	//the other. The pair of cities and their cost will be separated by one or more SPACE or TAB
	//characters. It doesn't matter how many spaces or tabs are present. BUT THERE HAS TO BE AT LEAST
	//ONE TAB CHARACTER between the pairs of cities and AT LEAST ONE TAB between the second city and
	//the cost. This is because the CMPT135_String class uses TAB as a deliminator (separator). This
	//means city names can be made up of one or more words separated by spaces. An example of one line
	//of text in the input text file is:
	//New Westminster Port Coquitlam 4.5
	//In this example, there has to be at least one TAB char between "New Westminster" and "Port
	//Coquitlam" and at least one TAB character between "Port Coquitlam" and 4. Of course there can be
	//more than one TAB characters. The number of TABs can be equal or different. There are can be
	//zero or more spaces as much as you like without causing any problem. Moreover there can be as
	//many empty lines as one likes at the end of the file. However there MUST NOT BE any empty line
	//before the last line consisting of city pair and cost.
	/*
	Thus this function should perform the following tasks
	1. Construct a non-default file input streaming object using the argument file name done
	2. Assert the file is opened successfully done
	3. While EOF is not reached	done
	a. Read city name (CMPT135_String data type). This is the departure city.
	b. If departure city is empty CMPT135_String object, then break.
	c. Read city name (CMPT135_String data type). This is the destination city.
	d. Read the cost
	e. Append a new vertex whose name is the departure city and whose edge set is empty.
	You must use the appendVertex member function to append appropriately.
	f. Append a new vertex whose name is the destination city and whose edge set is
	empty. You must use the appendVertex member function to append appropriately.
	g. Append a new edge from the departure city to the destination city with a cost
	read in part (d) above.
	h. Append a new edge from the destination city to the departure city with a cost
	read in part (d) above.
	4. Close the input file stream object and you are done.
	*/
	SmarterArray<Vertex> getVertexSet() const; //Return V
	int getVertexSetSize() const; //Return the number of elements of V
	Vertex getVertex(const int &) const; //Assert the index argument and then return the element at index
	int getVertexIndex(const CMPT135_String &) const; //Return the index of an element whose name matches
	//the argument. If no such element is found, return -1
	//Assertion is not required
	int getVertexIndex(const Vertex &) const; //Return the index of the element whose name matches the
	//name of the vertex argument. If no such element is found,
	//return -1. Assertion is not required
	CMPT135_String getRandomVertexName() const; //Pick a vertex at random and return its name
	void appendVertex(const Vertex &); //Append the argument only if no such vertex already exists
	//If same name vertex already exists then do nothing (just return)
	//Assertion is not required
	void appendVertex(const CMPT135_String &); //Append a new vertex with the given name and empty E
	void appendEdge(const CMPT135_String &dep, const CMPT135_String &des, const double &cost); //Assert
	//two vertices whose names match the arguments exist. Then append an edge to the vertex whose name matches
	//the dep argument. The destination vertex index of the edge must be set to the index of the vertex whose
	//name matches des and its cost must be set to the cost argument
	friend ostream& operator << (ostream &, const Graph &); //Implemented for you done
};

ostream& operator << (ostream &out, const Graph &g) {
	const int CITY_NAME_WIDTH = 25;
	out << endl;
	out << "The graph has " << g.getVertexSetSize() << " vertices." << endl;
	out << "These vertices are" << endl;
	for(int i = 0; i < g.getVertexSetSize(); i++) {
		Vertex v = g.V[i];
		out << "Vertex at index " << i << " = " << v.getName() << endl;
	}
	out << endl;
	out << "Each vertex together with its edge set looks like as follows" << endl;
	for (int i = 0; i < g.getVertexSetSize(); i++) {
		Vertex v = g.V[i];
		out << v << endl;
	}
	out << endl;
	out << "The graph connectivities are as follows..." << endl;
	out.setf(ios::fixed | ios::left);
	//Left aligned fixed decimal places formatting
	for (int i = 0; i < g.getVertexSetSize(); i++) {
		Vertex depVertex = g.getVertex(i);
		SmarterArray<Edge> E = depVertex.getEdgeSet();
		for (int j = 0; j < E.getSize(); j++) {
			int desVertexIndex = E[j].desVertexIndex;
			Vertex desVertex = g.getVertex(desVertexIndex);
			out << depVertex.getName() << setw(CITY_NAME_WIDTH - depVertex.getName().length()) << " ";
			out << desVertex.getName() << setw(CITY_NAME_WIDTH - desVertex.getName().length()) << " ";
			out << setprecision(2) << E[j].cost << endl;
		}
	}
	out.unsetf(ios::fixed | ios::left); //Removing formatting
	cout.precision(0);
	//Resetting the decimal places to default
	return out;
}

Graph::Graph() {
	// default constructor
	// V is already empty
}

Graph::Graph(const char* f_name) {
	//f_name is files name
	ifstream fin; // for reading file
	fin.open(&f_name);

	if(fin.fail()) {
		cerr<<"Cannot open file..."<<endl;
		return;
	}

	char c;
	CMPT135_String dep, des;
	double cost;

	while(!fin.eof()) {
		fin>>c;
		if(c != ' ')

		
	}

}


SmarterArray<Vertex> Graph::getVertexSet() const {
	return V;
}

int getVertexSetSize() const {
//Return the number of elements of V
	return V.getSize();
}

Vertex getVertex(const int &) const { 
//Assert the index argument and then return the element at index

}
int Graph::getVertexIndex(const CMPT135_String & str) const {
	//Return the index of an element whose name matches
	//the argument. If no such element is found, return -1
	for(int i=0;i<V.getSize();i++) {
		if(V[i].getName() == str)
			return i;
	}
	return -1;
}

int Graph::getVertexIndex(const Vertex &) const {
	 //Return the index of the element whose name matches the
	//name of the vertex argument. If no such element is found,
	//return -1. Assertion is not required
}