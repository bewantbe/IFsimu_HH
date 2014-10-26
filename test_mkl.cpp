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
test_mkl.cpp \
-Wl,--start-group "/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64"/libmkl_intel_lp64.a "/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64"/libmkl_intel_thread.a "/opt/intel/composer_xe_2013_sp1.2.144/mkl/lib/intel64"/libmkl_core.a -Wl,--end-group -L"/opt/intel/composer_xe_2013_sp1.2.144/mkl/../compiler/lib/intel64" -liomp5 -lm -ldl -lpthread -lrt \
-o ./bin/Release/speed_vec_eigen
*/
/* static MKL
g++ -march=native -O2 -DEIGEN_USE_MKL_ALL -I/usr/include/eigen3 -I/opt/intel/composer_xe_2013_sp1.2.144/mkl/include \
test_mkl.cpp \
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

/*
# GCC
CXXFLAGS="-O3 -march=native"
CPPFLAGS="-Ieigen3"
CPPWFLAGS="-ansi -Wall -Wno-unused-local-typedefs -fdiagnostics-color=auto"
LIBS="-static-libgcc -static-libstdc++ -lrt"
C="$HOME/gcc4.9.1/bin/g++ -o bin/Release/speed_vec_eigen $CXXFLAGS $CPPFLAGS $CPPWFLAGS test_mkl.cpp $LIBS"

# MKL
MKLROOT=/opt/intel/composer_xe_2013_sp1.2.144/mkl
CXXFLAGS="-O3 -march=native"
CPPFLAGS="-DEIGEN_USE_MKL_ALL -Ieigen3 -I$MKL_INC_PATH"
CPPWFLAGS="-ansi -Wall -Wno-unused-local-typedefs -fdiagnostics-color=auto"
LIBS="-static-libgcc -static-libstdc++ -Wl,--start-group $MKLROOT/lib/intel64/libmkl_intel_lp64.a $MKLROOT/lib/intel64/libmkl_core.a $MKLROOT/lib/intel64/libmkl_intel_thread.a -Wl,--end-group -lpthread -lm -lrt"
D="$HOME/gcc4.9.1/bin/g++ -o bin/Release/speed_vec_eigen $CXXFLAGS $CPPFLAGS $CPPWFLAGS test_mkl.cpp $LIBS"

*/

// to test
// time ./bin/Release/speed_vec_eigen 100 1000000

#include <stdio.h>
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


void Loop1(double *a, int n)
{
  for (int i=0; i<n; i++) {
    a[i] /= 1+2e-16;     // 10.7 clk
    //a[i] = cos(a[i]);    // 37.5 clk
    //a[i] = a[i] + sin(a[i]);  // 1081 clk
    //a[i] += sin(a[i]);  // 1099.6 clk
    //a[i] = sqrt(sin(a[i]));  // 48.6 clk
    //a[i] = 0.5*a[i] + sin(a[i]);  // 45.9 clk
    //a[i] = 2*sin(a[i]);  // 41.5 clk
    //a[i] = a[i] - (a[i]*a[i]+7.0/3.0*a[i]-2)/(2*a[i]+7.0/3.0);  // 21.3 clk
    //a[i] = a[i] - ((a[i]+7.0/3.0)*a[i]-2)/(2*a[i]+7.0/3.0);  // 21.2 clk
    a[i] = a[i] - (a[i]+6)*(a[i]+5)*(a[i]-1)/(19+20*a[i]+3*a[i]*a[i]);  // 21.3 clk
  }
//  for (int i=0; i<n; i+=4) {  // 2 | n, 46.6 clk (slower)
//    a[i  ] = 2*sin(a[i  ]);
//    a[i+1] = 2*sin(a[i+1]);
//    a[i+2] = 2*sin(a[i+2]);
//    a[i+4] = 2*sin(a[i+4]);
//  }
}

void Init2(Eigen::ArrayXd &v)
{
  v.Random();
}

void Loop2(Eigen::ArrayXd &v)
{
//  v /= 1+2e-16;     // 1.6 clk
//  v = v.cos();      // MKL: 9.5 clk, good. glibc: 35.5 clk
//  v = cos(v);       // MKL: 9.6 clk, good. glibc: 35.5 clk

//  v = v + sin(v);    // MKL: 1081.7 clk
//  Eigen::ArrayXd w(sin(v));  v += w;        // MKL: 12.7 clk
//  static Eigen::ArrayXd w;  w = sin(v);  v += w;   // MKL: 11.6 clk

//  v = 0.5*v + sin(v);    // MKL: 44.2 clk. glibc: 44.0 clk.

//  v = sqrt(sin(v));  // MKL: 48.1 clk
//  v = sin(v);  v = sqrt(v);  // MKL: 22.2 clk. glibc: 52.6 clk

//  v = 2*sin(v);  // MKL: 41.6 clk.
//  v = sin(v);  v+=v;  // MKL: 11.3 clk. glibc: 43.7 clk;
//  v = sin(v);  v*=2;  // MKL: 11.4 clk. glibc: 43.7 clk;

//  v = v - (v*v+7.0/3.0*v-2)/(2*v+7.0/3.0);  // MKL: 4.6 clk. glibc: 4.7 clk
//  v -= (v*v+7.0/3.0*v-2)/(2*v+7.0/3.0);  // MKL: 4.7 clk. glibc: 4.7 clk

  //v = v - (v+6)*(v+5)*(v-1)/(19+20*v+3*v*v);  // 5.3 clk.
  v = v - (v+6)*(v+5)*(v-1)/(19+(20+3*v)*v);  // 4.9 clk.
}

int main(int argc, char *argv[])
{
  int n     = atoi(argv[1]);
  int n_rep = atoi(argv[2]);
  double t;

  // C array
  double *a = new double[n];
  Init1(a, n);
  tic();
  for (int j=0; j<n_rep; j++) {
    Loop1(a, n);
  }
  t = toc0();
  printf("Elapsed time is %.6f seconds. %.1f clk each\n", t, t/n/n_rep/(1/3.1e9));
  cout << "a[1] = " << a[1] << endl;
  delete [] a;

  // Eigen
  Eigen::ArrayXd v(n);
  Init2(v);
  tic();
  for (int j=0; j<n_rep; j++) {
    Loop2(v);
  }
  t = toc0();
  printf("Elapsed time is %.6f seconds. %.1f clk each\n", t, t/n/n_rep/(1/3.1e9));
  cout << "v[1] = " << v(1) << endl;
  return 0;
}
