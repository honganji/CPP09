#ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP

#include <iostream>
#include <vector>
#include <set>
#include <ctime>
#include <cstring>
#include <fstream>
#include <sstream>
#include <ctime>

class PmergeMe
{
	private:
		int _partitionVecWithMedian(std::vector<int> &vec, int start, int end, int medianIndex);
		int _partitionDeqWithMedian(std::deque<int> &deq, int start, int end, int medianIndex);
		void _pmergeSortVec(std::vector<int> &vec, int start, int end);
		void _pmergeSortDeq(std::deque<int> &deq, int start, int end);
	public:
	  PmergeMe(void);
	  PmergeMe(const PmergeMe &ref);
	  PmergeMe &operator=(const PmergeMe &ref);
	  ~PmergeMe(void);
	  bool pmergeMeSort(std::vector<int> &vec, std::deque<int> &deq);
	  bool parsing(int argc, char *argv[], std::vector<int> &vec, std::deque<int> &deq);
	  // For test
	  void displayContainer(std::vector<int> &vec, std::deque<int> &deq);
};

#endif
