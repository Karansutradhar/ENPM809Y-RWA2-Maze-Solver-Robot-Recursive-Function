/**
* @file main.cpp
* @author Karan Sutradhar <kssutrad@terpmail.umd.edu>
* @version 1.0
*
* @section LICENSE
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of
* the License, or (at your option) any later version.
*
* @section DESCRIPTION
*
* This project is used to navigate a robot in a maze
*/
#include <iostream>
#include <vector>
#include <array>

using namespace std;
/**
 * @brief Function verifies if the coordinates given by user are outside the maze or not
 * @param x Current position along rows
 * @param y Current position along columns
 * @return Returns 1 if x or y goes outside the Maze
 */
int  Point_In_Maze(int x,int y);
/**
 * @brief Function checks if the coordinates matches the goal coordinates or not
 * @param x Current position along rows
 * @param y Current position along columns
 * @param goalx Coordinate of goal along rows
 * @param goaly Coordinate of goal along rows
 * @return Returns 1 if goal and start coordinates match
 */
int Goal_Position (int x,int y, int a, int b);
/**
 * @brief Function checks if the coordinates has an obstacle
 * @param x Current position along rows
 * @param y Current position along columns
 * @return Returns 1 if the coordinates lie on the obstacle
 */
int On_Obstacle (int x, int y);
/**
 * @brief Function to find a path based on given data to reach goal from start point.
 * The function checks whether the current coordinate is out side the maze.
 * Then it checks whether the current coordinate matches the goal or not
 * Then it checks whether the current position is an obstacle
 * Then function calls itself to find path first in north direction, then in East, then in South, and finally in West direction.
 * If any of these movements are possible it returns 1, then the data is saved in another vector
 * If any other movement is not possible then the function marks that location  with a 'O' and backtracks to previous locations 
 * To find the correct path to goal. When the goal is matched with the current coordinate, it returns a 1.
 * @param x Current position along rows
 * @param y Current position along columns
 * @return Returns 1 if a path is found
 */
int Find_Path (int x, int y);
/**
 * @brief Function makes a movement in the North
 * @param x Current position along rows
 * @param y Current position along columns
 * @return Returns a vector with new coordinates
 */
vector<int> Action_North (int x,int y);
/**
 * @brief Function makes a move in East
 * @param x Current position along rows
 * @param y Current position along columns
 * @return Returns a vector with new coordinates
 */
vector<int> Action_East (int x,int y);
/**
 * @brief Function makes a move in South
 * @param x Current position along rows
 * @param y Current position along columns
 * @return Returns a vector with new coordinates
 */
vector<int> Action_South (int x,int y);
/**
 * @brief Function makes a move in West
 * @param x Current position along rows
 * @param y Current position along columns
 * @return Returns a vector with new coordinates
 */
vector<int> Action_West (int x,int y);
/**
 * @brief Function checks if the coordinates entered by the user are on #(obstacle) or not
 * @param x Current position along rows
 * @param y Current position along columns
 * @return Returns 0 if there is an obstacle in the location of the coordinates
 */
int Obstacle_On_Entry(int x, int y);
/**
 * Function used to print the maze
 */
void Maze_Print();

int rowG{}; // To store x coordinate of goal
int columnG{}; // To store y coordinate of goal
vector<vector <char> > maze{
	{'#', '.', '.', '.', '#', '#'},
	{'.', '.', '#', '.', '.', '.'},
	{'#', '.', '#', '#', '.', '#'},
	{'#', '.', '#', '#', '.', '#'},
	{'.', '.', '.', '#', '#', '#'},
	{'.', '#', '#', '#', '#', '#'}};
	
