#include <bits/stdc++.h>
#define MM 120
using namespace std;

int SIZE_H, SIZE_W, MAZE_H, MAZE_W, SPEED;
int grid[MM][MM], checked, dx[4]={-1,0,1,0}, dy[4]={0,1,0,-1};
char maze[MM][MM];
enum states{FREE=0, BUSY, UP, RIGHT, DOWN, LEFT};
struct walls
{
    bool up=true;
    bool right=true;
    bool down=true;
    bool left=true;
} w[MM][MM]; // wall structure for every cell in the maze

void mazeInit() // initialize the topside-walls and the rightside-walls
{
    int i, j;
    cout<<"HEIGHT: "; cin>>SIZE_H;
    MAZE_H=(SIZE_H*2)+1;
    cout<<"WIDTH: "; cin>>SIZE_W;
    MAZE_W=(SIZE_W*2)+1;
    SPEED = 60;
    for(i=0;i<=MAZE_H;i++)
        for(j=0;j<=MAZE_W;j++) maze[i][j]=' ';
    for(i=1;i<=MAZE_H;i++)
        if(i%2) maze[i][MAZE_W]='+';
        else maze[i][MAZE_W]='|';
    for(i=1;i<=MAZE_W;i++)
        if(i%2) maze[1][i]='+';
        else maze[1][i]='-';
}

void mazeDraw() // display the maze
{
	ofstream out("labirint.txt");

    for(int i=1;i<=MAZE_H;i++)
    {
        for(int j=1;j<=MAZE_W;j++) out<<maze[i][j];
        if(i < MAZE_H) out<<endl;
    }
}

bool inGrid(int i, int j) // check if this cell is NOT outside the guidance grid
{
    return (i>0&&i<=SIZE_H&&j>0&&j<=SIZE_W);
}

void gridSetup(int i, int j) // set up the guidance grid
{
    int near=0, rnd, i_n, j_n, dir[5]={0}, oc[5]={0};
    bool ok=true;
    vector< pair<int,int> > cells;
    for(int d=0;d<4;d++) // count the nearby cells
    {
        i_n=i+dx[d]; j_n=j+dy[d];
        if(inGrid(i_n,j_n)&&grid[i_n][j_n]==FREE) // check if this cell is free
        {
            near++;
            cells.push_back(make_pair(i_n,j_n)); // place it into a vector
            dir[near]=d+2;
        }
    }
    if(near==0) grid[i][j]=BUSY; // if this cell has no neighbours then mark it as BUSY
    for(int it=1;it<=near&&ok;it++) // choose a random neighbour
    {
        do
        {
            rnd=rand()%near;
        }while(oc[rnd]==1);
        oc[rnd]=1;
        grid[i][j]=dir[rnd+1]; // assign this cell a direction based on what cell is going to be checked next
        switch(grid[i][j])
            {
            case 2: // going up
                w[i][j].up=false; w[cells[rnd].first][cells[rnd].second].down=false; // if we're going up then this cell will NOT have a wall on the topside
                break;            // and the NEXT CELL which we're going to visit will NOT have a wall in the downside - logically
            case 3: // going right
                w[i][j].right=false; w[cells[rnd].first][cells[rnd].second].left=false;
                break;
            case 4: // going down
                w[i][j].down=false; w[cells[rnd].first][cells[rnd].second].up=false;
                break;
            case 5: // going left
                w[i][j].left=false; w[cells[rnd].first][cells[rnd].second].right=false;
                break;
            }
        gridSetup(cells[rnd].first,cells[rnd].second); // visit the next cell
        ok=false; // unmark this cell so that we don't randomly RECHOOSE it
        for(int k=0;k<cells.size();k++)
            if(grid[cells[k].first][cells[k].second]==FREE) ok=true;
    }
}

void mazeGenerate() // creating the maze
{
    for(int i=1;i<=SIZE_H;i++)
        for(int j=1;j<=SIZE_W;j++) // based on every wall of the grid's cells
        {
            if(w[i][j].left)
            {
                maze[i*2-1][j*2-1]='+';
                maze[i*2][j*2-1]='|';
                maze[i*2+1][j*2-1]='+';
            }
            if(w[i][j].down)
            {
                maze[i*2+1][j*2-1]='+';
                maze[i*2+1][j*2]='-';
                maze[i*2+1][j*2+1]='+';
            }
        }
}

int mouse_i, mouse_j, cheese_i, cheese_j, found[MM][MM];
queue< pair<int,int> > Q;

void placeMaC() // place mouse and cheese
{
//    do
//    {
//        mouse_i=rand()%(SIZE_H-1)+1;
//        mouse_j=rand()%(SIZE_W-1)+1;
//    }while(maze[mouse_i][mouse_j]!=' ');
    mouse_i = mouse_j = 2;
    maze[mouse_i][mouse_j]='S'; found[mouse_i][mouse_j]=1;
//    do
//    {
//        cheese_i=rand()%(SIZE_H-1)+1;
//        cheese_j=rand()%(SIZE_W-1)+1;
//    }while(maze[cheese_i][cheese_j]!=' ');
    cheese_i = MAZE_H-1; cheese_j = MAZE_W-1;
    maze[cheese_i][cheese_j]='F';
}

void findCheese() // lee's algorithm
{
    int i, j, iu, ju;
    bool over=false;
    Q.push(make_pair(mouse_i,mouse_j)); // place the starting position
    while(!Q.empty()&&!over)
    {
        i=Q.front().first; j=Q.front().second; // we're now at this coordinates
        Q.pop();
        for(int d=0;d<4;d++) // look for every nearby cell
        {
            iu=i+dx[d]; ju=j+dy[d]; // neighbour
            if((maze[iu][ju]==' '||maze[iu][ju]=='o')&&found[iu][ju]==0) // check if it's a free cell
            {
                found[iu][ju]=found[i][j]+1; // mark the number of steps until here
                Q.push(make_pair(iu,ju)); // place in queue
                if(maze[iu][ju]=='F') over=true; // found the cheese
            }
        }
    }
}

vector< pair<int,int> > T;

void makeTrace() // from cheese to mouse
{
    int i, j, iu, ju, n;
    bool over=false;
    T.push_back(make_pair(cheese_i,cheese_j)); // starting from the cheese's position
    while(!over)
    {
        n=T.size()-1;
        i=T[n].first; j=T[n].second; // we're at this position
        for(int d=0;d<4;d++) // check every neighbour
        {
            iu=i+dx[d]; ju=j+dy[d];
            if(found[iu][ju]==found[i][j]-1&&(iu>=0&&ju>=0&&iu<MAZE_H&&ju<MAZE_W)) // it's a part of our trace
            {
                T.push_back(make_pair(iu,ju)); // add in the trace vector
                break;
            }
        }
        if(iu==mouse_i&&ju==mouse_j) over=true;
    }
}

int main()
{
    srand(time(NULL));
    mazeInit();
    gridSetup(1,1);
    mazeGenerate();
    placeMaC();
    mazeDraw();

    return 0;
}
