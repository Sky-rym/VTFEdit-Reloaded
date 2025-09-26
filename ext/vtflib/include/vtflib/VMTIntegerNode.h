/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#ifndef VMTINTEGERNODE_H
#define VMTINTEGERNODE_H

#include "stdafx.h"
#include "VMTValueNode.h"

namespace VTFLib
{
	namespace Nodes
	{
		class VTFLIB_API CVMTIntegerNode : public CVMTValueNode
		{
		private:
			vlInt iValue;

		public:
			CVMTIntegerNode(const vlChar *cName);
			CVMTIntegerNode(const vlChar *cName, const vlChar *cValue);
			CVMTIntegerNode(const vlChar *cName, vlInt iValue);
			CVMTIntegerNode(const CVMTIntegerNode &IntegerNode);
			virtual ~CVMTIntegerNode();

			virtual vlVoid SetValue(const vlChar *cValue);

			vlVoid SetValue(vlInt iValue);
			const vlInt GetValue() const;

			virtual VMTNodeType GetType() const;
			virtual CVMTNode *Clone() const;
		};
	}
}

#endif