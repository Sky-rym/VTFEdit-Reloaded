/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#ifndef VMTSINGLENODE_H
#define VMTSINGLENODE_H

#include "stdafx.h"
#include "VMTValueNode.h"

namespace VTFLib
{
	namespace Nodes
	{
		class VTFLIB_API CVMTSingleNode : public CVMTValueNode
		{
		private:
			vlFloat fValue;

		public:
			CVMTSingleNode(const vlChar *cName);
			CVMTSingleNode(const vlChar *cName, const vlChar *cValue);
			CVMTSingleNode(const vlChar *cName, vlFloat fValue);
			CVMTSingleNode(const CVMTSingleNode &SingleNode);
			virtual ~CVMTSingleNode();

			virtual vlVoid SetValue(const vlChar *cValue);

			vlVoid SetValue(vlFloat fValue);
			const vlFloat GetValue() const;

			virtual VMTNodeType GetType() const;
			virtual CVMTNode *Clone() const;
		};
	}
}

#endif