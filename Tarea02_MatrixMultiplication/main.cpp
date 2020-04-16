#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <ctime>

using namespace std;
unsigned t0, t1;

template <class T>
class Matrix{
    private:
        std::vector<std::vector<T> > array;
        int height;
        int width;

    public:
        Matrix<T>(int height, int width);
        Matrix<T>(std::vector<std::vector<T> > const &array);
        Matrix<T>();

        int getHeight() const;
        int getWidth() const;

        Matrix<T> multiply(const Matrix<T>& m) const;

        Matrix<T> multiply(const T& value) const;
        Matrix<T> block_matrix_mul(Matrix<T> &A, Matrix<T> &B, int size, int block_size);


        void fill(const T& value);
        void put(int h, int w, const T& value);
        T get(int h, int w) const;

        void print(std::ostream &flux) const;
};
template <class T> std::ostream& operator<<(std::ostream &flux, const Matrix<T>& m);
template <class T> Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b);
template <class T> Matrix<T> operator*(const T &b, const Matrix<T>& a);

template <class T>
std::ostream& operator<<(std::ostream &flux, const Matrix<T>& m){
    m.print(flux);
    return flux;
}

template <class T>
Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b){
    return a.multiply(b);
}

template <class T>
Matrix<T> operator*(const T &b, const Matrix<T>& a){
    return a.multiply(b);
}

template <class T>
Matrix<T>::Matrix(int height, int width){
    this->height = height;
    this->width = width;
    this->array = std::vector<std::vector<T> >(height, std::vector<T>(width));
}

template <class T>
Matrix<T>::Matrix(std::vector<std::vector<T> > const &array){
    if(array.size()==0)
        throw std::invalid_argument("Size of array must be greater than 0.");

    this->height = array.size();
    this->width = array[0].size();
    this->array = array;
}

template <class T>
Matrix<T>::Matrix(){
    height = 0;
    width = 0;
}

template <class T>
int Matrix<T>::getHeight() const{
    return height;
}

template <class T>
int Matrix<T>::getWidth() const{
    return width;
}

template <class T>
void Matrix<T>::fill(const T& value){
    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            array[i][j] = value;
        }
    }
}

template <class T>
Matrix<T> Matrix<T>::multiply(const T& value) const{
    Matrix result(array);
    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            result.array[i][j] *= value;
        }
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::multiply(const Matrix& m) const{
    if(!(height==m.height && width==m.width))
        throw std::invalid_argument("Matrix dimension must be the same.");

    Matrix result(height, width);

    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
                for (int k = 0; k < width; k++)
			{
				//C[i][j] += A[i][k] * B[k][j];
                result.array[i][j] += array[i][k] * m.array[k][j];
			}
        }
    }
    return result;
}
template <class T>
Matrix<T> Matrix<T>:: block_matrix_mul(Matrix<T> &A, Matrix<T> &B, int size, int block_size)
{
	int i, j, k;
	int tmp;
	Matrix result (size,size);
	for (int jj = 0; jj < size; jj += block_size)
	{
		for (int kk = 0; kk < size; kk += block_size)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = jj; j < ((jj + block_size) > size ? size : (jj + block_size)); j++)
				{
					tmp = 0;
					for (int k = kk; k < ((kk + block_size) > size ? size : (kk + block_size)); k++)
					{
						tmp += A.array[i][k] * B.array[k][j];
					}
					result.array[i][j] += tmp;
				}
			}
		}
	}
	return result;
}


template <class T>
void Matrix<T>::print(std::ostream &flux) const{
    int maxLength[width] = {};
    std::stringstream ss;

    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            ss << array[i][j];
            if(maxLength[j] < ss.str().size()){
                maxLength[j] = ss.str().size();
            }
            ss.str(std::string());
        }
    }

    for (int i=0 ; i<height ; i++){
        for (int j=0 ; j<width ; j++){
            flux << array[i][j];
            ss << array[i][j];
            for (int k=0 ; k<maxLength[j]-ss.str().size()+1 ; k++){
                flux << " ";
            }
            ss.str(std::string());
        }
        flux << std::endl;
    }
}

int main(){
    int i=100;
    Matrix<int> A(i,i);
    Matrix<int> B(i,i);
    A.fill(9);
    B.fill(9);
/*
    for(i=100 ; i<=800 ;){

        Matrix<int> A(i,i);
        Matrix<int> B(i,i);
        t0=clock();
        Matrix<int> Res=A*B;
        t1 = clock();
        i +=100;
        for(int j=100; j<i;j+=100){
        	cout<<"|";
        }
        double time = (double(t1-t0)/CLOCKS_PER_SEC);
        cout << "\t Execution Normal Multiplication Time: " << time << endl;
    }*/
    cout<< endl << endl;
    for(i=100 ; i<=800 ;){

        Matrix<int> A(i,i);
        Matrix<int> B(i,i);
        Matrix<int> Res(i,i);
        t0=clock();
        Res.block_matrix_mul(A, B, i, 6);
        t1 = clock();
        i +=100;
        for(int j=100; j<i;j+=100){
        	cout<<"/";
        }
        double time = (double(t1-t0)/CLOCKS_PER_SEC);
        cout << "\t  Execution Blocks Multiplication Time: " << time << endl;
    }


    

}
