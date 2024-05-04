#include <stdio.h>
#include <stdlib.h>
//source:https://rosettacode.org/wiki/N-queens_problem#C
//Available under GNU Free Document License 1.3 as stated in the source
int count = 0;
void solve(int n, int col, int *hist)
{
	if (col == n) {
		//printf("\nNo. %d\n-----\n", ++count);
		//for (int i = 0; i < n; i++, putchar('\n'))
		//	for (int j = 0; j < n; j++)
		//		putchar(j == hist[i] ? 'Q' : ((i + j) & 1) ? ' ' : '.');
                count++;
		return;
	}
 
#	define attack(i, j) (hist[j] == i || abs(hist[j] - i) == col - j)
	for (int i = 0, j = 0; i < n; i++) {
		for (j = 0; j < col && !attack(i, j); j++);
			if (j < col) continue;
			hist[col] = i;
		solve(n, col + 1, hist);
	}
}
 
int main(int n, char **argv)
{
	n = 10;
	int hist[n];
	solve(n, 0, hist);
	printf("Number of solutions = %d\n",count);
}
