#include <vector>
#include <array>

value struct point {
	float x, y;
};

value struct line {
	point start, end;
	System::String^ name;
};

#define M 3
typedef System::Collections::Generic::List<point> polygon;
typedef std::tr1::array<float, M> vec;
typedef std::tr1::array<vec, M> mat;

extern mat T;
extern std::vector<mat> matrices;

void times(mat a, mat b, mat &c);
void timesMatVec(mat a, vec b, vec &c);
void set(mat a, mat &b);
void point2vec(point a, vec &b);
void vec2point(vec a, point &b);
void makeHomogenVec(float x, float y, vec &c);
void unit(mat &a);
void move(float Tx, float Ty, mat &c);
void rotate(float phi, float x, float y, mat &c);
void scale(float Sx, float Sy, mat &c);
void reflectHorizontal(mat &c);
void reflectVertical(mat &c);
void frame (float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat &c);