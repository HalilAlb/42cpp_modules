#include "easyfind.hpp"

#include <iostream>
#include <vector>
#include <list>
#include <deque>

int main()
{
	std::cout << "=== Test 1: vector — bulundu ===" << std::endl;
	{
		std::vector<int> v;
		v.push_back(10);
		v.push_back(20);
		v.push_back(30);
		try
		{
			std::vector<int>::iterator it = easyfind(v, 20);
			std::cout << "Found 20 at index " << (it - v.begin()) << std::endl;
		}
		catch (std::exception& e) { std::cerr << e.what() << std::endl; }
	}


	std::cout << "\n=== Test 2: vector — bulunamadı (exception) ===" << std::endl;
	{
		std::vector<int> v;
		v.push_back(1);
		v.push_back(2);
		try
		{
			easyfind(v, 99);
		}
		catch (std::exception& e) { std::cerr << "Caught: " << e.what() << std::endl; }
	}


	std::cout << "\n=== Test 3: list — iterator döner ===" << std::endl;
	{
		std::list<int> l;
		l.push_back(5);
		l.push_back(15);
		l.push_back(25);
		try
		{
			std::list<int>::iterator it = easyfind(l, 15);
			std::cout << "Found: " << *it << std::endl;
		}
		catch (std::exception& e) { std::cerr << e.what() << std::endl; }
	}


	std::cout << "\n=== Test 4: deque + boş container ===" << std::endl;
	{
		std::deque<int> d;
		try { easyfind(d, 0); }
		catch (std::exception& e) { std::cerr << "Empty deque: " << e.what() << std::endl; }
	}


	std::cout << "\n=== Test 5: const container — const_iterator overload ===" << std::endl;
	{
		std::vector<int> v;
		v.push_back(7);
		v.push_back(8);
		v.push_back(9);
		const std::vector<int>& cref = v;
		try
		{
			std::vector<int>::const_iterator it = easyfind(cref, 8);
			std::cout << "Found in const ref: " << *it << std::endl;
		}
		catch (std::exception& e) { std::cerr << e.what() << std::endl; }
	}


	std::cout << "\n=== Test 6: çoklu eşleşme — first occurrence dönmeli ===" << std::endl;
	{
		std::vector<int> v;
		v.push_back(4);
		v.push_back(2);
		v.push_back(2);
		v.push_back(8);
		std::vector<int>::iterator it = easyfind(v, 2);
		std::cout << "First '2' at index " << (it - v.begin())
				  << " (beklenen: 1)" << std::endl;
	}

	return 0;
}
