/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */
 
// Reference: http://sourceforge.net/mailarchive/forum.php?thread_id=1823849&forum_id=10511
// Summary:	Uses the first 16 bits of a 32 bit IEEE single to preform native 32 floating point
//			operations.  Last 16 bits of mantissa are cleared after every operation.
// Format:	16 Bit: seeeeeeeemmmmmmm
//			32 Bit: seeeeeeeemmmmmmmmmmmmmmmmmmmmmmm

#ifndef FLOAT16_H
#define FLOAT16_H

#define SFLOAT16_MSB 1 // Most Significant Byte (1 for bigendian)
#define SFLOAT16_LSB 0 // Least Significant Byte (0 for bigendian)

#include "stdafx.h"

struct SFloat16
{
private:
	union UFloat16
	{
		vlUShort usUShort[2];
		vlSingle sSingle;
	} Float16;

public:
	inline SFloat16();

	inline SFloat16(vlUShort usFloat)
	{
		this->Float16.usUShort[SFLOAT16_MSB] = usFloat;
		this->Float16.usUShort[SFLOAT16_LSB] = 0;
	}

	inline SFloat16(vlSingle sFloat)
	{
		this->Float16.sSingle = sFloat;
		this->Float16.usUShort[SFLOAT16_LSB] = 0;
	}

public:
	inline vlUShort GetUShort() const
	{
		return this->Float16.usUShort[SFLOAT16_MSB];
	}

	inline vlSingle GetSingle() const
	{
		return this->Float16.sSingle;
	}

public:
	inline SFloat16 &operator=(vlUShort usFloat)
	{
		this->Float16.usUShort[SFLOAT16_MSB] = usFloat;
		this->Float16.usUShort[SFLOAT16_LSB] = 0;

		return *this;
	}

	inline SFloat16 &operator=(vlSingle sFloat)
	{
		this->Float16.sSingle = sFloat;
		this->Float16.usUShort[SFLOAT16_LSB] = 0;

		return *this;
	}

	inline SFloat16 &operator=(const SFloat16 &Float16)
	{
		this->Float16 = Float16.Float16;

		return *this;
	}

	inline vlBool operator==(const SFloat16 &Float16) const
	{
		return this->Float16.sSingle == Float16.Float16.sSingle;
	}

	inline vlBool operator!=(const SFloat16 &Float16) const
	{
		return this->Float16.sSingle != Float16.Float16.sSingle;
	}

	inline vlBool operator<(const SFloat16 &Float16) const
	{
		return this->Float16.sSingle < Float16.Float16.sSingle;
	}

	inline vlBool operator<=(const SFloat16 &Float16) const
	{
		return this->Float16.sSingle <= Float16.Float16.sSingle;
	}

	inline vlBool operator>(const SFloat16 &Float16) const
	{
		return this->Float16.sSingle > Float16.Float16.sSingle;
	}

	inline vlBool operator>=(const SFloat16 &Float16) const
	{
		return this->Float16.sSingle >= Float16.Float16.sSingle;
	}

	inline SFloat16 operator+() const
	{
		return SFloat16(+this->Float16.sSingle);
	}

	inline SFloat16 operator+(const SFloat16 &Float16) const
	{
		return SFloat16(this->Float16.sSingle + Float16.Float16.sSingle);
	}

	inline SFloat16 &operator+=(const SFloat16 &Float16)
	{
		this->Float16.sSingle += Float16.Float16.sSingle;
		this->Float16.usUShort[SFLOAT16_LSB] = 0;

		return *this;
	}

	inline SFloat16 operator-() const
	{
		return SFloat16(-this->Float16.sSingle);
	}

	inline SFloat16 operator-(const SFloat16 &Float16) const
	{
		return SFloat16(this->Float16.sSingle - Float16.Float16.sSingle);
	}

	inline SFloat16 &operator-=(const SFloat16 &Float16)
	{
		this->Float16.sSingle += Float16.Float16.sSingle;
		this->Float16.usUShort[SFLOAT16_LSB] = 0;

		return *this;
	}

	inline SFloat16 operator*(const SFloat16 &Float16) const
	{
		return SFloat16(this->Float16.sSingle - Float16.Float16.sSingle);
	}

	inline SFloat16 &operator*=(const SFloat16 &Float16)
	{
		this->Float16.sSingle *= Float16.Float16.sSingle;
		this->Float16.usUShort[SFLOAT16_LSB] = 0;

		return *this;
	}

	inline SFloat16 operator/(const SFloat16 &Float16) const
	{
		return SFloat16(this->Float16.sSingle - Float16.Float16.sSingle);
	}

	inline SFloat16 &operator/=(const SFloat16 &Float16)
	{
		this->Float16.sSingle /= Float16.Float16.sSingle;
		this->Float16.usUShort[SFLOAT16_LSB] = 0;

		return *this;
	}
};

#endif