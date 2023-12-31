#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 9

int checkSquare(int rowStart, int colStart, int num);
int checkRow(int x, int y, int num);
int checkCol(int x, int y, int num);
int solveSudoku(int x, int y);
void fillMatrix();
void fillDiagonalBox();
void fillThreeByThreeBox(int row, int col);
void copyMatrix();
int timer();
void save();
void load();
void loadPlay();
int score(int lives, int time_taken);

int mat[N][N], copyMat[N][N];

int checkCol(int x, int y, int num)
{
  for (int i = 0; i < 9; i++)
  {
    if (mat[x][i] == num)
      return 1;
  }
  return 0;
}
int checkRow(int x, int y, int num)
{
  for (int i = 0; i < 9; i++)
  {
    if (mat[i][y] == num)
      return 1;
  }
  return 0;
}

int checkSquare(int x, int y, int num)
{
  if (x < 3)
    x = 0;
  else if (x < 6)
    x = 3;
  else
    x = 6;
  if (y < 3)
    y = 0;
  else if (y < 6)
    y = 3;
  else
    y = 6;
  for (int i = x; i < x + 3; i++)
  {
    for (int j = y; j < y + 3; j++)
    {
      if (mat[i][j] == num)
      {
        return 1;
      }
    }
  }
  return 0;
}

int randomGenerator()
{
  return rand();
}

void fillThreeByThreeBox(int row, int col)
{
  int num;
  srand(time(NULL));
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      do
      {
        num = 1 + (rand() % 9);
      } while (checkSquare(row, col, num));

      mat[row + i][col + j] = num;
    }
  }
}

void fillDiagonalBox()
{
  for (int i = 0; i < N; i = i + 3)
    fillThreeByThreeBox(i, i);
}
int solveSudoku(int x, int y)
{
  int num = 9;
  int tempx = 0;
  int tempy = 0;
  if (mat[x][y] != 0)
  {
    if (x == 8 && y == 8)
    {
      return 1;
    }
    if (x < 8)
      x++;
    else
    {
      if (y < 8)
      {
        x = 0;
        y++;
      }
    }
    if (solveSudoku(x, y))
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  if (mat[x][y] == 0)
  {
    while (num > 0)
    {
      if (!checkCol(x, y, num) && !checkRow(x, y, num) && !checkSquare(x, y, num))
      {
        mat[x][y] = num;
        if (x == 8 && y == 8)
        {
          return 1;
        }
        if (x < 8)
        {
          tempx = x + 1;
        }
        else
        {
          if (y < 8)
          {
            tempx = 0;
            tempy = y + 1;
          }
        }
        if (solveSudoku(tempx, tempy))
        {
          return 1;
        }
      }
      num--;
    }
    mat[x][y] = 0;
    return 0;
  }
}

void removeKDigits()
{
  int i, j, a = 9, b = 9, cell;
  srand(time(NULL));

  int count = 50;
  while (count != 0)
  {
    cell = rand();
    i = (cell / a) % a;
    j = cell % b;

    if (mat[i][j] != 0)
    {

      mat[i][j] = 0;
    }

    count--;
  }
}

void fillMatrix()
{
  fillDiagonalBox();
  solveSudoku(0, 0);
  copyMatrix();
  removeKDigits();
}

void printSudoku()
{
  printf("--------------------------\n");
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      printf("%d", mat[i][j]);
      printf(" ");
      if (j % 3 + 1 == 3)
      {
        printf(" | ");
      }
    }
    if (i % 3 + 1 == 3)
    {
      printf("\n");
      printf("--------------------------");
    }
    printf("\n");
  }
  printf("\n");
}
void copyMatrix()
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      copyMat[i][j] = mat[i][j];
    }
  }
}
int matCompare()
{
  int k = 0;
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (mat[i][j] == copyMat[i][j])
        k++;
    }
  }
  return k;
}
void play()
{
  time_t seconds;
  time_t seconds1;
  seconds = time(NULL);

  int lives = 3;
  fillMatrix();
  printSudoku();

  int row, col, num, moves = 300;
  char c;
  printf("Lives %d                           Time %d seconds\n", 3, 0);
  while (lives != 0)
  {
    // printf("You have %d moves left\n", moves);
    printf("Enter the row, col, and the digit for your move-\n");
    scanf("%d%d%d", &row, &col, &num);
    if (!checkCol(row - 1, col - 1, num) && !checkRow(row - 1, col - 1, num) && !checkSquare(row - 1, col - 1, num))
    {
      mat[row - 1][col - 1] = num;
      printSudoku();
      printf("Press 'P' to pause, 's' to submit or press 'Enter' to proceed.\n");
      getchar();
      c = getchar();
      scanf("%c", &c);
      if (c == 'P')
      {
        save();
        break;
      }
      else if (c == 's')
      {
        if (matCompare() == 81)
        {
          printf("     Well Done!\nSuuuiDokuu!\n");
        }

        else
        {
          printf("      Ops! Try again!\n");
        }
        break;
      }
    }
    else
    {
      printf("Warning!!\n");
      lives--;
      mat[row - 1][col - 1] = num;
      printSudoku();
      if (lives > 0)
      {
        printf("Press 'P' to pause, 's' to submit or press 'Enter' to proceed.\n");

        getchar();
        c = getchar();
        if (c == 'P')
        {
          save();
          break;
        }
        else if (c == 's')
        {
          if (matCompare() == 81)
          {
            printf("     Well Done!\nSuuuiDokuu!\n");
          }

          else
          {
            printf("     Ops! Try again!\n");
          }
          break;
        }
      }
    }
    moves--;
    seconds1 = time(NULL);
    printf("Lives %d                           Time %d seconds\n", lives, seconds1 - seconds);
  }
  printf("         GAME OVER\n");
}

