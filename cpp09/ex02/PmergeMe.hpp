#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <vector>
#include <deque>
#include <cstddef>


class PmergeMe
{
private:
	std::vector<int>	_vec;
	std::deque<int>		_deq;

	
	static void	fjVector(std::vector<int>& v);
	static void	fjDeque(std::deque<int>& d);

	
	
	static std::vector<std::size_t>	jacobsthalOrder(std::size_t n);

	
	bool	parseArgs(int argc, char** argv);

	
	void	fillVector(int argc, char** argv);
	void	fillDeque(int argc, char** argv);

public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	
	
	bool	run(int argc, char** argv);
};

#endif
