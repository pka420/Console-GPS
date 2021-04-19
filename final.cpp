#include <iostream>
#include <fstream>
#include <cassert>
#include <ctime>
#include <iomanip>
using namespace std;

class CMPT135_String
{
private:
  char *buffer; //The dynamic array to store the printable characters and a null terminating character 
public:
  CMPT135_String(); //The buffer is initialized to nullptr value
  CMPT135_String(const char *); //A non-default constructor with a null terminated char array argument
  CMPT135_String(const CMPT135_String &); //Deep copy constructor
  ~CMPT135_String();  //Delete any heap memory and assign buffer nullptr value
  CMPT135_String& operator = (const CMPT135_String &); //Memory cleanup and deep copy assignment
  int length() const; //Return the number of printable characters. Return zero if buffer is nullptr
  bool empty() const;  //Return true if length is 0. Otherwise return false
  char& operator [] (const int &) const;  //Assert index and then return the char at the index
  CMPT135_String operator + (const char &) const; //Return *this appended with the argument character
  CMPT135_String& operator += (const char &); //Append the character argument to *this and return it
  bool operator == (const CMPT135_String &) const; //Case sensitive equality comparison
  bool operator != (const CMPT135_String &) const; //Case sensitive not equality comparison
  friend istream& operator >> (istream &, CMPT135_String &); //Implemented for you
  friend ostream& operator << (ostream &, const CMPT135_String &); //Implemented for you
};

CMPT135_String::CMPT135_String() {
  // default constructor 
  buffer = nullptr;
}

CMPT135_String::CMPT135_String(const CMPT135_String &str) {
  // deep copy constructor
  int len = str.length();
  if(len>0) {
    this->buffer = new char[len+1];
    int i;
    for(i = 0; i<len; i++)
      this->buffer[i] = str[i];
    this->buffer[i] = '\0';
  }
}

CMPT135_String::CMPT135_String(const char *troop) {
  //A non-default constructor with a null terminated char array argument
  int size = 0; // size of cstring troop
  if(troop != nullptr) 
    while(troop[size] != '\0') 
      size++;

  if (size == 0)
    buffer = nullptr;
  else {
    buffer = new char[size+1];
    for (int i = 0; i < size; i++)
      buffer[i] = troop[i];
    buffer[size] = '\0';
  }
}

CMPT135_String::~CMPT135_String() {
  // destructor
  if (this->length() > 0) {
    delete[] buffer;
    buffer = nullptr;
  }
}

CMPT135_String& CMPT135_String::operator = (const CMPT135_String &s) {
  // assignment operator
  if(s == *this)
    return *this;

  this->~CMPT135_String();
	
  int size = s.length();

  this->buffer = new char[size+1];
  for(int i=0;i<size;i++) {
    this->buffer[i] = s.buffer[i];
  }
  this->buffer[size] = '\0';
  return *this;
}


int CMPT135_String::length() const {
  // get size
  if (this->buffer == nullptr)
    return 0;
	
  int length = 0;
  while (buffer[length] != '\0') 
    length++;
  return length;
}

bool CMPT135_String::empty() const {
  // return true if CMPT135_String is empty
  if(this->length() == 0)
    return true;
  return false;
}

char& CMPT135_String::operator[](const int &index) const {
  if(index<0 || index>this->length()) {
    cout<<"\nERROR Index out of Bounds in CMPT135_String operator[]"<<endl;
    cout<<"Exiting the program"<<endl;
    abort();
  }
	
  return this->buffer[index];
}

CMPT135_String CMPT135_String::operator + (const char &ch) const {
  //addition operator 
  CMPT135_String temp;
  temp.buffer = new char[this->length() + 2];		
  int i=0;
  while(i<this->length()) {
    temp.buffer[i] = this->buffer[i];
    i++;
  }
  temp.buffer[i] = ch;
  i++;
  temp.buffer[i] = '\0';
  return temp;
}

CMPT135_String& CMPT135_String::operator += (const char &c) {
  *this = *this+c;
  return *this;
}

bool CMPT135_String::operator == (const CMPT135_String &str) const {
  // comparator
  int size = this->length();
  if (size != str.length())
    return false;
  else {
    for (int i = 0; i < size; i++) {
      if (buffer[i] != str[i])
	return false;
    }
    return true;
  }
}

bool CMPT135_String::operator != (const CMPT135_String &str) const {
  // inverse comparator
  return !(*this == str);
}

