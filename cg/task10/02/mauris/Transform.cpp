#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <math.h>

mat T;
mat3D T3d;
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
	b[0] = a.x; b[1] = a.y; b[2] = 1;
}

void vec2point(vec a, point &b) {
	b.x = ((float)a[0])/a[2];
	b.y = ((float)a[1])/a[2];
}

void makeHomogenVec(float x, float y, vec &c){
	c[0] = x; c[1] = y; c[2] = 1;
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
	unit (c);
	c[0][M-1] = Tx;
	c[1][M-1] = Ty;
}

void rotate_r(float phi, mat &c) {
	unit(c);
	c[0][0] = cos(phi); c[0][1] = sin(phi);
	c[1][0] = -sin(phi); c[1][1] =  cos(phi);
}

void scale(float x, float y, mat &c) { 
	unit(c);
	c[0][0] = x; 
	c[1][1] = y;
}
void reflectHoriz(mat &c) {
	unit(c);
	c[1][1] = -1;
}

void reflectVert(mat &c) { 
	unit(c);
	c[0][0] = -1;
}

void start(float Tx, mat &c){
	unit(c);
	c[1][1] =  -1;
	c[1][2] = Tx; 
}

void frame (float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat &c){
	mat R, c1;
	unit(R);
	unit(c);
	move(-Vcx, -Vcy, R);
	set(R, c1);
	scale(Wx / Vx, Wy / Vy, R);
	times(R, c1, c1);
	reflectHoriz(R);
	times(R, c1, c1);
	move(Wcx, Wcy, R);
	times(R, c1, c);
}


void times (mat3D a, mat3D b, mat3D &c)
{
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			float skalaar = 0;
			for(int k = 0; k < 4; k++)
				skalaar += a[i][k] * b[k][j];
			c[i][j] = skalaar;
		}
	}
}

void timesMatVec (mat3D a, vec3D b, vec3D &c)
{	
	for(int i = 0; i < 4; i++) {
		float skalaar = 0;
		for(int j = 0; j < 4; j++)
			skalaar += a[i][j] * b[j];
		c[i] = skalaar;
	}
}

