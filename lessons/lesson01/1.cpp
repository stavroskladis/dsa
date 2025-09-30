#include <iostream>
using namespace std;

void read_array(int A[], int n);
void print_array(int A[], int n);
void bubble_sort(int A[], int n);
void insertion_sort(int A[], int n);
void selection_sort(int A[], int n);
void merge(int A[], int l, int m, int r);
void merge_sort(int A[], int l, int r);

int main() {
    const int n = 5;
    int A[n];
    srand(time(NULL));

    read_array(A, n);

    cout << "Intial Array" << endl;
    print_array(A, n);

    bubble_sort(A, n);

    cout << "\nSorted Array by BubbleSort" << endl;
    print_array(A, n);

    insertion_sort(A, n);

    cout << "\nSorted Array by InsertionSort" << endl;
    print_array(A, n);

    selection_sort(A, n);

    cout << "\nSorted Array by SelectionSort" << endl;
    print_array(A, n);

    merge_sort(A, 0, n - 1);

    cout << "\nSorted Array by MergeSort" << endl;
    print_array(A, n);

    return 0;
}

void read_array(int A[], int n) {
    for (int i = 0; i < n; i++)
        A[i] = rand() % 10 + 1;
}

void print_array(int A[], int n) {
    for (int i = 0; i < n; i++)
        cout << A[i] << "\t";
}

void bubble_sort(int A[], int n) // O(n^2)
{
    int temp;
    bool swap;

    for (int b = 1; b < n; b++) // bimata
    {
        swap = false; // ypotheto oti o pinakas einai hdh
                      // taxinomimenos

        for (int i = 0; i < n - b; i++) // sygkriseis
            if (A[i] < A[i + 1])        // fthinousa seira
            {
                temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
                swap = true;
            }

        if (swap == false)
            break; // exodos apo exoteriko brogxo
    }
}

void insertion_sort(int A[], int n) // O(n^2)
{

    for (int i = 1; i < n; i++) // stoixeia tou pinaka
    {
        int key =
            A[i]; // to key einai to stoixeio pou taxinomeitai

        int j = i - 1; // proigoumeno thesi

        while (j >= 0 &&
               A[j] > key) // oso h synhikti einai true yparxoun
        // sta aristera tou mikrotera stoixeia
        {
            A[j + 1] = A[j]; // dexio shift
            j--;             // j=1
        }

        A[j + 1] = key; // sth thesi j+1 mpainei to stoixeio
                        // taxinomisis
    }
}

void selection_sort(int A[], int n) // O(n^2)
{
    for (int i = 0; i < n - 1; i++) // stoixeia tou pinaka
    {
        int min_idx = i; // ypotetjoume oti to stoixeio sti
                         // thesi i einai to min
        int key = A[i];

        for (int j = i + 1; j < n;
             j++) // entopizoume to min apo ta ypoloipa
            // dexia tou stoixeia
            if (A[j] < key)
                min_idx = j;

        // enallasoume to stoixeio sti thesi i me to pragmatiko
        // min
        int temp = A[i];
        A[i] = A[min_idx];
        A[min_idx] = temp;
    }
}

void merge_sort(int A[], int l,
                int r) // to l=aristero kai r=dexio akro
{
    if (l >= r)
        return;

    int m = (l + r) / 2; // enallaktika l+(r-1)/2 Thesi mesaiou

    merge_sort(A, l, m);
    merge_sort(A, m + 1, r);
    merge(A, l, m, r);
}

void merge(int A[], int l, int m, int r) {
    int n1 = m - l + 1; // megethos aristerou ypopinaka
    int n2 = r - m;     // megethos dexiou ypopinaka

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) // gemizei o aristeros pinakas
        L[i] = A[l + i];

    for (int j = 0; j < n2; j++) // gemizei o dexios pinakas
        R[j] = A[m + 1 + j];

    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2) { // ayth h epanalipsi kanei th
                               // synenosi me taxinomisi
        if (L[i] < R[j])
            A[k] = L[i++]; // to mikrotero stoixeio tis
                           // sygkrishs mpainei ston A
        else
            A[k] = R[j++]; // to mikrotero stoixeio tis
                           // sygkrishs mpainei ston A

        k++;
    }

    while (i < n1) // an sto aristero ypopinaka yparxoyn
                   //  perisseouymena stoixeia kai ta
                   //  topothetouem ston A
    {
        A[k++] = L[i++];
    }

    while (j < n2) // an sto dexio ypopinaka yparxoyn
                   //  perisseouymena stoixeia kai ta
                   //  topothetouem ston A
    {
        A[k++] = R[j++];
    }
}