/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include <vtflib/VMTSingleNode.h>

using namespace VTFLib::Nodes;

CVMTSingleNode::CVMTSingleNode(const vlChar *cName) : CVMTValueNode(cName)
{
	this->fValue = (vlFloat)0.0;
}

#pragma warning( disable : 26495 )
CVMTSingleNode::CVMTSingleNode(const vlChar *cName, const vlChar *cValue) : CVMTValueNode(cName)
{
	this->SetValue(cValue);
}

CVMTSingleNode::CVMTSingleNode(const vlChar *cName, vlFloat fValue) : CVMTValueNode(cName)
{
	this->fValue = fValue;
}

CVMTSingleNode::CVMTSingleNode(const CVMTSingleNode &SingleNode) : CVMTValueNode(SingleNode.GetName())
{
	this->fValue = SingleNode.fValue;
}

CVMTSingleNode::~CVMTSingleNode()
{

}

vlVoid CVMTSingleNode::SetValue(const vlChar *cValue)
{
	this->fValue = (vlFloat)atof(cValue);
}

vlVoid CVMTSingleNode::SetValue(vlFloat fValue)
{
	this->fValue = fValue;
}

const vlFloat CVMTSingleNode::GetValue() const
{
	return this->fValue;
}

VMTNodeType CVMTSingleNode::GetType() const
{
	return NODE_TYPE_SINGLE;
}

CVMTNode *CVMTSingleNode::Clone() const
{
	return new CVMTSingleNode(*this);
}