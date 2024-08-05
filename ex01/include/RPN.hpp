#ifndef RPN_HPP
# define RPN_HPP
# define DATA_PATH "data/data.csv"

#include <iostream>
#include <map>
#include <ctime>
#include <cstring>
#include <fstream>
#include <sstream>

class RPN
{
	private:
		std::stack<int> _stack;
		unsigned int _count;
		bool _classifyStr(const std::string str);
		void _addition(void);
		void _subtraction(void);
		void _multiplication(void);
		void _division(void);
		class _TooLowException : public std::exception
		{
			public:
			  const char *what() const throw();
		};
		class _TooHighException : public std::exception
		{
			public:
			  const char *what() const throw();
		};
		class _ZeroException : public std::exception
		{
			public:
			  const char *what() const throw();
		};
		class _TooManySignException : public std::exception
		{
			public:
			  const char *what() const throw();
		};
		class _TooManyNumException : public std::exception
		{
			public:
			  const char *what() const throw();
		};
		class _TooLessArgsException : public std::exception
		{
			public:
			  const char *what() const throw();
		};
		class _UnexpectedStrException : public std::exception
		{
			public:
			  const char *what() const throw();
		};

	  public:
		RPN(void);
		RPN(const RPN &ref);
		RPN &operator=(const RPN &ref);
		~RPN (void);
		bool calculate(const std::string &str);
		// For test
		void displayStack(void);
};

#endif
