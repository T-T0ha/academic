
#include <bits/stdc++.h>
#include <graphics.h>
#define N 9
using namespace std;
int checkSquare(int row, int col, int num);
int checkRow(int row, int col, int num);
int checkCol(int row, int col, int num);
int solveSudoku(int row, int col);
int solveDiagonalSudoku(int x, int y);
void fillMatrix(char difficulty);
void fillDiagonalBox();
void fillThreeByThreeBox(int row, int col);
void copyMatrix(int mat[][N], int copy[][N]);
int timer();
void save();
void load();
int score(int lives, int time_taken);
void navigate(const int &keyPressed, int &activex, int &activey, int &tempx, int &tempy);
void displayGameScreen(const int &activex, const int &activey, int time, int savedtime);
bool savingScreen(int time,char difficulty);
int loadingScreen(char difficulty);
char menuScreen();
int loadGame(int gameNum,char difficulty);
void saveGame(int gameNum,char difficulty);
bool isValid(int x, int y, int num);
void matInitialization();
char difficultyscreen();
void readFromFile(string filepath, int arr[][N]);
void writeToFile(string filepath, int arr[][N], int time);
char winningScreen(int time);
void highScore(int newTime);
void displayGameScreenForInput(const int &activex, const int &activey);

int mat[N][N], solution[N][N], locked[N][N], scoreArr[3];

void matInitialization()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            mat[i][j] = 0;
            solution[i][j] = 0;
            locked[i][j] = 0;
        }
    }
}

bool isValid(int row, int col, int num)
{
    if (checkSquare(row, col, num) || checkCol(row, col, num) || checkRow(row, col, num))
        return false;
    else
        return true;
}

int checkCol(int row, int col, int num)
{
    for (int i = 0; i < 9; i++)
    {
        if (mat[row][i] == num)
            return 1;
    }
    return 0;
}

int checkRow(int row, int col, int num)
{
    for (int i = 0; i < 9; i++)
    {
        if (mat[i][col] == num)
            return 1;
    }
    return 0;
}

int checkSquare(int row, int col, int num)
{
    if (row < 3)
        row = 0;
    else if (row < 6)
        row = 3;
    else
        row = 6;
    if (col < 3)
        col = 0;
    else if (col < 6)
        col = 3;
    else
        col = 6;
    for (int i = row; i < row + 3; i++)
    {
        for (int j = col; j < col + 3; j++)
        {
            if (mat[i][j] == num)
            {
                return 1;
            }
        }
    }
    return 0;
}



void rotateMat(int x,int y)
{
    int temp,dummyMat[3][3];
    for(int i=0; i<3; i++)
    {

        for(int j=0; j<3; j++)
        {

            dummyMat[i][j]=mat[j][i];
        }
    }
    for(int i=0; i<3; i++)
    {

        for(int j=0; j<3; j++)
        {
            mat[i][j]=dummyMat[i][j];
        }
    }
}

int checkDiagonal(int row, int col, int num)
{
  int arr[8];
  int k = 0;
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (i == j && i != row && j != col)
      {
        arr[k] = mat[i][j];
        k++;
      }
    }
  }
  for (int i = 0; i < 8; i++)
  {
    if (arr[i] == num)
      return 1;
  }
  return 0;
}

int checkDiagonalTheOtherOne(int row, int col, int num)
{
  int arr[8];
  int k = 0;
  for (int i = 0; i < 9; i++)
  {
    for (int j = 8; j >= 0; j--)
    {
      if (i + j == 8 && i != row && j != col)
      {
        arr[k] = mat[i][j];
        k++;
        break;
      }
    }
  }
  for (int i = 0; i < 8; i++)
  {
    if (arr[i] == num)
      return 1;
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
            }
            while (checkSquare(row, col, num));

            mat[row + i][col + j] = num;
        }
    }
}

void fillDiagonalBox()
{
    //for (int i = 0; i < N; i = i + 3)
    fillThreeByThreeBox(0, 0);
    rotateMat(0,0);
    fillThreeByThreeBox(6,3);
}


