
/*
 * Author		: huang li long <huanglilongwk@gmail.com>
 * Time			: 2016/10/10
*/

/*
Question 3.11 Write a function to add two polynomials. Do not destroy the
input. Use a linked list implementation. If the polynomials have M and N terms
respectively, what is the time complexity of your program.
*/

/*
Question 3.12 Write a function to multiply two polynomials P1 and P2, with
M and N terms respectively where M ≤ N. Use a linked list implementation.
You must make sure that the output polynomial is sorted by exponent and has
at most one term of any power.
a. Give an algorithm to solve this problem in O(M^2 * N^2) time.
*b. Write a program to perform the multiplication in O(M^2 * N) time.
*c. Write a program to perform the multiplication in O(MNlog(MN)) time.
d. Which time bound above is the best?
*/

#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

list<float> add_ploy(const list<float> &lf1, const list<float> &lf2);
list<float> mul_ploy(const list<float> &lf1, const list<float> &lf2);
void list_print(const list<float> &lt);

int main()
{
    int n, m;
    list<float> nf;
    list<float> mf;
    std::cout << "please enter n: ";
    cin >> n;
    std::cout << "please enter m: ";
    cin >> m;
    std::cout << "please enter n-polynomials's parameter: ";
    for(int i=0; i<n; i++)
    {
        float a;
        std::cin >> a;
        nf.push_front(a);   // high in end
    }

    std::cout << "please enter m-polynomials's parameter: ";
    for(int i=0; i<m; i++)
    {
        float a;
        std::cin >> a;
        mf.push_front(a);
    }
    list_print(nf);
    list_print(mf);
    auto ret_list = add_ploy(nf, mf);
    list_print(ret_list);

    auto ret_mul_list = mul_ploy(nf, mf);
    list_print(ret_mul_list);
}

list<float> add_ploy(const list<float> &lf1, const list<float> &lf2)
{
    list<float> retlist;

    auto itr1 = lf1.begin();
    auto itr2 = lf2.begin();

    while(itr1 != lf1.end() && itr2 != lf2.end())
    {
        retlist.push_back(*itr1 + *itr2);
        ++itr1;
        ++itr2;
    }

    if(itr1 == lf1.end())
    {
        while(itr2 != lf2.end())
        {
            retlist.push_back(*itr2);
            ++itr2;
        }
    }

    if(itr2 == lf2.end())
    {
        while(itr1 != lf1.end())
        {
            retlist.push_back(*itr1);
            ++itr1;
        }
    }
    return retlist;
}

list<float> mul_ploy(const list<float> &lf1, const list<float> &lf2)
{
    /*
    a. Give an algorithm to solve this problem in O(M^2 * N^2) time.
    */
    list<float> temp_list;
    list<float> ret_list;
    int power = 0;
    for(auto itr1 = lf1.begin(); itr1 != lf1.end(); ++itr1)
    {   
        temp_list.clear();
        for(auto itr2 = lf2.begin(); itr2 != lf2.end(); ++itr2)
        {
            temp_list.push_back(*itr1 * *itr2);
        }
        for(int i=0; i<power; ++i)
        {
            temp_list.push_front(0);    // low parts
        }
        //list_print(temp_list);
        ++power;
        ret_list = add_ploy(ret_list, temp_list);
        //list_print(ret_list);
    }
    return ret_list;
}

void list_print(const list<float> &lt)
{
    cout << "print polynomial: ";
    int power =0;
    for(auto itr = lt.begin(); itr != lt.end(); ++itr)
    {
        if(itr != (--lt.end()))
        {
            cout << *itr << " * x^" << power << " + ";
        }
        else 
        {
            cout << *itr << " * x^" << power;
        }
        power++;
    }
    cout << endl;
}