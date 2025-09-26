/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#ifndef VMTSTRINGNODE_H
#define VMTSTRINGNODE_H

#include "stdafx.h"
#include "VMTValueNode.h"

namespace VTFLib
{
	namespace Nodes
	{
		class VTFLIB_API CVMTStringNode : public CVMTValueNode
		{
		private:
			vlChar *cValue;

		public:
			CVMTStringNode(const vlChar *cName);
			CVMTStringNode(const vlChar *cName, const vlChar *cValue);
			CVMTStringNode(const CVMTStringNode &StringNode);
			virtual ~CVMTStringNode();

			virtual vlVoid SetValue(const vlChar *cValue);

			const vlChar *GetValue() const;

			virtual VMTNodeType GetType() const;
			virtual CVMTNode *Clone() const;
		};
	}
}

#endif