int solveSudoku(int row, int col)
{
    int num = 9;
    int tempx = 0;
    int tempy = 0;
    if (mat[row][col] != 0)
    {
        if (row == 8 && col == 8)
        {
            return 1;
        }
        if (row < 8)
            row++;
        else
        {
            if (col < 8)
            {
                row = 0;
                col++;
            }
        }
        if (solveSudoku(row, col))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if (mat[row][col] == 0)
    {
        while (num > 0)
        {
            if (!checkCol(row, col, num) && !checkRow(row, col, num) && !checkSquare(row, col, num))
            {
                mat[row][col] = num;
                if (row == 8 && col == 8)
                {
                    return 1;
                }
                if (row < 8)
                {
                    tempx = row + 1;
                }
                else
                {
                    if (col < 8)
                    {
                        tempx = 0;
                        tempy = col + 1;
                    }
                }
                if (solveSudoku(tempx, tempy))
                {
                    return 1;
                }
            }
            num--;
        }
        mat[row][col] = 0;
        return 0;
    }
}


int solveDiagonalSudoku(int row, int col)
{
  int num = 9;
  int tempx = 0;
  int tempy = 0;
  if (mat[row][col] != 0)
  {
    if (row == 8 && col == 8)
    {
      return 1;
    }
    if (row < 8)
      row++;
    else
    {
      if (col < 8)
      {
        row = 0;
        col++;
      }
    }
    if (solveDiagonalSudoku(row, col))
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  if (mat[row][col] == 0)
  {
    while (num > 0)
    {
      if (row == col && row != 4)
      {
        if (!checkCol(row, col, num) && !checkRow(row, col, num) && !checkSquare(row, col, num) && !checkDiagonal(row, col, num))
        {
          mat[row][col] = num;
          if (row == 8 && col == 8)
          {
            return 1;
          }
          if (row < 8)
          {
            tempx = row + 1;
          }
          else
          {
            if (col < 8)
            {
              tempx = 0;
              tempy = col + 1;
            }
          }
          if (solveDiagonalSudoku(tempx, tempy))
          {
            return 1;
          }
        }
      }
      else if ((row == 0 && col == 8) || (row == 1 && col== 7) || (row == 2 && col == 6) || (row == 3 && col == 5) || (row == 5 && col == 3) || (row == 6 && col== 2) || (row == 7 && col == 1) || (row == 8 && col== 0))
      {
        if (!checkCol(row, col, num) && !checkRow(row, col, num) && !checkSquare(row, col, num) && !checkDiagonalTheOtherOne(row, col, num))
        {

          mat[row][col] = num;
          if (row == 8 && col == 8)
          {
            return 1;
          }
          if (row < 8)
          {
            tempx = row + 1;
          }
          else
          {
            if (col < 8)
            {
              tempx = 0;
              tempy = col + 1;
            }
          }
          if (solveDiagonalSudoku(tempx, tempy))
          {
            return 1;
          }

        }
      }
      else if ((row == 4 && col == 4))
      {
        if (!checkCol(row, col, num) && !checkRow(row, col, num) && !checkSquare(row, col, num) && !checkDiagonal(row, col, num) && !checkDiagonalTheOtherOne(row, col, num))
        {
          mat[row][col] = num;
          if (row == 8 && col == 8)
          {
            return 1;
          }
          if (row < 8)
          {
            tempx = row + 1;
          }
          else
          {
            if (col < 8)
            {
              tempx = 0;
              tempy = col + 1;
            }
          }
          if (solveDiagonalSudoku(tempx, tempy))
          {
            return 1;
          }
        }
      }
      else
      {
        if (!checkCol(row, col, num) && !checkRow(row, col, num) && !checkSquare(row, col, num))
        {
          mat[row][col] = num;
          if (row == 8 && col == 8)
          {
            return 1;
          }
          if (row < 8)
          {
            tempx = row + 1;
          }
          else
          {
            if (col < 8)
            {
              tempx = 0;
              tempy = col + 1;
            }
          }
          if (solveDiagonalSudoku(tempx, tempy))
          {
            return 1;
          }
        }
      }
      num--;
    }
    mat[row][col] = 0;
    return 0;
  }
}


void removeKDigits(char difficulty)
{
    int i, j, a = 9, b = 9, cell;
    srand(time(NULL));
    int count;
    if (difficulty == '1')
        count = 30;
    else if (difficulty == '2')
        count = 45;
    else if (difficulty == '3')
        count = 60;
    else if  (difficulty=='4')
        count=60;

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

void fillMatrix(char difficulty)
{
    if(difficulty=='4')
    {
        //cout<<"Running";
        fillDiagonalBox();
        int x=solveDiagonalSudoku(0,0);
        copyMatrix(mat, solution);
        removeKDigits(difficulty);
        copyMatrix(mat,locked);
    }
    else
    {
        fillDiagonalBox();
        solveSudoku(0, 0);
        copyMatrix(mat, solution);
        removeKDigits(difficulty);
        copyMatrix(mat, locked);
    }
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
void copyMatrix(int mat[][N], int copy[][N])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            copy[i][j] = mat[i][j];
        }
    }
}
bool winner()
{
    bool k = true;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (mat[i][j] != solution[i][j])
                k = false;
        }
    }
    return k;
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

