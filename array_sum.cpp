#include <stdio.h>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main (int argc, char *argv[])
{
    int sum = 0;
    int n = 10000;
    int a[n];
    for(int i=0;i<n;i++)
        a[i]=rand()%10;
    auto start = steady_clock::now();
    for(int i = 0; i < n; i++)
        sum = sum + a[i];

    auto end = steady_clock::now();
    printf("%\nTime elapsed: %7.4f", (double)duration_cast<microseconds>(end - start).count() / 1000000.0);
    printf("The total sum is %d\n\n\n", sum);
}