int main(){
    int S1, S2, G1, G2;// int variables to store coordinates
	float D1, D2, E1, E2;
    int terminate1, terminate2 = 1; // int variables to terminate while loops
    int terminate4, terminate5 = 0; // int variables to terminate while loops
    cout << "Maze is : ";
    Maze_Print(); //Prints the maze
	
		do {
			do {
				cout << "\n\nEnter the coordinates for the start position separated by space: " << endl;
				cin >> S1 >> S2; //Taking input from user
				if ((S1>=6)||(S1<0)||(S2>=6)||(S2<0)) //checking if the the input lie inside the maze
				{
					terminate4 = 1;
					cout << "The entered start coordinate is lies outside the maze" << endl;

				}
				D1= S1%1;
				D2= S2%1;
				if ((D1!= 0) || (D2!=0))//checking if the input is float or not
				{
					terminate4 = 1;
					cout << "The given start coordinate is a float, give int value please" << endl;
				}
				else
				{
					terminate4 = 0;
				}
			}while (terminate4==1);
			
			cout << endl;
			if (Obstacle_On_Entry(S1, S2)) //checks if the coordinates entered by the user are on #(obstacle) or not 
			{
				terminate1 = 1;
			} else {
				cout << "The entered start coordinate lies on the obstacle, re-enter the coordinates please" << endl;
				terminate1 = 0;
			}
		}while(terminate1 == 0);
		do {
			do {
				cout << "\nEnter the coordinates for the goal position seperated by space: " << endl;
				cin >> G1 >> G2; //goal input from user
				if (((G1>=6)||(G1<0))||((G2>=6)||(G2<0))) //checking if the the input lie inside the maze
				{
					terminate5 = 1;
					cout << "The entered goal coordinate is lies outside the maze" << endl;

				}
				E1= G1%1;
				E2= G2%1;
				if ((E1!= 0) || (E2!=0))//checking if the input is float or not
				{
					terminate5 = 1;
					cout << "The given goal coordinate is a float, give int value please" << endl;
				}
				else
				{
					terminate5 = 0;
				}
			}while (terminate5==1);
			cout << endl;
                if (Obstacle_On_Entry(G1, G2)) //Checks if the location has an obstacle
                {
                    terminate2 = 1;
                }else
				{
                    cout << "The entered start coordinate lies on the obstacle, re-enter the coordinates please" << endl;
                    terminate2 = 0;
                }
            }while(terminate2 == 0);
    cout << endl;
    maze.at(S1).at(S2) = 'S';
    maze.at(G1).at(G2) = 'G';
    Maze_Print();
	
        maze.at(S1).at(S2) = '.';
        maze.at(G1).at(G2) = '.';

    rowG = G1;
    columnG = G2;
    maze.at(S1).at(S2) = '.';
    Find_Path(S1,S2); // Function to find a path based on given data to reach goal from start point.
    if(maze[S1][S2]=='+') {

        maze[S1][S1]='S';
        cout << "\n The Maze has been solved, Path found, Goal reached.\n" << endl;
        Maze_Print();
    }
    else
        cout << " Path not Found. \n" << endl;
    return 0;
}	

void Maze_Print()                                 //Function used to print the maze
{
   // nested for loops to iterate through Maze
   cout << endl;
   for ( int i = 0; i < 6; ++i ) 
   {
      for ( int j = 0; j < 6; ++j )
			  cout << maze.at(i).at(j) << " ";

      cout << '\n';
   } // end for
} // end function MazePrint

int Obstacle_On_Entry(int x,int y)     //Function checks if the coordinates entered by the user are on #(obstacle) or not
{
    if(maze[x][y]=='#' || maze[x][y]=='+')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int Point_In_Maze(int x,int y)        //Function checks if the coordinates matches the goal coordinates or not
{
    if(x>=6 || x<0)
    {
        return 1;
    }
    else if(y>=6 || y<0)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

int Goal_Position(int x,int y, int G1, int G2)    //Function checks if the coordinates has an obstacle
{
    if(x == G1 && y == G2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



int On_Obstacle(int x,int y)     //Function checks if the coordinates has an obstacle
{
    if(maze[x][y]=='#' || maze[x][y]=='+')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
vector<int> Action_North(int x,int y)     //Function makes a movement in the North
{
    x = x-1;
    y = y;
    vector<int> North{x,y};
    return North;
}
vector<int> Action_East(int x,int y)         //Function makes a movement in the east
{
    x = x;
    y = y+1;
    vector<int> East{x,y};
    return East;
}
vector<int> Action_South(int x,int y)		//Function makes a movement in the south
{
    x = x+1;
    y = y;
    vector<int> South{x,y};
    return South;
}
vector<int> Action_West(int x,int y)          //Function makes a movement in the west
{
    x = x;
    y = y-1;
    vector<int> West{x,y};
    return West;
}

int Find_Path (int x, int y) // Function to find a path based on given data to reach goal from start point.
{
    if(Point_In_Maze(x, y))
    {
        return 0;
    }
    if(Goal_Position(x, y, rowG, columnG))
    {
        return 1;
    }
    if(On_Obstacle(x, y))
    {
        return 0;
    }
    vector<int> Possible_Moves;
    maze[x][y] = '+';
    if(Find_Path(Action_North(x,y)[0],Action_North(x,y)[1])) //Function to find a path based on given data to reach goal from start point.
    {
        Possible_Moves = Action_North(x,y);                // Storing the coordinates of movement north
        return 1;

    }
    if(Find_Path(Action_East(x,y)[0],Action_East(x,y)[1]))
    {
        Possible_Moves = Action_East(x,y);                 // Storing the coordinates of movement East
        return 1;

    }
    if(Find_Path(Action_South(x,y)[0],Action_South(x,y)[1]))
    {
        Possible_Moves = Action_South(x,y);					// Storing the coordinates of movement East
        return 1;

    }
    if(Find_Path(Action_West(x,y)[0],Action_West(x,y)[1]))
    {
        Possible_Moves = Action_West(x,y);					// Storing the coordinates of movement East
        return 1;

    }
    maze[x][y] = 'B';
	maze[rowG][columnG]= 'G';
    return 0;
}