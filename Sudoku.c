#include <stdio.h>
#define N 9
typedef int Grid[N][N];
void printGrid(Grid g);
int solve(Grid g, int x, int y);
int isSafe(Grid g, int x, int y, int k);
int main() {
   Grid g = { { 1, 0, 0, 4, 0, 0, 7, 0, 0 },
         { 0, 2, 0, 0, 5, 0, 0, 8, 0 },
         { 0, 0, 3, 0, 0, 6, 0, 0, 9 },
         { 0, 1, 0, 0, 4, 0, 0, 7, 0 },
         { 0, 0, 2, 0, 0, 5, 0, 0, 8 },
         { 9, 0, 0, 3, 0, 0, 6, 0, 0 },
         { 7, 0, 0, 0, 0, 8, 0, 0, 2 },
         { 8, 0, 0, 2, 0, 0, 9, 0, 0 },
         { 0, 9, 0, 0, 7, 0, 0, 1, 0 } };
   printGrid(g);
   solve(g, 0, 0) ? (printGrid(g), 0) : printf("This grid is unsolveable\n");
   return 0;
}
void printGrid(Grid g) {
   int i, j;
   for (i = 0; i < N; ++i) {
      for (j = 0; j < N; ++j)
         printf("%-4d", g[i][j]);
      putchar('\n');
   }
   putchar('\n');
}
int solve(Grid g, int x, int y) {
   int k;
   if (x == N - 1 && y == N) 
      return 1;
   else if (y == N) 
      return solve(g, x + 1, 0);
   else if (g[x][y] > 0) 
      return solve(g, x, y + 1);

   for (k = 1; k <= N; ++k)
      if (isSafe(g, x, y, k)) {
         g[x][y] = k;
         if (solve(g, x, y + 1)) return 1;
      }

   g[x][y] = 0;
   
   return 0;
}
int isSafe(Grid g, int x, int y, int k) {
   int i, j, startRow, startCol;
   startRow = x - x % 3;
   startCol = y - y % 3;
   // checking row
   for (j = 0; j < N; ++j)
      if (g[x][j] == k) return 0; // not safe

   // checking col
   for (i = 0; i < N; ++i)
      if (g[i][y] == k) return 0; // not safe

   // checking square
   for (i = startRow; i < startRow + 3; ++i)
      for (j = startCol; j < startCol + 3; ++j)
         if (g[i][j] == k) return 0; // not safe

   return 1; // safe
}