void heap(int* ar, int n, int id)
{
	int max = id;
	int left = 2 * id + 1, right = 2 * id + 2;
	if (left < n && ar[left]>ar[max]) max = left;
	if (right < n && ar[right]>ar[max]) max = right;
	if (max != id)
	{
		swap(ar + id, ar + max);
		heap(ar, n, max);
	}
}



void heapsort(int* ar, int n, int* srav_count, int* peres_count, double* time, int outflag)
{
	clock_t start = clock();
	int sr = 0;
	int per = 0;
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heap(ar, n, i);
	}
	for (int i = n - 1; i >= 0; i--)
	{
		swap(ar,ar+i);
		heap(ar, i, 0);
	}



	

	clock_t end = clock();
	double ti = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
	if (outflag)
	{
		printf("sorted massive:\n");
		for (int i = 0; i < n; i++) printf("%d ", ar[i]);
		putchar('\n');
		printf("srav: %d\nperes: %d\ntime: %f\n", sr, per, ti);
	}
	*srav_count = sr;
	*peres_count = per;
	*time = ti;
}
