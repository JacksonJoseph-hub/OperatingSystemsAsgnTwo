// Jackson Joseph
// Bankers Algorithm
// 4/14/2022


#include <iostream>
#include <vector>
#include <fstream>
#include <string>


using std::cout; using std::cin; using std::endl; 
using std::vector; using std::ifstream; using std::string;


int main()
{

	//n # processes
	const int n = 5;
	//m # resource types
	const int m = 3;

	//Available:
	//vector of length m. If available [j] = k, there are k instancves of resource
	//Type R(j) available
	int Available[m];


	//Max:
	// n * m matrix.  if Max[i,j] = k, then process P may request at most k instances of resource
	// type R(j)
	int Max[n][m];



	//Allocation:
	// n * m matrix. If Allcoation[i,j] = k, then P is currently allocated k instances of R(j)
	int Allocation[n][m];

	//Need:
	// n * m matrix. if Need[i,j] = k then P may need k more instances of R(j) to complete
	int Need[n][m];

	//  Need[i,j] = Max[i,j] - Allocation[i,j]


	ifstream input;

	input.open("test.txt");

	// first m elements added to Available array
	int bp1 = m;

	// second breakpoint is after the first m elements, plus the size of the Allocation array (n * m)
	int bp2 = m + (m * n);
	int row = 0, col = 0;

	if (input.is_open()) {
		int a;
		int fcounter = 0;
		while (input >> a)
		{
			if (fcounter < bp1)
			{
				Available[fcounter] = a;
				fcounter++;
			}
			else if (fcounter < bp2)
			{
				Allocation[row][col] = a;
				col++;
				if (col % m == 0)
				{
					col = 0;
					row++;
				}
				fcounter++;
			}
			else
			{
				if (row % n == 0) row = 0;
				Max[row][col] = a;
				col++;
				if (col % m == 0)
				{
					col = 0;
					row++;
				}
				fcounter++;
			}
		}
	}
	cout << "processes n = " << n << endl;
	cout << "resources m = " << m << endl;
	//Display Allocation Matrix
	cout << "\n\n *** Allocation Matrix (n * m)\n";
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < m; k++) {
			cout << Allocation[i][k] << " ";
		}
		cout << endl;
	}
	cout << "\n";


	//Display Max Matrix
	cout << "\n\n *** Max Matrix (n * m)\n";
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < m; k++) {
			cout << Max[i][k] << " ";
		}
		cout << endl;
	}
	cout << "\n";



	// Calculate Need
	// By subtracting p(n) Max from p(n) Allocation
	// Where i is equivelant to p(n) and k modifies matrix values
	cout << "\n\n *** Need Matrix (n * m)\n";
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < m; k++) {
			Need[i][k] = Max[i][k] - Allocation[i][k];
			cout << Need[i][k] << " ";
		}
		cout << endl;
	}
	cout << "\n";

	// Array to hold the current value of work as 3 seperate elements (m)
	// Initialize to Available
	int Work[m];
	for (int i = 0; i < m; i++)
		Work[i] = Available[i];
	cout << "\n New Work Paramaters: ";
	for (int i = 0; i < m; i++) {
		cout << " " << Work[i];
	}


	// Keeps track of which processes have been successfully completed
	bool Finish[n] = { false };

	// Keeps track of order the processes safely completed
	int done[n];

	// Counter to track how many processes have completed
	// Terminate while loop when processes safely completed = total processes
	// Or -> continue until unsafe or bCounter = n

	int bCounter = 0;
	while (bCounter < n)
	{	

		bool flag = false; //reset the failswitch
		// i is equivalent to the process(i) 
		for (int i = 0; i < n; i++)
		{
			// if process(i) isn't marked as safe, evaluate it
			if (Finish[i] == 0)
			{

				bool temp = false;
				for (int k = 0; k < m; k++) {
					// Check if need is less than or equal to work
					// If need is greater, process is not safe yet
					// Move to next process
					if (Need[i][k] > Work[k])
					{
						cout << "\nprocess " << i << " failed this time\n";
						temp = true;
						break;
					}
				}
				if (!temp) 
					// If process is safe recalculate work as work = work + allocation
					// Add process to the safe process order (done)
					// And mark process as finished safely 
					// (flag) to not trip the fail and Finish to mark the process as safe
					{
						for (int l = 0; l < m; l++)
						{
							Work[l] = Work[l] + Allocation[i][l];
						}
						cout << "\n New Work Paramaters: ";
						for (int i = 0; i < m; i++) {
							cout << " " << Work[i];
						}
						done[bCounter] = i;
						bCounter++;
						Finish[i] = true; //mark process safe
						flag = true;
					}
				}
			}
		if (!flag)
		{
			cout << "Fail";
			exit(0);
		}
	}
	cout << "\nThe system is safe. Sequence: ";
	for (int i = 0; i < n; i++)
		cout << "p" << done[i] << " ";
	cout << endl;
	exit(0);
}

	
