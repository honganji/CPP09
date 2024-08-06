#include "include/PmergeMe.hpp"

int main(int argc, char *argv[])
{
	std::vector<int> vec;
	std::deque<int> deq;
	PmergeMe pmergeMe;
	if (argc >= 2)
	{
		if (!pmergeMe.parsing(argc, argv, vec, deq))
			return (1);
		return (pmergeMe.pmergeMeSort(vec, deq) ? 0 : 1);
	}
	else
	{
		std::cerr << "The input should be more than one" << std::endl;
		return (1);
	}
	return (0);
}
