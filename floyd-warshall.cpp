/**********************C++ program to perform floyd floyd_warshall algorithm by taking input from text file and writting output to the text file**************************/

/****************************Include Files**********************************/
#include <iostream>
#include <string>
#include <cctype> 
#include <fstream>
#include<vector>
#include<sstream>
#include<ctime>
#include<limits>

using namespace std;
#define inf 9999;

/***********************Global Variables**************************************/
int **_distance;
int **adjmatrix;
int numberofvertices;
int start_s;
int stop_s;
double timetaken;
/***********************Function Prototypes************************************/
int countvertices();
void fileread();
void floyd_warshall(int **adjmatrix);
void filewrite();


/**********************main Function starts here******************************/
int main()
{
	numberofvertices= countvertices();
	
	adjmatrix = new int*[numberofvertices];
	for (int i = 0;i < numberofvertices; i++)
	{
		adjmatrix[i] = new int[numberofvertices];

	}
	for (int i = 0;i < numberofvertices; i++)
	{
		for (int j = 0;j < numberofvertices; j++)
			adjmatrix[i][j] = inf;
	}
	fileread();
	start_s = clock();
	floyd_warshall(adjmatrix);
	stop_s = clock();
	timetaken = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000000;
	filewrite();
	getchar();
}

/********************This function counts the number of vertices in the graph******************************/
int countvertices()
{
	ifstream inFile("input.txt");
	string line;
	int count = 0;
	if (inFile.is_open())
	{
		while (!inFile.eof())// count the number of lines till the file reaches its end
		{
			getline(inFile, line);
			count++;
		}
	}
	inFile.close();
	return count;

}


/*********************************This function reads the input from the text file*****************************************/
void fileread()
{
	ifstream inFile("input.txt");
	string str;
	
	if (inFile.is_open())
	{
		for (string str;getline(inFile, str);)
		{
			vector <string> tok;
			string intial;
			stringstream flag(str);
			while (getline(flag, intial, ' ')) //tokenize the string
			{
				tok.push_back(intial);
			}
			int vertex1;
			stringstream stringstream1;
			stringstream1 << tok[0];
			stringstream1 >> vertex1;  //converts the string to integer and store the value to the vertex1
			int vertex2;
			for (int i = 1; i < tok.size(); i++)
			{
				string item1 = tok[i];
				string item2;
				int j;
				for (j = 0; j < item1.size(); j++)
				{
					if (item1[j] == ':')
						break;
					item2.push_back(item1[j]);
				}
				
				stringstream stringstream2;
				int vertex2;
				stringstream2 << item2;
				stringstream2 >> vertex2; //converts the string to integer and store the value to the vertex2
				int weight;
				string sub= item1.substr(j + 1);
				stringstream stringstream3;
				stringstream3 << sub;
				stringstream3 >> weight; //converts the string to integer and stores the value to weight
				adjmatrix[vertex1][vertex2] = weight;
				
			}


		}
	}


}



/************************************Perform Floyd floyd_warshall algorithm to calculate the minimum _distance********************/
void floyd_warshall(int **adjmatrix)
{

	_distance = new int*[numberofvertices];
	for (int i = 0;i < numberofvertices; i++)
	{
		_distance[i] = new int[numberofvertices];

	}

	for (int i = 0;i < numberofvertices; i++)
	{
		for (int j = 0;j < numberofvertices; j++)
			_distance[i][j] = adjmatrix[i][j];
	}
	for (int k = 0; k < numberofvertices; k++)
	{
		for (int i = 0; i < numberofvertices; i++)
		{

			for (int j = 0; j < numberofvertices; j++)

			{
				if ((_distance[i][k] + _distance[k][j]) < _distance[i][j])
					_distance[i][j] = _distance[i][k] + _distance[k][j];

			}
		}
	}

}

/*************************This function writes the output obtained from floyd floyd_warshall algorithm to the output file****************************/
void filewrite()
{
	ofstream outFile("output.txt"); //creates the output file to store the output obtained from floyd floyd_warshall algorithm

	if (outFile.is_open())
	{
		
		for (int i = 0; i < numberofvertices; i++)
		{
			_distance[i][i] = 0;
			for (int j = 0; j < numberofvertices; j++)
			{
				outFile << _distance[i][j] << " "; //writes the output to output file

			}
			outFile << endl;
		}

	}
	cout << timetaken;
	outFile.close();
}