void saveGame(int gameNum, int time,char difficulty)
{
    string gamefile, solutionfile, lockedfile;
    if(difficulty=='1')
    {
        if (gameNum == 1)
        {
            gamefile = "txt/games/easy/game1.txt";
            solutionfile = "txt/solutions/easy/solution1.txt";
            lockedfile = "txt/locks/easy/locked1.txt";
        }
        else if (gameNum == 2)
        {
            gamefile = "txt/games/easy/game2.txt";
            solutionfile = "txt/solutions/easy/solution2.txt";
            lockedfile = "txt/locks/easy/locked2.txt";
        }
        else
        {
            gamefile = "txt/games/easy/game3.txt";
            solutionfile = "txt/solutions/easy/solution3.txt";
            lockedfile = "txt/locks/easy/locked3.txt";
        }
    }
    else if(difficulty=='2')
    {
        if (gameNum == 1)
        {
            gamefile = "txt/games/mid/game1.txt";
            solutionfile = "txt/solutions/mid/solution1.txt";
            lockedfile = "txt/locks/mid/locked1.txt";
        }
        else if (gameNum == 2)
        {
            gamefile = "txt/games/mid/game2.txt";
            solutionfile = "txt/solutions/mid/solution2.txt";
            lockedfile = "txt/locks/mid/locked2.txt";
        }
        else
        {
            gamefile = "txt/games/mid/game3.txt";
            solutionfile = "txt/solutions/mid/solution3.txt";
            lockedfile = "txt/locks/mid/locked3.txt";
        }
    }
    else if(difficulty=='3')
    {
        if (gameNum == 1)
        {
            gamefile = "txt/games/hard/game1.txt";
            solutionfile = "txt/solutions/hard/solution1.txt";
            lockedfile = "txt/locks/hard/locked1.txt";
        }
        else if (gameNum == 2)
        {
            gamefile = "txt/games/hard/game2.txt";
            solutionfile = "txt/solutions/hard/solution2.txt";
            lockedfile = "txt/locks/hard/locked2.txt";
        }
        else
        {
            gamefile = "txt/games/hard/game3.txt";
            solutionfile = "txt/solutions/hard/solution3.txt";
            lockedfile = "txt/locks/hard/locked3.txt";
        }
    }
    else if(difficulty=='4')
    {
        if (gameNum == 1)
        {
            gamefile = "txt/games/master/game1.txt";
            solutionfile = "txt/solutions/master/solution1.txt";
            lockedfile = "txt/locks/master/locked1.txt";
        }
        else if (gameNum == 2)
        {
            gamefile = "txt/games/master/game2.txt";
            solutionfile = "txt/solutions/master/solution2.txt";
            lockedfile = "txt/locks/master/locked1.txt";
        }
        else
        {
            gamefile = "txt/games/master/game3.txt";
            solutionfile = "txt/solutions/master/solution3.txt";
            lockedfile = "txt/locks/master/locked3.txt";
        }
    }


    writeToFile(gamefile, mat, time);
    writeToFile(solutionfile, solution, time);
    writeToFile(lockedfile, locked, time);
}


int loadGame(int gameNum,char difficulty)
{
    string gamefile, solutionfile, lockedfile;
    if(difficulty=='1')
    {
        if (gameNum == 1)
        {
            gamefile = "txt/games/easy/game1.txt";
            solutionfile = "txt/solutions/easy/solution1.txt";
            lockedfile = "txt/locks/easy/locked1.txt";
        }
        else if (gameNum == 2)
        {
            gamefile = "txt/games/easy/game2.txt";
            solutionfile = "txt/solutions/easy/solution2.txt";
            lockedfile = "txt/locks/easy/locked2.txt";
        }
        else
        {
            gamefile = "txt/games/easy/game3.txt";
            solutionfile = "txt/solutions/easy/solution3.txt";
            lockedfile = "txt/locks/easy/locked3.txt";
        }
    }
    else if(difficulty=='2')
    {
        if (gameNum == 1)
        {
            gamefile = "txt/games/mid/game1.txt";
            solutionfile = "txt/solutions/mid/solution1.txt";
            lockedfile = "txt/locks/mid/locked1.txt";
        }
        else if (gameNum == 2)
        {
            gamefile = "txt/games/mid/game2.txt";
            solutionfile = "txt/solutions/mid/solution2.txt";
            lockedfile = "txt/locks/mid/locked2.txt";
        }
        else
        {
            gamefile = "txt/games/mid/game3.txt";
            solutionfile = "txt/solutions/mid/solution3.txt";
            lockedfile = "txt/locks/mid/locked3.txt";
        }
    }
    else if(difficulty=='3')
    {
        if (gameNum == 1)
        {
            gamefile = "txt/games/hard/game1.txt";
            solutionfile = "txt/solutions/hard/solution1.txt";
            lockedfile = "txt/locks/hard/locked1.txt";
        }
        else if (gameNum == 2)
        {
            gamefile = "txt/games/hard/game2.txt";
            solutionfile = "txt/solutions/hard/solution2.txt";
            lockedfile = "txt/locks/hard/locked2.txt";
        }
        else
        {
            gamefile = "txt/games/hard/game3.txt";
            solutionfile = "txt/solutions/hard/solution3.txt";
            lockedfile = "txt/locks/hard/locked3.txt";
        }
    }
    else if(difficulty=='4')
    {
        if (gameNum == 1)
        {
            gamefile = "txt/games/master/game1.txt";
            solutionfile = "txt/solutions/master/solution1.txt";
            lockedfile = "txt/locks/master/locked1.txt";
        }
        else if (gameNum == 2)
        {
            gamefile = "txt/games/master/game2.txt";
            solutionfile = "txt/solutions/master/solution2.txt";
            lockedfile = "txt/locks/master/locked1.txt";
        }
        else
        {
            gamefile = "txt/games/master/game3.txt";
            solutionfile = "txt/solutions/master/solution3.txt";
            lockedfile = "txt/locks/master/locked3.txt";
        }
    }

    bool notEmpty = false;
    ifstream GameFile(gamefile);
    int time;
    for (int r = 0; r < 9 && !GameFile.eof(); r++)
    {
        if (r == 8)
            notEmpty = true;
        for (int c = 0; c < 9; c++)
        {
            GameFile >> mat[r][c];
        }
    }
    GameFile >> time;
    GameFile.close();
    if (!notEmpty)
        return notEmpty;
    // int tim;
    readFromFile(solutionfile, solution);
    readFromFile(lockedfile, locked);
    return time;
}


