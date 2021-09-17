
#include <iostream>
#include <armadillo>

using namespace std;


double find_max_value(arma::mat A, int& k, int& l);


int main(int argc, char const *argv[]) {

  // Problem 3
  int N = 6;    // size of matrix
  int n = N+1; // number of steps
  double h = 1./n; // stepsize
  arma::mat A = arma::mat(N, N).fill(0.);

  cout << "h = " << h << endl;

  for (int i = 0; i < N; i++){  // row
    for (int j = 0; j < N; j++){ // // column
      if (i == j){
        A(i,j) = 2./(h*h);
      } else if ((j == i+1) || (i == j+1)){
        A(i,j) = -1./ (h*h);
      }
    }
  }
  //cout << A;
  arma::vec eigval;
  arma::mat eigvec;
  eig_sym(eigval, eigvec, A);

  cout << "Eigenvalues:\n" << eigval << endl; // printing out, delete later
  cout << "Eigenvectors:\n" << eigvec << endl;





//---------------Task 4B-------------

arma::mat B_4 = arma::mat(4, 4).fill(0.);
for (int i = 0; i < 3; i++){  // row
    for (int j = 0; j < 3; j++){ // // column
      if (i == j){
        B_4(i,j) = 1;
      }
    }
  }
  B_4(0,3) = 0.5; B_4(1,2) = -0.7; B_4(2,1) = -0.7; B_4(3,0) = 0.5;


int k; int l;
cout<< B_4 <<endl;
//returns max value and assigns k as the column index and l as the row index
cout <<"max value: "<< find_max_value(B_4,k,l) <<" row: "<<l<<" column: "<< k << endl; 

//---------------Task 4B(end)-------------

  return 0;
}

double analytical_eigenvectors(){

}
double analytical_eigenvalues(){
  
}


double find_max_value(arma::mat A, int& k, int& l){

  double max_value = 0;
  int N = arma::size(A)(0); //i is dimension N of matrix A
  

  for (int j=0; j<=N-1; j++){

          for (int i=1+j; i<=N-1; i++){
            if(abs(A(i,j))>abs(max_value)){
              max_value= A(i,j);
              k = j, l=i; //kolonne k rad l

            }
      }
      }

  return max_value;
}
