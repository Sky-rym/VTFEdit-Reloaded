/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#ifndef VMTNODE_H
#define VMTNODE_H

#include "stdafx.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum tagVMTNodeType
{
	NODE_TYPE_GROUP = 0,
	NODE_TYPE_GROUP_END,
	NODE_TYPE_STRING,
	NODE_TYPE_INTEGER,
	NODE_TYPE_SINGLE,
	NODE_TYPE_COUNT
} VMTNodeType;

#ifdef __cplusplus
}
#endif

namespace VTFLib
{
	namespace Nodes
	{
		class CVMTGroupNode;

		class VTFLIB_API CVMTNode
		{
		private:
			friend class CVMTGroupNode;	// For direct parent setting.

		private:
			vlChar *cName;
			CVMTGroupNode *Parent;

		public:
			CVMTNode(const vlChar *cName);
			virtual ~CVMTNode();

			const vlChar *GetName() const;
			vlVoid SetName(const vlChar *cName);

			CVMTGroupNode *GetParent();

			virtual VMTNodeType GetType() const = 0;
			virtual CVMTNode *Clone() const = 0;
		};
	}
}

#endif