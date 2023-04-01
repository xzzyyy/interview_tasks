//////////////////////////////////////////////////////////////////
// 1. Найти проблемы в коде 
//////////////////////////////////////////////////////////////////


// Задача: заполнить массив 128 элементов числами 77, затем сначала
// напечатать первый элемент, потом просуммировать их попарно и выдать результат,
//  т.е. "77.0, 154.0, 154.0, 154.0  ...."

#include <iostream>

void set_array(char a[]) {
    memset(a, 77, sizeof(a));
}

double* sum_pair(char a[], int idx) {
    double s = a[idx] + a[idx+1];       // a[-1] -- out of array
    return &s;                          // returning address of stack variable, doesn't exist after return
}

int main()
{
    const unsigned int sz = 128;
    char a[sz] = {};                    // redundant, we will memset array to 77 later
    memset(a, 0, sizeof(a));            // redundant, we already initialized a with \0s
    set_array(a);
    double* s[sz] = {};
    for (int i = -1; i < sz; ++i)       // ot of bound on i == sz - 1
                                        // will never be executed because comparing signed -1 and unsigned int
    {
        if (i < 0)
            std::cout << a[0] << " ";
        s[i] = sum_pair(a, i);
    }
    for (int i = 0; i < sz; ++i)        // s[sz - 1] is not filled
        std::cout << s[i] << " ";
}
