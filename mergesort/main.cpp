#include "merge.h"  
using namespace std;

void main() {
	int n, q;
	cout << "Input size of the array" << endl;
	do { cin >> n; } while (n < 1 && n>30);
	vector<int> arr(n);
	cout << "Input items of the array" << endl;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	m_sort(arr, 0, n - 1);
	cout << "Sorted array" << endl;
	for(int i =0; i<n;i++)
		cout << arr[i]<< endl;
	cout << "Input the item you want to find in array" << endl;
	cin >> q; 
	cout << "The item's index is"<< binary_s(arr, n, q) << endl;
}