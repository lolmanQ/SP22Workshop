#include <iostream>
#include <chrono>
#include <cmath>

const int SIZE = 64 * 1024 * 1024;
typedef void CalcTest(int*, int);
typedef void CalcTestVar(int*, int, int*);

std::chrono::milliseconds RunTests(int* arr, int size, CalcTest* calcTest);
std::chrono::milliseconds RunTests(int* arr, int size, CalcTestVar* calcTest);
void CT1(int* arr, int size);
void CT2(int* arr, int size);
void CT3(int* arr, int size, int* storage);
void CT4(int* arr, int size, int* storage);

long long GetAverage(int* arr, int size, CalcTest test, int amountOfRuns);
long long GetAverage(int* arr, int size, CalcTestVar test, int amountOfRuns);
void PrintTime(const char* testName, long long time);

int main()
{
	int size = 64 * 1024 * 1024;
	int amountOfRuns = 10;
	
	bool runAgain = false;
	do
	{
		runAgain = false;
		std::cout << "Enter parameters" << std::endl;

		std::cout << "Array size: ";
		std::cin >> size;
		
		while (!(size < 1 && size > 128) || std::cin.fail())
		{
			std::cout << "Not within bounds try again (1-100)" << std::endl;
			std::cout << "Array size: ";
			std::cin >> size;
		}

		size *= 8 * 1024 * 1024;

		std::cout << "Array true size: " << size << std::endl;

		/*while (!std::cin >> size)
		{
			std::cout << "Not number" << std::endl;
		}*/


		std::cout << "Sample size: ";

		std::cin >> amountOfRuns;
		
		while (!(amountOfRuns < 1 && amountOfRuns > 100) || std::cin.fail())
		{
			std::cout << "Not within bounds try again (1-100)" << std::endl;
			std::cout << "Sample size: ";
			std::cin >> amountOfRuns;
		}
		
		/*while (!std::cin >> amountOfRuns)
		{
			std::cout << "Not number" << std::endl;
		}*/

		int* arr1 = new int[size];
		int* arr2 = new int[size];

		for (int i = 0; i < size; i++)
		{
			arr1[i] = 1;
			arr2[i] = 1;
		}

		std::cout << "Starting tests..." << std::endl << std::endl;

		PrintTime("CT1", GetAverage(arr1, size, CT1, amountOfRuns));
		PrintTime("CT2", GetAverage(arr2, size, CT2, amountOfRuns));

		for (int i = 0; i < size; i++)
		{
			arr1[i] *= 3;
		}

		for (int i = 0; i < size; i += 6)
		{
			arr2[i] *= 3;
		}

		PrintTime("CT3", GetAverage(arr2, size, CT3, amountOfRuns));
		PrintTime("CT4", GetAverage(arr2, size, CT4, amountOfRuns));

		std::cout << std::endl << "Finished" << std::endl;
		
		std::cout << "Do you want to run again? (y/n)" << std::endl;

		char runAgainChar = 'n';

		std::cin >> runAgainChar;

		if (runAgainChar == 'y')
		{
			runAgain = true;
		}
		else
		{
			runAgain = false;
		}

	} while (runAgain);
	

	/*auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start);


	start = std::chrono::steady_clock::now();

	
	for (int i = 0; i < size; i++)
	{
		sumResult += arr2[i];
	}

	auto duration3 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start);

	start = std::chrono::steady_clock::now();

	for (int i = 0; i < size; i += 4)
	{
		a += arr2[i];
		b += arr2[i + 1];
		c += arr2[i + 2];
		d += arr2[i + 3];
	}

	auto duration4 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start);*/

	/*std::cout << "Time: " << duration1.count() << std::endl;
	std::cout << "Time: " << duration2.count() << std::endl;
	std::cout << "Time: " << duration3.count() << std::endl;
	std::cout << "Time: " << duration4.count() << std::endl;


	std::cout << std::endl << "Calculation values: " << std::endl;
	std::cout << "Add loop: " << sumResult << std::endl;
	std::cout << "Add multi: " << a << " " << b << " " << c << " " << d << std::endl;*/
}

long long GetAverage(int* arr, int size, CalcTest test, int amountOfRuns)
{
	long long sumTotal = 0;
	for (int i = 0; i < amountOfRuns; i++)
	{
		sumTotal += RunTests(arr, size, test).count();
	}
	long long sumAverage = sumTotal / amountOfRuns;
	return sumAverage;
}

long long GetAverage(int* arr, int size, CalcTestVar test, int amountOfRuns)
{
	long long sumTotal = 0;
	for (int i = 0; i < amountOfRuns; i++)
	{
		sumTotal += RunTests(arr, size, test).count();
	}
	long long sumAverage = sumTotal / amountOfRuns;
	return sumAverage;
}

void PrintTime(const char *testName, long long time)
{
	std::cout << testName << " " << time << "ms" << std::endl;
}

int* GiveCopy(int* arr, int size)
{
	int* arrCopy = new int[size];

	std::copy(arr, arr + size, arrCopy);

	return arrCopy;
}

std::chrono::milliseconds RunTests(int* arr, int size, CalcTest* calcTest)
{
	int* arrToUse = GiveCopy(arr, size);

	auto start = std::chrono::steady_clock::now();

	calcTest(arrToUse, size);

	auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);

	delete arrToUse;
	return duration1;
}

std::chrono::milliseconds RunTests(int* arr, int size, CalcTestVar* calcTest)
{
	int* arrToUse = GiveCopy(arr, size);

	int storage[100];

	auto start = std::chrono::steady_clock::now();

	calcTest(arrToUse, size, storage);

	auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);

	delete arrToUse;
	return duration1;
}

void CT1(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] *= 3;
	}
}

void CT2(int* arr, int size)
{
	for (int i = 0; i < size; i += 6)
	{
		arr[i] *= 3;
	}
}

void CT3(int* arr, int size, int* storage)
{
	int sum = 0;

	for (int i = 0; i < size; i++)
	{
		sum += arr[i];
	}

	storage[0] = sum;
}

void CT4(int* arr, int size, int* storage)
{
	int a = 0, b = 0, c = 0, d = 0;

	for (int i = 0; i < size; i += 4)
	{
		a += arr[i];
		b += arr[i + 1];
		c += arr[i + 2];
		d += arr[i + 3];
	}

	storage[0] = a;
	storage[1] = b;
	storage[2] = c;
	storage[3] = d;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
