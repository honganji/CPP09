#include "include/BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		// (void)argv;
		BitcoinExchange bc;
		bc.storeData();
		bc.readInput(argv[1]);
	}
	else
	{
		std::cerr << "The input should be one" << std::endl;
		return (1);
	}
	return (0);
}
