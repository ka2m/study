#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <math.h>


void Clip1Left(point &A, point &B, point Pmin, point Pmax) {
	A.y = B.y - (B.x - Pmin.x) * (B.y - A.y) / (B.x - A.x);
	A.x = Pmin.x;
}

void Clip1Top(point &A, point &B, point Pmin, point Pmax) {
	A.x = B.x - (B.y - Pmax.y) * (B.x - A.x) / (B.y - A.y);
	A.y = Pmax.y;
}

void Clip1Bottom(point &A, point &B, point Pmin, point Pmax) {
	A.x = B.x - (B.y - Pmin.y) * ((B.x - A.x) / (B.y - A.y));
	A.y = Pmin.y;
}

void Clip2Right(point &A, point &B, point Pmin, point Pmax) {
	B.y = A.y + (Pmax.x - A.x) * (B.y - A.y) / (B.x - A.x);
	B.x = Pmax.x;
}

void Clip2Top(point &A, point &B, point Pmin, point Pmax) {
	B.x = A.x + (Pmax.y - A.y) * (B.x - A.x) / (B.y - A.y);
	B.y = Pmax.y;
}

void Clip2Bottom(point &A, point &B, point Pmin, point Pmax) {
	B.x = A.x + (Pmin.y - A.y) * (B.x - A.x) / (B.y - A.y);
	B.y = Pmin.y;
}

bool clip(point &A, point &B, point Pmin, point Pmax) {
	if (A.x > B.x)
	{
		point C = B;
		B = A;
		A = C;
	}
	
	int C1 = 0;
	int C2 = 0;

	if (A.x < Pmin.x) C1++;	
	if (A.x > Pmax.x) C1 += 2;
	if (A.y < Pmin.y) C1 += 4;
	if (A.y > Pmax.y) C1 += 8;

	if (B.x < Pmin.x) C2++;	
	if (B.x > Pmax.x) C2 += 2;
	if (B.y < Pmin.y) C2 += 4;
	if (B.y > Pmax.y) C2 += 8;

	if (C1 & C2) return false;

	int C = C1*16 + C2;

	switch(C) {
	
	case 0x00:
		return true;
		break;
	case 0x02:
		Clip2Right(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x04:
		Clip2Bottom(A,B, Pmin, Pmax);
		return true;
		break;
	case 0x06:
		Clip2Right(A,B,Pmin,Pmax);
		if (B.y < Pmin.y) Clip2Bottom(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x08:
		Clip2Top(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x0A:
		Clip2Right(A, B, Pmin, Pmax);
		if (B.y > Pmax.y)
			Clip2Top(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x10:
		Clip1Left(A, B, Pmin,Pmax);
		return true;
		break;
	case 0x12:
		Clip1Left(A, B, Pmin ,Pmax);
		Clip2Right(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x14:
		Clip1Left(A, B, Pmin, Pmax);
		if (A.y < Pmin.y) return false;
		Clip2Bottom(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x16:
		Clip1Left(A, B, Pmin, Pmax);
		if (A.y < Pmin.y) return false;
		Clip2Bottom(A, B, Pmin, Pmax);
		if (B.x > Pmax.x) Clip2Right(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x18:
		Clip1Left(A, B, Pmin,Pmax);
		if (A.y > Pmax.y) return false;
		Clip2Top(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x1A:
		Clip1Left(A, B, Pmin,Pmax);
		if (A.y > Pmax.y) return false;
		Clip2Top(A, B, Pmin, Pmax);
		if (B.x > Pmax.x) Clip2Right(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x40:
		Clip1Bottom(A, B, Pmin, Pmax); return true;
		break;
	case 0x42:
		Clip1Bottom(A, B, Pmin, Pmax);
		if (A.x > Pmax.x) return false;
		Clip2Right(A, B, Pmin ,Pmax);
		return true;
		break;
	case 0x48:
		Clip1Bottom(A, B, Pmin, Pmax);
		Clip2Top(A, B, Pmin ,Pmax);
		return true;
		break;
	case 0x4A:
		Clip1Bottom(A, B, Pmin, Pmax);
		if (A.x > Pmax.x) return false;
		Clip2Right(A, B, Pmin ,Pmax);
		if (B.y > Pmax.y) Clip2Top(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x50:
		Clip1Left(A, B, Pmin, Pmax);
		if (A.y < Pmin.y) Clip1Bottom(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x52:
		Clip1Bottom(A, B, Pmin, Pmax);
		if (A.x > Pmax.x) return false;
		if (A.x < Pmin.x) Clip1Left(A, B, Pmin ,Pmax);
		Clip2Right(A, B, Pmin ,Pmax);
		return true;
		break;
	case 0x58:
		Clip1Left(A, B, Pmin, Pmax);
		if (A.y > Pmax.y) return false;
		if (A.y < Pmin.y) Clip1Bottom(A, B, Pmin, Pmax);
		Clip2Top(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x5A:
		Clip1Left(A, B, Pmin, Pmax);
		if (A.y > Pmax.y) return false;
		if (A.y < Pmin.y) {
			Clip1Bottom(A, B, Pmin, Pmax);
			if (A.x > Pmax.x) return false;
		}
		Clip2Top(A, B, Pmin, Pmax);
		if (B.x > Pmax.x) Clip2Right(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x80:
		Clip1Top(A, B,Pmin,Pmax);
		return true;
		break;
	case 0x82:
		Clip1Top(A, B, Pmin, Pmax);
		if (A.x > Pmax.x) return false;
		Clip2Right(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x84:
		Clip1Top(A, B, Pmin ,Pmax);
		Clip2Bottom(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x86:
		Clip1Top(A, B, Pmin ,Pmax);
		if (A.x > Pmax.x) return false;
		Clip2Right(A, B, Pmin, Pmax);
		if (B.y < Pmin.y) Clip2Bottom(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x90:
		Clip1Left(A, B, Pmin ,Pmax);
		if (A.y > Pmax.y) Clip1Top(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x92:
		Clip1Top(A, B, Pmin, Pmax);
		if (A.x > Pmax.x) return false;
		if (A.x < Pmin.x) Clip1Left(A, B, Pmin, Pmax);
		Clip2Right(A, B, Pmin, Pmax);
		return true;
		break;
	case 0x94:
		Clip1Left(A, B, Pmin, Pmax);
		if (A.y < Pmin.y) return false;
		if (A.y > Pmax.y) Clip1Top(A, B, Pmin, Pmax);
		Clip2Bottom(A, B, Pmin ,Pmax);
		return true;
		break;
	case 0x96:
		Clip1Left(A, B, Pmin ,Pmax);
		if (A.y < Pmin.y) return false;
		if (A.y > Pmax.y) {
			Clip1Top(A, B, Pmin, Pmax);
			if (A.x > Pmax.x) return false;
		}
		Clip2Bottom(A, B, Pmin ,Pmax);
		if (B.x > Pmax.x) Clip2Right(A, B, Pmin, Pmax);
		return true;
		break;

	}
	
	return false;
}