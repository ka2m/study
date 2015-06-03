#include <array>
#include <vector>
#define M_PI 3.14159265359
value struct point {
	float x, y;
};

value struct line {
	point start, end;
	System::String^ name;
};

value struct point3D {
	float x, y, z;
};

#define M 4
typedef std::tr1::array<float, M> vec3D;
typedef std::tr1::array<vec3D, M> mat3D;
typedef System::Collections::Generic::List<point3D> polygon3D;
extern mat3D T;

void times (mat3D a, mat3D b, mat3D &c);
void timesMatVec (mat3D a, vec3D b, vec3D &c);
void set (mat3D a, mat3D &b);

void point2vec (point3D a, vec3D &b);
void vec2point (vec3D a, point3D &b);

void makeHomogenVec (float x, float y, float z, vec3D &c);

void unit (mat3D &a);
void move (float Tx, float Ty, float Tz, mat3D &c);
void rotate (point3D n, float phi, mat3D &c);
void scale (float Sx, float Sy, float Sz, mat3D &c);

void LookAt (point3D eye, point3D center, point3D up, mat3D &c);
void Ortho (float Vx, float Vy, float near, float far, mat3D &c);
void Perspective (float fovy, float aspect, float near, float far, mat3D &c);
void Frustrum (float Vx, float Vy, float near, float far, mat3D &c);

void set (point3D a, point &b);

//redefine
#define M 3
typedef std::tr1::array<float, M> vec;
typedef std::tr1::array<vec, M> mat;
typedef System::Collections::Generic::List<point> polygon;

extern std::vector<mat> matrices;


void times(mat a, mat b, mat &c);
void timesMatVec(mat a, vec b, vec &c);
void set(mat a, mat &b);
void point2vec(point a, vec &b);
void vec2point(vec a, point &b);
void makeHomogenVec(float x, float y, vec &c);
void unit(mat &a);
void move(float Tx, float Ty, mat &c);
void rotate(float phi, mat &c);
void scale(float Sx, float Sy, mat &c);
void reflectHorizontal(mat &c);
void reflectVertical(mat &c);
void frame(float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat &c);