void getHighScore(char difficulty)
{
    string filename;
    if (difficulty == '1')
        filename = "txt/scores/easy.txt";
    else if (difficulty == '2')
        filename = "txt/scores/mid.txt";
    else if(difficulty=='3')
        filename = "txt/scores/hard.txt";
        else
            filename="txt/scores/master.txt";;
    ifstream fileObj(filename);
    for (int i = 0; i < 3; i++)
    {
        fileObj >> scoreArr[i];
    }
    fileObj.close();
}

void highScore(int newTime, char difficulty)
{
  string filename;
  if (difficulty == '1')
    filename = "txt/scores/easy.txt";
  else if (difficulty == '2')
    filename = "txt/scores/mid.txt";
  else if (difficulty == '3')
    filename = "txt/scores/hard.txt";
  else if(difficulty=='4')
    filename = "txt/scores/master.txt";
  ifstream inputFile(filename);
  int times[4];

  int prevTime;
  int i;
   for (i = 0;!inputFile.eof(); i++)
  {
    inputFile>>times[i];
  }
  inputFile.close();
  times[3]=newTime;

  int temp;
  for (i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i ; j++) {
            if (times[j] > times[j + 1]) {
                    temp=times[j];
                    times[j]=times[j+1];
                    times[j+1]=temp;
            }
        }
  }

  ofstream outputFile(filename);
  for (i=0;i<3;i++){
    outputFile << times[i] << endl;
  }
outputFile.close();
  }



void writeToFile(string filepath, int arr[][N], int time)
{
    ofstream fileObj(filepath);
    if (fileObj.fail())
        cout << "File Open Failed." << endl;
    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            fileObj << arr[r][c];
            if (c != 8)
                fileObj << " ";
        }
        fileObj << endl;
    }
    fileObj << time;
    fileObj.close();
}

void readFromFile(string filepath, int arr[][N])
{
    ifstream fileObj(filepath);
    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            fileObj >> arr[r][c];
        }
    }
    // int time;
    //  fileObj>>time;
    //  cout<<time<<endl;
    fileObj.close();
    // return time;
}

void showSolution()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            mat[i][j] = solution[i][j];
        }
    }
}

void newGame(char difficulty)
{
    fillMatrix(difficulty);
}

char menuScreen()
{
    cleardevice();
    // readimagefile("pic.jpg", 0, 0, 1366, 868);
    int midx = (getmaxx() / 2);
    int midy = (getmaxy() / 2);

    setcolor(LIGHTCYAN);
    setlinestyle(0, 0, 8);
    line(0, 2, getmaxx(), 2);
    rectangle(0, 0, getmaxx(), getmaxy());

    setcolor(LIGHTBLUE);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(midx - (textwidth("SUDOKU") / 2), 20, "SUDOKU");

    setcolor(LIGHTBLUE);
    settextstyle(0, HORIZ_DIR, 2);
    outtextxy(midx - textwidth("WELCOME TO SUDOKU!") / 2, midy - 50, "WELCOME TO SUDOKU!");
    outtextxy(midx - textwidth("Press N for New Game") / 2, midy - 25, "Press N for New Game");
    outtextxy(midx - textwidth("Press L to Load Game") / 2, midy, "Press L to Load Game");
    outtextxy(midx - textwidth("Press B to See LeaderBoard") / 2, midy + 25, "Press B to See LeaderBoard");
    outtextxy(midx - textwidth("Press I to Input Grid") / 2, midy + 50, "Press I to Input Grid");
    outtextxy(midx - textwidth("Press Esc to Exit Game") / 2, midy + 75, "Press Esc to Exit Game");

    char key = getch();
    // char key = getch();
    while ((!(int)key == 27) && !(key == 'n') && !(key == 'l') && !(key == 'b') && !(key == 'i'))
    {
        key = getch();
    }
    return key;
}

