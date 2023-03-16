class order
{
    static int  part(int *vet, int left, int right, bool inc);
    static void rquicksort(int *vet, int left, int right, bool inc);
    static void merge(int* vet, int left, int right, bool inc);
    static void rmergesort(int* vet, int left, int right, bool inc);
    static void modheap(int* vet, int n, int i, bool inc);
    public:
    static void shell_sort(int *x, bool inc, int n);
    static void selection_sort(int *x, bool inc, int n);
    static void bubble_sort(int *x,bool inc , int n);
   static void insertion(int *x,bool inc , int n);
    static void quicksort(int *x,bool inc , int n);
    static void mergesort(int *x, bool inc, int n);
    static void heapsort(int *x,bool inc, int n);
};
