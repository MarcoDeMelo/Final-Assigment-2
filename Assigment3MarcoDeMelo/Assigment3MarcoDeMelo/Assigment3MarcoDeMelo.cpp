#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <istream>
using namespace std;
const int SIZE = 25;

int loadArrays(ifstream&, string[], double[][4], int &);
void printReport(ofstream&, string[], double[][4], double[],int&, int&);
void computeSum(double[][4], double[], int);
void findWine(const double [][4], int& ,int& , int);
void mostWineSold(const double[], int& , int&);
int main()
{
	double salesAmt[SIZE][4];  //no need to change your variable names to match mine!
	string wine[SIZE];
	double yearlySales[SIZE] = { 0.00 };
	int noWines;
	int highestRow, highestCol, mostSold;
	cout << fixed << setprecision(2);
	ifstream fin("wines.dat");
	if (!fin.is_open())
	{
		cout << "error opening wines.dat file - contact systems";
		system("pause");
		exit(-1);
	}
	ofstream fout("winesales.rpt");
	if (!fout.is_open())
	{
		cout << "error opening winesales.rpt file - contact systems";
		system("pause");
		exit(-2);
	}
	fout << fixed << setprecision(2);

	cout << "\n\nLoad arrays\n\n";
	loadArrays(fin, wine, salesAmt, noWines);
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nCompute yearly Sale\n\n";
	computeSum(salesAmt, yearlySales, noWines);
	cout << "\n\n=======================================================\n\n";
	
	cout << "\n\nFind best selling wine and highest sales amount:\n\n";
	findWine(salesAmt, highestRow, highestCol, noWines);
	cout << "\n\n" << wine[highestRow] << " had the highest sales amount = $"
		<< salesAmt[highestRow][highestCol] << endl;
	cout << "\n\n=======================================================\n\n";
	
	
	cout << "\n\nFind the most sold wine:\n\n";
	mostWineSold(yearlySales, mostSold, noWines);
	cout << "\n\n Most sold wine is " << wine[mostSold] << endl;
	cout << mostSold << endl;
	cout << "\n\n=======================================================\n\n";
	printReport(fout, wine, salesAmt, yearlySales, mostSold, noWines);
	cout << "\n\n=======================================================\n\n";

	cout << "program ended successfully" << endl;
	cout << "\n\n Printing wines.dat file\n\n";
	system("type wines.dat");
	cout << "\n\n Printing winesales.rpt file\n\n";
	system("type winesales.rpt");
	system("pause");
	
}


int loadArrays(ifstream& fin, string wineName[], double salesEarning[][4], int& numWine)
{
	int row, col;

	for (row = 0; row < SIZE; row++) //or row<SIZE if declared as a global const
	{
		getline(fin, wineName[row]);
		if (fin.eof())
			break;
		for (col = 0; col < 4; col++)
			fin >> salesEarning[row][col];
		fin.ignore(80, '\n');
	}
	return numWine = row;
}
void printReport(ofstream& fout, string wineName[], double salesEarning[][4],double yearlySales[], int& mostSold, int& noWine)
{

	int row, col;
	double total = 0;
	fout  << "Wine" << setw(30) << "QuaterlySales" << endl;
	fout  << setw(15) << "1st"  << setw(15) << "2nd" << setw(15) << "3rd" << setw(15) << "4th" << setw(25)<< "Yearly Sales" << endl;
	for (row = 0; row < noWine; row++)
	{

		fout << left << setw(6) << wineName[row] << '\t';
		for (col = 0; col < 4; col++)
			fout << left << setw(15) << salesEarning[row][col] << '\t';
		if (row == mostSold)
			fout << yearlySales[mostSold] << setw(10) << " **** Most Sold ***" << endl;
		else
		fout << yearlySales[row] << endl;
		
		total += yearlySales[row];
			
	}
	fout << "Total Sales Amount = " << total<<"$" << endl;
	

}

void computeSum(double salesEarning[][4], double yearlySales[], int noWine)
{
	int row, col;

	for (row = 0; row < noWine; row++) //or row<SIZE if declared as a global const
	{
		
		for (col = 0; col < 4; col++)
			yearlySales[row] += salesEarning[row][col];
		
	}
}


void findWine(const double salesEarning[][4],int& highestSale,int& highestWine, int length)
{
	
	for (int row = 0; row < length; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (salesEarning[row][col] > highestSale)
			{
				highestSale = col;
				highestWine = row;
			}
		}
	}

}

void mostWineSold(const double yearlySales[], int& mostSold, int& length)
{
	int highest = 0;
	for (int num = 1; num < length; num++)
	{
		if (yearlySales[num] > yearlySales[highest])
		{
			highest = num;
		}
	}
	mostSold = highest;
	
	
}
/*

Load arrays



=======================================================



Compute yearly Sale



=======================================================



Find best selling wine and highest sales amount:



Pink had the highest sales amount = $5000.00


=======================================================



Find the most sold wine:



 Most sold wine is White
2


=======================================================



=======================================================

program ended successfully


 Printing wines.dat file

Red
200000.00       50200.00        57000.00        16800.00
Rose
25000.00                1.00      4500.00         7800.00
White
300000.00            4400.00            23000.00              53000.00
Pink
200.00            500.00                    313000.00                   1681.00
Gamay
220.00           5000.00             41000.00          100.00
Chardon
41200.00        5120.00          570.00             168.00


 Printing winesales.rpt file

Wine                 QuaterlySales
            1st            2nd            3rd            4th             Yearly Sales
Red     200000.00       50200.00        57000.00        16800.00        324000.00
Rose    25000.00        1.00            4500.00         7800.00         37301.00
White   300000.00       4400.00         23000.00        53000.00        380400.00 **** Most Sold ***
Pink    200.00          500.00          313000.00       1681.00         315381.00
Gamay   220.00          5000.00         41000.00        100.00          46320.00
Chardon 41200.00        5120.00         570.00          168.00          47058.00
Total Sales Amount = 1150460.00$
Press any key to continue . . .

C:\Users\16476\Desktop\Sc\Semester 2\c++\Assigment3MarcoDeMelo\Debug\Assigment3MarcoDeMelo.exe (process 39360) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .
*/