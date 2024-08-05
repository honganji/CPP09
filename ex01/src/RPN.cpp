#include "../include/RPN.hpp"

void RPN::_addition(void)
{
	int first;
	int second;

	second = _stack.top();
	_stack.pop();
	first = _stack.top();
	_stack.pop();
	_count--;
	if (second > 0 && first > INT_MAX - second)
		throw (_TooHighException());
	else if (second < 0 && first < INT_MIN - second)
		throw (_TooLowException());
	else
		_stack.push(first + second);
}

void RPN::_subtraction(void)
{
	int first;
	int second;

	second = _stack.top();
	_stack.pop();
	first = _stack.top();
	_stack.pop();
	_count--;
	if (second < 0 && first > INT_MAX + second)
		throw (_TooLowException());
	else if (second > 0 && first < INT_MIN + second)
		throw (_TooHighException());
	else
		_stack.push(first - second);
}

void RPN::_multiplication(void)
{
	int first;
	int second;

	second = _stack.top();
	_stack.pop();
	first = _stack.top();
	_stack.pop();
	_count--;
	if (second == 0)
		_stack.push(0);
	else if (((second < 0 && first < 0) || (second > 0 && first > 0)) && first > INT_MAX / second)
		throw (_TooLowException());
	else if (((second < 0 && first > 0) || (second > 0 && first < 0)) && first < INT_MIN / second)
		throw (_TooHighException());
	else
		_stack.push(first * second);
}

void RPN::_division(void)
{
	int first;
	int second;

	second = _stack.top();
	_stack.pop();
	first = _stack.top();
	_stack.pop();
	_count--;
	if (second == 0)
		throw (_ZeroException());
	else if (first == INT_MIN && second == -1)
		throw (_TooHighException());
	else
		_stack.push(first / second);
}

bool RPN::_classifyStr(const std::string str)
{
	if (std::isdigit(str[0]))
	{
		_stack.push(std::stoi(str));
		_count++;
	}
	else
	{
		if (_count < 2)
		{
			throw(_TooManySignException());
			return (false);
		}
		switch (str[0])
		{
		case '+':
			try
			{
				_addition();
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				return (false);
			}

			break;
		case '-':
			try
			{
				_subtraction();
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				return (false);
			}
			break;
		case '/':
			try
			{
				_division();
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				return (false);
			}
			break;
		case '*':
			try
			{
				_multiplication();
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				return (false);
			}
			break;
		default:
			break;
		}
	}
		return (true);
}
bool RPN::calculate(const std::string &str)
{
	std::istringstream iss(str);
	std::string value;

	while (iss >> value)
	{
		if (!_classifyStr(value))
			return (false);
		// displayStack();
	}
	if (_count > 1)
	{
		throw(_TooManyNumException());
		return (false);
	}
	std::cout << "The result is " << _stack.top() << std::endl;
	return (true);
}

void RPN::displayStack(void)
{
	std::stack<int> tmpStack = _stack;

	while (!tmpStack.empty())
	{
		std::cout << tmpStack.top() << " ";
		tmpStack.pop();
	}
	std::cout << std::endl;
}

RPN::RPN(void) : _count(0)
{
	std::cout << "\033[34mRPN class is created!\033[0m" << std::endl;
}

RPN::RPN(const RPN &ref) : _count(0)
{
	_stack = ref._stack;
}

RPN &RPN::operator=(const RPN &ref)
{
	if (this != &ref)
	{
		_stack = ref._stack;
		_count = ref._count;
	}
	return (*this);
}

RPN::~RPN (void)
{
	std::cout << "\033[34mRPN class is destroyed!\033[0m" << std::endl;
}

// TooLowException class
const char *RPN::_TooLowException::what() const throw()
{
	return ("\033[31mThe result of the operation would be too Low\033[0m");
}

// TooHighException class
const char *RPN::_TooHighException::what() const throw()
{
	return ("\033[31mThe result of the operation would be too High\033[0m");
}

// ZeroException class
const char *RPN::_ZeroException::what() const throw()
{
	return ("\033[31ma number is about to be divided by 0!\033[0m");
}

// TooManySignException class
const char *RPN::_TooManySignException::what() const throw()
{
	return ("\033[31mThere are too many signs\033[0m");
}

// TooManyNumException class
const char *RPN::_TooManyNumException::what() const throw()
{
	return ("\033[31mThere are too many nums\033[0m");
}

// TooLessArgException class
const char *RPN::_TooLessArgsException::what() const throw()
{
	return ("\033[31mThere are too less arguments\033[0m");
}

// UnexpectedStrException class
const char *RPN::_UnexpectedStrException::what() const throw()
{
	return ("\033[31mThere is an unexpected argument\033[0m");
}