istream& operator >> (istream &in, CMPT135_String &s)
{
  //This function reads characters input from a keyboard or a file until either a TAB, EOL, or EOF is 
  //reached. The function ignores any leading spaces, TAB, or EOL characters. It is designed 
  //to be able to read a string of characters that may or may not contain spaces without any problem.
  //It is also designed to ignore any trailing spaces.

  //Define some useful constant values
#define SPACE ' '
#define TAB '\t'
#define	EOL	'\n'

  //Delete the old value of s
  s.~CMPT135_String();

  //Skip leading spaces, tabs, and empty lines
  char ch;
  while (!in.eof())
    {
      in.get(ch);
      if (ch == SPACE || ch == TAB || ch == EOL)
	continue;
      break;
    }

  if (in.eof())
    return in;

  //Append ch to s
  if (ch != SPACE && ch != TAB && ch != EOL)
    s += ch;

  //Read characters into s until a TAB or EOL or EOF is reached
  while (!in.eof())
    {
      in.get(ch);
      if (ch == TAB || ch == EOL || in.eof())
	break;
      else
	s += ch;
    }

  //Remove trailing spaces if any
  int trailingSpacesCount = 0;
  for (int i = s.length()-1; i >= 0; i--)
    {
      if (s[i] != SPACE)
	break;
      trailingSpacesCount++;
    }
  if (trailingSpacesCount > 0)
    {
      CMPT135_String temp;
      for (int i = 0; i < s.length()-trailingSpacesCount; i++)
	temp += s[i];
      s = temp;
    }

  return in;
}
ostream& operator << (ostream &out, const CMPT135_String &s)
{
  for (int i = 0; i < s.length(); i++)
    out << s[i];
  return out;
}
/*
  int main()
  {
  CMPT135_String departure, destination;
  double cost;
  ifstream fin("ConnectivityMap1.txt");
  assert(!fin.fail());
  const int CITY_NAME_WIDTH = 25; //For output formatting purposes
  while (!fin.eof()) {
  fin >> departure;
  fin >> destination;
  if (departure.empty() || destination.empty())
  break;
  fin >> cost;
  cout << departure << setw(CITY_NAME_WIDTH - departure.length()) << " ";
  cout << destination << setw(CITY_NAME_WIDTH - destination.length()) << " ";
  cout << cost << endl;
  }
  fin.close();
  system("Pause");
  return 0;
  }
*/	

template <class T>
class SmarterArray
{
private:
  T *A; //The dynamic array to store the elements
  int size; //The number of elements in the array

public:
  //Constructors
  SmarterArray(); //Implemented for you
  SmarterArray(const SmarterArray<T>&); //Copy constructor. Deep copy of the argument

  //Assignment operator
  SmarterArray<T>& operator = (const SmarterArray<T>&); //Memory cleanup and deep copy of the argument

  //Destructor
  ~SmarterArray(); //Implemented for you

  //Getters, Setters, operators and other functions
  int getSize() const; //Return the number of elements in the container
  T& operator[](const int&) const; //Assert index and then return the element at the given index
  int find(const T&) const; //Return the index of the first element that is == to the argument. 
  //Return -1 if not found.
  void insert(const int &index, const T&); //Assert index >= 0 && index <= size and then insert the T
  //type argument into the calling object at the index. If index is
  //equal to size, then insert as a last element
  void append(const T&);  //Insert T as a last element
  bool remove(const int&); //If the index is valid, then remove the element at the index argument
  //from the calling object and return true. Otherwise do nothing and return 
  //false. Do not assert the index argument.
  bool operator == (const SmarterArray<T>&) const; //Return true if sizes are equal and elements at the
  //same indexes are equal. Otherwise return false
	
  template <class T1> //Those of you working with xCode, don't use the same template name T. T1 is ok.
  friend ostream& operator << (ostream&, const SmarterArray<T1>&); //Implemented for you
};

template <class T>
SmarterArray<T>::SmarterArray()
{
  this->A = nullptr;
  this->size = 0;
}

template<class T>
SmarterArray<T>::SmarterArray(const SmarterArray<T> &L) {
  // deep copy constructor
  this->size=L.getSize();
  if(this->getSize()>0) {
    this->A=new T [this->getSize()];
    for(int i=0;i<this->getSize();i++)
      this->A[i] = L[i];
  }
}

