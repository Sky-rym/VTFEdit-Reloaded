/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include <vtflib/VTFMathlib.h>


// Vector functions
//-----------------
void VecAdd(Vector *a, Vector *b, Vector *sum)
{
	sum->x = a->x + b->x;
	sum->y = a->y + b->y;
	sum->z = a->z + b->z;
}

void VecSub(Vector *a, Vector *b, Vector *diff)
{
	diff->x = a->x - b->x;
	diff->y = a->y - b->y;
	diff->z = a->z - b->z;
}

void VecScale(Vector *v, vlSingle scale)
{
	v->x *= scale;
	v->y *= scale;
	v->z *= scale;
}

vlSingle VecDot(Vector *u, Vector *v)
{
	return (u->x*v->x + u->y*v->y + u->z*v->z);
}

void VecReflect(Vector *axis, Vector *v, Vector *r)
{
	Vector t = *axis;
	VecScale(&t, 2*VecDot(axis, v));
	VecSub(&t, v, r);
}

vlInt Intersect(Vector *v)
{
	vlInt f;
	vlDouble x, y, z;
  
	x = fabs(v->x); y = fabs(v->y); z = fabs(v->z);
	
	if (x >= y && x >= z)
		f = (v->x > 0) ? 2 : 0;
	else if (y >= x && y >= z)
		f = (v->y > 0) ? 4 : 5;
	else
		f = (v->z > 0) ? 3 : 1;

	return f;
}
