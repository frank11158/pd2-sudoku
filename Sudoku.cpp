#include<iostream>
#include<cstdlib>
#include<ctime>
#include"Sudoku.h"
using namespace std;

void Sudoku::giveQuestion()
{
	 int map[9][9] = { 0, 1, 3, 2, 0, 0, 7, 0, 0,
	                   7, 0, 0, 0, 0, 9, 0, 3, 5,
	                   2, 0, 0, 0, 0, 0, 1, 0, 6,
	                   0, 4, 0, 0, 7, 2, 0, 0, 9,
	                   0, 0, 2, 0, 0, 0, 4, 0, 0,
	                   9, 0, 0, 1, 4, 0, 0, 2, 0,
	                   4, 1, 0, 0, 0, 0, 0, 0, 2,
	                   6, 3, 0, 4, 0, 0, 0, 0, 7,
	                   0, 0, 9, 0, 0, 7, 3, 1, 0 };
	printOut(map);
}

//readin question
void Sudoku::readIn()
{
	int i, j;
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			cin>> ans[i][j];
			temp[i][j]=ans[i][j];
		}
	}
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){			
			if(ans[i][j] == 0)fixed[i][j]=0;
			else fixed[i][j]=1;
		}
	};
}

//solve & output
void Sudoku::solve()
{
	int i, j;
	bool k;
	if(find_solution1(0, 0)){
		for(i=0; i<9; i++){
			for(j=0; j<9; j++){
				temp2[i][j]=ans[i][j];
				ans[i][j]=temp[i][j];
			}
		}	
		find_solution2(0, 0);
		for(i=0; i<9; i++){
			for(j=0; j<9; j++){
				if(temp2[i][j] == ans[i][j]){
					k=true;
				}else{
					k=false;
					break;
				}
			}
		}if(k){
			cout<< "1"<< endl;
			printOut(ans);
		}else cout<< "2"<<endl;
	}else cout<< "0"<< endl;
}

//find proper solution
bool Sudoku::find_solution1(int s, int t)
{
	if(s == 9)return true;
	else{
		if(fixed[s][t])next_position1(s,t);

		int i=s, j=t;

		next_position1(i,j);

		int N;

		for(N=1; N<10; N++){
			if(valid_number(N, s, t)){
				ans[s][t]=N;
				if(find_solution1(i, j)) return true;
				ans[s][t]=0;
			}
		}
		return false;
	}
}

//check mutiple answer
bool Sudoku::find_solution2(int s, int t)
{
	if(s == 9)return true;
	else{
		if(fixed[s][t])next_position1(s, t);

		int i=s, j=t;

		next_position1(i, j);

		int N;
		for(N=9; N>0; N--){
			if(valid_number(N, s, t)){
				ans[s][t]=N;
				if(find_solution2(i, j))return true;
				ans[s][t]=0;
			}
		}
		return false;
	}
}

//check whether N at position (i,j) is valid
bool Sudoku::valid_number(int N, int i, int j)const
{
	int k, l, n, m;
	for(k=0; k<9; k++){
		if(k==i)continue;
		if(ans[k][j] == N) return false;
	}
	for(l=0; l<9; l++){
		if(l==j)continue;
		if(ans[i][l] == N) return false;
	}
	for(n=(i/3)*3; n<(i/3)*3+3; n++){
		for(m=(j/3)*3; m<(j/3)*3+3; m++){
			if(n==i && m==j)continue;
			if(ans[n][m] == N) return false; 
		}
	}
	return true;
}

//find next position (i,j)
void Sudoku::next_position1(int& i, int& j)const
{
	if(i == 9)return;
	do{
		j++;
		if(j == 9){
			i++;
			j=0;
		}
		if(i == 9)return;
	}while(fixed[i][j]);
}

//change number
void Sudoku::changeNum(int a, int b)
{
	int i, j;
	if(a == b){
		changeNum(a, b);
	}
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
        	if(ans[i][j] == a)ans[i][j] = b;
			else if(ans[i][j] == b)ans[i][j] = a;
		}
	}
}

//change row
void Sudoku::changeRow(int a, int b)
{
	int i, j;
	if(a == b){
		changeRow(a,b);
	}
	for(i=0; i<3; i++){
		for(j=0; j<9; j++){
			temp[a*3+i][j] = ans[a*3+i][j];
			ans[a*3+i][j] = ans[b*3+i][j];
			ans[b*3+i][j] = temp[a*3+i][j];
		}
	}
}

//change colum
void Sudoku::changeCol(int a, int b)
{
	int i, j;
	if(a ==b){
		changeCol(a, b);
	}
	for(j=0; j<3; j++){
		for(i=0; i<9; i++){
			temp[i][a*3+j] = ans[i][a*3+j];
			ans[i][a*3+j] = ans[i][a*3+j];
			ans[i][a*3+j] = temp[i][a*3+j];
		}
	}
}

//rotate map
void Sudoku::rotate(int n)
{
	int i, j;
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			if(n%4 == 1)
				ans[i][j] = temp[8-j][i];
			else if(n%4 == 2)
				ans[i][j] = temp[8-i][8-j];
			else if(n%4 == 3)
				ans[i][j] = temp[j][8-i];
			else rotate(n);
		}
	}
}

//flip map
void Sudoku::flip(int n)
{
	int i, j;
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			if(n=0){
				ans[i][j] = temp[8-i][j];
			}
			if(n=1){
				ans[i][j] = temp[i][8-j];
			}
		}
	}
}

void Sudoku::transform()
{
	readIn();
	change();
	printOut(ans);
}

void Sudoku::change()
{
	srand(time(NULL));
	changeNum(rand()%9+1, rand()%9+1);
	changeRow(rand()%3, rand()%3);
	changeCol(rand()%3, rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
}

void Sudoku::printOut(int arr[9][9])
{
	int i, j;
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			cout<< arr[i][j];
				if(j == 8)cout<< endl;
				else cout<< ' ';
		}
	}
}

