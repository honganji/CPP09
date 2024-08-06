#include "../include/PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
	std::cout << "PmergeMe instance is created!" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &ref){(void)ref;}

PmergeMe &PmergeMe::operator=(const PmergeMe &ref)
{
	(void)ref;
	return (*this);
}

PmergeMe::~PmergeMe(void)
{
	std::cout << "PmergeMe instance is destroyed" << std::endl;
}

int PmergeMe::_partitionVecWithMedian(std::vector<int> &vec, int start, int end, int medianIndex)
{
	int tmpIndex = start;
	std::swap(vec[medianIndex], vec[end]);
	for (int i = start; i < end; i++)
	{
		if (vec[i] < vec[end])
			std::swap(vec[tmpIndex++], vec[i]);
	}
	std::swap(vec[tmpIndex], vec[end]);
	return (tmpIndex);
}

int PmergeMe::_partitionDeqWithMedian(std::deque<int> &deq, int start, int end, int medianIndex)
{
	int tmpIndex = start;
	std::swap(deq[medianIndex], deq[end]);
	for (int i = start; i < end; i++)
	{
		if (deq[i] < deq[end])
			std::swap(deq[tmpIndex++], deq[i]);
	}
	std::swap(deq[tmpIndex], deq[end]);
	return (tmpIndex);
}

void PmergeMe::_pmergeSortVec(std::vector<int> &vec, int start, int end)
{
	std::vector<int> indexVec;

	if (end - start <= 1)
	{
		if (end - start == 1 && vec[start] > vec[end])
			std::swap(vec[start], vec[end]);
		return;
	}

	for (int i = start; i < end; i += 2)
	{
		if (vec[i] > vec[i + 1])
			std::swap(vec[i], vec[i + 1]);
		indexVec.push_back(i + 1);
	}
	if ((end - start + 1) % 2)
		indexVec.push_back(end);
	int midIndex = _partitionVecWithMedian(vec, start, end, indexVec[indexVec.size() / 2]);
	_pmergeSortVec(vec, start, midIndex - 1);
	_pmergeSortVec(vec, midIndex, end);
}

void PmergeMe::_pmergeSortDeq(std::deque<int> &deq, int start, int end)
{
	std::deque<int> indexDeq;
	if (end - start <= 1)
	{
		if (end - start == 1 && deq[start] > deq[end])
			std::swap(deq[start], deq[end]);
		return;
	}

	for (int i = start; i < end; i += 2)
	{
		if (deq[i] > deq[i + 1])
			std::swap(deq[i], deq[i + 1]);
		indexDeq.push_back(i + 1);
	}
	if ((end - start + 1) % 2)
		indexDeq.push_back(end);
	int midIndex = _partitionDeqWithMedian(deq, start, end, indexDeq[indexDeq.size() / 2]);
	_pmergeSortDeq(deq, start, midIndex - 1);
	_pmergeSortDeq(deq, midIndex, end);
}

bool PmergeMe::pmergeMeSort(std::vector<int> &vec, std::deque<int> &deq)
{
	std::set<int> checkElement;
	for (std::vector<int>::iterator it = vec.begin(); it < vec.end(); it++)
	{
		std::pair<std::set<int>::iterator, bool> result = checkElement.insert(*it);
		if (!result.second)
		{
			std::cerr << "\033[31m" << "There is duplicate!" << "\033[0m" << std::endl;
			return (false);
		}
	}
	std::cout << "Before: ";
	displayContainer(vec, deq);
	// merge-insert sort for vector
	std::clock_t start = std::clock();
	_pmergeSortVec(vec, 0, vec.size() - 1);
	std::clock_t end = std::clock();
	double vecTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

	// merge-insert sort for deque
	start = std::clock();
	_pmergeSortDeq(deq, 0, deq.size() - 1);
	end = std::clock();
	double deqTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "After: ";
	displayContainer(vec, deq);
	std::cout << "\033[34m" << "Time to process a range of " << vec.size();
	std::cout << " elements with std::vector<int> : " << vecTime;
	std::cout << " sec" << "\033[0m" << std::endl;
	std::cout << "\033[34m" << "Time to process a range of " << vec.size();
	std::cout << " elements with std::deque<int> : " << deqTime;
	std::cout << " sec" << "\033[0m" << std::endl;
	return (true);
}

void PmergeMe::displayContainer(std::vector<int> &vec, std::deque<int> &deq)
{
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	(void)deq;
}

bool PmergeMe::parsing(int argc, char *argv[], std::vector<int> &vec, std::deque<int> &deq)
{
	std::vector<std::string> strVec;
	if (argc == 2)
	{
		std::istringstream tokenStream(argv[1]);
		std::string strNum;
		while (tokenStream >> strNum)
		{
			try
			{
				vec.push_back(std::stoi(strNum));
			}
			catch(const std::invalid_argument& e)
			{
				std::cerr << e.what() << std::endl;
				return (false);
			}
			catch(const std::out_of_range& e)
			{
				std::cerr << e.what() << std::endl;
				return (false);
			}
		}
		std::copy(vec.begin(), vec.end(), std::back_insert_iterator< std::deque<int> >(deq));
	}
	else
	{
		for (int i = 1; i < argc; i++)
		{
			try
			{
				vec.push_back(std::stoi(argv[i]));
			}
			catch(const std::invalid_argument& e)
			{
				std::cerr << "\033[31m" << e.what() << "\033[0m" << std::endl;
				return (false);
			}
			catch(const std::out_of_range& e)
			{
				std::cerr << "\033[31m" << e.what() << "\033[0m" << std::endl;
				return (false);
			}
		}
		std::copy(vec.begin(), vec.end(), std::back_insert_iterator< std::deque<int> >(deq));
	}
	return (true);
}
