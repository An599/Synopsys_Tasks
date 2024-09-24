#include "merge.h" 
using namespace std;

void m_sort(vector<int> &ptr, int start, int end) {
	if (start >= end)
		return;
	m_sort(ptr, start, (start + end) / 2);
	m_sort(ptr, (start + end) / 2 + 1, end);
	merge(ptr, start, end);
}
void merge(vector<int> &ptr, int start, int end) {
	int arr1_size = (start + end) / 2 - start + 1;
	int arr2_size = end - (start + end) / 2;

	vector<int> arr1(arr1_size);
	vector<int> arr2(arr2_size);


	for (int i = 0; i < arr1_size; i++)
		arr1[i] = ptr[start + i];
	for (int i = 0; i < arr2_size; i++)
		arr2[i] = ptr[(start + end) / 2 + 1 + i];

	int i = start, j = 0, k = 0;
	while (j < arr1_size && k < arr2_size)
	{
		if (arr1[j] < arr2[k])
			ptr[i++] = arr1[j++];
		else
			ptr[i++] = arr2[k++];
	}

	while (k < arr2_size)
		ptr[i++] = arr2[k++];
	while (j < arr1_size)
		ptr[i++] = arr1[j++];
}
