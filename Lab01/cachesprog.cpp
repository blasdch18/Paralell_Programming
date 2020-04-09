#include <iostream>
#include <ctime>
using namespace std;

unsigned t0, t1, t2, t3;
int main()
{
		int MAX=900;

		double A[MAX][MAX], x[MAX], y[MAX];

		/* Initialize A and x, assign y = 0 */
		//int y=0;
		int i , j;
		
		/* First pair of loops */
		t0=clock();
		for ( i = 0; i < MAX ; i++)
			for ( j = 0; j < MAX ; j++)
				y[ i ] += A[i][j] * x[ j ];
		t1=clock();
		double time = (double(t1-t0)/CLOCKS_PER_SEC);
		cout << "Execution Time: " << time << endl;


		/* Assign y = 0 */
		
		/* Second pair of loops */
		t2=clock();
		for (j = 0; j < MAX ; j ++)
			for (i = 0; i < MAX ; i ++)
				y[i] += A[i][j]* x[j];
		t3=clock();

		time = (double(t3-t2)/CLOCKS_PER_SEC);
		cout << "Execution Time: " << time << endl;

		return 0;

}