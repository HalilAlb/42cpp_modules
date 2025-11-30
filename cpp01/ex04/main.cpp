/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:00:00 by malbayra          #+#    #+#             */
/*   Updated: 2025/11/27 22:15:32 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <string>

std::string replaceAll(const std::string &content, const std::string &s1,
	const std::string &s2)
{
	size_t	pos;
	size_t	found;

	if (s1.empty())
		return (content);
	std::string result;
	pos = 0;
	while ((found = content.find(s1, pos)) != std::string::npos)
	{
		result.append(content, pos, found - pos);
		result.append(s2);
		pos = found + s1.length();
	}
	result.append(content, pos, content.length() - pos);
	return (result);
}

int	main(int argc, char **argv)
{
	bool	first;

	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
		return (1);
	}
	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];
	std::ifstream infile(filename.c_str());
	if (!infile.is_open())
	{
		std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
		return (1);
	}
	std::string content;
	std::string line;
	first = true;
	while (std::getline(infile, line))
	{
		if (!first)
			content += "\n";
		content += line;
		first = false;
	}
	infile.close();
	std::string result = replaceAll(content, s1, s2);
	std::string outfilename = filename + ".replace";
	std::ofstream outfile(outfilename.c_str());
	if (!outfile.is_open())
	{
		std::cerr << "Error: Could not create file '" << outfilename << "'" << std::endl;
		return (1);
	}
	outfile << result;
	outfile.close();
	std::cout << "File processed successfully. Output: " << outfilename << std::endl;
	return (0);
}
