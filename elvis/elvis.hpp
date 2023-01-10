#ifndef ELVIS_H
#define ELVIS_H

#include <map>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <mutex>

class Parser
{
public:
	void add_text(const std::string& text);
	void add_sep(const std::string& sep);
	std::vector<std::string> parse();

private:
	std::string text;
	std::vector<std::string> separators;
};

void process_file(const std::filesystem::directory_entry de, std::ofstream& out_f, std::mutex& mtx);
void parallel_process(const std::filesystem::path &in_folder, std::ofstream &out_f);

#endif
