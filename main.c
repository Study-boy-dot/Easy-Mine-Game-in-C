#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define true 1
#define false 0
#define Nmax 30
int n;
int m;
void produce(char real[n][n],char show[n][n]);
int check(char real[n][n],char show[n][n],int row,int col, int click);
int gameFinished(char map[n][n]);
void gameloop(char real_map[n][n], char user_map[n][n]);

int main(int argc,char *argv[])
{
    n=5;
    m=10;
    if (m>=n*n || n==1 || m==0) {printf("Error\n"); return 0;};
    if (n>Nmax) {printf("n is too large"); return 0;}
    char real[n][n],show[n][n];
    int i,j;

    // Print out user map
    printf("%dx%d map with %d bombs\n", n, n, m);
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            real[i][j]='0';
            show[i][j]='?';
            printf("%c ", show[i][j]);
        }
        printf("\n");
    }
    putchar('\n');
    produce(real,show);
    gameloop(real, show);
    return 0;
}

void produce(char real[n][n],char show[n][n])
{
    int x,y,first,second,i,row,col,j,a,count;
    srand(time(NULL));
    for(i=0;i<m;i++){
        first=rand()%n;
        second=rand()%n;
        if (real[first][second]=='*') {i=i-1;continue;}
        real[first][second]='*';
        for(x=-1;x<2;x++){
            if (first==0 && x==-1) continue;
            else if (first==n-1 && x==1) continue;
            for(y=-1;y<2;y++){
                if (second==0 && y==-1) continue;
                else if (second==n-1 && y==1) continue;
                else if ((x==0 && y==0) || real[first][second]=='*') continue;
                else real[first][second]+=1;
            }
        }
    }

    printf("Mine location\n");
    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
            if (j!=n-1) printf("%c ",real[i][j]);
            else printf("%c\n",real[i][j]);
        }
    putchar('\n');
    // label:
    // scanf("%d", &row);
    // scanf("%d", &col);
    // if (show[row][col]!='?') {printf("You have clicked\n");goto label;};
    // while(!mapIsDone(show))
    // {
    //     check(real, show, row, col, 1);
    //     for(int i=0;i<n;i++)
    //         for(int j=0;j<n;j++){
    //             if (j!=n-1) printf("%c ",show[i][j]);
    //             else printf("%c\n",show[i][j]);
    //         }
    //     putchar('\n');
    // }
    // while(check(real,show,row,col, 1)){
    //     count=0;
    //     //system("clear");
    //     // Print mine map
    //     for(i=0;i<n;i++)
    //         for(j=0;j<n;j++){
    //             if (j!=n-1) printf("%c ",show[i][j]);
    //             else printf("%c\n",show[i][j]);
    //         }
    //     putchar('\n');
    //     return;
    // }
}

void gameloop(char real_map[n][n], char user_map[n][n])
{
    // Main game loop
    // Game stop when clicked the bombs or game finished
    int row=0, col=0;
    
    while(!gameFinished(real_map))
    {
        printf("row:");
        scanf("%d", &row);
        printf("col:");
        scanf("%d", &col);
        if(user_map[row][col] != '?')
        {
            printf("You have clicked\n");
            continue;
        }
        int game_status = check(real_map, user_map, row, col, 1);

        if(!game_status)
        {
            exit(0);
        }
        
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                if (j!=n-1) printf("%c ",user_map[i][j]);
                else printf("%c\n",user_map[i][j]);
            }
        putchar('\n');
    }
    printf("Game Finished\n");

}

int check(char real[n][n],char show[n][n],int row,int col, int click)
{
    int i,j,a;
    if (row<0 || row >n-1 || col<0 || col>n-1) return false;
    if (click == 1 && real[row][col]=='*'){
        // Show correct answer
        printf("You are dead\nCorrect answer:\n");
        for(i=0;i<n;i++)
            for(j=0;j<n;j++){
                real[i][j];
                if (j!=n-1) printf("%c ",real[i][j]);
                else printf("%c\n",real[i][j]);}
        putchar('\n');
        return false;
    }
    // Spread linked none mine element
    if (real[row][col]=='0'){
        show[row][col]='-';
        real[row][col]='-';
        check(real,show,row-1,col, 0);
        check(real,show,row+1,col, 0);
        check(real,show,row,col-1, 0);
        check(real,show,row,col+1, 0);
        // check(real,show,row-1,col-1, 0);
        // check(real,show,row+1,col+1, 0);
        // check(real,show,row+1,col-1, 0);
        // check(real,show,row-1,col+1, 0);
    }
    else if (real[row][col]=='-') return true;
    // else {show[row][col]=real[row][col];}
    return true;
}

int gameFinished(char map[n][n])
{
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            if(map[i][j] == '0')
            {
                return 0;
            }
        }
    }
    return 1;
}