template<class T>
SmarterArray<T>& SmarterArray<T>::operator=(const SmarterArray<T> &L) {
  //assignment operator
  this->~SmarterArray();
  this->size=L.getSize();
  if(this->getSize()>0) {
    this->A = new T[this->getSize()];
    for(int i =0;i<this->getSize();i++) 
      this->A[i] = L[i];
  }
  return *this;
}

template <class T>
SmarterArray<T>::~SmarterArray() {
  // destructor
  if (this->getSize() > 0) {
    delete[] this->A;
    A = nullptr;
    this->size= 0;
  }
}

template<class T>
int SmarterArray<T>::getSize() const {
  //getter
  return this->size;
} 

template<class T>
T& SmarterArray<T>::operator[](const int& index ) const {
  // index operator
  if(index>=0  && index<this->getSize()){
    return this->A[index];
  }
  else {
    cout<<"ERROR! ARRAY INDEX OUT OF BUONDS!";
    abort();
  }
}

template<class T>
int SmarterArray<T>::find(const T &element) const {
  // finding element in SmarterArray
  for(int i=0;i<this->getSize();i++) 
    if(A[i]==element)
      return i+1;
  return -1;// not found
}

template<class T>
void SmarterArray<T>::append(const T& element) {
  // appending element at the end of SmarterArray
  T *temp=new T [this->getSize()+1];
	
  for(int i=0;i<this->getSize();i++) 
    temp[i]=this->A[i];
		
  temp[this->getSize()]=element;
  if(this->getSize()>0)
    delete[] A;

  this->size+=1;
  this->A=temp;
}

template<class T>
void SmarterArray<T>::insert(const int &index, const T &element) {
  // inserting element at index.
  if(index < 0 || index > this->getSize() )    // do nothing
    return;

  if(index == this->getSize() ) 
    this->append(element);

  T *temp=new T[this->getSize()+1];		
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
  // removing element at index
  if(index > this->getSize()  || index < 0) // do nothing
    return false;
       
  for(int i=0;i<this->getSize();i++) {  // to find.
    if(this->A[i] == A[index]) {
      for(int j=i;j<(this->getSize()-1);j++) {  // to copy
	this->A[j] = this->A[j+1];			
      }
      this->size = this->getSize()-1;
      return true;
    }
  }
  return false;
}

template<class T>
bool SmarterArray<T>::operator == (const SmarterArray<T>& L) const {
  // assignment operator.
  if(this->getSize() != L.getSize()) // do nothing
    return false;
	
  for(int i=0; i<this->getSize(); i++) { 
    if(this->A[i] != L[i])
      return false;
  }
  return true;
}


template <class T>
ostream& operator << (ostream& out, const SmarterArray<T>& L)
{
  if (L.getSize() == 0)
    out << "[Empty List]";
  else
    {
      cout << endl;
      for (int i = 0; i < L.getSize()-1; i++)
	out << L[i] << endl;
      out << L[L.getSize()-1] << endl;
    }
  return out;
}

struct Edge  {
  intdesVertexIndex; //the index (in the underlying graph) of the destination vertex of this edge
  double cost;//cost of an edge
};

class Vertex
{
private:
  CMPT135_String name; //Name of the city at the vertex
  SmarterArray<Edge> E; //A container to store the edges emanating from this vertex. All the elements of 
  //E have the same origin vertex which is the *this object. But they have different destination
  //vertices which are given by the desVertexIndex member variable of each element of the E container

public:
  Vertex(); //Assign name = "N/A" and initialize E to an empty container (default object E)
  Vertex(const CMPT135_String &); //Assign name = the argument and initialize E to an empty container
  CMPT135_String getName() const; //Return the name
  SmarterArray<Edge> getEdgeSet() const; //Return E
  int getEdgeSetSize() const; //Return the size of E
  Edge getEdge(const int & desVertexIndex) const; //Assert an edge whose destination vertex index is 
  //equal to the argument is found in E. Then return the edge
  double getEdgeCost(const int &desVertexIndex) const; //Assert an edge whose destination vertex index 
  //is equal to the argument is found in E. Then return its cost
  void setEdgeCost(const int &desVertexIndex, const double &cost); //Assert an edge whose destination vertex index 
  //is equal to the argument is found in E. Then assign its cost the argument
  void appendEdge(const int &desVertexIndex, const double &cost); //Assert there is no element of E 
  //whose destination vertex index and cost are equal to the argument values. Then append
  //a new element whose destination vertex index and cost are initialized with the
  //argument values to E
  friend ostream& operator << (ostream &, const Vertex &); //Implemented for you
};

