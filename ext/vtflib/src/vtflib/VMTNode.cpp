/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include <vtflib/VMTNode.h>

using namespace VTFLib::Nodes;

CVMTNode::CVMTNode(const vlChar *cName)
{
	this->cName = new vlChar[strlen(cName) + 1];
	strcpy(this->cName, cName);

	this->Parent = 0;
}

CVMTNode::~CVMTNode()
{
	delete []this->cName;
}

vlVoid CVMTNode::SetName(const vlChar *cName)
{
	delete []this->cName;
	this->cName = new vlChar[strlen(cName) + 1];
	strcpy(this->cName, cName);
}

const vlChar *CVMTNode::GetName() const
{
	return this->cName;
}

CVMTGroupNode *CVMTNode::GetParent()
{
	return this->Parent;
}