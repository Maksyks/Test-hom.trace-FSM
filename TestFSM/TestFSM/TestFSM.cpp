//The program tests the installation routes
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
using namespace std;
//The structure of transitions
struct Transition
{
	unsigned int s1; //Past state
	unsigned int trin; //Input character
	unsigned int trout; //Output character
	unsigned int s2; //New state
};

//The tree
class Node
{
public:
	vector <unsigned int> node; //States
	vector <Node*>* successor; //Successor
	Node() { successor = new vector<Node*>(); }
	friend class FSM;
};

class FSM
{
private:
	unsigned int s; //Number of states
	unsigned int i; //Number of input character
	unsigned int o; //Number of output character
	unsigned int tr; //Number of transitions
	Transition* Transit;
	Node* root;
public:
	friend class Node;
	FSM()
	{
		s = 0;
		i = 0;
		o = 0;
		tr = 0;
		Transit = NULL;
		root = NULL;
	}
	FSM(string FSMpr);
	unsigned int gettr()
	{
		return tr;
	}
	unsigned int geti()
	{
		return i;
	}
	unsigned int geto()
	{
		return o;
	}
	unsigned int gets()
	{
		return s;
	}
	Transition  getTr1(unsigned int y)
	{
		return Transit[y];
	}

	void test(string);
	void test_main(vector<vector<unsigned int>>, vector<vector<unsigned int>>, 
		vector<unsigned int>, vector<unsigned int>);
};

void FSM :: test_main(vector<vector<unsigned int>> listof_vec_out, vector<vector<unsigned int>> listof_vec_in,
	vector<unsigned int> vec_in, vector<unsigned int> vec_out)
{
	/*it takes inputs and outputs, looks for a transition from any state,
if there are several states, then it looks for the right one among them,
if nothing was found, an error*/
	vector<unsigned int> states;
	bool flag = false;
	for (unsigned int a = 0; a < listof_vec_in.size(); a++)
	{
		flag = false;
		unsigned int c = 0;
		for (unsigned int i = 0; i < s; i++)//to state
		{	
			unsigned int st = i;
			c = 0;
			//if the condition is found, reset the parameters, go to the next character
			for (int m = 0; m < tr; m++)
			{
				if (Transit[m].s1 == st && Transit[m].trin == listof_vec_in[a][c] && Transit[m].trout == listof_vec_out[a][c + 1])
				{
					st = Transit[m].s2;
					c++;
					m = -1;
					if (c == listof_vec_in[a].size())
					{
						/*saving states in case of existence 
						multiple states on the same path*/
						states.push_back(st);
						break;
					}
				}
			}
		}
		//search for the desired state among the found ones
		for (int g = 0; g < states.size();g++)
			if (states[g] == listof_vec_out[a][0])
				flag = true;

		if (!flag)
		{
			cout << "Error in trace: " + (a + 1) << "\n";
			break;
		}
		states.clear();
	}
	if(flag)
		cout << "Test was successful" << "\n";
}

void  FSM::test(string FSMht)
{
	ifstream fin;
	fin.open(FSMht);

	if (!fin.is_open())
		cout << "Error opening the Homing traces file" << "\n";
	else
		cout <<  "Homing traces file is open" << "\n";
	//saving vectors
	vector<vector<unsigned int>> listof_vec_out;
	vector<vector<unsigned int>> listof_vec_in;
	//working vectors
	vector<unsigned int> vec_in; 
	vector<unsigned int> vec_out;
	char v = 0;
	//for dividing the routes into inputs and outputs + state
	while (!fin.eof())
	{
		fin.get(v);
		if (v != '\n')
		{
			vec_out.push_back(v - '0');//state
			fin.get(v);
			fin.get(v);
			
			while (v != '\n')
			{	
				fin.get(v);
				fin.get(v);
				if (v == '\n')
					break;
				vec_in.push_back(v - '0');
				fin.get(v);
				fin.get(v);
				vec_out.push_back(v - '0');
			}
			listof_vec_out.push_back(vec_out);
			listof_vec_in.push_back(vec_in);
			vec_out.clear();
			vec_in.clear();
		}
	}
	this->test_main(listof_vec_out, listof_vec_in, vec_in, vec_out);
	fin.close();
}

FSM::FSM(string FSMpr)
{
	ifstream fin;
	fin.open(FSMpr);

	if (!fin.is_open())
		cout << "Error opening the Properties file" << "\n";
	else
		cout << "Properties file is open" << "\n";
	fin >> s;
	fin >> i;
	fin >> o;
	fin >> tr;
	Transit = new Transition[gettr()];
	while (!fin.eof())
	{
		for (unsigned int i = 0;i < tr;i++)
		{
			fin >> Transit[i].s1;
			fin >> Transit[i].trin;
			fin >> Transit[i].s2;
			fin >> Transit[i].trout;

		}
	}
	fin.close();
}

int main()
{
	string FSMpr = "C:\\Users\\Admin\\source\\repos\\FSM\\FSM\\Properties.txt";
	string FSMht = "C:\\Users\\Admin\\source\\repos\\FSM\\FSM\\Homing traces.txt";
	FSM obj(FSMpr);
	obj.test(FSMht);
}