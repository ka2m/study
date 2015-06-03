#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <cmath>

mat T;
mat3D T3D;

void times(mat a, mat b, mat& c) {
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < M; j++) {
			float skalaar = 0;
			for(int k = 0; k < M; k++)
				skalaar += a[i][k] * b[k][j];
			c[i][j] = skalaar;
		}
	}
}

void timesMatVec(mat a, vec b, vec& c) {
	for(int i = 0; i < M; i++) {
		float skalaar = 0;
		for(int j = 0; j < M; j++)
			skalaar += a[i][j] * b[j];
		c[i] = skalaar;
	}
}

void set(mat a, mat& b) {
	for(int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			b[i][j] = a[i][j];
}

void point2vec(point a, vec& b) {
	b[0] = a.x; 
	b[1] = a.y; 
	b[2] = 1;
}

void vec2point(vec a, point &b) {
	b.x = ((float) a[0]) / a[2];
	b.y = ((float) a[1]) / a[2];
}

void makeHomogenVec(float x, float y, vec& c){
	c[0] = x; 
	c[1] = y; 
	c[2] = 1;
}

void unit(mat& a) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (i == j) a[i][j] = 1;
			else a[i][j] = 0;
		}
	}
}

void move(float Tx, float Ty, mat& c) {
	unit(c);
	c[0][M - 1] = Tx;
	c[1][M - 1] = Ty;
}

void rotate(float phi, float x, float y, mat& c) {
	unit(c);
	float cosA = cos(phi);
	float sinA = sin(phi);

	c[0][0] = cosA; c[0][1] = -sinA;
	c[1][0] = sinA; c[1][1] =  cosA;
	c[0][M - 1] = -x * (cosA - 1.0) + y * sinA;
	c[1][M - 1] = -y * (cosA - 1.0) - x * sinA;
}

void scale(float Sx, float Sy, mat& c) {
	unit(c);
	c[0][0] = Sx; 
	c[1][1] = Sy;
}

void reflectHorizontal(mat& c) {
	unit(c);
	c[1][1] = -1;
}

void reflectVertical(mat& c) {
	unit(c);
	c[0][0] = -1;
}


void frame(float Vx, float Vy, float Vcx, float Vcy,
		   float Wx, float Wy, float Wcx, float Wcy,
		   mat& c) {
			   unit(c);
			   mat t;

			   move(-Vcx, -Vcy, t);
			   times(t, c, c);

			   scale(Wx / Vx, Wy / Vy, t);
			   times(t, c, c);

			   reflectHorizontal(t);
			   times(t, c, c);

			   move(Wcx, Wcy, t);
			   times(t, c, c);
}

void times (mat3D a, mat3D b, mat3D &c) {
	for(int i = 0; i < M3D; i++) {
		for(int j = 0; j < M3D; j++) {
			float skalaar = 0;
			for(int k = 0; k < M3D; k++)
				skalaar += a[i][k] * b[k][j];
			c[i][j] = skalaar;
		}
	}
}

void timesMatVec (mat3D a, vec3D b, vec3D &c) {
	for(int i = 0; i < M3D; i++) {
		float skalaar = 0;
		for(int j = 0; j < M3D; j++)
			skalaar += a[i][j] * b[j];
		c[i] = skalaar;
	}
}

void set(mat3D a, mat3D &b) {
	for(int i = 0; i < M3D; i++)
		for (int j = 0; j < M3D; j++)
			b[i][j] = a[i][j];
}

void set(point3D a, point &b) {
	b.x = a.x;
	b.y = a.y;
}

void point2vec (point3D a, vec3D &b) {
	b[0] = a.x; 
	b[1] = a.y; 
	b[2] = a.z;
	b[3] = 1;

}
void vec2point (vec3D a, point3D &b) {
	b.x = ((float) a[0]) / a[3];
	b.y = ((float) a[1]) / a[3];
	b.z = ((float) a[2]) / a[3];
}

void makeHomogenVec (float x, float y, float z, vec3D &c) {
	c[0] = x; 
	c[1] = y; 
	c[2] = z;
	c[3] = 1;
}
void unit (mat3D &a) {
	for (int i = 0; i < M3D; i++) {
		for (int j = 0; j < M3D; j++) {
			if (i == j) a[i][j] = 1;
			else a[i][j] = 0;
		}
	}
}

void move (float Tx, float Ty, float Tz, mat3D &c) {
	unit(c);
	c[0][3] = Tx;
	c[1][3] = Ty;
	c[2][3] = Tz;
}

