#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main (int argc, char *argv[])
{
   int sum = 0;
   int n = 10;
   int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
   std::cout<<"Enter number of threads: ";
   int num_threads = 0;
   std::cin>>num_threads;
   high_resolution_clock::time_point t1 = high_resolution_clock::now();

   omp_set_dynamic(0);    
   omp_set_num_threads(num_threads); 
   #pragma omp parallel reduction (+:sum)
   {
        #pragma omp for
        for(int i = 0; i < n; i++){
           sum = sum + a[i];
        }
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "Time of execution " << time_span.count()<< " seconds.\n";
    printf("The total sum is %d\n\n\n", sum);
}