#include <iostream>

using namespace std;

int LinarySearch(int* arr, int n, int key)
{
	for (int i = 0; i < n; i++)
	{
		if (key == arr[i])
			return i;
	}
	return -1;
}

int LinSearchWBarrier(int* arr, int n, int key)
{
	int i = 0, last = 0;

	if (key == arr[n - 1])
		return n - 1;
	else
	{
		last = arr[n - 1];
		arr[n - 1] = key;
	}

	while (arr[i] != key)
		i++;

	arr[n - 1] = last;

	if (i == n - 1)
		return -1;
	else
		return i;

	return 0;
}

int BinarySearch(int* arr, int n, int key)
{
	int start = 0, half = n / 2;

	while (start < n && start != n - 1)
	{
		if (arr[start] == key)
			return start;
		if (arr[n] == key)
			return n;

		half = (n + start) / 2;
		if (arr[half] <= key)
		{
			if (arr[half] == key)
				return half;
			start = half;
		}
		else
		{
			n = half;
		}
	}
	return -1;
}

int Fibonacci(int i)
{
	if (i < 1) return 0;

	if (i == 1) return 1;

	return Fibonacci(i - 1) + Fibonacci(i - 2);

}

int FibonacciSearch(int* arr, int start, int end, int* F, int i, int key)
{
	int half;

	if (i > 2)
		half = start + F[i - 2];
	else
		half = start + F[i];

	if (key == arr[half])
		return half;

	else if (key == arr[start])
		return start;

	else if (key == arr[end])
		return end;

	else if (half == start || half == end)
		return -1;

	else if (key > arr[half])
		FibonacciSearch(arr, half, end, F, i - 1, key);

	else
		FibonacciSearch(arr, start, half, F, i - 2, key);
}

void menu()
{
	int n, choise = 0, res, index;
	int key;

	cout << "Input array length: ";
	cin >> n;

	if (n < 0)
	{
		n = 10;
		cout << "Error data input. default length of array is " << n << endl;
	}

	int* arr = new int[n];
	int* F = new int[n];

	for (int i = 0; i < n; i++)
	{
		cout << "Input " << i + 1 << " element of array: " << i + 1 << endl;
		//cin >> arr[i];
		arr[i] = i + 1;
	}

	cout << "Input key: ";
	cin >> key;

	cout << "chiose search method:\n1. Linary search.\n2. Linary search with barrier.\n3. Binary search. \n4. Fibonachi search.\n5. Exit." << endl;
	cin >> choise;

	while (choise != 5)
	{
		switch (choise)
		{
		case 1:
			res = LinarySearch(arr, n, key);
			if (res != -1)
				cout << "Key element in array is " << res + 1<< endl;
			else
				cout << "Aray don't consist key" << endl;
			break;
		case 2:
			res = LinSearchWBarrier(arr, n, key);

			if (res != -1)
				cout << "Key element in array is " << res + 1 << endl;
			else
				cout << "Aray don't consist key" << endl;
			break;
		case 3:
			res = BinarySearch(arr, n - 1, key);
			if (res != -1)
				cout << "Key element in array is " << res + 1 << endl;
			else
				cout << "Aray don't consist key" << endl;
			break;
		case 4:
			F[0] = 1;
			F[1] = 1;
			index = 1;

			while (F[index] < n)
			{
				index++;
				F[index] = Fibonacci(index);
			}

			res = FibonacciSearch(arr, 0, n - 1, F, index, key);

			if (res != -1)
				cout << "Key element in array is " << res + 1 << endl;
			else
				cout << "Aray don't consist key" << endl;
			break;
		default:
			break;
		}

		cout << "chiose search method:\n1. Linary search.\n2. Linary search with barrier.\n3. Binary search. \n4. Fibonachi search.\n5. Exit." << endl;
		cin >> choise;
	}
}

int main(int argc, char* argv[])
{
	menu();
}
