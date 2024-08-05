#include "../include/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	_dataMap = new std::map<std::string, float>;
	std::cout << "\033[34mBitcoinExchange class is created!\033[0m" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &ref)
{
	_dataMap = new std::map<std::string, float>;
	for (std::map<std::string, float>::const_iterator it = ref._dataMap->begin(); it != ref._dataMap->end(); it++)
		_dataMap->insert(*it);
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &ref)
{
	if (this != &ref)
	{
		delete _dataMap;
		_dataMap = new std::map<std::string, float>;
		for (std::map<std::string, float>::const_iterator it = ref._dataMap->begin(); it != ref._dataMap->end(); it++)
			_dataMap->insert(*it);
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange (void)
{
	delete _dataMap;
	std::cout << "\033[34mBitcoinExchange class is destroyed!\033[0m" << std::endl;
}

void BitcoinExchange::storeData(void)
{
	std::ifstream file(DATA_PATH);
	std::string line;

	getline(file, line);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			std::size_t delimiter = line.find(",");
			if (delimiter != std::string::npos)
				(*_dataMap)[line.substr(0, delimiter)] = std::stof(line.substr(delimiter + 1));
		}
		file.close();
	}
	else
	{
		std::cerr << "\033[31mUnable to open file!\033[0m";
		std::exit(0);
	}
}

bool BitcoinExchange::_checkDateFormat(const std::string &str) const
{
	std::tm tm = {};
	std::istringstream ss(str);

	ss >> std::get_time(&tm, "%Y-%m-%d");
	if (ss.fail() || !ss.eof())
	{
		std::cerr << "\033[31mDate format is not correct...\033[0m" << std::endl;
		return (false);
	}
	return (true);
}

std::tm BitcoinExchange::_strToTm(const std::string &dateStr) const
{
	std::tm tm = {};
	std::istringstream ss(dateStr);
	ss >> std::get_time(&tm, "%Y-%m-%d");
	return (tm);
}

time_t BitcoinExchange::_tmToTimeT(const std::tm &dateTm) const
{
	return (mktime(const_cast<std::tm*>(&dateTm)));
}

std::string BitcoinExchange::_findClosestDate(const std::string &dateStr) const
{
	std::tm dateTm = _strToTm(dateStr);
	time_t dateTime = _tmToTimeT(dateTm);
	std::string closestDate;
	double minimumDiff = std::numeric_limits<double>::max();

	for (std::map<std::string, float>::const_iterator it = _dataMap->begin(); it != _dataMap->end(); it++)
	{
		std::tm tmpTm = _strToTm(it->first);
		time_t tmpTime = _tmToTimeT(tmpTm);
		double tmpDiff = std::abs(difftime(dateTime, tmpTime));

		if (tmpDiff < minimumDiff)
		{
			minimumDiff = tmpDiff;
			closestDate = it->first;
		}
	}
	return (closestDate);
}

float BitcoinExchange::_getPrice(const std::string &str) const
{
	
	return ((*_dataMap)[_findClosestDate(str)]);
}

bool BitcoinExchange::_getValue(float &value, const std::string &line) const
{
	std::size_t delimiter = line.find(" | ");
	try
	{
		value = std::stof(line.substr(delimiter + 3));
	}
	catch (const std::invalid_argument &e)
	{
		std::cerr << "\033[31m" << e.what() << "\033[0m" << std::endl;
		return (false);
	}
	catch(const std::out_of_range &d)
	{
		std::cerr << "\033[31m" << d.what() << "\033[0m" << std::endl;
		return (false);
	}
	if (value > 1000)
	{
		std::cerr << "\033[31mthe value is too big\033[0m" << std::endl;
		return (false);
	}
	else if (value < 0)
	{
		std::cerr << "\033[31mthe value should be positive\033[0m" << std::endl;
		return (false);
	}
	return (true);
}

void BitcoinExchange::_displayConversion(std::string line)
{
	std::size_t delimiter = line.find(" | ");
	float value;
	float price;
	std::string date;
	if (delimiter != std::string::npos)
	{
		std::cout << line.substr(0, delimiter) << ": ";
		if (!_checkDateFormat(date = line.substr(0, delimiter)) || !_getValue(value, line))
			return ;
		price = _getPrice(date);
		std::cout << value << " * ";
		std::cout << price << " -> ";
		std::cout << value * price << " BTC" << std::endl;
	}
	else
		std::cerr << "\033[31mThe format is not correct...\033[0m" << std::endl;
}

void BitcoinExchange::readInput(std::string path)
{
	std::ifstream file(path);
	std::string line;

	if (file.is_open())
	{
		while (getline(file, line))
			_displayConversion(line);
		file.close();
	}
	else
	{
		std::cerr << "\033[31mthe path doesn't exist...\033[0m" << std::endl;
		std::exit(0);
	}
}
