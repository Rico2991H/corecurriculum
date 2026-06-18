#include <iostream>
#include <string>


template <typename T, typename F> void iter(T x[], const size_t len, F fun)
{
    for (int i = 0; i < len; i++)
        fun(x[i]);
}