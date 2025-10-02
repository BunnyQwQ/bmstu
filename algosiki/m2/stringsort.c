#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
int main()
{
	char s[100];
	printf("Enter string:\n");
	fgets(s, 100, stdin);
	char* pn = strpbrk(s,"\n ");
	*pn = '\0';
	int n = strlen(s);

	//сортировка букв пузырьком
	char min;
	int ind;
	for (int i = 0; i < n; i++)
	{
		min = s[i];
		ind = i;
		for (int j = i + 1; j < n; j++)
		{
			if (s[j] < min) { min = s[j]; ind = j; }
		}
		for (int j = ind; j > i; j--)
		{
			s[j] = s[j - 1];
		}
		s[i] = min;
	}
	printf("Sorted string:\n");
	printf("%s", s);
}
