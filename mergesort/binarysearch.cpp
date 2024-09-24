#include "merge.h" 

int binary_s(vector<int>& ptr, int n, int q)
{
	int left = 0;
	int right = n - 1;
	int mid;

	while (left <= right) {
		mid = (left + right) / 2;
		if (ptr[mid] == q)
			return mid;
		if (ptr[mid] < q)
			left = mid + 1;
		else if (ptr[mid] > q)
			right = mid - 1;
		else
			return mid;
	}
	return(-1);
}