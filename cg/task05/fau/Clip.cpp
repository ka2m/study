#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <algorithm>

using namespace std;

void Clip1Left(point &p1, point &p2, point min, point max) {
	p1.y = p2.y - (p2.x - min.x) * (p2.y - p1.y) / (p2.x - p1.x);
	p1.x = min.x;
}

void Clip1Top(point &p1, point &p2, point min, point max) {
	p1.x = p2.x - (p2.y - max.y) * (p2.x - p1.x) / (p2.y - p1.y);
	p1.y = max.y;
}

void Clip1Bottom(point &p1, point &p2, point min, point max) {
	p1.x = p2.x - (p2.y - min.y) * (p2.x - p1.x) / (p2.y - p1.y);
	p1.y = min.y;
}

void Clip2Right(point &p1, point &p2, point min, point max) {
	p2.y = p1.y + (max.x - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
	p2.x = max.x;
}

void Clip2Top(point &p1, point &p2, point min, point max) {
	p2.x = p1.x + (max.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
	p2.y = max.y;
}

void Clip2Bottom(point &p1, point &p2, point min, point max) {
	p2.x = p1.x + (min.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
	p2.y = min.y;	
}

bool clip(point &p1, point &p2, point min, point max) {
	if (p1.x > p2.x)
		swap(p1, p2);

	int C1 = 0;
	int C2 = 0;

	if (p1.x < min.x) C1++;	
	if (p1.x > max.x) C1 += 2;
	if (p1.y < min.y) C1 += 4;
	if (p1.y > max.y) C1 += 8;

	if (p2.x < min.x) C2++;	
	if (p2.x > max.x) C2 += 2;
	if (p2.y < min.y) C2 += 4;
	if (p2.y > max.y) C2 += 8;

	if (C1 & C2) return false;

	int C = C1*16 + C2;

	switch(C) {
		case 0x00: return true;
		case 0x02: Clip2Right(p1, p2, min, max); return true;
		case 0x04: Clip2Bottom(p1,p2, min, max); return true;
		case 0x06: 
			Clip2Right(p1,p2,min,max);
			if (p2.y < min.y) Clip2Bottom(p1, p2, min, max);
			return true;
		case 0x08: 
			Clip2Top(p1, p2, min, max); return true;
		case 0x0A:
			Clip2Right(p1, p2, min, max);
			if (p2.y > max.y) Clip2Top(p1, p2, min, max);
			return true;
		case 0x10:
			Clip1Left(p1, p2, min,max);
			return true;
		case 0x12:
			Clip1Left(p1, p2, min ,max);
			Clip2Right(p1, p2, min, max);
			return true;
		case 0x14: 
			Clip1Left(p1, p2, min, max);
			if (p1.y < min.y) return false;
			Clip2Bottom(p1, p2, min, max);
			return true;
		case 0x16:
			Clip1Left(p1, p2, min, max);
			if (p1.y < min.y) return false;
			Clip2Bottom(p1, p2, min, max);
			if (p2.x > max.x) Clip2Right(p1, p2, min, max);
			return true;
		case 0x18:
			Clip1Left(p1, p2, min,max);
			if (p1.y > max.y) return false;
			Clip2Top(p1, p2, min, max);
			return true;
		case 0x1A:
			Clip1Left(p1, p2, min,max);
			if (p1.y > max.y) return false;
			Clip2Top(p1, p2, min, max);
			if (p2.x > max.x) Clip2Right(p1, p2, min, max);
			return true;
		case 0x40:
			Clip1Bottom(p1, p2, min, max); return true;
		case 0x42:
			Clip1Bottom(p1, p2, min, max);
			if (p1.x > max.x) return false;
			Clip2Right(p1, p2, min ,max);
			return true;
		case 0x48: 
			Clip1Bottom(p1, p2, min, max);
			Clip2Top(p1, p2, min ,max);
			return true;
		case 0x4A:
			Clip1Bottom(p1, p2, min, max);
			if (p1.x > max.x) return false;
			Clip2Right(p1, p2, min ,max);
			if (p2.y > max.y) Clip2Top(p1, p2, min, max);
			return true;
		case 0x50:
			Clip1Left(p1, p2, min, max);
			if (p1.y < min.y) Clip1Bottom(p1, p2, min, max);
			return true;
		case 0x52:
			Clip1Bottom(p1, p2, min, max);
			if (p1.x > max.x) return false;
			if (p1.x < min.x) Clip1Left(p1, p2, min ,max);
			Clip2Right(p1, p2, min ,max);
			return true;
		case 0x58:
			Clip1Left(p1, p2, min, max);
			if (p1.y > max.y) return false;
			if (p1.y < min.y) Clip1Bottom(p1, p2, min, max);
			Clip2Top(p1, p2, min, max);
			return true;
		case 0x5A:
			Clip1Left(p1, p2, min, max);
			if (p1.y > max.y) return false;
			if (p1.y < min.y) {
				Clip1Bottom(p1, p2, min, max);
				if (p1.x > max.x) return false;
			}
			Clip2Top(p1, p2, min, max);
			if (p2.x > max.x) Clip2Right(p1, p2, min, max);
			return true;
		case 0x80:
			Clip1Top(p1, p2,min,max);
			return true;
		case 0x82:
			Clip1Top(p1, p2, min, max);
			if (p1.x > max.x) return false;
			Clip2Right(p1, p2, min, max);
			return true;
		case 0x84:
			Clip1Top(p1, p2, min ,max);
			Clip2Bottom(p1, p2, min, max);
			return true;
		case 0x86:
			Clip1Top(p1, p2, min ,max);
			if (p1.x > max.x) return false;
			Clip2Right(p1, p2, min, max);
			if (p2.y < min.y) Clip2Bottom(p1, p2, min, max);
			return true;
		case 0x90:
			Clip1Left(p1, p2, min ,max);
			if (p1.y > max.y) Clip1Top(p1, p2, min, max);
			return true;
		case 0x92:
			Clip1Top(p1, p2, min, max);
			if (p1.x > max.x) return false;
			if (p1.x < min.x) Clip1Left(p1, p2, min, max);
			Clip2Right(p1, p2, min, max);
			return true;
		case 0x94:
			Clip1Left(p1, p2, min, max);
			if (p1.y < min.y) return false;
			if (p1.y > max.y) Clip1Top(p1, p2, min, max);
			Clip2Bottom(p1, p2, min ,max);
			return true;
		case 0x96:
			Clip1Left(p1, p2, min ,max);
			if (p1.y < min.y) return false;
			if (p1.y > max.y) {
				Clip1Top(p1, p2, min, max);
				if (p1.x > max.x) return false;
			}
			Clip2Bottom(p1, p2, min ,max);
			if (p2.x > max.x) Clip2Right(p1, p2, min, max);
			return true;

	}

	return false;
}
