#define _CRT_SECURE_NO_WARNINGS
#define ColSortFunc 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
void buffer_clear()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
void swap(int* ptr1, int* ptr2)
{
	int buf = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = buf;
}
void copy_ar(int* ar1, int* ar2, int n)
{
	for (int i = 0; i < n; i++)
	{
		ar1[i] = ar2[i];
	}
}
int* new_copy_arr(int* ar, int n)
{
	int* arn = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) arn[i] = ar[i];
	return arn;
}
void outxchr(int n, char c)
{
	for (int i = 0; i < n; i++) putchar(c);
}
int lend(int n)
{
	int s = 0;
	if (n < 0) { n *= -1; s++; }
	while (n > 0)
	{
		n /= 10;
		s++;
	}
	return s;
}
char* first_command(char* string)
{
	int len_com;
	for (len_com = 1; string[len_com] != ' ' && string[len_com] != '\n'; len_com++);
	char* result = (char*)malloc((len_com) * sizeof(char));
	char* ptr = result;
	for (int i = 0; i < len_com - 1; i++)
	{
		result[i] = string[i + 1];
	}
	result[len_com-1] = '\0';
	return result;
}
void inputer() { printf("Input error!\nTry again\n"); }
int cmpfunc(const void* a, const void* b)
{
	const int* A = (int*)a, * B = (int*)b;
	return (*A > *B) - (*A < *B);
}



void help()
{
	printf("Command list:\n");
	printf("1) -help\n2) -goida\n3) -shakesort\n4) -vstavkisort\n5) -sortsravn\n6) -superstring\n7) -sumpow2\n8) -Shellsort\n9) -csort\n10) -end\n");
	return;
}
void goida()
{
	printf("GOGOGOiDADADA\nZDDZZDZZZZWAZWWSVOSVOSVSVOSVOSOVSOVOSVOVOVO\nGoIdA\n");
	return;
}
void wrongcommand()
{
	printf("That command doesnt exist\nTo see command list input [-help]\n");
}


