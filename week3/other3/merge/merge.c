#include <stdio.h>
#include <math.h>

void mergeSort(int arr[], int len, int off);

int main(void)
{
    int len = 7;
    int nums[] = {7, 1, 5, 4, 3, 9, 8};

    mergeSort(nums, len, 0);
}

// Implement merge sort (ascending) on array arr of length len
// Off is an offset to map arr index overwrites to correct locations (not strictly necessary)
void mergeSort(int arr[], int len, int off)
{
    // If array has only one value return (end of halving)
    if (len == 1)
    {
        return;
    }

    // Get middle index of array
    int mid = len / 2;

    // Get lengths of left and right halves
    int llen = mid;
    int rlen = len - mid;

    // Initialize arrays to hold halves
    int left[llen];
    int right[rlen];

    // Populate left half
    for (int i = 0; i < llen; i++)
    {
        left[i] = arr[i];
    }

    // Populate right half
    for (int i = 0; i < rlen; i++)
    {
        right[i] = arr[mid + i];
    }

    // Recursively pass left and right halves
    mergeSort(left, llen, off);
    mergeSort(right, rlen, off + mid);

    // Initialize sorting variables
    int k = 0;
    int li = 0;
    int ri = 0;

    // While within arr bounds
    while (k < rlen + llen)
    {
        if (li >= llen)
        {
            // if left depleted add remaining from right
            for (int i = 0; i < rlen - ri; i++)
            {
                // printf("Setting arr[%i] to %i\n", k + off, right[ri + i]);
                arr[k] = right[ri + i];
                k++;
            }
        }
        else if (ri >= rlen)
        {
            // if right depleted add remaining from left
            for (int i = 0; i < llen - li; i++)
            {
                // printf("Setting arr[%i] to %i\n", k + off, left[li + i]);
                arr[k] = left[li + i];
                k++;
            }
        }
        else
        {
            // Compare values in left and right arrays
            if (left[li] < right[ri])
            {
                // If left < right sort left value, increment index in left array
                arr[k] = left[li];
                // printf("Setting arr[%i] to %i\n", k + off, left[li]);
                li++;
            }
            else
            {
                // If right < left sort right value, increment index in right array
                arr[k] = right[ri];
                // printf("Setting arr[%i] to %i\n", k + off, right[ri]);
                ri++;
            }
            k++;
        }
    }
}