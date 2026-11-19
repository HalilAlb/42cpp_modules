#include "PmergeMe.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>   
#include <utility>     
#include <cstdlib>     
#include <climits>
#include <ctime>
#include <cstddef>

PmergeMe::PmergeMe() : _vec(), _deq() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}





bool PmergeMe::parseArgs(int argc, char** argv)
{
	if (argc < 2)
		return false;

	for (int i = 1; i < argc; ++i)
	{
		std::string arg(argv[i]);
		if (arg.empty()) return false;

		
		for (std::size_t j = 0; j < arg.size(); ++j)
		{
			if (arg[j] < '0' || arg[j] > '9')
				return false;
		}

		char* end = NULL;
		long v = std::strtol(arg.c_str(), &end, 10);
		if (*end != '\0' || v < 0 || v > INT_MAX)
			return false;

	}
	return true;
}



void PmergeMe::fillVector(int argc, char** argv)
{
	_vec.clear();
	_vec.reserve(argc - 1);
	for (int i = 1; i < argc; ++i)
		_vec.push_back(std::atoi(argv[i]));
}

void PmergeMe::fillDeque(int argc, char** argv)
{
	_deq.clear();
	for (int i = 1; i < argc; ++i)
		_deq.push_back(std::atoi(argv[i]));
}













std::vector<std::size_t> PmergeMe::jacobsthalOrder(std::size_t n)
{
	std::vector<std::size_t> order;
	if (n == 0) return order;

	std::vector<std::size_t> J;
	J.push_back(0);
	J.push_back(1);
	while (J.back() < n + 2)
		J.push_back(J[J.size() - 1] + 2 * J[J.size() - 2]);

	std::vector<bool> inserted(n, false);

	for (std::size_t i = 1; i + 2 < J.size(); ++i)
	{
		std::size_t max_b = J[i + 2];
		std::size_t min_b = J[i + 1] + 1;

		
		
		std::size_t b = max_b;
		while (true)
		{
			if (b >= 2)
			{
				std::size_t pIdx = b - 2;
				if (pIdx < n && !inserted[pIdx])
				{
					order.push_back(pIdx);
					inserted[pIdx] = true;
				}
			}
			if (b == min_b) break;
			--b;
		}
		if (max_b >= n + 1) break;  
	}

	
	for (std::size_t i = 0; i < n; ++i)
		if (!inserted[i]) order.push_back(i);

	return order;
}





void PmergeMe::fjVector(std::vector<int>& v)
{
	if (v.size() < 2) return;

	
	bool hasStraggler = (v.size() % 2 == 1);
	int  straggler = 0;
	if (hasStraggler)
	{
		straggler = v.back();
		v.pop_back();
	}

	
	std::vector< std::pair<int, int> > pairs;
	pairs.reserve(v.size() / 2);
	for (std::size_t i = 0; i + 1 < v.size(); i += 2)
	{
		int a = v[i];
		int b = v[i + 1];
		if (a > b) std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}

	
	std::vector<int> larges;
	larges.reserve(pairs.size());
	for (std::size_t i = 0; i < pairs.size(); ++i)
		larges.push_back(pairs[i].second);

	fjVector(larges);  

	
	
	std::vector< std::pair<int, int> > sorted_pairs;
	sorted_pairs.reserve(pairs.size());
	std::vector<bool> used(pairs.size(), false);
	for (std::size_t i = 0; i < larges.size(); ++i)
	{
		for (std::size_t j = 0; j < pairs.size(); ++j)
		{
			if (!used[j] && pairs[j].second == larges[i])
			{
				sorted_pairs.push_back(pairs[j]);
				used[j] = true;
				break;
			}
		}
	}

	
	std::vector<int> main_chain;
	main_chain.reserve(v.size() + (hasStraggler ? 1 : 0));
	main_chain.push_back(sorted_pairs[0].first);
	for (std::size_t i = 0; i < sorted_pairs.size(); ++i)
		main_chain.push_back(sorted_pairs[i].second);

	
	std::vector<int> pending;
	for (std::size_t i = 1; i < sorted_pairs.size(); ++i)
		pending.push_back(sorted_pairs[i].first);

	
	std::vector<std::size_t> order = jacobsthalOrder(pending.size());
	for (std::size_t k = 0; k < order.size(); ++k)
	{
		int value = pending[order[k]];
		std::vector<int>::iterator pos =
			std::lower_bound(main_chain.begin(), main_chain.end(), value);
		main_chain.insert(pos, value);
	}

	
	if (hasStraggler)
	{
		std::vector<int>::iterator pos =
			std::lower_bound(main_chain.begin(), main_chain.end(), straggler);
		main_chain.insert(pos, straggler);
	}

	v.swap(main_chain);
}








