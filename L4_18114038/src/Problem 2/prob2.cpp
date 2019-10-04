/**
* @file prob2.cpp
* @brief This Cpp file is a program used to solve the N Queens problem.
*
* @author Prathamesh Katkar
*
* @date 04/09/2019
*/


#include <iostream>

using namespace std;

int count=0;
/**
* This method isAttacked() will be used to check if a queen is being attacked or not.
* @param int **board, int row, int col,int n
* @date 04/09/2019
*/

bool isAttacked(int **board, int row, int col,int n){
	
	int i, j; 
  
    /* Check this row on left side */
    for (i = 0; i < col; i++) 
        if (board[row][i]) 
            return true; 
  
    /* Check upper diagonal on left side */
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) 
        if (board[i][j]) 
            return true; 
  
    /* Check lower diagonal on left side */
    for (i = row, j = col; j >= 0 && i < n; i++, j--) 
        if (board[i][j]) 
            return true; 
  
    return false;
}
/**
* This method solveNQ() will be used to solve the N Queens problem.
* @param int** board, int total_no_of_queens, int index
* @date 04/09/2019
*/
void solveNQ(int** board, int total_no_of_queens, int index){

	if (index==total_no_of_queens){

		for (int l=0;l<total_no_of_queens;l++){
			for (int j=0;j<total_no_of_queens;j++){
				cout<<board[l][j]<<" ";
			}
			cout<<""<<endl;
		}
		cout<<""<<endl;
		count=count+1;
		return;
	}
		
		int check=0;

		for (check=0;check<total_no_of_queens;check++){

			if (isAttacked(board, check,index, total_no_of_queens)==false){
				
				board[check][index]=1;

				solveNQ(board,total_no_of_queens,index+1);
		
			board[check][index]=0;
		}
	}
	

}
/**
* This method main() will be the driver program for the class.
* @param int argc, char const *argv[]
* @date 04/09/2019
*/
int main(int argc, char const *argv[])
{
	int n;
	cout<<"Enter the size of the ChessBoard."<<endl;
	cin>>n;
	int **board;
	board = new int *[n];
	for(int i = 0; i <n; i++)
	    board[i] = new int[n];
	cout<<"All the possible combinations are:"<<endl<<endl;
	solveNQ(board, n, 0);
	cout<<"The number of possible combinations is : "<<count<<endl;
	return 0;
}