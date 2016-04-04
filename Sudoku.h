#include<iostream>
#include<cstdlib>

using namespace std;

class Sudoku
{
public:
	void giveQuestion();
	void readIn();
	void solve();
	bool find_solution1(int s, int t);
	bool find_solution2(int s, int t);
	void next_position1(int& i, int& j)const;
	void next_position2(int& i, int& j)const;
	bool valid_number(int N, int i, int j)const;
	void insert_number(int N, int i, int j);
	void delete_number(int N, int i, int j);
	void changeNum(int a, int b);
	void changeRow(int a, int b);
	void changeCol(int a, int b);
	void rotate(int n);
	void flip(int n);
	void transform();
	void change();
	void printOut(int arr[9][9]);
private:
	int ans[9][9]; //store number of solution
	int temp[9][9]; //store template number for change functions
	int fixed[9][9]; //store whether the number is fixed
};

