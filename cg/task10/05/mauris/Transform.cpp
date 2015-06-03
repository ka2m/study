#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <math.h>
#define M 3


mat3D T;
std::vector<mat> matrices(0);

void times(mat a, mat b, mat &c) {
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < M; j++) {
			float skalaar = 0;
			for(int k = 0; k < M; k++)
				skalaar += a[i][k] * b[k][j];
			c[i][j] = skalaar;
		}
	}
}

void timesMatVec(mat a, vec b, vec &c) {
	for(int i = 0; i < M; i++) {
		float skalaar = 0;
		for(int j = 0; j < M; j++)
			skalaar += a[i][j] * b[j];
		c[i] = skalaar;
	}
}

void set(mat a, mat &b) {
	for(int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			b[i][j] = a[i][j];
}

void point2vec(point a, vec &b) {
	b[0] = a.x; 
	b[1] = a.y; 
	b[2] = 1;
}

void vec2point(vec a, point &b) {
	b.x = ((float) a[0]) / a[2];
	b.y = ((float) a[1]) / a[2];
}

void makeHomogenVec(float x, float y, vec &c){
	c[0] = x; 
	c[1] = y; 
	c[2] = 1;
}

void unit(mat &a) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (i == j) a[i][j] = 1;
			else a[i][j] = 0;
		}
	}
}

void move(float Tx, float Ty, mat &c) {
	unit(c);
	c[0][M - 1] = Tx;
	c[1][M - 1] = Ty;
}

void rotate(float phi, mat &c) {
	unit (c);
	c[0][0] = cos(phi); c[0][1] = -sin(phi);
	c[1][0] = sin(phi); c[1][1] = cos(phi);
}


void scale(float Sx, float Sy, mat &c) {
	unit(c);
	c[0][0] = Sx; 
	c[1][1] = Sy;
}

void reflectVertical(mat &c) {
	unit(c);
	c[1][1] = -1;
}

void reflectHorizontal(mat &c) {
	unit(c);
	c[0][0] = -1;
}

void frame(float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat &c)
{
	unit(c);
	mat Mov, Mow, Scale, Ref;
	move(-Vcx, -Vcy, Mov);
	move(Wcx, Wcy, Mow);
	scale(Wx/Vx, Wy/Vy, Scale);
	reflectVertical(Ref);
	
	mat MWR;
	times(Mow, Ref, MWR);
	mat SMV;
	times(Scale, Mov, SMV);
	times(MWR, SMV, c);
}

//3d
#define M 4
void times (mat3D a, mat3D b, mat3D &c)
{
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < M; j++) {
			float skalaar = 0;
			for(int k = 0; k < M; k++)
				skalaar += a[i][k] * b[k][j];
			c[i][j] = skalaar;
		}
	}
}

void timesMatVec (mat3D a, vec3D b, vec3D &c)
{	
	for(int i = 0; i < M; i++) {
		float skalaar = 0;
		for(int j = 0; j < M; j++)
			skalaar += a[i][j] * b[j];
		c[i] = skalaar;
	}
}

void set (mat3D a, mat3D &b)
{
	for(int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			b[i][j] = a[i][j];
}

void point2vec (point3D a, vec3D &b)
{
	b[0] = a.x; 
	b[1] = a.y; 
	b[2] = a.z;
	b[3] = 1;
}

void vec2point (vec3D a, point3D &b)
{
	b.x = a[0] / a[3];
	b.y = a[1] / a[3];
	b.z = a[2] / a[3];
}

void makeHomogenVec (float x, float y, float z, vec3D &c)
{
	c[0] = x;
	c[1] = y;
	c[2] = z;
	c[3] = 1;
}

void unit (mat3D &a)
{
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (i == j)
				a[i][j] = 1;
			else 
				a[i][j] = 0;
		}
	}
}

void move (float Tx, float Ty, float Tz, mat3D &c)
{
	unit(c);
	c[0][M - 1] = Tx;
	c[1][M - 1] = Ty;
	c[2][M - 1] = Tz;
}