int loadingScreen(char difficulty)
{
    cleardevice();

    int midx = (getmaxx() / 2);
    int midy = (getmaxy() / 2);

    setcolor(YELLOW);
    setlinestyle(0, 0, 4);
    line(0, 2, getmaxx(), 2);
    rectangle(0, 0, getmaxx(), getmaxy());

    setcolor(LIGHTBLUE);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(midx - (textwidth("SUDOKU") / 2), 20, "SUDOKU");

    setcolor(LIGHTBLUE);
    settextstyle(0, HORIZ_DIR, 2);
    outtextxy(midx - textwidth("LOAD FROM?") / 2, midy - 50, "LOAD FROM?");
    outtextxy(midx - textwidth("Press 1 for Game 1") / 2, midy - 25, "Press 1 for Game 1");
    outtextxy(midx - textwidth("Press 2 for Game 2") / 2, midy, "Press 2 for Game 2");
    outtextxy(midx - textwidth("Press 3 for Game 3") / 2, midy + 25, "Press 3 for Game 3");

    char key = getch();
    while (!(key == '1') && !(key == '2') && !(key == '3'))
    {
        key = getch();
    }
    int success = loadGame((int)key - 48,difficulty);
    if (success)
        outtextxy(midx - textwidth("Game Loaded Successfully!") / 2, midy + 50, "Game Loaded Successfully!");
    else
        outtextxy(midx - textwidth("No Game To Load") / 2, midy + 50, "No Game To Load");
    delay(2000);
    return success;
}

// Save Game
bool savingScreen(int time,char difficulty)
{

    cleardevice();

    int midx = (getmaxx() / 2);
    int midy = (getmaxy() / 2);

    setcolor(YELLOW);
    setlinestyle(0, 0, 4);
    line(0, 2, getmaxx(), 2);
    rectangle(0, 0, getmaxx(), getmaxy());

    setcolor(LIGHTBLUE);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(midx - (textwidth("SUDOKU") / 2), 20, "SUDOKU");

    setcolor(LIGHTBLUE);
    settextstyle(0, HORIZ_DIR, 2);
    outtextxy(midx - textwidth("WHERE TO SAVE?") / 2, midy - 50, "WHERE TO SAVE?");
    outtextxy(midx - textwidth("Press 1 for Game 1") / 2, midy - 25, "Press 1 for Game 1");
    outtextxy(midx - textwidth("Press 2 for Game 2") / 2, midy, "Press 2 for Game 2");
    outtextxy(midx - textwidth("Press 3 for Game 3") / 2, midy + 25, "Press 3 for Game 3");

    char key = getch();
    while (!(key == '1') && !(key == '2') && !(key == '3'))
    {
        key = getch();
    }
    saveGame((int)key - 48, time,difficulty);
    outtextxy(midx - textwidth("Game Saved Successfully!") / 2, midy + 50, "Game Saved Successfully!");
    delay(2000);
    return true;
}

void showHint(const int &activex, const int &activey)
{
    if (locked[activey][activex] == 0)
    {
        mat[activey][activex] = solution[activey][activex];
    }
}

char inputGridInfo(int &activex, int &activey, int &tempx, int &tempy)
{

    matInitialization();
    bool game = true;

    //cout << "runnin";
    displayGameScreenForInput(activex, activey);
    // int tempx = -1, tempy = -1;
    while (game)
    {
        if (kbhit())
        {
            int keyPress;
            keyPress = (int)getch();
            if (keyPress == 72 || keyPress == 80 || keyPress == 75 || keyPress == 77)
            {
                navigate(keyPress, activex, activey, tempx, tempy);
            }
            else if (keyPress >= 49 && keyPress <= 57)
            {
                if (locked[activey][activex] == 0)
                {
                    int digit = keyPress - 48;
                    mat[activey][activex] = digit;
                    displayGameScreenForInput(activex, activey);
                }
            }
            else if (keyPress == 27)
                game = false;
        }
    }

    copyMatrix(mat, locked);
    solveSudoku(0, 0);
    copyMatrix(mat, solution);
    copyMatrix(locked, mat);

    char key = getch();
    while (!(key == 'p') && !(key == 'm') && !(key == 'a') && !(key == 27))
    {
        key = getch();
    }
    return key;
}

