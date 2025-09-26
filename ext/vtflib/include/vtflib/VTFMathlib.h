/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

// ============================================================
// NOTE: This file is commented for compatibility with Doxygen.
// ============================================================
/*!
	\file VTFMathlib.h
	\brief Small math library used by VTFLib

	A small collection of math functions and defines used by VTFLib.
*/

#ifndef VTFMATHLIB_H
#define VTFMATHLIB_H

#include "stdafx.h"

// Defines for data alignment
//---------------------------
#define CACHE_LINE  16								//!< Alignment size.
#define CACHE_ALIGN alignas(CACHE_LINE)				//!< Storage-class information alignment.

// Macros
//-------
#define drand48() (((vlSingle) rand())/((vlSingle) RAND_MAX))		//!< Random number generator for the spheremap generation function.

// Vector class
//-------------
//! Simple 3D Vector class
/*!
	A simple 3D Vector class.
*/
class Vector
{
	public:

		vlSingle x;		//!< Vector value in the X axis.
		vlSingle y;		//!< Vector value in the Y axis.
		vlSingle z;		//!< Vector value in the Z axis.
	
	//! Initialise the vector with the three given values.
	inline void Init(vlSingle vX, vlSingle vY, vlSingle vZ)
	{
		x = vX;
		y = vY;
		z = vZ;
	}

	//! Initialise the vector defaulting all values to zero.
	inline void Init(void)
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

// VectorAligned class
//--------------------
//! Simple Aligned 3D Vector class
/*!
	An aligned 3D Vector class with data alignment set by CACHE_ALIGN.
	Can be initialized with a value or set to zero by default.
	\see CACHE_ALIGN
*/
class CACHE_ALIGN VectorAligned
{
	public:
		
	vlSingle x;		//!< Vector value in the X axis.
		vlSingle y;		//!< Vector value in the Y axis.
		vlSingle z;		//!< Vector value in the Z axis.

		//! Initialise the vector with the three given values.
		inline VectorAligned(vlSingle vX, vlSingle vY, vlSingle vZ) 
		{
			x = vX;
			y = vY;
			z = vZ;
		}

		//! Initialise the vector defaulting all values to zero.
		inline VectorAligned(void)
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		};
};

void VecAdd(Vector *a, Vector *b, Vector *sum);			//!< Vector addition function.
void VecSub(Vector *a, Vector *b, Vector *diff);		//!< Vector subtraction function.
void VecScale(Vector *v, vlSingle scale);				//!< Vector scale function.
vlSingle VecDot(Vector *u, Vector *v);					//!< Vector dot-product function.
void VecReflect(Vector *axis, Vector *v, Vector *r);	//!< Vector reflect function.
vlInt Intersect(Vector *v);								//!< Vector intersect function.

#endif //VTF_MATHLIB