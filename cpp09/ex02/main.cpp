#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
	PmergeMe pm;
	return pm.run(argc, argv) ? 0 : 1;
}
