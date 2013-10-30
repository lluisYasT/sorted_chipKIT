#define N_ORDENAR 12 // Numero de funciones para ordenar

void bubble0(int *, int) __attribute__((optimize(0)));
void bubble1(int *, int) __attribute__((optimize(1)));
void bubble2(int *, int) __attribute__((optimize(2)));
void bubble3(int *, int) __attribute__((optimize(3)));

//Algoritmo Quicksort de la wikipedia
void quick0(int *, int);
void quick1(int *, int);
void quick2(int *, int);
void quick3(int *, int);
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

struct  algoritmo {
	char *nombre;
	void (*funcion)(int *, int);
};

struct algoritmo funcion_ordenar[N_ORDENAR] = 
	{
		{"Bubble0", &bubble0},
		{"Bubble1", &bubble1},
		{"Bubble2", &bubble2},
		{"Bubble3", &bubble3},
		{"Quick0", &quick0},
		{"Quick1", &quick1},
		{"Quick2", &quick2},
		{"Quick3", &quick3},
		{"Selection0", &selection0},
		{"Selection1", &selection1},
		{"Selection2", &selection2},
		{"Selection3", &selection3}
	};

// funcion_ordenar[0] = {"Bubble0", &bubble0};
// funcion_ordenar[1].nombre = "Bubble1";
// funcion_ordenar[1].funcion = &bubble1;
// funcion_ordenar[2].nombre = "Bubble2";
// funcion_ordenar[2].funcion = &bubble2;
// funcion_ordenar[3].nombre = "Bubble3";
// funcion_ordenar[3].funcion = &bubble3;
// 
// funcion_ordenar[4].nombre = "Quick0";
// funcion_ordenar[4].funcion = &quick0;
// funcion_ordenar[5].nombre = "Quick1";
// funcion_ordenar[5].funcion = &quick1;
// funcion_ordenar[6].nombre = "Quick2";
// funcion_ordenar[6].funcion = &quick2;
// funcion_ordenar[7].nombre = "Quick3";
// funcion_ordenar[7].funcion = &quick3;
// 
// funcion_ordenar[8].nombre = "Selection0";
// funcion_ordenar[8].funcion = &selection0;
// funcion_ordenar[9].nombre = "Selection1";
// funcion_ordenar[9].funcion = &selection1;
// funcion_ordenar[10].nombre = "Selection2";
// funcion_ordenar[10].funcion = &selection2;
// funcion_ordenar[11].nombre = "Selection3";
// funcion_ordenar[11].funcion = &selection3;
