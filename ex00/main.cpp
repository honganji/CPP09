#include "include/easyfind.hpp"
#include <random>

int main( void )
{
	std::vector<int> vec;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1, 100);
	for (size_t i = 0; i < 100; i++)
	{
		vec.push_back(distrib(gen));
		if (vec.at(i) == 10)
			std::cout << "There is 10!" << std::endl;
	}
	try
	{
		std::cout << *(easyfind(vec, 10)) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}
