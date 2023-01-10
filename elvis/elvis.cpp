// Не указанные моменты:
// - что должно быть на выходе, если один разделитель идёт вплотную за другим: пустая строка, или ничего?
// - что, если один разделитель это подстрока другого разделителя, какой из них должен иметь приоритет?
// В этих случаях я считаю, что любое поведение правильное

#include "elvis.hpp"
#include <iostream>
#include <thread>
#include <future>
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

    for (const string& sep : separators)
    {
        size_t pos = text.find(sep);
        if (pos != string::npos)
            sep_pos_dict[pos] = sep;
    }

    size_t cur = 0;
    size_t len = text.length();
    while (cur < len)
    {
        auto ps = sep_pos_dict.begin();
        if (ps == sep_pos_dict.end())
        {
            res.push_back(text.substr(cur));
            cur = len;
        }
        else
        {
            size_t old_pos = ps->first;
            string sep = ps->second;

            res.push_back(text.substr(cur, old_pos - cur));
            cur = old_pos + sep.length();

            size_t new_pos = text.find(sep, cur);
            sep_pos_dict.erase(ps);
            if (new_pos != string::npos)
                sep_pos_dict[new_pos] = sep;
        }
    }
    
    return res;
}
// -----Parser-----------------------------------------------------------

void check_args(int argc, const char*[])
{
	if (argc != 2)
        throw invalid_argument(ERR_WRONG_ARGUMENTS_NUM);
}

void process_file(const filesystem::directory_entry de, mutex& mtx)
{
    {
        lock_guard<mutex> lg(mtx);
        cout << "thread " << this_thread::get_id() << " started" << endl;
    }

    ifstream in_f(de.path());
    if (!in_f)
    {
        lock_guard<mutex> lg(mtx);
        cerr << "ERROR: can't open file for reading: " << de << endl;
        return;
    }

    Parser parser;

    string line;
    getline(in_f, line);
    parser.add_text(line);

    while (in_f)
    {
        string s;
        getline(in_f, s);
        parser.add_sep(s);
    }

    vector<string> res = parser.parse();
    {
        lock_guard<mutex> lg(mtx);

        cout << "[" << de.path().filename() << "]:" << endl;
        for (const string& str : res)
            cout << str << endl;

        cout << "thread " << this_thread::get_id() << " finished" << endl;
    }
}

void parallel_process(const string& dir_path)
{
    filesystem::path in_folder(dir_path);
    if (!filesystem::exists(in_folder))
        throw invalid_argument(ERR_PATH_NOT_EXIST);
    if (!filesystem::is_directory(in_folder))
        throw invalid_argument(ERR_PATH_NOT_DIR);

    unsigned thr_num = thread::hardware_concurrency();
    vector<future<void>> tasks(thr_num);
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
                    tasks[i] = async(launch::async, process_file, *file_iter, ref(mtx));
                    ++file_iter;
                    ++running;
                    started = true;
                }
            }
            else if (tasks[i].wait_for(0ms) == future_status::ready)
            {
                if (file_iter != file_iter_end)
                {
                    tasks[i] = async(launch::async, &process_file, *file_iter, ref(mtx));
                    ++file_iter;
                }
                else
                {
                    tasks[i] = future<void>();
                    --running;
                }
            }
        this_thread::sleep_for(100ms);
    }

    cout << "running == " << running << endl;
}
