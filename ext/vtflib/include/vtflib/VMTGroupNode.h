/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#ifndef VMTGROUPNODE_H
#define VMTGROUPNODE_H

#include "stdafx.h"
#include "VMTNode.h"

#include "VMTStringNode.h"
#include "VMTIntegerNode.h"
#include "VMTSingleNode.h"

#include <list>

namespace VTFLib
{
	class CVMTFile;

	namespace Nodes
	{
		class VTFLIB_API CVMTGroupNode : public CVMTNode
		{
		//private:
		//	friend class CVMTFile;	// For direct node addition.

		private:
			typedef std::list<CVMTNode *> CVMTNodeList;

		private:
			CVMTNodeList *VMTNodeList;

		public:
			CVMTGroupNode(const vlChar *cName);
			CVMTGroupNode(const CVMTGroupNode &GroupNode);
			virtual ~CVMTGroupNode();

			virtual VMTNodeType GetType() const;
			virtual CVMTNode *Clone() const;

		public:
			vlUInt GetNodeCount() const;

			CVMTNode *AddNode(CVMTNode *VMTNode);
			CVMTGroupNode *AddGroupNode(const vlChar *cName);
			CVMTStringNode *AddStringNode(const vlChar *cName, const vlChar *cValue);
			CVMTIntegerNode *AddIntegerNode(const vlChar *cName, vlInt iValue);
			CVMTSingleNode *AddSingleNode(const vlChar *cName, vlFloat fValue);

			vlVoid RemoveNode(CVMTNode *VMTNode);
			vlVoid RemoveAllNodes();

			CVMTNode *GetNode(vlUInt uiIndex) const;
			CVMTNode *GetNode(const vlChar *cName) const;		
		};
	}
}

#endif