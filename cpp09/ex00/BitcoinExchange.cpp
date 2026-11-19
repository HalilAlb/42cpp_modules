#include "BitcoinExchange.hpp"

#include <iostream>
#include <fstream>
#include <cstdlib>   



static const char* DEFAULT_DB_PATH = "data.csv";


BitcoinExchange::BitcoinExchange() : _db()
{
	loadDatabase(DEFAULT_DB_PATH);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _db(other._db)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_db = other._db;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}



bool BitcoinExchange::loadDatabase(const std::string& csvPath)
{
	std::ifstream f(csvPath.c_str());
	if (!f.is_open())
	{
		std::cerr << "Error: could not open database '" << csvPath << "'." << std::endl;
		return false;
	}

	std::string line;
	bool firstLine = true;
	while (std::getline(f, line))
	{
		if (firstLine) { firstLine = false; continue; }  
		if (line.empty()) continue;

		std::size_t comma = line.find(',');
		if (comma == std::string::npos) continue;

		std::string date = line.substr(0, comma);
		std::string val  = line.substr(comma + 1);

		char* end = NULL;
		float rate = std::strtod(val.c_str(), &end);
		if (end == val.c_str()) continue;  

		_db[date] = rate;
	}
	return true;
}





bool BitcoinExchange::isValidDate(const std::string& date)
{
	if (date.length() != 10) return false;
	if (date[4] != '-' || date[7] != '-') return false;
	for (int i = 0; i < 10; ++i)
	{
		if (i == 4 || i == 7) continue;
		if (date[i] < '0' || date[i] > '9') return false;
	}
	int month = (date[5] - '0') * 10 + (date[6] - '0');
	int day   = (date[8] - '0') * 10 + (date[9] - '0');
	if (month < 1 || month > 12) return false;
	if (day < 1 || day > 31) return false;
	return true;
}


bool BitcoinExchange::getRate(const std::string& date, float& out) const
{
	
	std::map<std::string, float>::const_iterator it = _db.lower_bound(date);

	if (it != _db.end() && it->first == date)
	{
		out = it->second;
		return true;
	}
	
	if (it == _db.begin())
		return false;  
	--it;
	out = it->second;
	return true;
}


void BitcoinExchange::processInputLine(const std::string& line) const
{
	
	std::size_t sep = line.find('|');
	if (sep == std::string::npos)
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return;
	}

	
	std::string date  = line.substr(0, sep);
	std::string value = line.substr(sep + 1);
	while (!date.empty() && date[date.size() - 1] == ' ') date.erase(date.size() - 1);
	while (!value.empty() && value[0] == ' ') value.erase(0, 1);

	if (!isValidDate(date))
	{
		std::cerr << "Error: bad input => " << date << std::endl;
		return;
	}

	char* end = NULL;
	float v = std::strtod(value.c_str(), &end);
	if (value.empty() || *end != '\0')
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return;
	}
	if (v < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return;
	}
	if (v > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return;
	}

	float rate = 0;
	if (!getRate(date, rate))
	{
		std::cerr << "Error: no rate available for " << date << std::endl;
		return;
	}

	std::cout << date << " => " << v << " = " << (v * rate) << std::endl;
}


bool BitcoinExchange::run(const std::string& inputPath)
{
	std::ifstream f(inputPath.c_str());
	if (!f.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return false;
	}

	std::string line;
	bool firstLine = true;
	while (std::getline(f, line))
	{
		
		if (firstLine)
		{
			firstLine = false;
			if (line.find("date") != std::string::npos
				&& line.find("value") != std::string::npos)
				continue;
		}
		if (line.empty()) continue;
		processInputLine(line);
	}
	return true;
}
