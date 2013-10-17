#include "funciones.h"
void bubble0(int * array, int len)
{
	int c, d, swap;

	for (c = 0; c < len; c++)
  {
		for (d = 0; d < (len - c - 1); d++)
    {
			if(array[d] > array[d+1])
      {
				swap = array[d];
				array[d] = array[d+1];
				array[d+1] = swap;
			}
		}
	}
}

void bubble1(int * array, int len)
{
	int c, d, swap;

	for (c = 0; c < len; c++)
  {
		for (d = 0; d < (len - c - 1); d++)
    {
			if(array[d] > array[d+1])
      {
				swap = array[d];
				array[d] = array[d+1];
				array[d+1] = swap;
			}
		}
	}
}

void bubble2(int * array, int len)
{
	int c, d, swap;

	for (c = 0; c < len; c++)
  {
		for (d = 0; d < (len - c - 1); d++)
    {
			if(array[d] > array[d+1])
      {
				swap = array[d];
				array[d] = array[d+1];
				array[d+1] = swap;
			}
		}
	}
}

void bubble3(int * array, int len)
{
	int c, d, swap;

	for (c = 0; c < len; c++)
  {
		for (d = 0; d < (len - c - 1); d++)
    {
			if(array[d] > array[d+1])
      {
				swap = array[d];
				array[d] = array[d+1];
				array[d+1] = swap;
			}
		}
	}
}

void quick0(int * array, int len)
{
	quicksort0(array, 0, len-1);
}

void quick1(int * array, int len)
{
	quicksort1(array, 0, len-1);
}

void quick2(int * array, int len)
{
	quicksort2(array, 0, len-1);
}

void quick3(int * array, int len)
{
	quicksort3(array, 0, len-1);
}

void quicksort0(int *v, int b, int t)
{
	if(b < t)
  {
		int pivote = colocar0(v, b, t);
		quicksort0(v, b, pivote - 1);
		quicksort0(v, pivote + 1, t);
	}
}

int colocar0(int *v, int b, int t)
{
	int i;
	int pivote, valor_pivote;
	int temp;

	pivote = b;
	valor_pivote = v[pivote];
	for (i = b + 1; i <= t; i++)
	{
		if (v[i] < valor_pivote)
		{
			pivote++;
			temp = v[i];
			v[i] = v[pivote];
			v[pivote] = temp;
		}
	}
	temp = v[b];
	v[b] = v[pivote];
	v[pivote] = temp;

	return pivote;
}

void quicksort1(int *v, int b, int t)
{
	if(b < t)
  {
		int pivote = colocar1(v, b, t);
		quicksort1(v, b, pivote - 1);
		quicksort1(v, pivote + 1, t);
	}
}

int colocar1(int *v, int b, int t)
{
	int i;
	int pivote, valor_pivote;
	int temp;

	pivote = b;
	valor_pivote = v[pivote];
	for (i = b + 1; i <= t; i++)
	{
		if (v[i] < valor_pivote)
		{
			pivote++;
			temp = v[i];
			v[i] = v[pivote];
			v[pivote] = temp;
		}
	}
	temp = v[b];
	v[b] = v[pivote];
	v[pivote] = temp;

	return pivote;
}

void quicksort2(int *v, int b, int t)
{
	if(b < t)
  {
		int pivote = colocar2(v, b, t);
		quicksort2(v, b, pivote - 1);
		quicksort2(v, pivote + 1, t);
	}
}

int colocar2(int *v, int b, int t)
{
	int i;
	int pivote, valor_pivote;
	int temp;

	pivote = b;
	valor_pivote = v[pivote];
	for (i = b + 1; i <= t; i++)
	{
		if (v[i] < valor_pivote)
		{
			pivote++;
			temp = v[i];
			v[i] = v[pivote];
			v[pivote] = temp;
		}
	}
	temp = v[b];
	v[b] = v[pivote];
	v[pivote] = temp;

	return pivote;
}

void quicksort3(int *v, int b, int t)
{
	if(b < t)
  {
		int pivote = colocar3(v, b, t);
		quicksort3(v, b, pivote - 1);
		quicksort3(v, pivote + 1, t);
	}
}

int colocar3(int *v, int b, int t)
{
	int i;
	int pivote, valor_pivote;
	int temp;

	pivote = b;
	valor_pivote = v[pivote];
	for (i = b + 1; i <= t; i++)
	{
		if (v[i] < valor_pivote)
		{
			pivote++;
			temp = v[i];
			v[i] = v[pivote];
			v[pivote] = temp;
		}
	}
	temp = v[b];
	v[b] = v[pivote];
	v[pivote] = temp;

	return pivote;
}

void selection0(int *array, int len)
{
	for (int i = 0; i < len; ++i)
	{
		int index_of_min = i;
		for (int j = i; j < len; ++j)
		{
			if (array[index_of_min] > array[j])
			{
				index_of_min = j;
			}
		}
		int temp = array[i];
		array[i] = array[index_of_min];
		array[index_of_min] = temp;
	}
}

void selection1(int *array, int len)
{
	for (int i = 0; i < len; ++i)
	{
		int index_of_min = i;
		for (int j = i; j < len; ++j)
		{
			if (array[index_of_min] > array[j])
			{
				index_of_min = j;
			}
		}
		int temp = array[i];
		array[i] = array[index_of_min];
		array[index_of_min] = temp;
	}
}

void selection2(int *array, int len)
{
	for (int i = 0; i < len; ++i)
	{
		int index_of_min = i;
		for (int j = i; j < len; ++j)
		{
			if (array[index_of_min] > array[j])
			{
				index_of_min = j;
			}
		}
		int temp = array[i];
		array[i] = array[index_of_min];
		array[index_of_min] = temp;
	}
}

void selection3(int *array, int len)
{
	for (int i = 0; i < len; ++i)
	{
		int index_of_min = i;
		for (int j = i; j < len; ++j)
		{
			if (array[index_of_min] > array[j])
			{
				index_of_min = j;
			}
		}
		int temp = array[i];
		array[i] = array[index_of_min];
		array[index_of_min] = temp;
	}
}
