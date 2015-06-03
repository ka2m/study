#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <math.h>
#include <cfloat>
int extCode(point a, point Pmin, point Pmax);
point angle(point Pmin, point Pmax, int C);
int corr(int C);

polygon^ Pclip (polygon^ P, point Pmin, point Pmax)
{
	polygon^ poly = gcnew polygon(0);
	
	point p1 = P[P->Count-1], p2;
	for(int k = 0; k<P->Count; k++)
	{
		p2 = P[k];
		point delta;
		point in, out, tout, tin;
		delta.x = p2.x - p1.x;
		delta.y = p2.y - p1.y;
		if(delta.x > 0 || delta.x == 0 && p1.x > Pmax.x)
		{
			in.x = Pmin.x;
			out.x = Pmax.x;
		}
		else
		{
			in.x = Pmax.x;
			out.x = Pmin.x;
		}
		if(delta.y >0 || delta.y == 0 && p1.y > Pmax.y)
		{
			in.y = Pmin.y;
			out.y = Pmax.y;
		}
		else
		{
			in.y = Pmax.y;
			out.y = Pmin.y;
		}

		if(delta.x != 0)
		{
			tout.x = (out.x - p1.x)/delta.x;
		}
		else
		{
			if(Pmin.x <= p1.x && p1.x <= Pmax.x)
				tout.x = FLT_MAX;
			else
				tout.x = -FLT_MAX;
		}
		
		if(delta.y != 0)
		{
			tout.y = (out.y - p1.y)/delta.y;
		}
		else
		{
			if(Pmin.y <= p1.y && p1.y <= Pmax.y)
				tout.y = FLT_MAX;
			else
				tout.y = -FLT_MAX;
		}
		float t1out, t2out;
		if(tout.x < tout.y)
		{
			t1out = tout.x;
			t2out = tout.y;
		}
		else
		{
			t1out = tout.y;
			t2out = tout.x;
		}
		float t2in;
		if(t2out > 0)
		{
			if(delta.x != 0)
				tin.x = (in.x - p1.x)/delta.x;
			else
				tin.x = -FLT_MAX;

			if(delta.y != 0)
				tin.y = (in.y - p1.y)/delta.y;
			else
				tin.y = -FLT_MAX;

			if(tin.x < tin.y)
				t2in = tin.y;
			else
				t2in = tin.x;
			if(t1out < t2in)
			{
				//i
				if(0 < t1out && t1out <= 1) //отрезок заходит в угловую область
				{
					point a;
					if(tin.x < tin.y)
					{
						a.x = out.x;
						a.y = in.y;
						poly->Add(a);
					}
					else
					{
						a.x = in.x;
						a.y = out.y;
						poly->Add(a);
					}
					
				}
			}
			else if(t1out > 0 && t2in <= 1)
			{
				//отрезок имеет видимую часть
				point a;
				if(t2in >= 0)
				{
					if(tin.x > tin.y)
					{
						a.x = in.x;
						a.y = p1.y + tin.x * delta.y;
					}
					else
					{
						a.x = p1.x + tin.y * delta.x;
						a.y = in.y;
					}
					poly->Add(a);
				}
				
				if(t1out <= 1)
				{
					if(tout.x < tout.y)
					{
						a.x = out.x;
						a.y = p1.y + tout.x * delta.y;
					}
					else
					{
						a.x = p1.x + tout.y * delta.x;
						a.y = out.y;
					}
					poly->Add(a);
				}
				else
				{
					poly->Add(p2);
				}
			}
			if(0 < t2out && t2out <= 1)
				poly->Add(out);

		}

		p1 = p2;
	}
	
	return poly;
}