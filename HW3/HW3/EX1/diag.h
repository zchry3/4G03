#include <vector>
using namespace std;

typedef vector<double> Row;
typedef vector<Row> Matrix;

int sgn(double val);

void jacdiag(Matrix & A, vector<double> & d);

void jacuppdiag(Matrix & A, vector<double> & d);
