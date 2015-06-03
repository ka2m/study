#include <array>
#include <vector>
#include <cmath>
value struct point {
	float x, y;
};
value struct line {
	point start, end;
	System::String^ name;
};


#define M 3 //ѕор€док матрицы (2-х мерное изображение)
typedef std::tr1::array<float, M> vec;
typedef std::tr1::array<vec, M> mat;
typedef System::Collections::Generic::List<point> polygon;

extern std::vector<mat> matrices;

extern mat T;

void times(mat a, mat b, mat &c);//a*b=c
void timesMatVec(mat a, vec b, vec &c);//a*b=c
void set(mat a, mat &b);//a переписываем в b
void point2vec(point a, vec &b);//декартовы координаты из point в в однородные координаты vec
void vec2point(vec a, point &b);//наоборот
void makeHomogenVec(float x, float y, vec &c);//x и y в c
void unit(mat &a);//свой аргумент в единичную матрицу
void move(float Tx, float Ty, mat &c);//T,G,F,H
void rotate_r(float phi, mat &c);//поворот
void scale(float x, float y, mat &c);//масштабирование
void reflectHoriz(mat &c); //U
void reflectVert(mat &c);//J
void start(float Tx, mat &c);
void frame (float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat &c);

value struct point3D {
	float x, y, z;
};

value struct line3D {
	point3D start, end;
};

typedef std::tr1::array<float, 4> vec3D;
typedef std::tr1::array<vec3D, 4> mat3D;
typedef System::Collections::Generic::List<point3D> polygon3D;
extern mat3D T3d;

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

void frame3D (float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat3D &c);