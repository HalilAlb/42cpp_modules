#include "MutantStack.hpp"

#include <iostream>
#include <list>
#include <stack>

int main()
{
	std::cout << "=== Test 1: PDF örnek main'i — MutantStack<int> ===" << std::endl;
	{
		MutantStack<int> mstack;

		mstack.push(5);
		mstack.push(17);

		std::cout << "top: " << mstack.top() << " (beklenen: 17)" << std::endl;

		mstack.pop();

		std::cout << "size after pop: " << mstack.size() << " (beklenen: 1)" << std::endl;

		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		
		mstack.push(0);

		MutantStack<int>::iterator it  = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();

		++it;
		--it;

		std::cout << "Iterating (bottom→top):" << std::endl;
		while (it != ite)
		{
			std::cout << "  " << *it << std::endl;
			++it;
		}

		
		std::stack<int> s(mstack);
		std::cout << "std::stack copy size: " << s.size() << " (beklenen: 5)" << std::endl;
	}


	std::cout << "\n=== Test 2: PDF kontrolü — std::list ile aynı sırayı vermeli ===" << std::endl;
	{
		
		std::list<int> lst;
		lst.push_back(5);
		lst.push_back(17);
		lst.pop_back();          
		lst.push_back(3);
		lst.push_back(5);
		lst.push_back(737);
		lst.push_back(0);

		std::list<int>::iterator it  = lst.begin();
		std::list<int>::iterator ite = lst.end();
		++it;
		--it;

		std::cout << "std::list iterating:" << std::endl;
		while (it != ite)
		{
			std::cout << "  " << *it << std::endl;
			++it;
		}
		
	}


	std::cout << "\n=== Test 3: const_iterator ===" << std::endl;
	{
		MutantStack<int> m;
		m.push(10); m.push(20); m.push(30);
		const MutantStack<int>& cref = m;

		std::cout << "const iterate:";
		for (MutantStack<int>::const_iterator it = cref.begin(); it != cref.end(); ++it)
			std::cout << " " << *it;
		std::cout << std::endl;
	}


	std::cout << "\n=== Test 4: reverse_iterator (üstten dibe) ===" << std::endl;
	{
		MutantStack<int> m;
		m.push(1); m.push(2); m.push(3); m.push(4);

		std::cout << "rbegin → rend:";
		for (MutantStack<int>::reverse_iterator it = m.rbegin(); it != m.rend(); ++it)
			std::cout << " " << *it;
		std::cout << std::endl;
	}


	std::cout << "\n=== Test 5: std::string ile farklı T ===" << std::endl;
	{
		MutantStack<std::string> sm;
		sm.push("alpha");
		sm.push("beta");
		sm.push("gamma");
		std::cout << "top: " << sm.top() << std::endl;
		for (MutantStack<std::string>::iterator it = sm.begin(); it != sm.end(); ++it)
			std::cout << "  " << *it << std::endl;
	}


	std::cout << "\n=== Test 6: OCF — copy ctor & op= ===" << std::endl;
	{
		MutantStack<int> a;
		a.push(1); a.push(2);
		MutantStack<int> b(a);                  
		MutantStack<int> c;
		c = a;                                  

		std::cout << "b.size=" << b.size() << ", c.size=" << c.size() << std::endl;
		std::cout << "b.top=" << b.top() << ", c.top=" << c.top() << std::endl;

		b.pop();
		std::cout << "After b.pop(): a.size=" << a.size()
				  << " (deep copy → a etkilenmemeli, =2)" << std::endl;
	}

	return 0;
}