void takeInputgrid()
{
  printf("Give input grid:\n");
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      scanf("%d", &mat[i][j]);
    }
  }
}

int timer()
{
  time_t seconds;
  seconds = time(NULL);
  time_t seconds1;
  seconds1 = time(NULL);
  return seconds1 - seconds;
}
void save()
{
  FILE *file = fopen("file.txt", "w");
  if (file == NULL)
  {
    return;
  }
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      fprintf(file, "%d", mat[i][j]);
      if (j < 9 - 1)
      {
        fprintf(file, " ");
      }
    }
    fprintf(file, "\n");
  }
  fclose(file);
}

void loadPlay()
{
  time_t seconds;
  time_t seconds1;
  seconds = time(NULL);

  int lives = 3;
  // fillMatrix();
  printSudoku();

  int row, col, num, moves = 300;
  char c;
  printf("Lives %d                           Time %d seconds\n", 3, 0);
  while (lives > 0)
  {
    // printf("You have %d moves left\n", moves);
    printf("Enter the row, col, and the digit for your move-\n");
    scanf("%d%d%d", &row, &col, &num);
    if (!checkCol(row - 1, col - 1, num) && !checkRow(row - 1, col - 1, num) && !checkSquare(row - 1, col - 1, num))
    {
      mat[row - 1][col - 1] = num;
      printSudoku();
      printf("Press 'P' to pause, 's' to submit or press 'Enter' to proceed.\n");
      getchar();
      c = getchar();
      scanf("%c", &c);
      if (c == 'P')
      {
        save();
        break;
      }
      else if (c == 's')
      {
        if (matCompare() == 81)
        {
          printf("     Well Done!\nSuuuiDokuu!\n");
        }

        else
        {
          printf("      Ops! Try again!\n");
        }
        break;
      }
    }
    else
    {
      printf("Warning!!\n");
      --lives;
      mat[row - 1][col - 1] = num;
      printSudoku();
      if (lives > 0)
      {
        printf("Press 'P' to pause, 's' to submit or press 'Enter' to proceed.\n");
        getchar();
        c = getchar();
        if (c == 'P')
        {
          save();
          break;
        }
        else if (c == 's')
        {
          if (matCompare() == 81)
          {
            printf("     Well Done!\nSuuuiDokuu!\n");
          }

          else
          {
            printf("     Ops! Try again!\n");
          }
          break;
        }
      }
    }
    // moves--;
    seconds1 = time(NULL);
    printf("Lives %d                           Time %d seconds\n", lives, seconds1 - seconds);
  }
  printf("         GAME OVER\n");
}

void load()
{
  int value;
  FILE *file = fopen("file.txt", "r");
  if (file == NULL)
  {
    return;
  }
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      fscanf(file, "%d", &value);
      mat[i][j] = value;
    }
  }

  fclose(file);
  loadPlay();
}

int score(int lives, int time_taken)
{
}

int main()
{
  char choice;
  printf("Press G For New Game\n");
  printf("Press R to Resume\n");
  scanf("%c", &choice);
  switch (choice)
  {
  case 'G':
    play();
    break;
  case 'R':
    load();
    break;
  }
  // save();
  // printSudoku();
  // fillMatrix();
  // takeInputgrid();
  // printSudoku();
  // play();
  // printSudoku();
  //   for(int i=0;i<9;i++){
  //     for(int j=0;j<9;j++){
  //       mat[i][j]=0;
  //     }
  //   }
  // printSudoku();

  // save();
  // solveSudoku(0, 0);
  // printSudoku();
}
