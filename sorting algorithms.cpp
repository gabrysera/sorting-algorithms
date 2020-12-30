#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <math.h>
#include <stdio.h>
using namespace std;
int size_vector(vector<int>& elements)
{
    return static_cast<int>(elements.size());
}
void fill_vector(vector<int>& elements)
{
    int size = 16;
    for (int i = 0; i < size; i++)
    {
        elements.push_back(rand() % 20);
    }
}
bool is_sorted(vector<int>& elements)
{
    for (int i = 0; i < size_vector(elements)-1; i++)
    {
        if (elements[i] > elements[i + 1])
            return false;
    }
    return true;
}
void swap(vector<int>& elements, int a, int b)
{
    const int c = elements[a];
    elements[a] = elements[b];
    elements[b] = c;
}

void display_vector(vector<int>& elements)
{
    for (int i = 0; i < elements.size(); i++)
    {
        cout << elements[i] << "  ";
    }
    cout << endl;
}

void pushup(vector<int>& elements, int element)
{
    while (element > 0 && elements[floor((element - 1) / 2)] < elements[element])
    {
        swap(elements, element, floor((element - 1) / 2));
        element = floor((element - 1) / 2);
    }
}

void build_heap(vector<int>& elements)
{
    for (int i = 1; i < size_vector(elements); i++)
    {
        pushup(elements, i);
    }
}

void push_down(vector<int>& elements, int unsorted)
{
    int i = 0;
    int j_1 = 2 * (i + 1);
    int j_2 = 2 * (i + 1) - 1;
    int j;
    while ((j_1 < size_vector(elements) || j_2 < size_vector(elements)) && (elements[i] < elements[j_2] || elements[i] < elements[j_1]) && (j_1 <= unsorted || j_2 <= unsorted))
    {
        if (j_1 >= size_vector(elements) || j_1 >= unsorted)
            j = j_2;
        else if (elements[j_1] > elements[j_2])
            j = j_1;
        else
            j = j_2;
            swap(elements, i, j);
            i = j;
            j_1 = 2 * (i + 1);
            j_2 = 2 * (i + 1) - 1;
    }
}

void pick_heap(vector<int>& elements)
{
    int unsorted = size_vector(elements) - 1;
    while (unsorted > 0)
    {
        swap(elements, 0, unsorted);
        
        unsorted--;
        push_down(elements, unsorted); 
    }
}

void heap_sort(vector<int>& elements)
{
    build_heap(elements);
    pick_heap(elements);
}

void DNF(vector<int>& elements, int first, int last, int& red, int& blue)
{
    int white = last + 1;
    blue = last + 1;
    red = first - 1;
    int pivot = elements[first+(last-first)/2];
    while (red < white - 1)
    {
        int next = white - 1;
        if (elements[next] < pivot)
        {
            red++;
            swap(elements, next, red);
        }
        else if (elements[next] == pivot)
            white--;
        else if (elements[next] > pivot)
        {
            white--;
            blue--;
            swap(elements, next, blue);
        }
    }
}
void quick_sort(vector<int>& elements, int first, int last)
{
    assert(first >= 0 && last < size_vector(elements));
    if (first >= last)
        return;
    int red, blue;
    DNF(elements, first, last, red, blue);
    quick_sort(elements, first, red);
    quick_sort(elements, blue, last);
}
void DNFOrange(vector<int>& elements, int first, int last, int& red, int& blue)
{
    int white = first-1;
    blue = last + 1;
    red = first - 1;
    int pivot = elements[first + (last - first) / 2];
    while (white - 1  - blue < 0 )
    {
        int next = white+1;
        if (elements[next] < pivot)
        {
            red++;
            white++;
            swap(elements, next, red);
        }
        else if (elements[next] == pivot)
            white++;
        else if (elements[next] > pivot)
        {
            blue--;
            swap(elements, next, blue);
        }
    }
}
void quick_sortOrange(vector<int>& elements, int first, int last)
{
    assert(first >= 0 && last < size_vector(elements));
    if (first >= last)
        return;
    int red, blue;
    DNFOrange(elements, first, last, red, blue);
    quick_sort(elements, first, red);
    quick_sort(elements, blue, last);
}
int largest(vector<int>& elements, int low, int up)
{
    if (low >= up)
        return low ;
    const int pos = largest(elements, low + 1, up);
    if (elements[low] > elements[pos])
        return low;
    else
        return pos;
}
void sort(vector<int>& elements, int n)
{
    if (n > 1)
    {
        const int pos = largest(elements, 0, n - 1);
        swap(elements, pos, n - 1);
        sort(elements, n - 1);
    }
}
void merge(vector<int>& elements, int first, int last, int pivot)
{
    int n1 = pivot - first + 1;
    int n2 = last - pivot;
    vector<int> A;
    vector<int> B;
    int k = first;
    for (int i = 0; i < n1; i++)
    {
        A.push_back(elements[k]);
        k++;
    }
    k = pivot + 1;
    for (int i = 0; i < n2; i++)
    {
        B.push_back(elements[k]);
        k++;
    }
    k = first;
    int i = 0;
    int j = 0;
    while (i < n1 && j < n2)
    {
        if (A[i] <= B[j])
        {
            elements[k] = A[i];
            k++;
            i++;
        }
        else
        {
            elements[k] = B[j];
            k++;
            j++;
        }
    }
    while (i < n1)
    {
        elements[k] = A[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        elements[k] = B[j];
        j++;
        k++;
    }
}
void merge_sort(vector<int>& elements, int first, int last)
{
    if (first >= last)
        return;
    if (first < last)
    {
        int pivot = (last - (last - first) / 2)-1;
        merge_sort(elements, first, pivot);
        merge_sort(elements, pivot + 1, last);
        merge(elements, first, last, pivot);
    }
    return;
}
int main()
{
    vector<int> elements;
    vector<int> A;
    vector<int> B;
    fill_vector(elements);
    int last = elements.size() - 1;
    //heap_sort(elements);
    //quick_sort(elements,0,last);
    //quick_sortOrange(elements, 0, last);
    display_vector(elements);
    merge_sort(elements, 0, last);
    cout << endl;
    display_vector(elements);
    if (is_sorted(elements))
        cout << "sorted";
    else
        cout << "nope";
    return 0;
}

