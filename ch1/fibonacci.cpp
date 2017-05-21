#include <iostream>

using namespace std;

int fib_table(int n, int *prev);
int fib_dynamic(int n);

int main(int argc, char *argv[])
{
    int n, prev;
    cout << "n : ";
    cin >> n;
    cout << "fib_table : " << fib_table(n, &prev) << endl;
    cout << "fib_dynamic : " << fib_dynamic(n) << endl;
}

int fib_table(int n, int *prev){
    if(n == 0){
        *prev = 1;
        return 0;
    }
    int prevprev;
    *prev = fib_table(n-1, &prevprev);
    return *prev+prevprev;
}

int fib_dynamic(int n)
{
    int g = 0; // f(0) = 0;
    int f = 1; // f(1) = 1;
    while(n-- > 0)
    {
        f += g;
        g = f - g;
    }
    return g;
}