// обычная сортировка
void vstavkisort(int* ar, int n, int* srav_count, int* peres_count, double* time, int outflag)
{
	clock_t start = clock();
	int sr = 1, per = 1, j, temp;
	for (int i = 1; i < n; i++)
	{
		sr++;
		j = i;
		temp = ar[j];
		per+=2;

		sr++;
		while (j > 0 && temp < ar[j - 1])
		{
			sr += 2;
			ar[j]=ar[j - 1];
			per++;
			j--;
		}
		ar[j] = temp;
		per++;
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
// задача 3 двунаправленная шейкер сортировка
void shakesort(int* ar, int n, int* srav_count, int* peres_count, double* time, int outflag)
{
	clock_t start = clock();
	int sr = 0;
	int per = 3;
	int l = 0, r = n - 1, direction = 1;
	int max, min, id;
	while (l <= r)
	{
		sr++;
		if (direction++ % 2)
		{
			int max = ar[l];
			int id = l;
			per += 4;
			for (int i = l; i <= r; i++)
			{
				if (ar[i] >= max)
				{
					max = ar[i];
					id = i;
					per += 2;
				}
				sr += 2;

			}
			sr++;
			per++;
			for (int i = id; i < r; i++)
			{
				ar[i] = ar[i + 1];
				sr++;
				per++;
			}
			sr++;
			ar[r] = max;
			per++;
			r--;
		}
		else
		{
			int min = ar[r];
			int id = r;
			per += 4;
			for (int i = l; i <= r; i++)
			{
				if (ar[i] < min)
				{
					min = ar[i];
					id = i;
					per += 2;
				}
				sr += 2;
			}
			sr++;
			for (int i = id; i > l; i--)
			{
				ar[i] = ar[i - 1];
				sr++;
				per++;
			}
			sr++;
			ar[l] = min;
			per++;
			l++;
		}
		sr++;
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
//сортировка методом Шелла (Залача 4)
void shellsort(int* ar, int n, int* srav_count, int* peres_count, double* time, int outflag)
{
	clock_t start = clock();

	int sr = 1, per = 2;

	int gap1, gap2, temp, h;
	int* gaps = (int*)malloc(sizeof(int) * (int)(log(n) / log(2)) * 2 + 10);
	int count = 0, i = 0;
	while (1)
	{
		sr++;
		gap1 = 9 * ((1 << (2 * i)) - (1 << i)) + 1;;
		gap2 = (1 << (2 * (i + 2))) - 3 * (1 << (i + 2)) + 1;
		per += 2;
		if (gap1 < n)
		{
			gaps[count++] = gap1; per++;
		}
		if (gap2 < n && gap1 != gap2)
		{
			gaps[count++] = gap2; per++;
		}
		sr += 4;
		if (gap1 >= n && gap2 >= n)
			break;
		i++;
	}
	qsort(gaps, count, sizeof(int), cmpfunc);
	if (outflag)
	{
		printf("\n%d Gaps: ", count);
		for (int j = 0; j < count; j++)
			printf("%d ", gaps[j]);
		putchar('\n');
	}
	per++;
	sr++;
	for (int f = count - 1; f >= 0; f--)
	{
		sr++;
		int inter = gaps[f];
		per += 2;
		sr++;
		for (int j = inter; j < n; j++)
		{
			sr++;
			temp = ar[j];
			per++;

			per++;
			sr++;
			for (h = j; h >= inter && ar[h - inter] > temp; h = h - inter)
			{
				sr += 2;
				per+=2;
				ar[h] = ar[h - inter];
			}
			ar[h] = temp;
			per++;
		}
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


int next_permutation(int* array, int n) {
	int i = n - 2;
	while (i >= 0 && array[i] >= array[i + 1]) {
		i--;
	}
	if (i < 0) {
		return 0;
	}
	int j = n - 1;
	while (array[j] <= array[i]) {
		j--;
	}
	int temp = array[i];
	array[i] = array[j];
	array[j] = temp;
	int left = i + 1;
	int right = n - 1;
	while (left < right) {
		temp = array[left];
		array[left] = array[right];
		array[right] = temp;
		left++;
		right--;
	}

	return 1;
}
int dlina_ob(char* str1, char* str2)
{
	int len1 = strlen(str1), len2 = strlen(str2);
	int count = 0;
	for (int i = 1; i <= len1 && i <= len2; i++)
	{
		int l = len1 - i;
		int flag = 1;
		for (int j = 0; j < i && flag; j++)
		{
			if (str1[l + j] != str2[j]) flag = 0;
		}
		if (flag) count = i;
	}
	return count;
}
// задача 1 супер строка
void superstring()
{
	int n;
	printf("Enter count strings:\n");
	scanf("%d", &n);
	buffer_clear();
	while (n < 0)
	{
		inputer();
		scanf("%d", &n);
		buffer_clear();
	}
	char** ar = (char**)malloc(n * sizeof(char*));
	printf("Enter %d strings:\n", n);

	int flag = 1;
	while (flag) 
	{
		flag = 0;
		for (int i = 0; i < n; i++)
		{
			
			ar[i] = (char*)malloc(100 * sizeof(char));
			
			if (fgets(ar[i], 100, stdin)==NULL || strchr(ar[i],'\n')==ar[i])
			{
				for (int j = 0; j <= i; j++) free(ar[j]);
				flag = 1;
				inputer();
				break;
			}
			char* ptrj = strchr(ar[i], '\n');
			if (ptrj) *ptrj = '\0';
		}
	}
	
	printf("Matrix:\n");
	int* mat = (int*)malloc(n * n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j) { mat[i * n + j] = 0; printf("0 "); }
			else { printf("%d ", mat[i * n + j] = dlina_ob(ar[i], ar[j])); }
		}
		putchar('\n');
	}
	int* ind = (int*)malloc(n * sizeof(n));
	int* strind = (int*)malloc(n * sizeof(n));
	int dlina_min = n * 100;
	int dlina;
	for (int i = 0; i < n; i++) ind[i] = i;
	do
	{
		dlina = strlen(ar[ind[0]]);
		for (int i = 1; i < n; i++)
		{
			dlina = dlina + strlen(ar[ind[i]]) - mat[n * ind[i - 1] + ind[i]];
		}
		if (dlina < dlina_min)
		{
			dlina_min = dlina;
			copy_ar(strind, ind, n);
		}



	} while (next_permutation(ind, n));
	char* vstr = (char*)malloc(n * 100);
	vstr[0] = '\0';
	strcat(vstr, ar[strind[0]]);
	char* ptre = strchr(vstr, '\0');
	for (int i = 1; i < n; i++)
	{
		for (int j = mat[n * strind[i - 1] + strind[i]]; j < strlen(ar[strind[i]]); j++)
		{
			*ptre++ = ar[strind[i]][j];
		}
	}
	*ptre = '\0';
	printf("length: %d\nstring: %s\n", dlina_min, vstr);
	free(vstr); free(ind); free(strind); free(mat);
	for (int i = 0; i < n; i++) free(ar[i]);
	free(ar);
}

// задача 2 суммы образующие степень двойки
void sumpow2(int* ar, int n)
{
	printf("n: % d\n", n);
	int space = 0;
	for (int i = 0; i < n; i++)
	{
		space += 1 + lend(ar[i]);
	}
	int count = 0;
	int subsets = 1 << n;
	long sum;
	for (int mask = 1; mask < subsets; mask++)
	{
		sum = 0;
		int spa = space;
		printf("subset: ");
		for (int i = 0; i < n; i++)
		{
			if (mask & (1 << i))
			{
				printf("%d ", ar[i]);
				spa -= lend(ar[i]) + 1;
				sum += ar[i];
			}
		}
		outxchr(spa,' ');
		printf(" sum = %d", sum);
		if (sum > 0 && !(sum & (sum - 1))) { count++; printf(" = 2^%d YES", (int)log2((double)sum)); }
		putchar('\n');
	}
	printf("\nCount: %d\n", count);
}

//Задача 5 Сортировка слов в строке
void csort()
{
	char buf[1001];
	printf("Input string:\n");
	fgets(buf, 1000, stdin);
	while (strlen(buf) < 2) { printf("string length shoule be >0\n"); fgets(buf, 1000, stdin);}
	char* nptr = strchr(buf, '\n');
	if (nptr)
	{
		*nptr++ = ' '; *nptr = '\0';
	}
	else
	{
		nptr = strchr(buf, '\0');
		*nptr++ = ' ';
		*nptr = '\0';
	}
	int wl = 0, count;
	if (buf[0] == ' ') count = 0;
	else count = 1;
	for (int i = 1; i < strlen(buf); i++)
	{
		if (buf[i] != ' ' && buf[i - 1] == ' ')
			count++;
	}
	char** ar = (char**)malloc(count * sizeof(char*));//free
	int* size = (int*)malloc(count * sizeof(int));//free
	for (int i = 0; i < count; i++) ar[i] = (char*)malloc(100 * sizeof(char));//free
	int id = 0;
	char* ptr = ar[0];
	for (int i = 0; i < strlen(buf); i++)
	{
		if (buf[i] != ' ')
		{
			wl++;
			*ptr++ = buf[i];
		}
		if (buf[i] == ' ' && buf[i - 1] != ' ')
		{
			size[id] = wl;
			*ptr = '\0';
			id++;
			ptr = ar[id];
			wl = 0;
		}
	}
	int temp, j;
	char* tempptr;
	for (int i = 1; i < count; i++)
	{
		temp = size[i];
		tempptr = ar[i];
		j = i;
		while (j > 0 && size[j - 1] > temp)
		{
			ar[j] = ar[j - 1];
			size[j] = size[j - 1];
			j--;
		}
		ar[j] = tempptr;
		size[j] = temp;
	}
	for (int i = 0; i < count; i++)
	{
		printf("%s ", ar[i]);
		outxchr(size[count - 1] - size[i], ' ');
		printf(" | length: % d\n", size[i]);
	}
	free(size);
	for (int i = 0; i < count; i++) free(ar[i]);
	free(ar);
}

//Все сортировки
void sortsravn(int* ar, int n, int* srav_count, int* peres_count, double* time, int outflag)
{
	void (*funcs_array[ColSortFunc])(int*, int, int*, int*, double*, int) = { vstavkisort , shakesort, shellsort };
	char name[ColSortFunc][20] = { "vstavkisort","shakesort","shellsort"};
	int srav_all = 0, peres_all = 0;
	double time_all = 0;
	int srav, peres;
	double timesort;
	int* car = (int*)malloc(n*sizeof(int));
	for (int i = 0; i < ColSortFunc; i++)
	{
		copy_ar(car,ar,n);
		printf("%s\n", name[i]);
		funcs_array[i](car, n, &srav, &peres, &timesort, 0);
		printf("srav: %d peres: %d time: %f\n", srav, peres, timesort);
		srav_all += srav; peres_all += peres; time_all += timesort;
	}
	free(car);
}




int* arvvod(int* lenar)
{
	int n = -1;
	char nonbaseinput[10];
	int* ar = NULL;
	printf("Input massive length:\n");
	scanf("%d", &n);
	buffer_clear();
	while (n < 0)
	{
		inputer();
		scanf("%d", &n);
		buffer_clear();
	}
	*lenar = n;
	ar = (int*)malloc(n * sizeof(n));
	printf("Ways to set massive: -elements or -rand or -file\n"); //file realisation 
	while (1)
	{
		fgets(nonbaseinput, 10, stdin);
		if (nonbaseinput[0] == '-')
		{
			if (!strcmp(first_command(nonbaseinput), "rand"))
			{
				int a, b;
				printf("Input rand min and rand max:\n");
				if (scanf("%d %d", &a, &b) == 2)
				{
					buffer_clear();
					srand(time(NULL));
					printf("Massive:\n");
					for (int i = 0; i < n; i++)
					{
						ar[i] = rand() % (b - a + 1) + a;
						printf("%d ", ar[i]);
					}
					putchar('\n');
					break;
				}
				buffer_clear();
			}
			if (!strcmp(first_command(nonbaseinput), "elements"))
			{
				printf("Input %d elements:\n", n); 
				int flag = 1;
				for (int i = 0; i < n; i++)
				{
					if (scanf("%d", ar + i) != 1)
					{
						flag = 0; break;
					}
				}
				buffer_clear();
				if (flag) break;
			}
			if (!strcmp(first_command(nonbaseinput), "file"))
			{
				printf("no realisation\n");
				break;
			}

		}
		printf("enter: -elements or -rand or -file\n");
	}
	return ar;

}

void vvod() //long long type sr per
{
	char str[100];
	int sr;
	int per;
	int lenar;
	double tim;

	while (1)
	{
		fgets(str, 100, stdin);
		if (str[0] == '-')
		{
			char* fc = first_command(str);
			if (!strcmp(fc, "help")) help();
			else if (!strcmp(fc, "end")) { printf("End of programm\nbyby\n"); free(fc); return; }
			else if (!strcmp(fc, "goida")) goida();
			else if (!strcmp(fc, "shakesort")) 
			{
				int* ar = arvvod(&lenar);
				shakesort(ar, lenar, &sr, &per, &tim, 1);
				free(ar);
			}
			else if (!strcmp(fc, "vstavkisort"))
			{
				int* ar = arvvod(&lenar);
				vstavkisort(ar, lenar, &sr, &per, &tim, 1);
				free(ar);
			}
			else if (!strcmp(fc, "shellsort"))
			{
				int* ar = arvvod(&lenar);
				shellsort(ar, lenar, &sr, &per, &tim, 1);
				free(ar);
			}
			else if (!strcmp(fc, "sortsravn"))
			{
				int* ar = arvvod(&lenar);
				sortsravn(ar, lenar, &sr, &per, &tim, 1);
				free(ar);
			}
			else if (!strcmp(fc, "superstring")) superstring();
			else if (!strcmp(fc, "csort")) csort();
			else if (!strcmp(fc, "sumpow2"))
			{
				int* ar = arvvod(&lenar);
				sumpow2(ar, lenar);
				free(ar);
			}

			else wrongcommand();
			free(fc);
		}
	}
	

}

int password()
{
	char buf[100];
	int s = 0;
	while (1)
	{
		fgets(buf,100,stdin);
		char* ptrb = strchr(buf, '\n');
		if (ptrb) *ptrb = '\0';
		if (!strcmp(buf, "1234") || !strcmp(buf, "admin!") || !strcmp(buf, "QwQ")) return 1;
		else
		{
			if (s > 4)
				return 0;
			else
			{
				s++; printf("Wrong Password!\nTry again\n");
			}
		}
	}
}
void welcome()
{
	printf("Welcome to Module2 Console Programm!!\n");
	printf("To login to programm, enter password:\n");
	if (password())
	{

		printf("Congratulations!!!!!\nCommand input format:\n<-[command] [atributs] ... >\n");
		vvod();
	}
	else printf("OBMANSHEHEEHEHKKK!!!!! poka!\n");
}


int main()
{
	welcome();
}
