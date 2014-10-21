// GCC
// g++ -march=native -O2 -I/usr/include/eigen3 main.cpp -lrt -o ./bin/Release/speed_vec_eigen

// ICC (source /opt/intel/bin/compilervars.sh intel64)
// icpc -march=native -O2 -I/usr/include/eigen3 main.cpp -lrt -o ./bin/Release/speed_vec_eigen
//
/*
icc -march=native -O2 \
-I/usr/include/eigen3 \
-I/opt/intel/composer_xe_2013_sp1.2.144/mkl/include \
main.cpp \
-Wl,--start-group \
"/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64"/libmkl_intel_lp64.a \
"/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64"/libmkl_intel_thread.a \
"/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64"/libmkl_core.a \
-Wl,--end-group \
-L"/opt/intel/composer_xe_2013_sp1.2.144/mkl/../compiler/lib/intel64" \
-liomp5 -lm -ldl -lpthread -lrt \
-o ./bin/Release/speed_vec_eigen
*/
// cos case
// compile time: 7.297 seconds
//Elapsed time is 1.931160 seconds.
//a[1] = 0.739085
//Elapsed time is 0.369876 seconds.
//v[1] = 0.739085

/* single core?

*/


// GCC plus MKL - cool! now template is fast
/* (not all) dynamically
LD_LIBRARY_PATH="/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64":"/opt/intel/composer_xe_2013_sp1.2.144/compiler/lib/intel64:/opt/intel/composer_xe_2013_sp1.2.144/mpirt/lib/intel64:/opt/intel/composer_xe_2013_sp1.2.144/ipp/../compiler/lib/intel64:/opt/intel/composer_xe_2013_sp1.2.144/ipp/lib/intel64:/opt/intel/composer_xe_2013_sp1.2.144/compiler/lib/intel64:/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64:/opt/intel/composer_xe_2013_sp1.2.144/tbb/lib/intel64/gcc4.4":"/usr/lib" \
g++ -march=native -O2 -DEIGEN_USE_MKL_ALL -I/usr/include/eigen3 -I/opt/intel/composer_xe_2013_sp1.2.144/mkl/include \
main.cpp \
-Wl,--start-group "/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64"/libmkl_intel_lp64.a "/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64"/libmkl_intel_thread.a "/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64"/libmkl_core.a -Wl,--end-group -L"/opt/intel/composer_xe_2013_sp1.2.144/mkl/../compiler/lib/intel64" -liomp5 -lm -ldl -lpthread -lrt \
-o ./bin/Release/speed_vec_eigen
*/
/* static MKL
g++ -march=native -O2 -DEIGEN_USE_MKL_ALL -I/usr/include/eigen3 -I/opt/intel/composer_xe_2013_sp1.2.144/mkl/include \
main.cpp \
-Wl,--start-group "/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64"/libmkl_intel_lp64.a "/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64"/libmkl_intel_thread.a "/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64"/libmkl_core.a -Wl,--end-group -L"/opt/intel/composer_xe_2013_sp1.2.144/mkl/../compiler/lib/intel64" -Wl,-Bstatic -liomp5 -Wl,-Bdynamic -lm -ldl -lpthread -lrt \
-o ./bin/Release/speed_vec_eigen
*/
// cos case
// compile time: 5.054 seconds
//Elapsed time is 1.275474 seconds.
//a[1] = 0.739085
//Elapsed time is 0.357404 seconds.
//v[1] = 0.739085

/* static MKL
g++ -march=native -O2 -DEIGEN_USE_MKL_ALL -I/usr/include/eigen3 -I/opt/intel/composer_xe_2013_sp1.2.144/mkl/include \
main.cpp \
-Wl,--start-group \
/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64/libmkl_intel_thread.a \
/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64/libmkl_core.a \
/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64/libmkl_intel_lp64.a \
 -Wl,--end-group \
/opt/intel/composer_xe_2013_sp1.2.144/compiler/lib/intel64/libiomp5.a \
-lm -ldl -lpthread -lrt \
-o ./bin/Release/speed_vec_eigen
*/

// to test
// time ./bin/Release/speed_vec_eigen 100 1000000


#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#if defined(__ICC) || defined(__INTEL_COMPILER)
#  define EIGEN_USE_MKL_ALL
#endif
#define NDEBUG
#include <Eigen/Dense>   // remember to add -I/usr/include/eigen3 in compiler include path
#include "../tictocs.cpp"

void Init1(double *&a, int n)
{
  for (int i=0; i<n; i++) {
    a[i] = (double)rand()/RAND_MAX;
  }
}


void Loop1(double *&a, int n)
{
  for (int i=0; i<n; i++) {
    //a[i] /= 1+2e-16;
    a[i] = cos(a[i]);
  }
}

void Init2(const Eigen::ArrayXd &v)
{
  v.Random();
}

void Loop2(Eigen::ArrayXd &v)
{
  //v /= 1+2e-16;
  v = v.cos();
  //v = cos(v);
}

int main(int argc, char *argv[])
{
  int n_rep = atoi(argv[2]);
  int n = atoi(argv[1]);
  cout << "aa" << endl;

  // C array
  double *a = new double[n];
  Init1(a, n);
  tic();
  for (int j=0; j<n_rep; j++) {
    Loop1(a, n);
  }
  toc();
  cout << "a[1] = " << a[1] << endl;
  delete [] a;

  // Eigen
  Eigen::ArrayXd v(n);
  Init2(v);
  tic();
  for (int j=0; j<n_rep; j++) {
    Loop2(v);
  }
  toc();
  cout << "v[1] = " << v(1) << endl;
  Eigen::ArrayXd q(n,2);
  q.col(0) = v;
  const Eigen::ArrayXd &u = q.col(0);
  cout << "u[1] = " << u(1) << endl;
  return 0;
}
