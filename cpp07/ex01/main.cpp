#include "iter.hpp"

#include <iostream>
#include <string>




template <typename T>
void doubleIt(T& value)
{
	value = value * 2;
}


template <typename T>
void printIt(const T& value)
{
	std::cout << value << " ";
}


void printInt(const int& v)
{
	std::cout << "[int=" << v << "] ";
}


int main()
{
	std::cout << "=== Test 1: int array — doubleIt + printIt ===" << std::endl;
	{
		int arr[] = { 1, 2, 3, 4, 5 };
		size_t len = sizeof(arr) / sizeof(arr[0]);

		std::cout << "Before: ";
		iter(arr, len, printIt<int>);
		std::cout << std::endl;

		iter(arr, len, doubleIt<int>);

		std::cout << "After:  ";
		iter(arr, len, printIt<int>);
		std::cout << std::endl;
	}


	std::cout << "\n=== Test 2: string array — sadece print ===" << std::endl;
	{
		std::string arr[] = { "alpha", "beta", "gamma" };
		size_t len = sizeof(arr) / sizeof(arr[0]);
		iter(arr, len, printIt<std::string>);
		std::cout << std::endl;
	}


	std::cout << "\n=== Test 3: const array — const callback ile ===" << std::endl;
	{
		const int carr[] = { 10, 20, 30 };
		
		
		
		iter(carr, 3, printIt<int>);
		std::cout << std::endl;
	}


	std::cout << "\n=== Test 4: function pointer (template değil) ===" << std::endl;
	{
		int arr[] = { 7, 8, 9 };
		iter(arr, 3, printInt);
		std::cout << std::endl;
	}


	std::cout << "\n=== Test 5: length = 0 (sınır durumu) ===" << std::endl;
	{
		int arr[1] = { 0 };
		iter(arr, 0, printIt<int>);  
		std::cout << "(yazdırılan eleman yok — beklenen)" << std::endl;
	}

	return 0;
}
