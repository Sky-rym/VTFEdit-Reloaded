/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include "VMTStringNode.h"

using namespace VTFLib::Nodes;

CVMTStringNode::CVMTStringNode(const vlChar *cName) : CVMTValueNode(cName)
{
	this->cValue = new vlChar[1];
	*this->cValue = '\0';
}

CVMTStringNode::CVMTStringNode(const vlChar *cName, const vlChar *cValue) : CVMTValueNode(cName)
{
	this->cValue = new vlChar[strlen(cValue) + 1];
	strcpy(this->cValue, cValue);
}

CVMTStringNode::CVMTStringNode(const CVMTStringNode &StringNode) : CVMTValueNode(StringNode.GetName())
{
	this->cValue = new vlChar[strlen(StringNode.cValue) + 1];
	strcpy(this->cValue, StringNode.cValue);
}

CVMTStringNode::~CVMTStringNode()
{
	delete this->cValue;
}

vlVoid CVMTStringNode::SetValue(const vlChar *cValue)
{
	delete this->cValue;
	this->cValue = new vlChar[strlen(cValue) + 1];
	strcpy(this->cValue, cValue);
}

const vlChar *CVMTStringNode::GetValue() const
{
	return this->cValue;
}

VMTNodeType CVMTStringNode::GetType() const
{
	return NODE_TYPE_STRING;
}

CVMTNode *CVMTStringNode::Clone() const
{
	return new CVMTStringNode(*this);
}