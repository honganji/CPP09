#include "include/RPN.hpp"

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		RPN rpn;
		try
		{
			return (rpn.calculate(argv[1]));
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		
	}
	else
	{
		std::cerr << "The input should be one" << std::endl;
		return (1);
	}
	return (0);
}