Vertex::Vertex() {
  // constructor.
  name = "N/A";
}

Vertex::Vertex(const CMPT135_String &myName) {
  //Assign name = the argument and initialize E to an empty container
  name = myName;
}

CMPT135_String Vertex::getName() const {
  return name;
}

SmarterArray<Edge> Vertex::getEdgeSet() const {
  return E;
}

int Vertex::getEdgeSetSize() const {
  return E.getSize();
}

Edge Vertex::getEdge(const int & desVertexIndex) const {
//Assert an edge whose destination vertex index is 
//equal to the argument is found in E. Then return the edge
  Edge dummy_e;
  if( desVertexIndex < 0 || desVertexIndex > this->getEdgeSetSize())  // do nothing
    return dummy_e;
  
  for(int i=0; i<this->E.getEdgeSetSize(); i++)
    if(desVertexIndex == E[i].desVertexIndex)
      return E[i];
  
  return dummy_e;
}

double Vertex::getEdgeCost(const int &desVertexIndex) const {
  // finding desVertexIndex in Edge array.
  for(int i=0;i<E.getSize();i++) {
    if(E[i].desVertexIndex == desVertexIndex)
      return E[i].cost;
  }
  // not found
  return -1;
}

void Vertex::setEdgeCost(const int &desVertexIndex, const double &cost) {
  // setter for cost.
  bool flag=false;
  for(int i=0;i<E.getSize();i++) {
    if(E[i].desVertexIndex == desVertexIndex) {
      E[i].cost = cost;
      flag = true;
    }
  }
  if(flag == false) {
    cout<<"ERROR: "
    cout<<"desVertexIndex "<<desVertexIndex<<" not found in Edge, setter failed!."<<endl;
  }
}

void Vertex::appendEdge(const int &desVertexIndex, const double &cost) {
  // appending vertex desVertexIndex and cost to Edge
  int i=0;
  while(i<this->E.getSize()) {
    if(E[i].desVertexIndex == desVertexIndex) { // match found, !bad!
      if(E[i].cost == cost) // do nothing.
	return;
      else {  // edge exist but at different cost. Updating cost and exiting. 
	E[i].cost = cost;
	return;
      }
    }
    i++;
  }
  Edge newEdge;
  newEdge.desVertexIndex = desVertexIndex;
  newEdge.cost = cost;
  E.append(newEdge); // SmarterArray's append.
}

ostream& operator << (ostream &out, const Vertex &vertex)
{
  out << "Name = " << vertex.name << endl;
  out << "Edge Set" << endl;
  for (int i = 0; i < vertex.E.getSize(); i++)
    out << "\t to ---> " << vertex.E[i].desVertexIndex << ", cost = " << vertex.E[i].cost << endl;
  return out;
}

class Graph
{
private:
  SmarterArray<Vertex> V; //A graph is simply a container that contains many vertex objects where each vertex
  //will have all its connectivity information in it.

public:
  Graph();//Construct empty graph (default object V)
  Graph(const char *); //Construct a graph from a text file whose path is given by the argument cstring.
  //The input text file will consist pairs of cities and the cost to go from one to the other as in the 
  //following examples

  //        Vancouver             Port Coquitlam        4.5
  //        Burnaby          Surrey        2.5
  //        UBC					Delta          6.8

  //The pairs of cities and their costs will be separated by one or more SPACE, TAB or EOL characters.
  //It doesn't matter how many spaces, tabs or EOL characters are present. All leading spaces, tabs and 
  //EOL characters will be ignored. Moreover any trailing spaces will be removed.

  //The reading of characters will start at the first non space, tab, or EOL character and it will stop 
  //when either a tab, EOL, or EOF character is read. This means THERE MUST BE AT LEAST ONE TAB OR EOL 
  //character between pairs of city names and cost. Last but not least, there can be as many spaces, TABs,
  //or EOL characters at the end of the file and these do not affect the reading of the input file.
	
  //This means a city name can have a space in it as in "Port Coquitlam" and it will be read correctly.
	
  //Please note that we do not need to worry about all these input format details because our CMPT135_String
  //class is designed to do all the reading details for us as shown in the test program given above.