void displayGameScreenForInput(const int &activex, const int &activey)
{

    cleardevice();
    int midx = (getmaxx() / 2);
    int midy = (getmaxy() / 2);

    setcolor(YELLOW);
    setlinestyle(0, 0, 4);
    line(0, 2, getmaxx(), 2);
    rectangle(0, 0, getmaxx(), getmaxy());

    setcolor(LIGHTBLUE);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(midx - (textwidth("SUDOKU") / 2), 20, "SUDOKU");

    int gridStartX = midx - 153;
    int gridStartY = midy - 153;
    setcolor(LIGHTBLUE);
    //lines
    for (int i = gridStartX, count = 0; i <= gridStartX + 306; i += 34, count++)
    {
        if (count % 3 == 0)
            setlinestyle(0, 0, 5);
        else
            setlinestyle(0, 0, 1);
        line(i, gridStartY, i, gridStartY + 306);
    }
    for (int i = gridStartY, count = 0; i <= gridStartY + 306; i += 34, count++)
    {
        if (count % 3 == 0)
            setlinestyle(0, 0, 5);
        else
            setlinestyle(0, 0, 1);
        line(gridStartX, i, gridStartX + 306, i);
    }

    settextstyle(0, HORIZ_DIR, 3);
    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            char elem[3];
            if (mat[r][c] == 0)
                continue;

            setcolor(WHITE);
            sprintf(elem, "%d", mat[r][c]);
            outtextxy(gridStartX + 5 + c * 34, gridStartY + 8 + r * 34, elem);
        }
    }

    // char elem[3];
    settextstyle(0, HORIZ_DIR, 2);
    setcolor(LIGHTBLUE);
    // outtextxy(100, 40, elem);
    outtextxy(10, 170, "P-Play");
    outtextxy(10, 200, "M-Menu");
    outtextxy(10, 230, "A-Answer");
    outtextxy(10, 260, "Esc-Exit");
}

void displayGameScreen(const int &activex, const int &activey, int time, int savedtime)
{
    cleardevice();
    int midx = (getmaxx() / 2);
    int midy = (getmaxy() / 2);

    setcolor(YELLOW);
    setlinestyle(0, 0, 4);
    line(0, 2, getmaxx(), 2);
    rectangle(0, 0, getmaxx(), getmaxy());

    setcolor(LIGHTBLUE);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(midx - (textwidth("SUDOKU") / 2), 20, "SUDOKU");

    int gridStartX = midx - 153;
    int gridStartY = midy - 153;
    // gridwidth=306 cause 306 is can be devided by 9
    setcolor(LIGHTBLUE);

    for (int i = gridStartX, count = 0; i <= gridStartX + 306; i += 34, count++)
    {
        if (count % 3 == 0)
            setlinestyle(0, 0, 5);
        else
            setlinestyle(0, 0, 1);
        line(i, gridStartY, i, gridStartY + 306);
    }

    for (int i = gridStartY, count = 0; i <= gridStartY + 306; i += 34, count++)
    {
        if (count % 3 == 0)
            setlinestyle(0, 0, 5);
        else
            setlinestyle(0, 0, 1);
        line(gridStartX, i, gridStartX + 306, i);
    }

    settextstyle(0, HORIZ_DIR, 3);
    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            char elem[3];
            if (mat[r][c] == 0)
                continue;
            if (locked[r][c] != 0)
            {
                setcolor(WHITE);
                sprintf(elem, "%d", mat[r][c]);
                outtextxy(gridStartX + 5 + c * 34, gridStartY + 8 + r * 34, elem);
            }
            else if (mat[r][c] == solution[r][c])
            {
                // cout << mat[r][c];
                setcolor(GREEN);
                sprintf(elem, "%d", mat[r][c]);
                outtextxy(gridStartX + 5 + c * 34, gridStartY + 8 + r * 34, elem);
                // setcolor(WHITE);
            }
            else
            {
                // cout << "imp " << mat[r][c];
                setcolor(RED);
                sprintf(elem, "%d", mat[r][c]);
                outtextxy(gridStartX + 5 + c * 34, gridStartY + 8 + r * 34, elem);
                // setcolor(WHITE);
            }
        }
    }

    char elem[3];
    setcolor(LIGHTBLUE);
    settextstyle(0, HORIZ_DIR, 2);
    sprintf(elem, "%d", time + savedtime);
    outtextxy(10, 40, "Time-");
    outtextxy(100, 40, elem);
    outtextxy(10, 170, "H-Hint");
    outtextxy(10, 200, "M-Menu");
    outtextxy(10, 230, "S-Save");
    outtextxy(10, 260, "A-Answer");
    outtextxy(10, 290, "Esc-Exit");
}

