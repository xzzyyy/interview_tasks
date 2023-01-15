#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <future>
#include <algorithm>
#include <cmath>        // for `round`
#include "elvis.hpp"
using namespace std;

// -----Parser-----------------------------------------------------------
void Parser::add_text(const std::string& text)
{
    this->text = text;
}

void Parser::add_sep(const std::string& sep)
{
    separators.push_back(sep);
}

vector<string> Parser::parse()
{
    map<size_t, string> sep_pos_dict;
    vector<string> res;

    // this is needed to always remove longs separators first and short substring of long in the second turn
    sort(separators.begin(), separators.end(), [](const string& l, const string& r){ return l.length() < r.length(); });
    
    for (const string& sep : separators)
    {
        size_t pos = 0;
        while ((pos = text.find(sep, pos)) != string::npos)
        {
            sep_pos_dict[pos] = sep;
            pos += sep.length();
        }
    }

    size_t cur = 0;
    size_t len = text.length();
    auto ps = sep_pos_dict.begin();
    thread_local int last_pcnt = 0;
    size_t cnt = 0;
    while (cur < len)
    {
        double new_pcnt = double(cur) / len * 100;
        if (new_pcnt > (last_pcnt + 10))
        {
            int new_pcnt_int = static_cast<int>(round(new_pcnt));
            last_pcnt = new_pcnt_int;

            lock_guard guard(mtx);
            cerr << this_thread::get_id() << " | " << (string(new_pcnt_int, '.') + ' ') << new_pcnt_int << "%" << endl;
        }

        if (ps == sep_pos_dict.end())
        {
            res.push_back(text.substr(cur));
            // cerr << "'" << res.back() << "'" << endl;        // DBG
            cur = len;
        }
        else if (ps->first < cur)
            ++ps;
        else
        {
            size_t sep_pos = ps->first;
            string sep = ps->second;

            if (sep_pos > cur)
            {
                res.push_back(text.substr(cur, sep_pos - cur));
                // cerr << "'" << res.back() << "'" << endl;        // DBG
            }
            cur = sep_pos + sep.length();

            ++ps;
        }
        if (++cnt % 10 == 0)
            this_thread::sleep_for(5ms);       // wasted time to demonstrate multithreading in action
    }
    
    return res;
}
// -----Parser-----------------------------------------------------------

void check_args(int argc, const char*[])
{
	if (argc != 2)
        throw invalid_argument(ERR_WRONG_ARGUMENTS_NUM);
}

vector<string> process_file(const string& fpath)
{
    ifstream in_f(fpath);
    if (!in_f)
        throw system_error(error_code{}, "can't read file [" + fpath + "]");

    Parser parser;

    string line;
    getline(in_f, line);
    // cerr << "line: " << line << endl;        // DBG
    parser.add_text(line);

    getline(in_f, line);
    while (in_f)
    {
        // cerr << "sep: '" << line << "'" << endl;     // DBG
        parser.add_sep(line);
        getline(in_f, line);
    }

    vector<string> res = parser.parse();
    return res;
}

void parallel_process(const string& dir_path, unsigned thr_num, bool limit_output)
{
    filesystem::path in_folder(dir_path);
    if (!filesystem::exists(in_folder))
        throw invalid_argument(ERR_PATH_NOT_EXIST);
    if (!filesystem::is_directory(in_folder))
        throw invalid_argument(ERR_PATH_NOT_DIR);

    vector<future<vector<string>>> tasks(thr_num);
    vector<string> filenames(thr_num);

    auto file_iter = filesystem::directory_iterator(in_folder);
    auto file_iter_end = end(filesystem::directory_iterator(in_folder));

    int running = 0;
    do
    {
        for (unsigned i = 0; i < thr_num; ++i)
        {
            bool finished = false;
            if (!tasks[i].valid() || (finished = tasks[i].wait_for(0ms) == future_status::ready))
            {
                if (finished)
                {
                    --running;

                    cout << reinterpret_cast<const char*>(u8"[Имя файла ") << filenames[i] << "]:" << '\n';
                    auto res = tasks[i].get();
                    size_t cycle_num = min(res.size(), limit_output ? 10 : SIZE_MAX);
                    for (size_t i = 0; i < cycle_num; ++i)
                    {
                        cout << res[i];
                        if (i < cycle_num - 1)
                            cout << '\n';
                        else if (limit_output)
                            cout << "..." << endl;
                        else
                            cout << endl;
                    }
                }

                if (file_iter != file_iter_end)
                {
                    filenames[i] = file_iter->path().string();
                    tasks[i] = async(launch::async, process_file, filenames[i]);
                    ++running;
                    ++file_iter;
                }
                else
                    tasks[i] = {};
            }
        }
        this_thread::sleep_for(100ms);
    }
    while (running > 0);
}