void set (mat3D a, mat3D &b)
{
	for(int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
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
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
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
	c[0][3] = Tx;
	c[1][3] = Ty;
	c[2][3] = Tz;
}

void rotate (point3D n, float phi, mat3D &c)
{
	c[0][0] = cos(phi) + n.x * n.x * (1 - cos(phi));
	c[0][1] = n.x * n.y * (1 - cos(phi)) - n.z * sin(phi);
	c[0][2] = n.x * n.z * (1 - cos(phi)) + n.y * sin(phi);
	c[0][3] = 0;
	
	c[1][0] = n.y * n.x * (1 - cos(phi)) + n.z * sin(phi);
	c[1][1] = cos(phi) + n.y * n.y * (1 - cos(phi));
	c[1][2] = n.y * n.z * (1 - cos(phi)) - n.x * sin(phi);
	c[1][3] = 0;

	c[2][0] = n.z * n.x * (1 - cos(phi)) - n.y * sin(phi);
	c[2][1] = n.z * n.y * (1 - cos(phi)) + n.x * sin(phi);
	c[2][2] = cos(phi) + n.z * n.z * (1 - cos(phi));
	c[2][3] = 0;

	c[3][0] = 0;
	c[3][1] = 0;
	c[3][2] = 0;
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
	point3D e1, e2, e3;
	e3.x = center.x - eye.x;
	e3.y = center.y - eye.y;
	e3.z = center.z - eye.z;
	float de3 = sqrt(e3.x * e3.x + e3.y * e3.y + e3.z * e3.z);
	e3.x = e3.x / de3;
	e3.y = e3.y / de3;
	e3.z = e3.z / de3;
	float z = e3.x * eye.x + e3.y * eye.y + e3.z * eye.z;
	e1.x = up.y * e3.z - e3.y * up.z;
	e1.y = up.z * e3.x - e3.z * up.x;
	e1.z = up.x * e3.y - e3.x * up.y;
	float de1 = sqrt(e1.x * e1.x + e1.y * e1.y + e1.z * e1.z);
	e1.x = e1.x / de1;
	e1.y = e1.y / de1;
	e1.z = e1.z / de1;
	float x = e1.x * eye.x + e1.y * eye.y + e1.z * eye.z;
	e2.x = e3.y * e1.z - e1.y * e3.z;
	e2.y = e3.z * e1.x - e1.z * e3.x;
	e2.z = e3.x * e1.y - e1.x * e3.y;
	float y = e2.x * eye.x + e2.y * eye.y + e2.z * eye.z;
		
	c[0][0] = e1.x; c[1][0] = e2.x; c[2][0] = e3.x; c[3][0] = 0;
	c[0][1] = e1.y; c[1][1] = e2.y; c[2][1] = e3.y; c[3][1] = 0;
	c[0][2] = e1.z; c[1][2] = e2.z; c[2][2] = e3.z; c[3][2] = 0;
	c[0][3] = -x; c[1][3] = -y; c[2][3] = -z; c[3][3] = 1;
}

void Ortho (float Vx, float Vy, float near, float far, mat3D &c)
{
	c[0][0] = -2/Vx;
	c[0][1] = 0;
	c[0][2] = 0;
	c[0][3] = 0;
	c[1][0] = 0;
	c[1][1] = 2/Vy;
	c[1][2] = 0;
	c[1][3] = 0;
	c[2][0] = 0;
	c[2][1] = 0;
	c[2][2] = 2/(far - near);
	c[2][3] = (far + near) / (far - near);
	c[3][0] = 0;
	c[3][1] = 0;
	c[3][2] = 0;
	c[3][3] = 1;	
}

void Frustrum (float Vx, float Vy, float near, float far, mat3D &c)
{
	c[0][0] = near * 2 / Vx;
	c[0][1] = 0;
	c[0][2] = 0;
	c[0][3] = 0;
	c[1][0] = 0;
	c[1][1] = near * 2 / Vy;
	c[1][2] = 0;
	c[1][3] = 0;
	c[2][0] = 0;
	c[2][1] = 0;
	c[2][2] = (far + near)/(far - near);
	c[2][3] = (2 * far * near)/(far - near);
	c[3][0] = 0;
	c[3][1] = 0;
	c[3][2] = -1;
	c[3][3] = 0;
}

void Perspective (float fovy, float aspect, float near, float far, mat3D &c)
{
	float fovyrad = fovy * 3.1415 / 180 / 2;
	
	c[0][0] = 1/aspect * (1/tan(fovyrad));
	c[0][1] = 0;
	c[0][2] = 0;
	c[0][3] = 0;
	c[1][0] = 0;
	c[1][1] = -(1/tan(fovyrad));
	c[1][2] = 0;
	c[1][3] = 0;
	c[2][0] = 0;
	c[2][1] = 0;
	c[2][2] = -(far + near)/(far - near);
	c[2][3] = (2 * far * near)/(far - near);
	c[3][0] = 0;
	c[3][1] = 0;
	c[3][2] = -1;
	c[3][3] = 0;	
}

void frame3D (float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat3D &c)
{
	c[0][0] = Wx/2;
	c[0][1] = 0;
	c[0][2] = 0;
	c[0][3] = Wcx + Wx/2;
	c[1][0] = 0;
	c[1][1] = -Wy/2;
	c[1][2] = 0;
	c[1][3] = Wcy-Wy/2;
	c[2][0] = 0;
	c[2][1] = 0;
	c[2][2] = 1;
	c[2][3] = 0;
	c[3][0] = 0;
	c[3][1] = 0;
	c[3][2] = 0;
	c[3][3] = 1;
}