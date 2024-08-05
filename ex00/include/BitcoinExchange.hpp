#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP
# define DATA_PATH "data/data.csv"

#include <iostream>
#include <map>
#include <ctime>
#include <cstring>
#include <fstream>
#include <sstream>

class BitcoinExchange
{
	private:
		std::map<std::string, float> *_dataMap;
		bool _getValue(float &value, const std::string &line) const;
		float _getPrice(const std::string &str) const;
		void _displayConversion(std::string line);
		bool _checkDateFormat(const std::string &str) const;
		std::tm _strToTm(const std::string &dateStr) const;
		time_t _tmToTimeT(const std::tm &dateTm) const;
		std::string _findClosestDate(const std::string &dateStr) const;

	  public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &ref);
		BitcoinExchange &operator=(const BitcoinExchange &ref);
		~BitcoinExchange (void);
		void storeData(void);
		void readInput(std::string path);
};

#endif
