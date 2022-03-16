#include <locale>
#include <iostream>
#include <fstream>

#include <math.h>
#include <ctime>
#define N 3
#define Eps 0.000001
#define inputFile "input.txt"
#define OutputFile "Output.txt"
using namespace std;






void ReadDataFile(double** MATR,int size_of_matrix)
{
	ifstream fin;
	fin.open(inputFile);
	for (int i = 0; i < size_of_matrix; i++)
	{
		for (int j = 0; j < size_of_matrix; j++)
		{
			fin >> MATR[i][j];
		}
	}
	for (int i = 0; i < size_of_matrix; i++) {
		fin >> MATR[i][size_of_matrix];
	}
	fin.close();
}
void ConsoleALL(double** MATR, int size_of_matrix,std::ofstream &fout)
{

	for (int i = 0; i < size_of_matrix; i++)
	{
		for (int j = 0; j < size_of_matrix; j++)
		{
			cout << MATR[i][j] << "\t";
			fout<< MATR[i][j] << "\t";
		}
		cout << "| " << MATR[i][size_of_matrix] << "\n";
		fout<< "| " << MATR[i][size_of_matrix] << "\n";
	}


}
void ConsoleResult(double* result, int size_of_matrix, std::ofstream& fout)
{
	fout << "\nRESULTS:\n";
	cout << "\nRESULTS:\n";
	for (int i = 0; i < size_of_matrix; i++)
	{
		printf("X%d = %f\n",i+1, result[i]);
		fout << "X"<<i+1<<" = "<< result[i] << "\n";
	}
}
void ConsoleNorm(double* result, int size_of_matrix, std::ofstream& fout)
{
	fout << "\nNORM:\n";
	cout << "\nNORM:\n";
	for (int i = 0; i < size_of_matrix; i++)
	{
		printf("N%d = %f\n", i + 1, result[i]);
		fout << "N" << i + 1 << " = " << result[i] << "\n";
	}
}
void MoveRow(double **MATR,int size_of_matrix, int firstRow, int secondRow)
{
	for (int i = 0; i < size_of_matrix+1; i++)
	{
		int buff;
		buff = MATR[firstRow][i];
		MATR[firstRow][i] = MATR[secondRow][i];
		MATR[secondRow][i] = buff;
	}
}
void MoveIntRow(int** MATR, int size_of_matrix, int firstRow, int secondRow)
{
	for (int i = 0; i < size_of_matrix; i++)
	{
		int buff;
		buff = MATR[firstRow][i];
		MATR[firstRow][i] = MATR[secondRow][i];
		MATR[secondRow][i] = buff;
	}
}
bool CheckСonvergence(double** MATR, int size_of_matrix)
{
	int **CheckMATR = new(int* [size_of_matrix]);
	double *Max_elements_in_Raw = new(double[size_of_matrix]);
	for (int i = 0; i < size_of_matrix; i++)
	{
		CheckMATR[i] = new(int[size_of_matrix]);
	}
	for (int i = 0; i < size_of_matrix; i++)
	{
		for (int j = 0; j < size_of_matrix; j++)
		{
			CheckMATR[i][j] = 0;
		}
	}


	for (int i = 0; i < size_of_matrix; i++)
	{
		int t = 0;
		for (int j = 0; j < size_of_matrix; j++)
		{
			if (abs(MATR[i][t]) < abs(MATR[i][j]))
			{
				t = j;
			}
		}
		CheckMATR[i][t] = 1;
		Max_elements_in_Raw[i] = MATR[i][t];
	}


	for (int i = 0; i < size_of_matrix; i++)
	{
		int ControlSum = 0;
		for (int j = 0; j < size_of_matrix; j++)
		{
			ControlSum += CheckMATR[j][i];
		}
		if (ControlSum > 1)
		{
			return false;
		}
	}

	for (int i = 0; i < size_of_matrix; i++)
	{
		double Sum_Of_Raw = 0;
		for (int j = 0; j < size_of_matrix; j++)
		{
			Sum_Of_Raw += abs(MATR[i][j]);
		}
		if (Sum_Of_Raw > (2 * Max_elements_in_Raw[i]))
		{
			return false;
		}
	}

	return true;
}
void DiagonalDominance(double** MATR, int size_of_matrix)
{
	
	int** CheckMATR = new(int* [size_of_matrix]);
	for (int i = 0; i < size_of_matrix; i++)
	{
		CheckMATR[i] = new(int[size_of_matrix]);
	}
	for (int i = 0; i < size_of_matrix; i++)
	{
		for (int j = 0; j < size_of_matrix; j++)
		{
			CheckMATR[i][j] = 0;
		}
	}

	


	for (int i = 0; i < size_of_matrix; i++)
	{
		int t = 0;
		for (int j = 0; j < size_of_matrix; j++)
		{
			if (abs(MATR[i][t]) < abs(MATR[i][j]))
			{
				t = j;
			}
		}
		CheckMATR[i][t] = 1;
	}


	//В итоге получается матрица где наибольшие по модулю элементы отмечены 1

	for (int i = 0; i < size_of_matrix; i++)
	{
		int t = i;
		for (int j = 0; j < size_of_matrix; j++)
		{
			if (CheckMATR[j][i] == 1)
			{
				MoveRow(MATR, size_of_matrix, i, j);
				MoveIntRow(CheckMATR, size_of_matrix, i, j);
				break;
			}

		}
	}


}
void YakobiAlgoritm(double** MATR, int size_of_matrix, double* result, std::ofstream& fout)
{
	
	

	for (int i = 0; i < size_of_matrix; i++)
	{
		result[i] = 0;
	}
	

	int counter = 1;
	bool flag = true;
	while (flag && counter<500)
	{
		double* previous = new(double[size_of_matrix]);
		for (int i = 0; i < size_of_matrix; i++)
		{
			previous[i] = result[i];
		}


		for (int i = 0; i < size_of_matrix; i++)
		{
			double Sum = 0;
			for (int j = 0; j < size_of_matrix; j++)
			{
				if (i != j)
				{
					Sum += MATR[i][j] * previous[j];
				}
			}
			result[i] = (MATR[i][size_of_matrix] - Sum) / MATR[i][i];
		}




		double MAX = abs(result[0] - previous[0]);
		for (int i = 1; i < size_of_matrix; i++)
		{
			if (MAX < abs(result[i] - previous[i]))
			{
				MAX = abs(result[i] - previous[i]);
			}
		}


		printf("\n %d| ", counter);
		fout << "\n"<< counter<< "|  ";
		counter++;
		for (int i = 0; i < N; i++)
		{
			printf("%d) %f\t", i + 1, result[i]);
			fout << i + 1 << ") " << result[i] << "\t";
		}
		printf("MAXdelta = %f\n", MAX);
		fout << "MAXdelta = " << MAX << "\n";




		if (MAX < Eps)
		{
			flag = false;
		}

	}

	
}
void ZeydelAlgoritm(double** MATR, int size_of_matrix, double* result, std::ofstream& fout)
{
	
	for (int i = 0; i < size_of_matrix; i++)
	{
		result[i] = 0;
	}
	
	int counter = 1;
	bool flag = true;
	while (flag && counter < 100)
	{
		double* previous = new(double[size_of_matrix]);
		for (int i = 0; i < size_of_matrix; i++)
		{
			previous[i] = result[i];
		}


		for (int i = 0; i < size_of_matrix; i++)
		{
			double Sum = 0;
			for (int j = 0; j < size_of_matrix; j++)
			{
				if (i > j)
				{
					Sum += MATR[i][j] * result[j];
				}
				if (i < j)
				{
					Sum += MATR[i][j] * previous[j];
				}
			}
			result[i] = (MATR[i][size_of_matrix] - Sum) / MATR[i][i];
		}




		double MAX = abs(result[0] - previous[0]);
		for (int i = 1; i < size_of_matrix; i++)
		{
			if (MAX < abs(result[i] - previous[i]))
			{
				MAX = abs(result[i] - previous[i]);
			}
		}


		printf("\n %d| ", counter);
		fout << "\n" << counter << "|  ";
		counter++;
		for (int i = 0; i < N; i++)
		{
			printf("%d) %f\t", i + 1, result[i]);
			fout << i + 1 << ") " << result[i] << "\t";
		}
		printf("MAXdelta = %f\n", MAX);
		fout << "MAXdelta = " << MAX << "\n";




		if (MAX < Eps)
		{
			flag = false;
		}

	}
}
void findmNorm(double** MATR, int size_of_matrix, double* result, std::ofstream& fout) {
	
	double* norm = new(double[size_of_matrix]);
	for (int i = 0; i < size_of_matrix; i++)
	{
		norm[i] = 0;
	}

	for (int i = 0; i < size_of_matrix; i++)
	{
		for (int j = 0; j < size_of_matrix; j++)
		{
			norm[i] += MATR[i][j] * result[j];
		}
		norm[i] = abs(MATR[i][size_of_matrix] - norm[i]);
	}

	ConsoleNorm(norm, size_of_matrix, fout);

}