  //Thus this function should perform the following tasks
  //1.	Construct a non-default file input streaming object fin using the cstring argument file name
  //2.	Assert the file is opened successfully
  //3.	While EOF is not reached do
  //	a.	Read city name. This is the departure city.
  //	b.	Read city name. This is the destination city.
  //	b.	If either the departure city or the destination city is empty CMPT135_String object, then break.
  //	d.	Read the cost.
  //	e.	Append a vertex whose name is the departure city and whose edge set is empty to the graph. 
  //		You must use the appendVertex member function of this class (see below) to append appropriately.
  //	f.	Append a vertex whose name is the destination city and whose edge set is empty to the graph. 
  //		You must use the appendVertex member function of this class to append appropriately.
  //	g.	Append an edge from the departure city to the destination city with a cost read in part (d) above 
  //		to the graph. You must use the appendEdge member function of this class (see below) to append 
  //		appropriately.
  //	h.	Append an edge from the destination city to the departure city with a cost read in part (d) above 
  //		to the graph. You must use the appendEdge member function of this class (see below) to append 
  //		appropriately.
  //4.	Close the input file stream object and you are done.

  SmarterArray<Vertex> getVertexSet() const; //Return V
  int getVertexSetSize() const; //Return the number of elements of V
  Vertex& operator[](const int &index) const; //Assert the index argument and then return the element at index
  int getVertexIndex(const CMPT135_String &) const; //Return the index of an element whose name matches	
  //the argument. If no such element is found, return -1.
  //Assertion should not be performed.
  int getVertexIndex(const Vertex &) const; //Return the index of the element whose name matches the
  //name of the vertex argument. If no such element is found, 
  //return -1. Assertion should not be performed.
  CMPT135_String getRandomVertexName() const; //Pick a vertex at random and return its name
  void appendVertex(const CMPT135_String &); //Append a vertex with the given name and empty E only 
  //if no vertex with the same name already exists in the graph. If same name 
  //vertex already exists then do nothing and return. Assertion should not be performed.
  void appendVertex(const Vertex &); //Append the argument only if no vertex with the same name already exists 
  //in the graph. If same name vertex already exists then do nothing 
  //and return. Assertion should not be performed.

  void appendEdge(const CMPT135_String &departure, const CMPT135_String &destination, const double &cost); 
  //Assert two vertices whose names match the departure and destination arguments exist in the graph.
  //If there is already an edge from the departure argument to the destination argument, then
  //Update (modify) its cost to the cost argument.
  //Otherwise
  //Append an edge to the vertex whose name matches the departure argument. The destination vertex index of the 
  //edge must be set to the index of the vertex whose name matches destination argument and its cost must be set to
  // the cost argument.
  friend ostream& operator << (ostream &, const Graph &); //Implemented for you
};

Graph::Graph() {}

Graph::Graph(const char* txt_file) {
  //-> txt file contains connectivity information.
	ifstream fin; 
	fin.open(txt_file);

	if(fin.fail() == true) {
	  cout<<"File: "<<txt_file<<" cannot be found"<<endl;
	  cout<<"Exiting the program"<<endl;
	  return;
	}

	CMPT135_String departureCity, destinationCity;
	double cost;

	while(!fin.eof()) {
		fin>>departureCity>>destinationCity>>cost;

		if(departureCity.empty() == true || destinationCity.empty() == true) {
		  cout<<"Error reading file: "<<txt_file<<endl;
		}
		this->appendVertex(departureCity);
		this->appendVertex(destinationCity);
		this->appendEdge(destinationCity, departureCity, cost);
		this->appendEdge(departureCity, destinationCity, cost);
	}
	fin.close();	
}

SmarterArray<Vertex> Graph::getVertexSet() const {
  return V;
}

int Graph::getVertexSetSize() const {
  return V.getSize();
}

int Graph::getVertexIndex(const CMPT135_String &vertex_name) const {
  //Return the index of an element whose name matches	
  //the argument. If no such element is found, return -1.
  //Assertion should not be performed.

  for(int i=0;i<this->getVertexSetSize();i++) {
    if(this->V[i].getName() == vertex_name)
      return i;
  }
  return -1; // not found.
}
int Graph::getVertexIndex(const Vertex &v) const {
  //Return the index of the element whose name matches the
  //name of the vertex argument. If no such element is found, 
  //return -1. Assertion should not be performed.
  for(int i=0;i<this->getVertexSetSize();i++) {
    if(this->V[i] == v)
      return i;
  }
  return -1; // not found.
}

