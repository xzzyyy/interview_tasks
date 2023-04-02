//////////////////////////////////////////////////////////////////
// 1. Найти проблемы в коде 
//////////////////////////////////////////////////////////////////


// Задача: заполнить массив 128 элементов числами 77, затем сначала
// напечатать первый элемент, потом просуммировать их попарно и выдать результат,
//  т.е. "77.0, 154.0, 154.0, 154.0  ...."

// #include <iostream>

// void set_array(char a[]) {
//     memset(a, 77, sizeof(a));
// }

// double* sum_pair(char a[], int idx) {
//     double s = a[idx] + a[idx+1];
//     return &s;
// }

// int main()
// {
//     const unsigned int sz = 128;
//     char a[sz] = {};
//     memset(a, 0, sizeof(a));
//     set_array(a);
//     double* s[sz] = {};
//     for (int i = -1; i < sz; ++i)
//     {
//         if (i < 0)
//             std::cout << a[0] << " ";
//         s[i] = sum_pair(a, i);
//     }
//     for (int i = 0; i < sz; ++i)
//         std::cout << s[i] << " ";
// }

#include <cstring>                      // missing `#include` (ex. `memset` requires `cstring`)
#include <iostream>

void set_array(char a[], unsigned sz) {
    memset(a, 77, sz);                  // C-style array doesn't hold length inside
}

double sum_pair(char a[], int idx) {
    return a[idx] + a[idx+1];           // returning address of stack variable
}

int main()
{
    const unsigned int sz = 128;
    char a[sz] = {};
    // memset(a, 0, sizeof(a));         // redundant array initialization
    set_array(a, sz);
    double s[sz] = {};

    // for (int i = -1; i < sz; ++i)    // out of bound access (first cycle, last cycle)
    // {                                // implicit arithmetic conversion (ex. signed, unsigned comparison)
    //     if (i < 0)
    //         std::cout << a[0] << " ";
    //     s[i] = sum_pair(a, i);
    // }

    for (unsigned i = 0; i < sz; ++i)
        s[i] =
            i == 0 || i == sz - 1 ?
                a[i] :
                sum_pair(a, i);

    for (int i = 0; i < sz; ++i)
        std::cout << s[i] << " ";
    std::cout << std::endl;             // no EOL printed
}
