#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <math.h>
#include <algorithm>
//poop
using namespace std;
void BFS( vector<int> permutation, int n );
bool isValid( vector<int> state );
int h(vector<int> a);
struct Node
{
	vector<int> key;
	int parent;
	int path;
	int f;
	Node(vector<int> x, int y, int a, int b){ key = x; parent = y; path = a; f = b;}
	void PrintNode() { 
       		for (int i = 0; i < key.size(); i++)
			cout<< key[i]<< ' ';
		cout<< endl;
	
	}
	vector<int> getKey() { return key; }
	void SetParent(int x) {
		parent = x;
	}
	void Setkey(vector<int> x) {
		key = x;
	}
	void SetPath(int x) {
		path = x;
	}
	void SetF(int x) {
		f = x;
	}
};
struct CompareF
{
	bool operator() (Node* const & n1, Node* const & n2) { return n1->f > n2->f; }
};
int main() {	
	cout << "Enter a list of numbers: ";
	string ary;
	getline(cin, ary);
	vector<int> perm;
	string tmp;
	for( int i = 0; i < ary.length(); i++) {
		if( ary[i] == ' ' ) {
			perm.push_back( stoi(tmp) );
			tmp = "";
		}
		tmp += ary[i];
	}
	perm.push_back( stoi(tmp) );
	BFS(perm, perm.size() );
	return 0;
}
void BFS( vector<int> permutation, int n ) {
  	vector<Node*>Pointers;
	cout<< "DECLARATION" << endl;
	priority_queue<Node*,vector<Node*>,CompareF> Queue;
	cout<< "DECLARATION" << endl;
	Node* start = new Node(permutation, -1, 0, 0);
	cout<< "DECLARATION" << endl;
	Node* temp =  new Node(permutation, 0, 0, 0+h(start->key));
	Pointers.push_back(start);
	temp->SetParent(0);
	Queue.push(temp);
	int count = 1;
	//cout<< "DECLARATION" << endl;
	while ( !Queue.empty()){
		Node *currentNode = Queue.top();
		Queue.pop();
		if (isValid(currentNode->key)) {
			cout << "we got it" << endl;
			currentNode->PrintNode();
			return;
		}
		vector<vector<int>> children;
		for ( int i = 0; i < currentNode->key.size(); i++) {
                	for ( int j = i+1; j <= currentNode->key.size(); j++) {
                        	vector<int> temp = currentNode->key;
                        	reverse(temp.begin()+i, temp.begin()+j);
                        	if (temp != currentNode->key){
					count++;
                                	if (isValid(temp)) {
                        			cout << "we got it" << endl;
                        			currentNode->Setkey(temp);
						currentNode->PrintNode();
                        			Node* tmp = new Node(temp, currentNode->parent, 0, 0);
                        		        Pointers.push_back( tmp );
                	               		Node* tmp2 = new Node(temp, Pointers.size()-1, currentNode->path +1, (currentNode->path +1) + h(currentNode->key) );
		                                Queue.push( tmp2 );
						int idx = tmp->parent;
						cout << "Value of idx: " << count << endl;	
						while (idx!= -1){
                					Pointers[idx]->PrintNode();
							idx = Pointers[idx]->parent;
						}			
						return;
                			}

					children.push_back( temp );
				}
                	}
        	}

		for (auto child : children) {
			if ( child != currentNode->key){
				Node* tmp = new Node(child, currentNode->parent, 0 ,0);
				Pointers.push_back( tmp );
				Node* tmp2 = new Node(child, Pointers.size()-1, currentNode->path +1, (currentNode->path +1) + h(currentNode->key) );
				Queue.push( tmp2 );
				//count++;		
			}
		}
	}
}

bool isValid( vector<int> state ) {

  for( int i = 0; i < state.size() - 1; i++ )
    if( state[i] > state[i+1] )
      return false;
  return true; 
}
int h(vector<int> a) {
	int total=0;
	for( int i = 0; i < a.size()-1; i++) {
		if ( (a[i] - a[i+1]) > 1 || (a[i] - a[i+1]) < -1 )
		       total++;	
	} 
	return total/2;
}
