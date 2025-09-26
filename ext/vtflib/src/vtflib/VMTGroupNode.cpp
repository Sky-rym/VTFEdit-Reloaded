/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include <vtflib/VMTGroupNode.h>

using namespace VTFLib::Nodes;

CVMTGroupNode::CVMTGroupNode(const vlChar *cName) : CVMTNode(cName)
{
	this->VMTNodeList = new CVMTNodeList();
}

#pragma warning( disable : 26495 )
CVMTGroupNode::CVMTGroupNode(const CVMTGroupNode &GroupNode) : CVMTNode(GroupNode.GetName())
{
	for(CVMTNodeList::const_iterator it = GroupNode.VMTNodeList->begin(); it != GroupNode.VMTNodeList->end(); ++it)
	{
		this->AddNode((*it)->Clone());
	}
}

CVMTGroupNode::~CVMTGroupNode()
{
	for(CVMTNodeList::const_iterator it = this->VMTNodeList->begin(); it != this->VMTNodeList->end(); ++it)
	{
		delete *it;
	}

	delete this->VMTNodeList;
}

VMTNodeType CVMTGroupNode::GetType() const
{
	return NODE_TYPE_GROUP;
}

vlUInt CVMTGroupNode::GetNodeCount() const
{
	return (vlUInt)this->VMTNodeList->size();
}

CVMTNode *CVMTGroupNode::AddNode(CVMTNode *VMTNode)
{
	// We can do this because we are friends.
	VMTNode->Parent = this;

	this->VMTNodeList->push_back(VMTNode);

	return VMTNode;
}

CVMTGroupNode *CVMTGroupNode::AddGroupNode(const vlChar *cName)
{
	CVMTGroupNode *Group = new CVMTGroupNode(cName);
	
	this->AddNode(Group);

	return Group;
}

CVMTStringNode *CVMTGroupNode::AddStringNode(const vlChar *cName, const vlChar *cValue)
{
	CVMTStringNode *String = new CVMTStringNode(cName, cValue);
	
	this->AddNode(String);

	return String;
}

CVMTIntegerNode *CVMTGroupNode::AddIntegerNode(const vlChar *cName, vlInt iValue)
{
	CVMTIntegerNode *Integer = new CVMTIntegerNode(cName, iValue);
	
	this->AddNode(Integer);

	return Integer;
}

CVMTSingleNode *CVMTGroupNode::AddSingleNode(const vlChar *cName, vlFloat fValue)
{
	CVMTSingleNode *Single = new CVMTSingleNode(cName, fValue);
	
	this->AddNode(Single);

	return Single;
}

vlVoid CVMTGroupNode::RemoveNode(CVMTNode *VMTNode)
{
	for(CVMTNodeList::const_iterator it = this->VMTNodeList->begin(); it != this->VMTNodeList->end(); ++it)
	{
		if(*it == VMTNode)
		{
			delete *it;
			this->VMTNodeList->remove(*it);

			return;
		}
	}
}

vlVoid CVMTGroupNode::RemoveAllNodes()
{
	for(CVMTNodeList::const_iterator it = this->VMTNodeList->begin(); it != this->VMTNodeList->end(); ++it)
	{
		delete *it;
	}

	this->VMTNodeList->clear();
}

CVMTNode *CVMTGroupNode::GetNode(vlUInt uiIndex) const
{
	vlUInt uiCount = 0;
	for(CVMTNodeList::const_iterator it = this->VMTNodeList->begin(); it != this->VMTNodeList->end(); ++it)
	{
		if(uiCount == uiIndex)
		{
			return *it;
		}
		uiCount++;
	}

	return 0;
}

CVMTNode *CVMTGroupNode::GetNode(const vlChar *cName) const
{
	for(CVMTNodeList::const_iterator it = this->VMTNodeList->begin(); it != this->VMTNodeList->end(); ++it)
	{
		if(stricmp(cName, (*it)->GetName()) == 0)
		{
			return *it;
		}
	}

	return 0;
}

CVMTNode *CVMTGroupNode::Clone() const
{
	return new CVMTGroupNode(*this);
}