void rotate (point3D n, float phi, mat3D &c) {
	unit(c);
	mat3D m1, m2, m3, tmp;

	unit(m1); unit(m2); unit(m3);

	m2[0][0] = 0;	  m2[0][1] = -n.z;	m2[0][2] = n.y;	
	m2[1][0] = n.z;	  m2[1][1] = 0;		m2[1][2] = -n.x;
	m2[2][0] = -n.y;  m2[2][1] = n.x;	m2[2][2] = 0;	

	mul(m2, sin(phi), tmp);
	add(m1, tmp, m2);

	m3[0][0] = n.x * n.x - 1; m3[0][1] = n.x * n.y;		m3[0][2] = n.x * n.z;
	m3[1][0] = n.x * n.y;	  m3[1][1] = n.y * n.y - 1;	m3[1][2] = n.y * n.z;
	m3[2][0] = n.x * n.z;	  m3[2][1] = n.y * n.z;		m3[2][2] = n.z * n.z - 1;

	mul(m3, 1 - cos(phi), tmp);
	add(m2, tmp, m3);

	m3[3][3] = 1;
	set(m3, c);
}
void scale (float Sx, float Sy, float Sz, mat3D &c) {
	unit(c);
	c[0][0] = Sx; 
	c[1][1] = Sy;
	c[1][2] = Sz;
}

void normalize(vec3D &v) {
	float l = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

	for (int i = 0; i < M3D; i++) {
		v[i] = v[i] / l;
	}

	v[3] = 1;
}

void LookAt (point3D eye, point3D center, point3D up, mat3D &c) {
	unit(c);

	vec3D e1, e2, e3;
	vec3D s, p, u;

	point2vec(eye, s);
	point2vec(center, p);
	point2vec(up, u);

	normalize(u);

	vec3D tmp;
	mul(p, -1, tmp);
	add(s, tmp, e3);
	normalize(e3);

	mul(u, e3, e1);
	normalize(e1);

	mul(e3, e1, e2);
	normalize(e2);

	mat3D R1, R2;
	unit(R1);
	unit(R2);

	move(-eye.x, -eye.y, -eye.z, R1);

	R2[0][0] = e1[0];	R2[0][1] = e1[1];	R2[0][2] = e1[2];
	R2[1][0] = e2[0];	R2[1][1] = e2[1];	R2[1][2] = e2[2];
	R2[2][0] = e3[0];	R2[2][1] = e3[1];	R2[2][2] = e3[2];

	times(R2, R1, c);
}
void Ortho (float Vx, float Vy, float near, float far, mat3D &c) {
	unit(c);

	c[0][0] = 2.0 / Vx;
	c[1][1] = 2.0 / Vy;
	c[2][2] = 2.0 / (far - near);
	c[2][3] = (far + near) / (far - near);
}
void Frustrum (float Vx, float Vy, float near, float far, mat3D &c) {
}

double cot(double d)
{
  return (1 / tan(d));
}

void Perspective (float fovy, float aspect, float near, float far, mat3D &c) {
	unit(c);
    c[0][0] = cot(fovy / 2.0) * (1.0 / aspect);
	c[1][1] = cot(fovy / 2.0);
	c[2][2] = (far + near) / (far - near);
	c[2][3] = (2.0 * far * near) / (far - near);
	c[3][2] = -1.0;
	c[3][3] = 0;
}

void add (mat3D a, mat3D b, mat3D &c) {
	unit(c);
	for (int i = 0; i < M3D; i++) {
		for (int j = 0; j < M3D; j++) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}

void add (vec3D a, vec3D b, vec3D &c) {
	for (int i = 0; i < M3D; i++) {
		c[i] = a[i] + b[i];
	}
	c[3] = 1;
}

void add (point3D a, point3D b, point3D &c) {
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}


void sub (vec3D a, vec3D b, vec3D &c) {
	for (int i = 0; i < M3D; i++) {
		c[i] = a[i] - b[i];
	}
	c[3] = 1;
}


void mul (mat3D a, float k, mat3D &c) {
	unit(c);
	for (int i = 0; i < M3D; i++) {
		for (int j = 0; j < M3D; j++) {
			c[i][j] = a[i][j] * k;
		}
	}
}

void mul (vec3D a, float k, vec3D &c) {
	for (int i = 0; i < M3D; i++) {
		c[i] = a[i] * k;
	}
	c[3] = 1;
}


void mul (vec3D a, vec3D b, vec3D &c) {
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
	c[3] = 1;
}