void PmergeMe::fjDeque(std::deque<int>& d)
{
	if (d.size() < 2) return;

	bool hasStraggler = (d.size() % 2 == 1);
	int  straggler = 0;
	if (hasStraggler)
	{
		straggler = d.back();
		d.pop_back();
	}

	std::deque< std::pair<int, int> > pairs;
	for (std::size_t i = 0; i + 1 < d.size(); i += 2)
	{
		int a = d[i];
		int b = d[i + 1];
		if (a > b) std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}

	std::deque<int> larges;
	for (std::size_t i = 0; i < pairs.size(); ++i)
		larges.push_back(pairs[i].second);

	fjDeque(larges);

	std::deque< std::pair<int, int> > sorted_pairs;
	std::deque<bool> used(pairs.size(), false);
	for (std::size_t i = 0; i < larges.size(); ++i)
	{
		for (std::size_t j = 0; j < pairs.size(); ++j)
		{
			if (!used[j] && pairs[j].second == larges[i])
			{
				sorted_pairs.push_back(pairs[j]);
				used[j] = true;
				break;
			}
		}
	}

	std::deque<int> main_chain;
	main_chain.push_back(sorted_pairs[0].first);
	for (std::size_t i = 0; i < sorted_pairs.size(); ++i)
		main_chain.push_back(sorted_pairs[i].second);

	std::deque<int> pending;
	for (std::size_t i = 1; i < sorted_pairs.size(); ++i)
		pending.push_back(sorted_pairs[i].first);

	std::vector<std::size_t> order = jacobsthalOrder(pending.size());
	for (std::size_t k = 0; k < order.size(); ++k)
	{
		int value = pending[order[k]];
		std::deque<int>::iterator pos =
			std::lower_bound(main_chain.begin(), main_chain.end(), value);
		main_chain.insert(pos, value);
	}

	if (hasStraggler)
	{
		std::deque<int>::iterator pos =
			std::lower_bound(main_chain.begin(), main_chain.end(), straggler);
		main_chain.insert(pos, straggler);
	}

	d.swap(main_chain);
}






bool PmergeMe::run(int argc, char** argv)
{
	if (!parseArgs(argc, argv))
	{
		std::cerr << "Error" << std::endl;
		return false;
	}

	
	std::cout << "Before:";
	for (int i = 1; i < argc; ++i)
		std::cout << " " << argv[i];
	std::cout << std::endl;

	
	std::clock_t startVec = std::clock();
	fillVector(argc, argv);
	fjVector(_vec);
	std::clock_t endVec = std::clock();
	double usVec = static_cast<double>(endVec - startVec) * 1e6
				 / static_cast<double>(CLOCKS_PER_SEC);

	
	std::clock_t startDeq = std::clock();
	fillDeque(argc, argv);
	fjDeque(_deq);
	std::clock_t endDeq = std::clock();
	double usDeq = static_cast<double>(endDeq - startDeq) * 1e6
				 / static_cast<double>(CLOCKS_PER_SEC);

	
	std::cout << "After: ";
	for (std::size_t i = 0; i < _vec.size(); ++i)
		std::cout << " " << _vec[i];
	std::cout << std::endl;

	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << _vec.size()
			  << " elements with std::vector : " << usVec << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size()
			  << " elements with std::deque  : " << usDeq << " us" << std::endl;

	
	
	
	
	return true;
}
