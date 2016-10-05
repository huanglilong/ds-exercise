/*
 * Author		: huang li long <huanglilongwk@outlook.com>
 * Time			: 2016/10/05
*/

/*
 * Problem 1.5
 Write a recursive function that returns the number of 1 in the binary representation
 of N. Use the fact that this is equal to the number of 1 in the representation of N/2,
 plus 1, if N is odd.
*/

#include <iostream>

using namespace std;

int binary_nums(unsigned int n);

int main()
{
	unsigned int n;
	int nums = 0;
	cout << "please enter n: ";
	cin >> n;
	nums = binary_nums(n);
	cout << "the numbers of ones：" << nums << endl;
}

int binary_nums(unsigned int n)
{
	if (n == 0)
		return 0;
	return binary_nums(n / 2) + n % 2;
}
