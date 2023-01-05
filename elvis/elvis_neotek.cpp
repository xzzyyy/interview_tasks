// Не указанные моменты:
// - что должно быть на выходе, если один разделитель идёт вплотную за другим: пустая строка, или ничего?
// - что, если один разделитель это подстрока другого разделителя, какой из них должен иметь приоритет?
// В этих случаях я считаю, что любое поведение правильное

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <future>
using namespace std;

// -----Parser-----------------------------------------------------------
class Parser
{
	string text;
	map<size_t, string> positions;
public:
	Parser(const string& text);
	void addSeparator(const string& sep);
	vector<string> parse();
};

Parser::Parser(const string& text)
	: text(text)
{
}

void Parser::addSeparator(const string& sep)
{
	size_t pos = text.find(sep);
	if (pos != string::npos)
		positions[pos] = sep;
}

vector<string> Parser::parse()
{
	vector<string> out;
	size_t cur = 0;
	size_t len = text.length();
	while (cur < len)
	{
		auto pos_sep = positions.begin();
		if (pos_sep == positions.end())
		{
			out.push_back(text.substr(cur));
			cur = len;
		}
		else
		{
			size_t old_pos = pos_sep->first;
			string sep = pos_sep->second;

			out.push_back(text.substr(cur, old_pos - cur));
			cur = old_pos + sep.length();

			size_t new_pos = text.find(sep, cur);
			positions.erase(pos_sep);
			if (new_pos != string::npos)
			{
				positions[new_pos] = sep;
			}
		}
	}
	return out;
}
// -----Parser-----------------------------------------------------------

void print_help()
{
	cout << "elvis_neotek <input-folder> <output-file>\n";
}

mutex m;
void process_file(const filesystem::directory_entry de, ofstream& out_f)
{
	{
		lock_guard<mutex> lg(m);
		cout << "thread " << this_thread::get_id() << " started\n";
	}

	if (!de.is_regular_file())
		return;

	ifstream in_f(de.path());
	if (!in_f)
	{
		lock_guard<mutex> lg(m);
		cout << "ERROR: can't open file for reading: " << de;
		return;
	}

	string text;
	getline(in_f, text);

	Parser parser(text);
	string s;
	while (in_f)
	{
		getline(in_f, s);
		parser.addSeparator(s);
	}

	vector<string> res = parser.parse();
	{
		lock_guard<mutex> lg(m);

		out_f << "[" << de.path().filename() << "]:\n";
		for (const string& str : res)
			out_f << str << "\n";

		cout << "thread " << this_thread::get_id() << " finished\n";
	}
}

void parallel_process(const filesystem::path &in_folder, ofstream &out_f)
{
	unsigned thr_num = thread::hardware_concurrency();
	vector<future<void>> tasks(thr_num);

	auto file_iter = filesystem::directory_iterator(in_folder);
	auto file_iter_end = end(filesystem::directory_iterator(in_folder));

	bool started = false;
	int running = 0;
	while (!started || running > 0)
	{
		for (unsigned i = 0; i < thr_num; ++i)
		{

			if (!tasks[i].valid())
			{
				if (file_iter != file_iter_end)
				{
					tasks[i] = async(launch::async, process_file, *file_iter, ref(out_f));
					++file_iter;
					++running;
					started = true;
				}
			}
			else
			{
				if (tasks[i].wait_for(0ms) == future_status::ready)
				{
					if (file_iter != file_iter_end)
					{
						tasks[i] = async(launch::async, process_file, *file_iter, ref(out_f));
						++file_iter;
					}
					else
					{
						tasks[i] = future<void>();
						--running;
					}
				}
				else
				{

				}
			}
		}

		this_thread::sleep_for(100ms);
	}

	cout << "running == " << running << "\n";
}

int main(int argc, char** argv)
{
    if (argc != 3)
	{
		cout << "ERROR: 2 parameters should be passed\n";
		print_help();
		return EINVAL;
	}

	filesystem::path in_folder(argv[1]);
	if (!filesystem::exists(in_folder))
	{
		cout << "ERROR: input folder doesn't exist\n";
		return ENOENT;
	}

	ofstream out_f(argv[2]);
	if (!out_f)
	{
		cout << "ERROR: can't create output file\n";
		return EIO;
	}

	parallel_process(in_folder, out_f);
	return 0;
}
