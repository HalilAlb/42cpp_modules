#include "Span.hpp"

#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>

int main()
{
	std::cout << "=== Test 1: PDF örneği ===" << std::endl;
	{
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << " (beklenen: 2)" << std::endl;
		std::cout << sp.longestSpan() << " (beklenen: 14)" << std::endl;
	}


	std::cout << "\n=== Test 2: Dolu container'a ekleme → exception ===" << std::endl;
	{
		Span sp(2);
		sp.addNumber(1);
		sp.addNumber(2);
		try { sp.addNumber(3); }
		catch (std::exception& e) { std::cerr << "Caught: " << e.what() << std::endl; }
	}


	std::cout << "\n=== Test 3: Yetersiz eleman (< 2) — span hesaplanamaz ===" << std::endl;
	{
		Span sp(10);
		try { sp.shortestSpan(); }
		catch (std::exception& e) { std::cerr << "Empty: " << e.what() << std::endl; }

		sp.addNumber(42);
		try { sp.longestSpan(); }
		catch (std::exception& e) { std::cerr << "Single: " << e.what() << std::endl; }
	}


	std::cout << "\n=== Test 4: addRange — vector'den iterator aralığı ===" << std::endl;
	{
		Span sp(5);
		std::vector<int> v;
		v.push_back(10); v.push_back(20); v.push_back(15); v.push_back(8);
		sp.addRange(v.begin(), v.end());
		std::cout << "size: " << sp.size() << std::endl;
		std::cout << "shortest: " << sp.shortestSpan() << " (beklenen: 2 → 8,10 farkı)" << std::endl;
		std::cout << "longest:  " << sp.longestSpan()  << " (beklenen: 12)" << std::endl;
	}


	std::cout << "\n=== Test 5: addRange overflow ===" << std::endl;
	{
		Span sp(3);
		std::vector<int> v;
		v.push_back(1); v.push_back(2); v.push_back(3); v.push_back(4);  
		try { sp.addRange(v.begin(), v.end()); }
		catch (std::exception& e) { std::cerr << "Caught: " << e.what() << std::endl; }
		std::cout << "size after fail: " << sp.size() << " (beklenen: 0 — hiçbiri eklenmedi)" << std::endl;
	}


	std::cout << "\n=== Test 6: addRange — list (forward iterator) ===" << std::endl;
	{
		Span sp(4);
		std::list<int> l;
		l.push_back(100); l.push_back(200); l.push_back(150);
		sp.addRange(l.begin(), l.end());
		std::cout << "shortest: " << sp.shortestSpan() << " (beklenen: 50)" << std::endl;
		std::cout << "longest:  " << sp.longestSpan()  << " (beklenen: 100)" << std::endl;
	}


	std::cout << "\n=== Test 7: 10000 random number stres testi (PDF: at least 10k) ===" << std::endl;
	{
		std::srand(static_cast<unsigned int>(std::time(NULL)));
		const unsigned int N = 10000;
		Span sp(N);
		std::vector<int> bulk;
		bulk.reserve(N);
		for (unsigned int i = 0; i < N; ++i)
			bulk.push_back(std::rand());
		sp.addRange(bulk.begin(), bulk.end());
		std::cout << "filled " << sp.size() << " numbers" << std::endl;
		std::cout << "shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "longest:  " << sp.longestSpan()  << std::endl;
	}


	std::cout << "\n=== Test 8: Negatif sayılar + sıfır mesafe ===" << std::endl;
	{
		Span sp(4);
		sp.addNumber(-5);
		sp.addNumber(0);
		sp.addNumber(5);
		sp.addNumber(5);   
		std::cout << "shortest: " << sp.shortestSpan() << " (beklenen: 0 — iki 5)" << std::endl;
		std::cout << "longest:  " << sp.longestSpan()  << " (beklenen: 10)" << std::endl;
	}


	std::cout << "\n=== Test 9: OCF — copy ctor & op= ===" << std::endl;
	{
		Span a(5);
		a.addNumber(1); a.addNumber(7);
		Span b(a);                    
		Span c;
		c = a;                        
		std::cout << "b shortest: " << b.shortestSpan() << " (=6)" << std::endl;
		std::cout << "c longest:  " << c.longestSpan()  << " (=6)" << std::endl;
	}

	return 0;
}
