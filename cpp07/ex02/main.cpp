#include "Array.hpp"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int main()
{
	std::cout << "=== Test 1: Boş Array (default ctor) ===" << std::endl;
	{
		Array<int> empty;
		std::cout << "size: " << empty.size() << " (beklenen: 0)" << std::endl;
		try
		{
			empty[0];  
		}
		catch (std::exception& e)
		{
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}


	std::cout << "\n=== Test 2: Array<int>(5) — default-init kontrolü ===" << std::endl;
	{
		Array<int> arr(5);
		std::cout << "size: " << arr.size() << std::endl;
		
		for (unsigned int i = 0; i < arr.size(); ++i)
			std::cout << "arr[" << i << "] = " << arr[i] << " (beklenen: 0)" << std::endl;
	}


	std::cout << "\n=== Test 3: Yazma + okuma ===" << std::endl;
	{
		Array<int> arr(3);
		arr[0] = 10;
		arr[1] = 20;
		arr[2] = 30;
		for (unsigned int i = 0; i < arr.size(); ++i)
			std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
	}


	std::cout << "\n=== Test 4: Out of bounds — exception fırlat ===" << std::endl;
	{
		Array<int> arr(3);
		try
		{
			arr[3] = 99;  
		}
		catch (std::exception& e)
		{
			std::cout << "Exception (3): " << e.what() << std::endl;
		}
		try
		{
			arr[1000000];  
		}
		catch (std::exception& e)
		{
			std::cout << "Exception (1e6): " << e.what() << std::endl;
		}
	}


	std::cout << "\n=== Test 5: Deep copy — copy ctor ===" << std::endl;
	{
		Array<int> orig(3);
		orig[0] = 1; orig[1] = 2; orig[2] = 3;

		Array<int> copy(orig);
		copy[0] = 99;  

		std::cout << "orig[0] = " << orig[0] << " (beklenen: 1)" << std::endl;
		std::cout << "copy[0] = " << copy[0] << " (beklenen: 99)" << std::endl;
	}


	std::cout << "\n=== Test 6: Deep copy — op= ===" << std::endl;
	{
		Array<int> a(3);
		a[0] = 10; a[1] = 20; a[2] = 30;

		Array<int> b(5);  
		b = a;
		b[0] = 999;

		std::cout << "a.size() = " << a.size() << ", b.size() = " << b.size() << std::endl;
		std::cout << "a[0] = " << a[0] << " (beklenen: 10)" << std::endl;
		std::cout << "b[0] = " << b[0] << " (beklenen: 999)" << std::endl;
	}


	std::cout << "\n=== Test 7: string ile (T = std::string) ===" << std::endl;
	{
		Array<std::string> s(3);
		s[0] = "alpha";
		s[1] = "beta";
		s[2] = "gamma";
		for (unsigned int i = 0; i < s.size(); ++i)
			std::cout << "s[" << i << "] = " << s[i] << std::endl;
	}


	std::cout << "\n=== Test 8: const Array — const operator[] ===" << std::endl;
	{
		Array<int> mutable_arr(2);
		mutable_arr[0] = 7;
		mutable_arr[1] = 8;
		const Array<int>& cref = mutable_arr;
		std::cout << "cref[0] = " << cref[0] << std::endl;
		std::cout << "cref[1] = " << cref[1] << std::endl;
		
	}


	std::cout << "\n=== Test 9: Rastgele stres testi ===" << std::endl;
	{
		std::srand(static_cast<unsigned int>(std::time(NULL)));
		const unsigned int N = 100;
		Array<int> arr(N);
		for (unsigned int i = 0; i < N; ++i)
			arr[i] = static_cast<int>(i * 2);

		
		for (int t = 0; t < 5; ++t)
		{
			unsigned int idx = static_cast<unsigned int>(std::rand()) % (N + 10);
			try { std::cout << "arr[" << idx << "] = " << arr[idx] << std::endl; }
			catch (std::exception& e) { std::cout << "arr[" << idx << "] → " << e.what() << std::endl; }
		}
	}

	return 0;
}
