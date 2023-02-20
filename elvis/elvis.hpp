#ifndef ELVIS_H
#define ELVIS_H

#include <string>
#include <vector>
#include <mutex>
#include <thread>

class Parser
{
public:
	void add_text(const std::string& text);
	void add_sep(const std::string& sep);
	std::vector<std::string> parse();

private:
	std::string text;
	std::vector<std::string> separators;
	static std::mutex mtx;
};

void check_args(int argc, const char*[]);
std::vector<std::string> process_file(const std::string& fpath);
void parallel_process(const std::string& dir_path, unsigned thr_num = std::thread::hardware_concurrency(), 
					  bool limit_output = false);

constexpr std::string_view ERR_WRONG_ARGUMENTS_NUM = "wrong number of arguments";
constexpr std::string_view ERR_PATH_NOT_EXIST = "the path doesn't exist";
constexpr std::string_view ERR_PATH_NOT_DIR = "the path is not the folder";

#endif