void MoveEl(double* Raw, int first, int second)
{
	double buff = Raw[first];
	Raw[first] = Raw[second];
	Raw[second] = buff;
}

void AvtoInput(double** MATR, int size_of_matrix)
{

	srand(time(NULL));
	int* PositionOfMaxEl = (new int[size_of_matrix]);
	int counter = 0;
	while (counter != size_of_matrix)
	{
	n: int a = rand() % size_of_matrix;

		for (int i = 0; i < counter; i++)
		{
			if (PositionOfMaxEl[i] == a)
			{
				goto n;
			}
		}
		PositionOfMaxEl[counter] = a;
		counter++;
	}
	
	for (int i = 0; i < size_of_matrix; i++)
	{
		double Sum = 0;
		for (int j = 0; j < size_of_matrix-1; j++)
		{

			MATR[i][j] = -100 + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 100 + 100));
			Sum += abs(MATR[i][j]);
		}
		MATR[i][size_of_matrix - 1] = Sum + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (2 * Sum) + Sum));
		MoveEl(MATR[i], PositionOfMaxEl[i], size_of_matrix - 1);
	}


	for (int i = 0; i < size_of_matrix; i++)
	{
		MATR[i][size_of_matrix] = -100 + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 100 + 100));
	}
}
int main()
{

	ofstream fout;
	fout.open(OutputFile);
	double** MATR;
	double* freeMembers = new (double[100]);
	double* result = new(double[100]);
	MATR = new (double* [100]);
	for (int i = 0; i < 100; i++)
	{
		MATR[i] = new (double[100]);
	}


	char answer;
	int size_of_matrix;
	printf("File or Random (F/R)");
	cin >> answer;

	if (answer == 'f')
	{

		size_of_matrix = N;
		ReadDataFile(MATR, size_of_matrix);
	}
	else
	{
		printf("\n\nSize of MATRIX = ");
		cin >> size_of_matrix;

		AvtoInput(MATR, size_of_matrix);
		

	}


	
	ConsoleALL(MATR, size_of_matrix,fout);







	if (CheckСonvergence(MATR, size_of_matrix))
	{
		DiagonalDominance(MATR, size_of_matrix);
		printf("Diagonal dominance is possible\n\n");
		fout << "Diagonal dominance is possible\n\n";
		ConsoleALL(MATR, size_of_matrix,fout);
	}
	else
	{
		printf("Diagonal dominance is impossible\n\n");
		fout << "Diagonal dominance is impossible\n\n";
	}


	fout << "\nYakobi Algoritm\n";
	cout << "\nYakobi Algoritm\n";
	YakobiAlgoritm(MATR, size_of_matrix, result,fout);
	findmNorm(MATR, size_of_matrix, result, fout);
	ConsoleResult(result, size_of_matrix,fout);



	fout << "\nZeydel Algoritm\n";
	cout << "\nZeydel Algoritm\n";
	ZeydelAlgoritm(MATR, size_of_matrix, result, fout);
	findmNorm(MATR, size_of_matrix, result, fout);
	ConsoleResult(result, size_of_matrix, fout);

	fout.close();

}