#include <iostream>
#include <vector>
std::vector<int> vc;    // vector global
#include <string.h>
#include <thread>
#include <time.h>
#include <stdlib.h>

using namespace std;

void run_par()
{
	int n = vc.size();
	for (int i = 0; i<n / 2; i++)
	{
		if (vc[2*i]>vc[2*i + 1])
			swap(vc[2*i], vc[2*i + 1]);
	}
}
void run_impar()
{
	int n = vc.size();
	for (int i = 0; i<n / 2 - 1; i++)
	{
		if (vc[2*i + 1]>vc[2*i + 2])
			swap(vc[2 * i + 1], vc[2 * i + 2]);
	}
}
void bubbleSort_para()
{
	int n = vc.size();
	for (int i = 0; i < n; ++i){
		if (i % 2 == 0) {
			thread u((run_par));
			u.join();
		}
		else {
			thread  t((run_impar));
			t.join();
		}
	}
}
void mostrar(vector <int>& num)
{
	int tam = num.size();
	for (int i = 0; i <tam; i++){
		cout << num[i] << "  ";
	}
	cout << endl;
}
int main()
{
	int ale;
	int tam_vector;
    cout << "ALGORITMOS DE ORDENACION PARALELO : BUBBLE SORT" << endl;
	cout << "Ingresar cantidad de datos:";
	cin >> tam_vector;
	int tmp = tam_vector;
	srand(time(NULL));
	for (int i = 0; i < tam_vector; i++){
		ale = rand() % 100;
		vc.push_back(ale);
	}
	mostrar(vc);
	bubbleSort_para();
	cout<<endl<<endl;
	mostrar(vc);
}