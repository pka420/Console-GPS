#include<iostream>
#include<fstream>
#include<cstdlib>		// for random number
#include<iomanip>
#include<time.h>
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
// destructor
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
	// adds	character s to the calling object and return a new string
	CMPT135_String temp;
	temp.buffer = new char[this->length() + 2];		// 1 space for s and another for null character.
	int i=0;
	for(;i<this->length();i++) {
		cout<<this->buffer[i]<<endl;
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
void SmarterArray<T>::insert(const int &index, const T &element) {
	//Assert the integer argument index >= 0 && index <= size and then
	//Insert the T type argument into the calling object at the index.
	//If the integer argument is equal to size, then perform append

	if(index < 0 || index > this->getSize() )
		return;

	if(index == this->getSize() ) 
		this->append(element);

	T *temp=new T[this->getSize()+1];		// 1 for element and 1 for null character
	int i = 0;
	for(; i<index; i++) 
		temp[i]=this->A[i];
	
	temp[i]=element;
	i++;

	for(; i<this->getSize(); i++)
		temp[i] = this->A[i-1];

	if(this->getSize()>0)
		delete[] A;
		
	this->A=temp;
	this->size+=1;
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

	cerr<<"cannot find the requested edge in the Edge set."<<endl;
	abort();
}

double Vertex::getEdgeCost(const int &desVertexIndex) const {
	for(int i=0;i<E.getSize();i++) {
		if(E[i].desVertexIndex == desVertexIndex)
			return E[i].cost;
	}
	// if not found.
	cerr<<"Cannot find the edge requested"<<endl;
	cerr<<"Aborting the program"<<endl;
	abort();
}

void Vertex::appendEdge(const int &desVertexIndex, const double &cost) {
	//Assert there is no existing edge
	//whose destination vertex index and cost are equal to the argument values and then
	//append a new element whose destination vertex index and cost are initialized with the
	//argument values to E
	int i=0;
	bool flag = false;
	for(;i<this->E.getSize();i++) {
		if(E[i].desVertexIndex == desVertexIndex) {
			flag == true;		// only update cost.
			if(E[i].cost == cost)
				return;		// don't do anything
			break;
		}
	}

	if(flag == true) {
		// update cost
		E[i].cost = cost;
	}
	else {	// initialize new edge and append.
		Edge temp;
		temp.desVertexIndex = desVertexIndex;
		temp.cost = cost;
		E.append(temp);
	}
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
	SmarterArray<Vertex> getVertexSet() const; //Return V done
	int getVertexSetSize() const; //Return the number of elements of V done
	Vertex getVertex(const int &) const; //Assert the index argument and then return the element at index done
	int getVertexIndex(const CMPT135_String &) const; //Return the index of an element whose name matches done
	//the argument. If no such element is found, return -1
	//Assertion is not required done
	int getVertexIndex(const Vertex &) const; //Return the index of the element whose name matches the
	//name of the vertex argument. If no such element is found,
	//return -1. Assertion is not required done
	CMPT135_String getRandomVertexName() const; //Pick a vertex at random and return its name done
	void appendVertex(const Vertex &); //Append the argument only if no such vertex already exists
	//If same name vertex already exists then do nothing (just return)
	//Assertion is not required done
	void appendVertex(const CMPT135_String &); //Append a new vertex with the given name and empty E done
	void appendEdge(const CMPT135_String &dep, const CMPT135_String &des, const double &cost); //assert  
	//two vertices whose names match the arguments exist. Then append an edge to the vertex whose name matches
	//the dep argument. The destination vertex index of the edge must be set to the index of the vertex whose
	//name matches des and its cost must be set to the cost argument done
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
	//cout<<f_name<<endl;
	fin.open(f_name);

	if(fin.fail() == true) {
		cerr<<"Cannot open file..."<<endl;
		return;
	}
	//else
	//	cout<<"\nWe reading..."<<endl;		

	//cout<<"I am ok"<<endl;

	char c;
	CMPT135_String dep, des, temp;
	double cost;
	bool flag = false;		// to know when to insert
	bool flag_read_dep = false;
	bool flag_read_des = false;

	fin>>noskipws;		// this way it won't skip white space

	while(!fin.eof()) {
		fin>>c;
		temp = temp + c;
		//cout<<"\ntemp: "<<temp<<"  c: "<<c<<endl;

		if(c == ' '  && flag_read_dep == false) {
			dep = temp;
			flag_read_dep = true;
			temp.~CMPT135_String();
			//cout<<"\ndep="<<dep<<endl;
			continue;
		}

		if( c == ' ' && flag_read_dep == true && flag_read_des == false) {
		//	cout<<temp<<"..."<<endl;
			des = temp;
			flag_read_des = true;
			temp.~CMPT135_String();
		//	cout<<"\ndes="<<des<<endl;
			//fin>>c;		//reading one more space before the cost.
			//continue;
		}

		if(flag_read_des == true) {
			fin>>cost;
			flag = true;
			//cout<<"\ncost: "<<cost<<endl;
		}
		//	cout<<dep<<endl;
		//cout<<"flag"<<flag<<endl;
		if(flag == true) {
		//cout<<dep<<"	"<<des<<"	"<<cost<<endl;
		//	cout<<"\nwe appending"<<endl;
			this->appendVertex(dep);
			this->appendVertex(des);
			this->appendEdge(des, dep, cost);
			this->appendEdge(dep, des, cost);
			dep.~CMPT135_String();
			des.~CMPT135_String();
			flag_read_des = flag_read_dep = flag = false;
			fin>>c;		// for taking pointer to next fucking level.
		//	cout<<"done"<<endl;
		}
	}

	fin.close();	// done
}


SmarterArray<Vertex> Graph::getVertexSet() const {
	return V;
}

int Graph::getVertexSetSize() const {
//Return the number of elements of V
	return V.getSize();
}	
	
Vertex Graph::getVertex(const int &index) const { 
//Assert the index argument and then return the element at index

	if(index < 0 || index > V.getSize() ) {
		Vertex v;		//empty vertex
		return v;
	}

	return V[index];	// and we are done
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

int Graph::getVertexIndex(const Vertex & v) const {
	//Return the index of the element whose name matches the
	//name of the vertex argument. If no such element is found,
	//return -1

	for(int i=0;i<V.getSize(); i++) 
		if(V[i].getName() == v.getName()) 
			return i;
	
	return -1;
}


CMPT135_String Graph::getRandomVertexName() const {
	//Pick a vertex at random and return its name
	int size = V.getSize();
	int x = rand()%size; 	// x is our random number between 0 to size-1.

	return V[x].getName();		// return name of the vertex at index 'x'
	//return CMPT135_String("UBC");
}
void Graph::appendVertex(const Vertex &v ) {
	//Append the argument only if no such vertex already exists
	//If same name vertex already exists then do nothing (just return)
	for(int i=0;i<V.getSize();i++) {
		if(v.getName() == V[i].getName())		// checks if the vertex already exists in the graph.
			return;		// exits the function
	}

	V.append(v);		// and we are done.
}


void Graph::appendVertex(const CMPT135_String &name) {
	//Append a new vertex with the given name and empty E
	Vertex v(name);		// name is name and E will be emoty

	for(int i=0;i<V.getSize();i++) {
		if(v.getName() == V[i].getName())		// checks if the vertex already exists in the graph.
			return;		// exits the function
	}

	V.append(v);		// appending new vertex to the graph

}
void Graph::appendEdge(const CMPT135_String &dep, const CMPT135_String &des, const double &cost) {
	//Assert two vertices whose names match the arguments exist. Then append an edge to the vertex whose name matches
	//the dep argument. The destination vertex index of the edge must be set to the index of the vertex whose
	//name matches des and its cost must be set to the cost argument

	if(dep == des)
		return;			// if the departure and destinations are equal, then don't do anything.

	bool flag1(0), flag2(0);
	int pos1 , pos2, i(0);

	while(flag1 == false || flag2 == false) {
		if(dep == V[i].getName()) {
			flag1 = true;
			pos1 = i;
		}

		if(des == V[i].getName()) {
			flag2 = true;
			pos2 = i;
		}
		i++;
	}

	if((flag1&flag2) == true )
		V[pos1].appendEdge(pos2, cost);		// it will call Vertex::appendEdge(destVertexIndex, cost) of vertex at pos1
	else	
		return;					// any of the cities were not present in the map.
	
		
	// now lets append the edge

	/*
	// don'r worry about this idea.
	Edge AtoB, BtoA;		// edge A to B (dep to des)	and vice versa.

	AtoB.desVertexIndex = pos2;	// edge from deparure city(pos1) to destination(pos2)

	BtoA.desVertexIndex = pos2;	// edge from deparure city(pos[2) to destination(pos1)
	
	AtoB.cost = BtoA.cost = cost;		// both have same cost.
	*/
	

}


class Path {
private:
	SmarterArray<CMPT135_String> p; //The names of the vertices along the path
public:
	Path(); //Construct an empty path
	int length() const; //Return the number of vertices in the path (the number of elements of p)
	int find(const CMPT135_String &) const; //Return the index of element of p whose name matches the
	//argument. If no element satisfies the condition, then return -1
	double computePathCost(const Graph &) const; //Compute the sum of the costs of edges along this path
	//given the underlying graph argument. Remember that the path object stores only city names. Thus
	//you need the underlying graph argument to determine the vertices in the graph that belong to the
	//cities. Then you will be able to find the edges that connect the vertices which will enable you to
	//get the costs of the edges. The sume of the costs of these edges is returned from this function.
	CMPT135_String& operator [] (const int &) const; //Assert index is valid and then return the
	//element of p at the given index
	void append(const CMPT135_String &); //Append the argument to the calling object
	void insert(const int &index, const CMPT135_String &); //Assert the condition index >= 0 &&
	//index <= the length and then insert the CMPT135_String argument
	//at the specified index
	void remove(const int &); //Assert the index argument and then remove the element at the specified index
	friend ostream& operator << (ostream &, const Path &); //Implemented for you.
};
ostream& operator << (ostream &out, const Path &p) {
	out << "[";
	if (p.length() > 0) {
		for (int i = 0; i < p.length()-1; i++)
			out << p[i] << " -> ";
		out << p[p.length()-1];
	}
	out << "]";
	return out;
}

Path::Path() {
	// p smarterarray is already empty
	// no need to do anything

}

int Path::length() const {
	//Return the number of vertices in the path (the number of elements of p)
	return p.getSize();
}

int Path::find(const CMPT135_String &name) const {
	//Return the index of element of p whose name matches the	
	//argument. If no element satisfies the condition, then return -1
	for(int i=0;i<p.getSize();i++) {
		if(name == p[i])
			return i;
	}
	return -1;
}

	
double Path::computePathCost(const Graph & googol) const {
	//Compute the sum of the costs of edges along this path
	//given the underlying graph argument. Remember that the path object stores only city names. Thus
	//you need the underlying graph argument to determine the vertices in the graph that belong to the
	//cities. Then you will be able to find the edges that connect the vertices which will enable you to
	//get the costs of the edges. The sume of the costs of these edges is returned from this function.

	double tot_cost = 0.0;
	int start = 0;
	int finish = 0;

	for(int i=0;i<p.getSize()-1;i++) {
		start = googol.getVertexIndex(p[i]);		//p[i] is the departure city and p[i+1] is the destination city
		Vertex a = googol.getVertex(start);			// which is again departure city's vertex
		finish = googol.getVertexIndex(p[i+1]);

		SmarterArray<Edge> E1 = a.getEdgeSet();
		for(int x=0; x<a.getEdgeSetSize();x++) {
			if(E1[x].desVertexIndex == finish)
				tot_cost += a.getEdgeCost(E1[x].desVertexIndex);
		}
	}
	return tot_cost;
}


CMPT135_String& Path::operator [] (const int &index) const {
	//Assert index is valid and then return the
	//element of p at the given index

	if(index < 0 || index>p.getSize()) { 
		cerr<<"Invalid index \n not found\n aborting the program."<<endl;
		abort();
	}

	return p[index];
}


void Path::append(const CMPT135_String &add_me) {
	//Append the argument to the calling object
	for(int i=0;i<p.getSize();i++) {
		if(p[i] == add_me )
			return;			// already exists
	}

	p.append(add_me);
}

void Path::insert(const int &index, const CMPT135_String &insert_me) {
	//Assert the condition index >= 0 &&
	//index <= the length and then insert the CMPT135_String argument
	//at the specified index
	if(index < 0 || index>p.getSize()) {
		return;
	}

	p.insert(index, insert_me);			// done
}

void Path::remove(const int &three_thousand) {
	//Assert the index argument and then remove the element at the specified index
	if(three_thousand < 0 || three_thousand>p.getSize()) 
		return;

	if(p.remove(three_thousand) == false) {
		cerr<<"cannot find the element for removing"<<endl;
		cerr<<"Aborting program"<<endl;
		abort();
	}
}




Path computeMinCostPath(const Graph &g, const CMPT135_String &departure, const CMPT135_String &destination, Path currentPath = Path() ) {
	if(g.getVertexSetSize() < 1) {
		cerr<<"Cannot find a path in the graph because of insufficient number of cities."<<endl;
		cerr<<"Aborting the program"<<endl;
		abort();
	}

	int desVertexIndex;

	desVertexIndex = g.getVertexIndex(destination);	// destination city index

	if(departure == destination) {
		Path minCostPath = currentPath;
		minCostPath.append(destination);
		cout<<minCostPath<<endl;
		return minCostPath;
	}
	else if(currentPath.find(departure) != -1) {
		Path minCostPath = currentPath;
		return minCostPath;
	}

	Vertex depVertex = g.getVertex(g.getVertexIndex(departure) );

	SmarterArray<Edge> E = depVertex.getEdgeSet();		// Edge set of depVertex.

	Path minCostPath;		// default empty path.

	currentPath.append(depVertex.getName());		// appending name of depVertex to the path.

	for(int i=0;i<E.getSize();i++) {
		CMPT135_String nextVertexName = g.getVertex(E[i].desVertexIndex).getName();  
		cout<<"Next vertex name: "<<nextVertexName<<endl;

		if(currentPath.find(nextVertexName) == -1) {		// current path does not contain nextVertex name, i.e safe to proceed
			Path candidatePath = computeMinCostPath(g, nextVertexName, destination, currentPath);
			if(candidatePath.length() != 0) {
				if((candidatePath[candidatePath.length() - 1] == destination)) {
					if(minCostPath.length() == 0)
						minCostPath = candidatePath;
					else if(minCostPath.computePathCost(g) > candidatePath.computePathCost(g)) 
						minCostPath = candidatePath;
				}
			}
		}
	}

	// remove the last element of the currentPath.
	currentPath.remove(currentPath.length() - 1);

	// i am done
	return minCostPath;
}


int main()  {
	srand(time(0));
	Graph g("Connectivity Map Large.txt");
	cout << "Graph constructed successfully." << endl;
	cout << g << endl;
	CMPT135_String departure = g.getRandomVertexName();
	CMPT135_String destination = g.getRandomVertexName();
	//CMPT135_String departure("UBC");
	//CMPT135_String destination("Richmond");
	cout << "Computing shortest path from " << departure << " to " << destination << endl;
	Path minCostPath = computeMinCostPath(g, departure, destination);
	cout << endl;
	cout << "Departure: " << departure << endl;
	cout << "Destination: " << destination << endl;
	if (minCostPath.length() == 0)
		cout << "No path found." << endl;
	else
		cout << "The minimum cost path is: " << minCostPath << " with cost = " <<
	minCostPath.computePathCost(g) << endl;
	//system("Pause");
	return 0;
}