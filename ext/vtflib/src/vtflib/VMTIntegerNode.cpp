/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include <vtflib/VMTIntegerNode.h>

using namespace VTFLib::Nodes;

CVMTIntegerNode::CVMTIntegerNode(const vlChar *cName) : CVMTValueNode(cName)
{
	this->iValue = 0;
}

#pragma warning( disable : 26495 )
CVMTIntegerNode::CVMTIntegerNode(const vlChar *cName, const vlChar *cValue) : CVMTValueNode(cName)
{
	this->SetValue(cValue);
}

CVMTIntegerNode::CVMTIntegerNode(const vlChar *cName, vlInt iValue) : CVMTValueNode(cName)
{
	this->iValue = iValue;
}

CVMTIntegerNode::CVMTIntegerNode(const CVMTIntegerNode &IntegerNode) : CVMTValueNode(IntegerNode.GetName())
{
	this->iValue = IntegerNode.iValue;
}

CVMTIntegerNode::~CVMTIntegerNode()
{

}

vlVoid CVMTIntegerNode::SetValue(const vlChar *cValue)
{
	this->iValue = atoi(cValue);
}

vlVoid CVMTIntegerNode::SetValue(vlInt iValue)
{
	this->iValue = iValue;
}

const vlInt CVMTIntegerNode::GetValue() const
{
	return this->iValue;
}

VMTNodeType CVMTIntegerNode::GetType() const
{
	return NODE_TYPE_INTEGER;
}

CVMTNode *CVMTIntegerNode::Clone() const
{
	return new CVMTIntegerNode(*this);
}