void rotate (point3D n, float phi, mat3D &c)
{
	float cosine = cos(phi);
	float sine = sin(phi);
	c[0][0] = cosine + n.x * n.x * (1 - cosine);
	c[0][1] = n.x * n.y * (1 - cosine) - n.z * sine;
	c[0][2] = n.x * n.z * (1 - cosine) + n.y * sine;
	c[0][3] = 0;
	
	c[1][0] = n.y * n.x * (1 - cosine) + n.z * sine;
	c[1][1] = cosine + n.y * n.y * (1 - cosine);
	c[1][2] = n.y * n.z * (1 - cosine) - n.x * sine;
	c[1][3] = 0;

	c[2][0] = n.z * n.x * (1 - cosine) - n.y * sine;
	c[2][1] = n.z * n.y * (1 - cosine) + n.x * sine;
	c[2][2] = cosine + n.z * n.z * (1 - cosine);
	c[2][3] = 0;

	c[3][0] = c[3][1] = c[3][2] = 0;
	c[3][3] = 1;
}

void scale (float Sx, float Sy, float Sz, mat3D &c)
{
	unit(c);
	c[0][0] = Sx; 
	c[1][1] = Sy;
	c[2][2] = Sz;
}

void set (point3D a, point &b)
{
	b.x = a.x;
	b.y = a.y;
}

void LookAt (point3D eye, point3D center, point3D up, mat3D &c)
{
	point3D dir, ndir;
	ndir.x = dir.x = center.x - eye.x;
	ndir.y = dir.y = center.y - eye.y;
	ndir.z = dir.z = center.z - eye.z;
	float dist = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
	ndir.x /= dist;
	ndir.y /= dist;
	ndir.z /= dist;
	
	point3D x;
	x.x = ndir.y * up.z - up.y * ndir.z;
	x.y = ndir.z * up.x - up.z * ndir.x;
	x.z = ndir.x * up.y - up.x * ndir.y;
	dist = sqrtf(x.x * x.x + x.y * x.y + x.z * x.z);
	x.x /= dist;
	x.y /= dist;
	x.z /= dist;

	point3D y;
	y.x = x.y * ndir.z - ndir.y * x.z;
	y.y = x.z * ndir.x - ndir.z * x.x;
	y.z = x.x * ndir.y - ndir.x * x.y;
	
	mat3D t, lat;
	lat[0][0] = x.x;
	lat[0][1] = x.y;
	lat[0][2] = x.z;
	lat[0][3] = 0;

	lat[1][0] = y.x;
	lat[1][1] = y.y;
	lat[1][2] = y.z;
	lat[1][3] = 0;

	lat[2][0] = ndir.x;
	lat[2][1] = ndir.y;
	lat[2][2] = ndir.z;
	lat[2][3] = 0;
	
	lat[3][0] = 0;
	lat[3][1] = 0;
	lat[3][2] = 0;
	lat[3][3] = 1;
	move(-(x.x * eye.x + x.y * eye.y + x.z *eye.z), -(y.x * eye.x + y.y * eye.y + y.z *eye.z), -(ndir.x * eye.x + ndir.y * eye.y + ndir.z *eye.z), t);
	times(t, lat, c);
}

void Ortho (float Vx, float Vy, float near, float far, mat3D &c)
{
	unit(c);
	c[0][0] = -2/Vx;
	c[1][1] = 2/Vy;
	c[2][2] = 2/(far - near);
	c[2][3] = (far + near) / (far - near);
}

void Frustrum (float Vx, float Vy, float near, float far, mat3D &c)
{
	unit(c);
	c[0][0] = near * 2 / Vx;
	c[1][1] = -near * 2 / Vy;
	c[2][2] = (far + near)/(far - near);
	c[2][3] = (2 * far * near)/(far - near);
	c[3][2] = -1;
	c[3][3] = 0;
}

void Perspective (float fovy, float aspect, float near, float far, mat3D &c)
{
	unit(c);
	float fovyrad = fovy * M_PI / 360;
	
	float xmin, xmax, ymin, ymax;
	
	ymax = 2 * near * tan(fovyrad);
	xmax = ymax * aspect;
	Frustrum(xmax, ymax, near, far, c);
}