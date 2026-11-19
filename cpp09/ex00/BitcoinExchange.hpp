#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <string>
#include <map>












class BitcoinExchange
{
private:
	std::map<std::string, float>	_db;

	
	bool	loadDatabase(const std::string& csvPath);

	
	static bool	isValidDate(const std::string& date);

	
	void	processInputLine(const std::string& line) const;

	
	
	bool	getRate(const std::string& date, float& out) const;

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	
	
	bool	run(const std::string& inputPath);
};

#endif
