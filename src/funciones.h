void bubble0(int *, int) __attribute__((optimize(0)));
void bubble1(int *, int) __attribute__((optimize(1)));
void bubble2(int *, int) __attribute__((optimize(2)));
void bubble3(int *, int) __attribute__((optimize(3)));

//Algoritmo Quicksort de la wikipedia
int colocar0(int *, int, int) __attribute__((optimize(0)));
void quicksort0(int *, int, int)__attribute__((optimize(0)));
int colocar1(int *, int, int) __attribute__((optimize(1)));
void quicksort1(int *, int, int)__attribute__((optimize(1)));
int colocar2(int *, int, int) __attribute__((optimize(2)));
void quicksort2(int *, int, int)__attribute__((optimize(2)));
int colocar3(int *, int, int) __attribute__((optimize(3)));
void quicksort3(int *, int, int)__attribute__((optimize(3)));

// http://www.cprogramming.com/tutorial/computersciencetheory/sorting2.html
void selection0(int *array, int len) __attribute__((optimize(0)));
void selection1(int *array, int len) __attribute__((optimize(1)));
void selection2(int *array, int len) __attribute__((optimize(2)));
void selection3(int *array, int len) __attribute__((optimize(3)));