char difficultyscreen()
{
    cleardevice();

    int midx = (getmaxx() / 2);
    int midy = (getmaxy() / 2);

    setcolor(YELLOW);
    setlinestyle(0, 0, 4);
    line(0, 2, getmaxx(), 2);
    rectangle(0, 0, getmaxx(), getmaxy());

    setcolor(LIGHTBLUE);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(midx - (textwidth("SUDOKU") / 2), 20, "SUDOKU");

    setcolor(LIGHTBLUE);
    settextstyle(0, HORIZ_DIR, 2);
    outtextxy(midx - textwidth("CHOOSE DIFFICULTY") / 2, midy - 50, "CHOOSE DIFFICULTY");
    outtextxy(midx - textwidth("Press 1 for Easy") / 2, midy - 25, "Press 1 for Easy");
    outtextxy(midx - textwidth("Press 2 for Medium") / 2, midy, "Press 2 for Medium");
    outtextxy(midx - textwidth("Press 3 for Hard") / 2, midy + 25, "Press 3 for Hard");
    outtextxy(midx - textwidth("Press 4 for Master(Diagonal)") / 2, midy + 50, "Press 4 for Master(Diagonal)");

    char key = getch();
    while (!(key == '1') && !(key == '2') && !(key == '3') && !(key=='4'))
    {
        key = getch();
    }
    return key;
}

char winningScreen(int time)
{
    int midx = getmaxx() / 2;
    int midy = getmaxy() / 2;
    char msg[50], elem[30];
    cleardevice();
    setcolor(GREEN);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
    sprintf(msg, "%s", "CONGRATS! YOU WON!");
    outtextxy(midx - textwidth(msg) / 2, midy - textheight(msg) / 2 - 3, msg);
    setcolor(GREEN);
    sprintf(msg, "%s", "Time taken-");
    outtextxy(midx - textwidth(msg) / 2, midy - textheight(msg) / 2 + 30, msg);
    sprintf(elem, "%d", time);
    outtextxy(midx + textwidth(msg) / 2, midy - textheight(msg) / 2 + 30, elem);
    sprintf(msg, "%s", "CONGRATS! YOU WON!");
    setcolor(WHITE);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 1);
    sprintf(msg, "%s", "Press M to go back to Main Menue.");
    outtextxy(midx - textwidth(msg) / 2, midy + textheight(msg) / 2 + 50, msg);

    char key = getch();
    while (!((int)key == 27) && !((key == 'm')))
    {
        key = getch();
    }
    return key;
}


void navigate(const int &keyPressed, int &activex, int &activey, int &tempx, int &tempy)
{

    int gridStartX = getmaxx() / 2 - 153;
    int gridStartY = getmaxy() / 2 - 153;

    if (tempx != -1)
    {
        setcolor(BLACK);
        setlinestyle(0, 0, 3);
        rectangle(
            gridStartX + tempx * 34 + 2, gridStartY + tempy * 34 + 2,
            gridStartX + (tempx + 1) * 34 - 2, gridStartY + (tempy + 1) * 34 - 2);
    }

    if (keyPressed == 72)
    {
        if (activey == 0)
            activey = 8;
        else
            activey--;
    }
    else if (keyPressed == 80)
    {
        if (activey == 8)
            activey = 0;
        else
            activey++;
    }
    else if (keyPressed == 75)
    {
        if (activex == 0)
            activex = 8;
        else
            activex--;
    }
    else if (keyPressed == 77)
    {
        if (activex == 8)
            activex = 0;
        else
            activex++;
    }

    setcolor(YELLOW);
    setlinestyle(0, 0, 3);
    tempx = activex;
    tempy = activey;
    rectangle(
        gridStartX + activex * 34 + 2, gridStartY + activey * 34 + 2,
        gridStartX + (activex + 1) * 34 - 2, gridStartY + (activey + 1) * 34 - 2);
}

