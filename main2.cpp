#include<iostream>
#include<fstream>
#include<cstdlib>		// for random number
using namespace std;
struct Edge
{
	int desVertexIndex; //the index (in the graph) of the destination vertex of this edge
	double cost; //cost of an edge
};


class Vertex {
private:
	CMPT135_String name; //name of the vertex
	SmarterArray<Edge> E; //edges emanating from this vertex. All the elements of E have the same origin vertex which is the this object. But they have different destination vertices which are given by the desVertexIndex member variable of each element
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
	fin.open(&f_name);

	if(fin.fail()) {
		cerr<<"Cannot open file..."<<endl;
		return;
	}

	char c;
	CMPT135_String dep, des;
	Vertex v;
	double cost;
	bool flag = false;		// to know when to insert
	bool flag_read_dep = false;
	bool flag_read_des = false;

	while(!fin.eof()) {
		fin>>c
		if(c != ' ' ) 
			dep = dep + c;
		else 
			flag_read_dep = true;

		if(dep.Empty())
			break;

		if(flag_read_dep == true ) {
			if(c != ' ') 
				des = des + c;
			else
				flag_read_des = true;

			if(des.Empty())
				break;
		}

		if(flag_read_des == true) {
			fin>>cost;
			flag = true;
		}
			
		if(flag == true) {
			V.appendVertex(dep);
			V.appendVertex(des);
			V.appendEdge(dep, des, cost);
			V.appendEdge(des, dep, cost);
			flag_read_des = flag_read_dep = flag = false;
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

	return V[i];	// and we are done
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


CMPT135_String getRandomVertexName() const {
	//Pick a vertex at random and return its name
	int size = V.getSize();
	int x = rand()%size; 	// x is our random number between 0 to size-1.

	return V[x].getName();		// return name of the vertex at index 'x'
}
void Graph::appendVertex(const Vertex &v ) {
	//Append the argument only if no such vertex already exists
	//If same name vertex already exists then do nothing (just return)
	for(int i=0;i<V.getSize();i++) {
		if(v.name == V[i].name)		// checks if the vertex already exists in the graph.
			return;		// exits the function
	}

	V.append(v);		// and we are done.
}


void Graph::appendVertex(const CMPT135_String &name) {
	//Append a new vertex with the given name and empty E
	Vertex v(name);		// name is name and E will be emoty
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
	}

	if(flag1 == false || flag2 == false)
		return;					// any of the cities were not present in the map.

	// now lets append the edge

	/*
	// don'r worry about this idea.
	Edge AtoB, BtoA;		// edge A to B (dep to des)	and vice versa.

	AtoB.desVertexIndex = pos2;	// edge from deparure city(pos1) to destination(pos2)

	BtoA.desVertexIndex = pos2;	// edge from deparure city(pos[2) to destination(pos1)
	
	AtoB.cost = BtoA.cost = cost;		// both have same cost.
	*/
	
	V[pos1].appendEdge(pos2, cost);		// it will call Vertex::appendEdge(destVertexIndex, cost) of vertex at pos1
}
