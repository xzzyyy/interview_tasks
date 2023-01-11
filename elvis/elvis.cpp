#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <future>
#include <algorithm>
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
    while (cur < len)
    {
        if (ps == sep_pos_dict.end())
        {
            res.push_back(text.substr(cur));
            // cerr << "'" << res.back() << "'" << endl;
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
                // cerr << "'" << res.back() << "'" << endl;
            }
            cur = sep_pos + sep.length();

            ++ps;
        }
    }
    
    return res;
}
// -----Parser-----------------------------------------------------------

mutex mtx;

void check_args(int argc, const char*[])
{
	if (argc != 2)
        throw invalid_argument(ERR_WRONG_ARGUMENTS_NUM);
}

vector<string> process_file(const string& fpath)
{
    {
        lock_guard<mutex> lg(mtx);
        cerr << "thread " << this_thread::get_id() << " started" << endl;
    }

    ifstream in_f(fpath);       // TODO
    if (!in_f)
    {
        lock_guard<mutex> lg(mtx);
        cerr << "ERROR: can't open file for reading: " << fpath << endl;
        return {};
    }

    Parser parser;

    string line;
    getline(in_f, line);
    // cerr << "line: " << line << endl;
    parser.add_text(line);

    getline(in_f, line);
    while (in_f)
    {
        // cerr << "sep: '" << line << "'" << endl;
        parser.add_sep(line);
        getline(in_f, line);
    }

    vector<string> res = parser.parse();
    {
        lock_guard<mutex> lg(mtx);
        cerr << "thread " << this_thread::get_id() << " finished" << endl;

        // cout << "[" << de.path().filename() << "]:" << endl;     // TODO
        // for (const string& str : res)
        //     cout << str << endl;
    }
    return res;
}

void parallel_process(const string& dir_path)
{
    filesystem::path in_folder(dir_path);
    if (!filesystem::exists(in_folder))
        throw invalid_argument(ERR_PATH_NOT_EXIST);
    if (!filesystem::is_directory(in_folder))
        throw invalid_argument(ERR_PATH_NOT_DIR);

    unsigned thr_num = thread::hardware_concurrency();
    vector<future<vector<string>>> tasks(thr_num);
    mutex mtx;
    // TODO | maybe we can just create as many tasks as we wish and they will be executed in cores number batches

    auto file_iter = filesystem::directory_iterator(in_folder);
    auto file_iter_end = end(filesystem::directory_iterator(in_folder));

    bool started = false;
    int running = 0;
    while (!started || running > 0)
    {
        for (unsigned i = 0; i < thr_num; ++i)
            if (!tasks[i].valid())
            {
                if (file_iter != file_iter_end)
                {
                    tasks[i] = async(launch::async, process_file, file_iter->path().string());
                    ++file_iter;
                    ++running;
                    started = true;
                }
            }
            else if (tasks[i].wait_for(0ms) == future_status::ready)
            {
                if (file_iter != file_iter_end)
                {
                    tasks[i] = async(launch::async, &process_file, file_iter->path().string());
                    ++file_iter;
                }
                else
                {
                    tasks[i] = {};
                    --running;
                }
            }
        this_thread::sleep_for(100ms);
    }

    cout << "running == " << running << endl;
}
