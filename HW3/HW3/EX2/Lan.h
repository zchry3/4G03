#include <vector>
using namespace std;

typedef vector<double> Row;
typedef vector<Row> Matrix;

inline double dotprod(const vector<double>& y, const vector<double>& x);

void makelan(Matrix& Lan, int m, int N, int L);