Vertex& Graph::operator[](const int &index) const {
  //Assert the index argument and then return the element at index
  if(index < 0 || index > this->getSetSize())
    cout<<"ERROR: Index out of bounds in Graph operator[]"<<endl;

  return V[index];
}

CMPT135_String Graph::getRandomVertexName() const {
   //Pick a vertex at random and return its name
  if(this->V.getSize() < 0 ) {
    cout<<"Not enough vertices in Graph to produce a random vertex name"<<endl;
    cout<<"Exiting the program"<<endl;
    abort();
  }
  int random_index = rand()%V.getSize(); 
  return V[random_index].getName();
}

void Graph::appendVertex(const CMPT135_String &vertex_name) {
//Append a vertex with the given name and empty E only
//if no vertex with the same name already exists in the graph. If same name
//vertex already exists then do nothing and return. Assertion should not be performed.
  Vertex temp_vertex(vertex_name);  // using constructor 
  for(int i=0;i<V.getSize();i++) {
    if(some_vertex.getName() == V[i].getName())		
      return;		
  }
  V.append(temp_vertex);		
}

void Graph::appendVertex(const Vertex & v ) {
//Append the argument only if no vertex with the same name already exists
//in the graph. If same name vertex already exists then do nothing
//and return. Assertion should not be performed.
  for(int i=0;i<V.getSize();i++) {
    if(v.getName() == V[i].getName())	// already exists
      return;		
  }
  V.append(v);		// done
}

void Graph::appendEdge(const CMPT135_String &departure, const CMPT135_String &destination, const double &cost) {
//Assert two vertices whose names match the departure and destination arguments exist in the graph.
//If there is already an edge from the departure argument to the destination argument, then
//Update (modify) its cost to the cost argument.
//Otherwise
//Append an edge to the vertex whose name matches the departure argument. The destination vertex index of the
//edge must be set to the index of the vertex whose name matches destination argument and its cost must be set to
// the cost argument.

  if(departure == destination) // do nothing.
    return;			
 
  int dep_index = this->getVertexIndex(departure);
  int des_index = this->getVertexIndex(destination);
  
  if(dep_index != -1 && desIndex != -1) {
    for (int i = 0; i < this->V[depIndex].getEdgeSetSize(); i++)  {
      if (this->V[depIndex].getEdgeSet()[i].desVertexIndex == desIndex) {
	this->V[depIndex].setEdgeCost(desIndex, cost); // already exists, updating cost and exiting
	return;
      }			
    }
    V[dep_index].appendEdge(des_index, cost); // appending edge.
  }
  else	
    return; //assertion failed.
}

ostream& operator << (ostream &out, const Graph &g)
{
  const int CITY_NAME_WIDTH = 25;
  out << endl;
  out << "The graph has " << g.getVertexSetSize() << " vertices." << endl;
  out << "These vertices are" << endl;
  for (int i = 0; i < g.getVertexSetSize(); i++)
    {
      Vertex v = g.V[i];
      out << "Vertex at index " << i << " = " << v.getName() << endl;
    }
  out << endl;
  out << "Each vertex together with its edge set looks like as follows" << endl;
  for (int i = 0; i < g.getVertexSetSize(); i++)
    {
      Vertex v = g.V[i];
      out << v << endl;
    }
  out << endl;
  out << "The graph connectivities are as follows..." << endl;
  out.setf(ios::fixed | ios::left);	//Left aligned fixed decimal places formatting
  for (int i = 0; i < g.getVertexSetSize(); i++)
    {
      Vertex depVertex = g[i];
      SmarterArray<Edge> E = depVertex.getEdgeSet();
      for (int j = 0; j < E.getSize(); j++)
	{
	  int desVertexIndex = E[j].desVertexIndex;
	  Vertex desVertex = g[desVertexIndex];
	  out << depVertex.getName() << setw(CITY_NAME_WIDTH - depVertex.getName().length()) << " ";
	  out << desVertex.getName() << setw(CITY_NAME_WIDTH - desVertex.getName().length()) << " ";
	  out << setprecision(2) << E[j].cost << endl;
	}
    }
  out.unsetf(ios::fixed | ios::left);	//Removing formatting
  cout.precision(0);					//Resetting the decimal places to default
  return out;
}

