void merge(unsigned long arr[], unsigned long l, unsigned long m, unsigned long r) 
{ 
    unsigned long i, j, k; 
    unsigned long n1 = m - l + 1; 
    unsigned long n2 =  r - m; 
  
    unsigned long L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) R[j] = arr[m + 1+ j]; 
  
    i = 0; j = 0; k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]){ 
            arr[k] = L[i]; 
            i++; 
        } 
        else { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) { 
        arr[k] = L[i]; 
        i++; k++; 
    } 
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; k++; 
    } 
} 

void mergeSort(unsigned long arr[], unsigned long l, unsigned long r) 
{ 
    if (l < r) { 
        unsigned long m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 

void printArray(adjlist *g, unsigned long A[], unsigned long size) 
{ 
    unsigned long i; 
    for (i=0; i < size; i++) 
        printf("%d (%d) ", A[i], g->cd[A[i]+1]-g->cd[A[i]]); 
    printf("\n"); 
} 