#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

void read_vector(vector<int>& A, int n);
void print_vector(const vector<int>& A);
void bubble_sort(vector<int>& A);                // O(n^2)
void insertion_sort(vector<int>& A);             // O(n^2)
void selection_sort(vector<int>& A);             // O(n^2)
void merge(vector<int>& A, int l, int m, int r); // O(n)
void merge_sort(vector<int>& A, int l, int r);   // O(n log n)

int main() 
{
    srand(static_cast<unsigned>(time(nullptr))); // static_cast<unsigned>(...) Μετατρέπει το
    // time_t σε unsigned int, που είναι ο τύπος που περιμένει η srand.

    const int n = 5;
    vector<int> arr; //o vector εχει αρχικο μεγεθος 0

    read_vector(arr, n);

    cout<<"Initial array\n";
    print_vector(arr);

    //Κάνουμε αντίγραφα ώστε κάθε αλγόριθμος να δουλεύει στο ίδιο αρχικό ΜΗ ταξινομημένο vector
    auto v1 = arr; // οι αλλαγές στο v1 δεν επηρεάζουν το arr.

    bubble_sort(v1);

    cout << "\nSorted by Bubble Sort (ascending)\n";
    print_vector(v1);

    auto v2 = arr;
    insertion_sort(v2);

    cout << "\nSorted by Insertion Sort (ascending)\n";
    print_vector(v2);

    auto v3 = arr;
    selection_sort(v3);

    cout << "\nSorted by Selection Sort (ascending)\n";
    print_vector(v3);

    auto v4 = arr;

    merge_sort(v4, 0,static_cast<int>(v4.size())-1); //τα ορίσματα της merge_sort είναι το διάνυσμα v4, η αρχική και η τελική του θέση

    cout << "\nSorted by Merge Sort (ascending)\n";
    print_vector(v4);

    return 0;
}

void read_vector(vector<int> & A,int n) 
// Με αναφορά όπως εδώ ταξινομεί το ίδιο vector που έχει ο καλών δηλ. το main διότι το Α ειναι ψευδώνυμο του arr ότι
//κάνω στο vector A γινεται στο arr γιατι ειναι το ιδιο ακριβως vector 
// Με τιμή // δημιουργείται αντίγραφο. Η συνάρτηση θα ταξινομήσει το
// αντίγραφο και ο καλών δεν θα δει αλλαγές (εκτός αν // επιστρέψουμε τον vector).
{
    A.resize(n); // μεγαλώνει/μικραίνει το vector ώστε να έχει ακριβώς n στοιχεία

    for (int i = 0; i < n; ++i)
        A[i] = rand() % 10 + 1; // 1..10
}

void print_vector(const vector<int>& A) //Η δήλση const αναφορά εγγυάται ότι η συνάρτηση δεν θα τροποποιεί τα δεδομένα.
{
    for (int x : A) // σε καθε επανάληψη στο x μπαίνει ενα στοιχείο του vector A
        cout << x << "\t";

    cout << '\n';
}

void bubble_sort(vector<int>& A)
{
    int n = static_cast<int>(A.size()); //A.size() επιστρέφει αποτέλεσμα τύπου size_t (unsigned).
    // Άρα μετατρέπουμε ρητά το μέγεθος σε int για να τ αιριάζειτο κάνουμε για Αποφυγή warnings σφαλμάτων αν συγκρίνουμε int με size_t θα πάρουμε warnings
    // (signed/unsigned).
    bool swapped;

    for (int b = 1; b<n; b++) 
    {
        swapped = false;

        for (int i = 0; i < n - b; ++i)
            if (A[i] > A[i + 1]) 
            {
                swap(A[i], A[i+1]); // καλειται η έτοιμη συνάρτηση swap για εναλλαγή των A[i] και Α[i+1]
                swapped = true;
            }

        if (!swapped) //if (swapped==false)
            break; // ήδη ταξινομημένος πίνακας
    }
}

void insertion_sort(vector<int>& A)
{
    int n = static_cast<int>(A.size());

    for (int i = 1; i < n; ++i) //αρχίζουμε απο το 2ο στοιχείο του vector
    {
        int key = A[i]; //στο key μπαίνει το στοιχείο που θέλουμε κάθε φορά να ταξινομείται
        int j = i - 1;

        while (j>=0 && A[j]>key) //όσο υπάρχει αριστερά απο το key ένα στοιχείο που ειναι μεγαλύτερο αυτού κάνω δεξιό shift των στοιχείων
        {
            A[j+1] = A[j];
            j--;
        }

        A[j+1] = key; //στη θέση j+1 μπαίνει το στοιχείο πυο ταξινομείται
    }
}

void selection_sort(vector<int>& A) 
{
    int n = static_cast<int>(A.size());

    for (int i=0;i<n-1;i++) 
    {
        int min_idx=i;//στο min_idx είναι η θέση του στοιχείου πυο κάθε φορά ταξινομείται

        for (int j = i + 1; j < n; ++j) //βρίσκουμε το min στοιχείο απο τα επόμενα στοιχεία δεξιά
            if (A[j] < A[min_idx]) //αν υπάρχει μικρότερο στοιχείο από αυτό που υποθέσαμε ως ελάχιστο
                min_idx = j; //στο min_idx μπαίνει η θέση του

        if (min_idx != i) //αν όντως βρέθηκε διαφορετικό ελέχιστο τότε κάνουμε την εναλαλγή
            swap(A[i], A[min_idx]);
    }
}

void merge_sort(vector<int>& A, int left, int right)
{
    if (left >= right)
        return;

    int m = left + (right - left) / 2; // θέση μεσαίου στοιχείου

    merge_sort(A, left, m); // Αναδρομική κλήση στο αριστερό μισό του Α

    merge_sort(A, m + 1, right); //αναδρομική κλήση στο δεξιό μισό του Α

    merge(A, left, m, right); //συγχώνευση με ταξινόμηση των 2 vector
}

void merge(vector<int>& A, int left, int m, int right) 
{
    int n1 = m - left + 1; // μέγεθος αριστερού vector
    int n2 = right - m;     // μέγεθος δεξιού vector

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = A[left + i]; // γεμίζει ο αριστερός vector με το αριστερό μισό του Α

    for (int j = 0; j < n2; ++j)
        R[j] = A[m + 1 + j]; // γεμίζει ο δεξιός vector με το δεξιό μισό του Α

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) // όσο υπάρχουν στοιχεία στα 2 vector
    {
        if (L[i] <= R[j]) // το μικρότερο στοιχείο μπαίνει στο vector A
            A[k++] = L[i++];
        else // το μικρότερο στοιχείο μπαίνει στο vector A
            A[k++] = R[j++];
    }

    while (i < n1) // υπάρχουν περισσεούμενα στοιχεία στο vector
                   // L και αντιγράφονται στο τέλος του vector A
        A[k++] = L[i++];

    while (j < n2) // υπάρχουν περισσεούμενα στοιχεία στο vector
                   // R και αντιγράφονται στο τέλος του vector A
        A[k++] = R[j++];
}