class Path
{
private:
  SmarterArray<int> P; //The indices (singular index) the vertices along the path
public:
  Path(); //Construct an empty path. Default object P.
  int length() const; //Return the number of vertices along the path (the number of elements of P)
  int find(const int &vertexIndex) const; //Return the index of an element of P such that P[index] == vertexIndex. 
  //If no element satisfies the condition, then return -1
  //Do not perform assertion operation.
  double computePathCost(const Graph &) const; //Compute the sum of the costs of edges along this path 
  //given the underlying Graph argument. Remember that the path object stores only vertex indices. Thus 
  //you need the underlying graph argument to determine the vertex objects in the graph that correspond to  
  //the indices. Then you will be able to find the edges that connect the vertices which will enable you to 
  //get the costs of the edges. The sum of the costs of these edges is returned from this function. If 
  //during the computation of the path cost, you find that there is no any edge in the underlying graph
  //that connects successive elements in P, then it means your path is an invalid path and you
  //need to abort your application.

  //For example, if the Path object contains P = [3, 8, 6, 4, 9] then this function will return the 
  //cost(from vertex whose index in G is 3 to the vertex whose index in G is 8) +
  //cost(from vertex whose index in G is 8 to the vertex whose index in G is 6) +
  //cost(from vertex whose index in G is 6 to the vertex whose index in G is 4) +
  //cost(from vertex whose index in G is 4 to the vertex whose index in G is 9)

  int& operator [](const int &index) const; //Assert index is valid in P and then return P[index]
  void insert(const int &index, const int &vertexIndex); //Assert the condition index >= 0 && 
  //index <= the length and then insert the vertexIndex argument 
  //at the specified index. If index is equal to the length, then 
  //perform append.
  void append(const int &vertexIndex); //Insert the argument as a last element.
  void remove(const int &index); //Assert the index argument and then remove the element P[index]
  SmarterArray<CMPT135_String> getPathNamesList(const Graph &) const; //Implemented for you
  friend ostream& operator << (ostream &, const Path &); //Implemented for you.
};

Path::Path() {}  // empty constructor

int Path::length() const {
  //Return the number of vertices along the path (the number of elements of P)
  return p.getSize();
}

int Path::find(const int &vertexIndex) const {
//Return the index of an element of P such that P[index] == vertexIndex.
//If no element satisfies the condition, then return -1
//Do not perform assertion operation
  for(int i=0;i<p.getSize();i++) {
    if(vertexIndex == p[i])
      return i;
  }
  return -1; // not found.
}

double Path::computePathCost(const Graph &map) const {
  double pathCost = 0.0;
  int dep_index = 0;
  int des_index = 0;
  
  for(int i=0;i<p.getSize()-1;i++) {
    dep_index = map.getVertexIndex(p[i]);		
    Vertex city = map.getVertex(dep_index);			
    des_index = map.getVertexIndex(p[i+1]);

    SmarterArray<Edge> E1 = city.getEdgeSet();
    for(int i=0; i<city.getEdgeSetSize();i++) {
      if(E1[i].desVertexIndex == des_index)
	pathCost += city.getEdgeCost(E1[i].desVertexIndex);
    }
  }
  return pathCost;
}

int& operator [](const int &index) const {
//Assert index is valid in P and then return P[index]
  if(index<0 || index>this->length()) {
    cout<<"ERROR Index out of bounds in Path::operator[]"<<endl;
    cout<<"Exiting the program"<<endl;
    abort();
  }
  return P[index];
}

void insert(const int &index, const int &vertexIndex); //Assert the condition index >= 0 &&
//index <= the length and then insert the vertexIndex argument
//at the specified index. If index is equal to the length, then
//perform append.
void append(const int &vertexIndex); //Insert the argument as a last element.
void remove(const int &index); //Assert the index argument and then remove the element P[index]



SmarterArray<CMPT135_String> Path::getPathNamesList(const Graph &g) const
{
  SmarterArray<CMPT135_String> path;
  for (int i = 0; i < this->length(); i++)
    {
      int vertexIndex = (*this)[i];
      path.append(g[vertexIndex].getName());
    }
  return path;
}
ostream& operator << (ostream &out, const Path &path)
{
  out << "[";
  if (path.length() > 0)
    {
      for (int i = 0; i < path.length()-1; i++)
	out << path[i] << " -> ";
      out << path[path.length()-1];
    }
  out << "]";
  return out;
}