char highscoreScreen()
{
    char difficulty = difficultyscreen();
    for (int i = 0; i < 3; i++)
    {
        scoreArr[i] = 0;
    }
    getHighScore(difficulty);
    cleardevice();
    int midx = (getmaxx() / 2);
    int midy = (getmaxy() / 2);

    setcolor(YELLOW);
    setlinestyle(0, 0, 4);
    line(0, 2, getmaxx(), 2);
    rectangle(0, 0, getmaxx(), getmaxy());
    char msg[50], elem[3];

    setcolor(LIGHTBLUE);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(midx - (textwidth("SUDOKU") / 2), 20, "SUDOKU");

    setcolor(LIGHTBLUE);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);

    sprintf(msg, "%s", " First - ");
    outtextxy(midx - (textwidth(msg) / 2) - 107, midy - (textheight(msg)) - 25, msg);
    sprintf(elem, "%d", scoreArr[0]);
    outtextxy(midx - (textwidth(elem) / 2), midy - (textheight(elem)) - 25, elem);
    setcolor(LIGHTBLUE);

    sprintf(msg, "%s", "Second - ");
    outtextxy(midx - (textwidth(msg) / 2) - 120, midy - (textheight(msg)), msg);
    sprintf(elem, "%d", scoreArr[1]);
    outtextxy(midx - (textwidth(elem) / 2), midy - (textheight(elem)), elem);
    setcolor(LIGHTBLUE);

    sprintf(msg, "%s", "Third - ");
    outtextxy(midx - (textwidth(msg) / 2) - 107, midy - (textheight(msg)) + 25, msg);
    sprintf(elem, "%d", scoreArr[2]);
    outtextxy(midx - (textwidth(elem) / 2), midy - (textheight(elem)) + 25, elem);
    setcolor(WHITE);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 1);
    sprintf(msg, "%s", "Press M to go back to Main Mene.");
    outtextxy(midx - textwidth(msg) / 2, midy + textheight(msg) / 2 + 50, msg);

    char key = getch();
    while (!((int)key == 27) && !((key == 'm')))
    {
        key = getch();
    }
    return key;
}

int main()
{
    int gDriver = DETECT, gMode, errorCode;
    initgraph(&gDriver, &gMode, (char *)"");
    bool program = true, gamePlay = true;
    int tim = 0, tim2 = 0;
    char difficulty;
    int activex = 0, activey = 0;
    while (program)
    {
        bool game = false;

        int tempx = -1, tempy = -1;
        char action;
        // menu
        action = menuScreen();
        if ((int)action == 27)
        {
            game = false;
            program = false;
        }
        // load saved game
        else if (action == 'l')
        {
            game = true;
            difficulty=difficultyscreen();
            tim2 = loadingScreen(difficulty);

            // cout<<time;
            if (game)
                displayGameScreen(activex, activey, tim2, 0);
        }
        //new game
        else if (action == 'n')
        {
            matInitialization();
            tim2 = 0;
            difficulty = difficultyscreen();
            newGame(difficulty);
            displayGameScreen(activex, activey, 0, tim2);

            game = true;
        }
        else if (action == 'b')
        {
            char key = highscoreScreen();
            if ((int)key == 27)
            {
                program = false;
                game = false;
            }
            else
                game = false;
        }
        else if (action == 'i')
        {
            char key = inputGridInfo(activex, activey, tempx, tempy);
            if ((int)key == 27)
            {
                program = false;
                game = false;
            }

            else if (key == 'a')
            {
                showSolution();
                displayGameScreen(activex, activey, 0, 0);
                game = true;
                gamePlay = false;
                // game=false;
            }
            else if (key == 'p')
            {
                displayGameScreen(activex, activey, 0, 0);
                game = true;
            }
            else
                game = false;
        }

        time_t seconds1 = time(NULL);
        while (game)
        {
            if (kbhit())
            {
                int keyPress = (int)getch();
                time_t seconds2 = time(NULL);
                // cout<<"Time prev--"<<tim2<<endl;
                tim = (seconds2 - seconds1);
                // cout<<"Time after--"<<tim<<endl;
                // tim2=0;
                //esc to exit
                if (int(keyPress) == 27)
                {
                    game = false;
                    program = false;
                }
                //arrow key
                else if (keyPress == 72 || keyPress == 80 || keyPress == 75 || keyPress == 77)
                {
                    navigate(keyPress, activex, activey, tempx, tempy);
                }
                else if (keyPress >= 49 && keyPress <= 57)
                {

                    //deny input in locked
                    if (locked[activey][activex] == 0)
                    {
                        int digit = keyPress - 48;
                        mat[activey][activex] = digit;
                        displayGameScreen(activex, activey, tim, tim2);
                    }
                }
                //save
                else if (keyPress == 's')
                {
                    tim = tim + tim2;
                    game = !savingScreen(tim,difficulty);
                }
                //menu
                else if (keyPress == 'm')
                    game = false;

                else if (keyPress == 'h')
                {
                    showHint(activex, activey);
                    displayGameScreen(activex, activey, tim, tim2);
                }
                else if (keyPress == 'a')
                {
                    gamePlay = false;
                    // game=false;
                    showSolution();
                    displayGameScreen(activex, activey, 9999, 9999);
                }
            }

            if (winner() && gamePlay)
            {
                // cout << tim;
                highScore(tim + tim2, difficulty);
                char key = winningScreen(tim + tim2);
                if ((int)key == 27)
                {
                    program = false;
                    game = false;
                }
                else
                    game = false;
            }
        }
    }
    closegraph();
    return 0;
}
