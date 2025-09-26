/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include <deque>

#include <vtflib/VTFLib.h>
#include <vtflib/VMTWrapper.h>
#include <vtflib/VMTFile.h>

using namespace VTFLib;

namespace VTFLib
{
	std::deque<vlInt> CurrentIndex;
	Nodes::CVMTGroupNode *CurrentNode = 0;
}

//
// vlMaterialBound()
// Returns true if an material is bound, false otherwise.
//
VTFLIB_API vlBool vlMaterialIsBound()
{
	if(!bInitialized)
	{
		LastError.Set("VTFLib not initialized.");
		return vlFalse;
	}

	return Material != 0;
}

//
// vlBindMaterial()
// Bind a material to operate on.
// All library routines will use this material.
//
VTFLIB_API vlBool vlBindMaterial(vlUInt uiMaterial)
{
	if(!bInitialized)
	{
		LastError.Set("VTFLib not initialized.");
		return vlFalse;
	}

	if(uiMaterial >= MaterialVector->size() || (*MaterialVector)[uiMaterial] == 0)
	{
		LastError.Set("Invalid material.");
		return vlFalse;
	}

	if(Material == (*MaterialVector)[uiMaterial])	// If it is already bound do nothing.
		return vlTrue;

	Material = (*MaterialVector)[uiMaterial];

	CurrentIndex.clear();
	CurrentNode = 0;

	return vlTrue;
}

//
// vlCreateMaterial()
// Create an material to work on.
//
VTFLIB_API vlBool vlCreateMaterial(vlUInt *uiMaterial)
{
	if(!bInitialized)
	{
		LastError.Set("VTFLib not initialized.");
		return vlFalse;
	}

	MaterialVector->push_back(new CVMTFile());
	*uiMaterial = (vlUInt)MaterialVector->size() - 1;

	return vlTrue;
}

//
// vlDeleteMaterial()
// Delete a material and all resources associated with it.
//

VTFLIB_API vlVoid vlDeleteMaterial(vlUInt uiMaterial)
{
	if(!bInitialized)
		return;

	if(uiMaterial >= MaterialVector->size())
		return;

	if((*MaterialVector)[uiMaterial] == 0)
		return;

	if((*MaterialVector)[uiMaterial] == Material)
	{
		Material = 0;

		CurrentIndex.clear();
		CurrentNode = 0;
	}

	delete (*MaterialVector)[uiMaterial];
	(*MaterialVector)[uiMaterial] = 0;
}

VTFLIB_API vlBool vlMaterialCreate(const vlChar *cRoot)
{
	if(Material == 0)
	{
		LastError.Set("No material bound.");
		return vlFalse;
	}

	CurrentIndex.clear();
	CurrentNode = 0;

	return Material->Create(cRoot);
}

VTFLIB_API vlVoid vlMaterialDestroy()
{
	if(Material == 0)
	{
		return;
	}

	CurrentIndex.clear();
	CurrentNode = 0;

	Material->Destroy();
}

VTFLIB_API vlBool vlMaterialIsLoaded()
{
	if(Material == 0)
	{
		LastError.Set("No material bound.");
		return vlFalse;
	}

	return Material->IsLoaded();
}

VTFLIB_API vlBool vlMaterialLoad(const vlChar *cFileName)
{
	if(Material == 0)
	{
		LastError.Set("No material bound.");
		return vlFalse;
	}

	CurrentIndex.clear();
	CurrentNode = 0;

	return Material->Load(cFileName);
}

VTFLIB_API vlBool vlMaterialLoadLump(const vlVoid *lpData, vlUInt uiBufferSize)
{
	if(Material == 0)
	{
		LastError.Set("No material bound.");
		return vlFalse;
	}

	CurrentIndex.clear();
	CurrentNode = 0;

	return Material->Load(lpData, uiBufferSize);
}

VTFLIB_API vlBool vlMaterialLoadProc(vlVoid *pUserData)
{
	if(Material == 0)
	{
		LastError.Set("No material bound.");
		return vlFalse;
	}

	CurrentIndex.clear();
	CurrentNode = 0;

	return Material->Load(pUserData);
}

VTFLIB_API vlBool vlMaterialSave(const vlChar *cFileName)
{
	if(Material == 0)
	{
		LastError.Set("No material bound.");
		return vlFalse;
	}

	return Material->Save(cFileName);
}

VTFLIB_API vlBool vlMaterialSaveLump(vlVoid *lpData, vlUInt uiBufferSize, vlUInt *uiSize)
{
	if(Material == 0)
	{
		LastError.Set("No material bound.");
		return vlFalse;
	}

	return Material->Save(lpData, uiBufferSize, *uiSize);
}

VTFLIB_API vlBool vlMaterialSaveProc(vlVoid *pUserData)
{
	if(Material == 0)
	{
		LastError.Set("No material bound.");
		return vlFalse;
	}

	return Material->Save(pUserData);
}

//
// vlMaterialGetCurretNode()
// Gets the current node in the transversal.
//
Nodes::CVMTNode *vlMaterialGetCurretNode()
{
	if(Material == 0 || CurrentNode == 0)
		return 0;

	vlInt iIndex = CurrentIndex.back();

	if(iIndex == -1 || iIndex == (vlInt)CurrentNode->GetNodeCount())
	{
		return CurrentNode;
	}

	return CurrentNode->GetNode((vlUInt)iIndex);
}

//
// vlMaterialGetCurretNode()
// Gets the current node type in the transversal.
//
VMTNodeType vlMaterialGetCurretNodeType()
{
	if(Material == 0 || CurrentNode == 0)
		return NODE_TYPE_COUNT;

	vlInt iIndex = CurrentIndex.back();

	if(iIndex == -1)
	{
		return NODE_TYPE_GROUP;
	}

	if(iIndex == (vlInt)CurrentNode->GetNodeCount())
	{
		return NODE_TYPE_GROUP_END;
	}

	return CurrentNode->GetNode((vlUInt)iIndex)->GetType();
}

//
// vlMaterialGetFirstNode()
// Moves the current node to the stat of the root node.
//
VTFLIB_API vlBool vlMaterialGetFirstNode()
{
	if(Material == 0 || Material->GetRoot() == 0)
		return vlFalse;

	CurrentNode = Material->GetRoot();
	CurrentIndex.push_back(-1);

	return vlTrue;
}

//
// vlMaterialGetLastNode()
// Moves the current node to the end of the root node.
//
VTFLIB_API vlBool vlMaterialGetLastNode()
{
	if(Material == 0 || Material->GetRoot() == 0)
		return vlFalse;

	CurrentNode = Material->GetRoot();
	CurrentIndex.push_back(CurrentNode->GetNodeCount());

	return vlTrue;
}

//
// vlMaterialGetNextNode()
// Moves the current node to the next node depth first style.
//
VTFLIB_API vlBool vlMaterialGetNextNode()
{
	if(Material == 0 || CurrentNode == 0)
		return vlFalse;

	// If we are at the end of the current node, go up a level.
	if(CurrentIndex.back() == (vlInt)CurrentNode->GetNodeCount())
	{
		if(CurrentNode->GetParent() != 0)
		{
			CurrentNode = CurrentNode->GetParent();
			CurrentIndex.pop_back();

			return vlTrue;
		}
		else
		{
			return vlFalse;
		}
	}

	// Go to the next node in the current node.
	CurrentIndex.back()++;

	// Check if we are at the end.
	if(CurrentIndex.back() == (vlInt)CurrentNode->GetNodeCount())
	{
		return vlTrue;
	}

	Nodes::CVMTNode *VMTNode = CurrentNode->GetNode((vlUInt)CurrentIndex.back());

	// If the current node is a group, enter it at the start.
	if(VMTNode->GetType() == NODE_TYPE_GROUP)
	{
		CurrentNode = static_cast<Nodes::CVMTGroupNode *>(VMTNode);
		CurrentIndex.push_back(-1);
	}

	return vlTrue;
}

//
// vlMaterialGetPreviousNode()
// Moves the current node to the previous node depth first style.  This
// is the reverse of vlMaterialGetNextNode().
//
VTFLIB_API vlBool vlMaterialGetPreviousNode()
{
	if(Material == 0 || CurrentNode == 0)
		return vlFalse;

	// If we are at the start of the current node, go up a level.
	if(CurrentIndex.back() == -1)
	{
		if(CurrentNode->GetParent() != 0)
		{
			CurrentNode = CurrentNode->GetParent();
			CurrentIndex.pop_back();

			return vlTrue;
		}
		else
		{
			return vlFalse;
		}
	}

	// Go to the previous node in the current node.
	CurrentIndex.back()--;

	// Check if we are at the start.
	if(CurrentIndex.back() == -1)
	{
		return vlTrue;
	}

	Nodes::CVMTNode *VMTNode = CurrentNode->GetNode((vlUInt)CurrentIndex.back());

	// If the current node is a group, enter it at the end.
	if(VMTNode->GetType() == NODE_TYPE_GROUP)
	{
		CurrentNode = static_cast<Nodes::CVMTGroupNode *>(VMTNode);
		CurrentIndex.push_back(CurrentNode->GetNodeCount());
	}

	return vlTrue;
}

//
// vlMaterialGetParentNode()
// Moves the current node to the current node's parent.
//
VTFLIB_API vlBool vlMaterialGetParentNode()
{
	if(Material == 0 || CurrentNode == 0)
		return vlFalse;

	// If we are not the root node, go up a level.
	if(CurrentNode->GetParent() != 0)
	{
		CurrentNode = CurrentNode->GetParent();
		CurrentIndex.pop_back();

		return vlTrue;
	}

	return vlFalse;
}

//
// vlMaterialGetParentNode()
// Moves the current node to the specified child node of the current node.
//
VTFLIB_API vlBool vlMaterialGetChildNode(const vlChar *cName)
{
	if(Material == 0 || CurrentNode == 0)
		return vlFalse;

	Nodes::CVMTNode *VMTNode = vlMaterialGetCurretNode();

	// Only groups have children.
	if(VMTNode->GetType() != NODE_TYPE_GROUP)
		return vlFalse;

	Nodes::CVMTGroupNode *VMTGroupNode = static_cast<Nodes::CVMTGroupNode *>(VMTNode);

	// Search for the specified child.
	for(vlUInt i = 0; i < VMTGroupNode->GetNodeCount(); i++)
	{
		VMTNode = VMTGroupNode->GetNode(i);
		if(_stricmp(VMTNode->GetName(), cName) == 0)
		{
			// If the child is a group, enter it at the start.
			if(VMTNode->GetType() == NODE_TYPE_GROUP)
			{
				CurrentNode = static_cast<Nodes::CVMTGroupNode *>(VMTNode);
				CurrentIndex.push_back(-1);
			}
			else
			{
				CurrentIndex.back() = (vlInt)i;
			}

			return vlTrue;
		}
	}

	return vlFalse;
}

//
// vlMaterialGetNodeName()
// Gets the current node's name.
//
VTFLIB_API const vlChar *vlMaterialGetNodeName()
{
	Nodes::CVMTNode *VMTNode = vlMaterialGetCurretNode();

	if(VMTNode == 0)
		return 0;

	return VMTNode->GetName();
}

//
// vlMaterialSetNodeName()
// Sets the current node's name.
//
VTFLIB_API vlVoid vlMaterialSetNodeName(const vlChar *cName)
{
	Nodes::CVMTNode *VMTNode = vlMaterialGetCurretNode();

	if(VMTNode == 0)
		return;

	VMTNode->SetName(cName);
}

//
// GetNodeType()
// Get the type of node.  Returns VL_NODE_UNKOWN at the end of a group.
// For example, subsequent calls to vlGetNextNode() may return the following
// structure.  After the last VL_NODE_UNKOWN, vlGetNextNode() will fail.
//
// NODE_TYPE_GROUP
//   NODE_TYPE_GROUP
//     NODE_TYPE_STRING
//     NODE_TYPE_INTEGER
//   NODE_TYPE_GROUP_END
//   NODE_TYPE_GROUP
//     NODE_TYPE_SINGLE
//     NODE_TYPE_SINGLE
//   NODE_TYPE_GROUP_END
//   NODE_TYPE_STRING
// NODE_TYPE_GROUP_END
//
VTFLIB_API VMTNodeType vlMaterialGetNodeType()
{
	return vlMaterialGetCurretNodeType();
}

//
// vlMaterialGetNodeString()
// If the current node is a string node, this gets its value.
//
VTFLIB_API const vlChar *vlMaterialGetNodeString()
{
	Nodes::CVMTNode *VMTNode = vlMaterialGetCurretNode();

	if(VMTNode->GetType() != NODE_TYPE_STRING)
		return 0;

	return static_cast<Nodes::CVMTStringNode *>(VMTNode)->GetValue();
}

//
// vlMaterialSetNodeString()
// If the current node is a string node, this sets its value.
//
VTFLIB_API vlVoid vlMaterialSetNodeString(const vlChar *cValue)
{
	Nodes::CVMTNode *VMTNode = vlMaterialGetCurretNode();

	if(VMTNode->GetType() != NODE_TYPE_STRING)
		return;

	static_cast<Nodes::CVMTStringNode *>(VMTNode)->SetValue(cValue);
}

//
// vlMaterialGetNodeInteger()
// If the current node is a integer node, this gets its value.
//
VTFLIB_API vlUInt vlMaterialGetNodeInteger()
{
	Nodes::CVMTNode *VMTNode = vlMaterialGetCurretNode();

	if(VMTNode->GetType() != NODE_TYPE_INTEGER)
		return 0;

	return static_cast<Nodes::CVMTIntegerNode *>(VMTNode)->GetValue();
}

//
// vlMaterialSetNodeInteger()
// If the current node is a integer node, this sets its value.
//
VTFLIB_API vlVoid vlMaterialSetNodeInteger(vlUInt iValue)
{
	Nodes::CVMTNode *VMTNode = vlMaterialGetCurretNode();

	if(VMTNode->GetType() != NODE_TYPE_INTEGER)
		return;

	static_cast<Nodes::CVMTIntegerNode *>(VMTNode)->SetValue(iValue);
}

//
// vlMaterialGetNodeSingle()
// If the current node is a single node, this gets its value.
//
VTFLIB_API vlFloat vlMaterialGetNodeSingle()
{
	Nodes::CVMTNode *VMTNode = vlMaterialGetCurretNode();

	if(VMTNode->GetType() != NODE_TYPE_SINGLE)
		return 0.0f;

	return static_cast<Nodes::CVMTSingleNode *>(VMTNode)->GetValue();
}

//
// vlMaterialSetNodeSingle()
// If the current node is a single node, this sets its value.
//
VTFLIB_API vlVoid vlMaterialSetNodeSingle(vlFloat sValue)
{
	Nodes::CVMTNode *VMTNode = vlMaterialGetCurretNode();

	if(VMTNode->GetType() != NODE_TYPE_SINGLE)
		return;

	static_cast<Nodes::CVMTSingleNode *>(VMTNode)->SetValue(sValue);
}

//
// vlMaterialAddNodeGroup()
// If the current node is a group node, this adds a group node to the current node.
//
VTFLIB_API vlVoid vlMaterialAddNodeGroup(const vlChar *cName)
{
	Nodes::CVMTNode *VMTNode = vlMaterialGetCurretNode();

	if(VMTNode->GetType() != NODE_TYPE_GROUP)
		return;

	static_cast<Nodes::CVMTGroupNode *>(VMTNode)->AddGroupNode(cName);
}

//
// vlMaterialAddNodeString()
// If the current node is a group node, this adds a string node to the current node.
//
VTFLIB_API vlVoid vlMaterialAddNodeString(const vlChar *cName, const vlChar *cValue)
{
	Nodes::CVMTNode *VMTNode = vlMaterialGetCurretNode();

	if(VMTNode->GetType() != NODE_TYPE_GROUP)
		return;

	static_cast<Nodes::CVMTGroupNode *>(VMTNode)->AddStringNode(cName, cValue);
}

//
// vlMaterialAddNodeInteger()
// If the current node is a group node, this adds a integer node to the current node.
//
VTFLIB_API vlVoid vlMaterialAddNodeInteger(const vlChar *cName, vlUInt iValue)
{
	Nodes::CVMTNode *VMTNode = vlMaterialGetCurretNode();

	if(VMTNode->GetType() != NODE_TYPE_GROUP)
		return;

	static_cast<Nodes::CVMTGroupNode *>(VMTNode)->AddIntegerNode(cName, iValue);
}

//
// vlMaterialAddNodeSingle()
// If the current node is a group node, this adds a single node to the current node.
//
VTFLIB_API vlVoid vlMaterialAddNodeSingle(const vlChar *cName, vlFloat sValue)
{
	Nodes::CVMTNode *VMTNode = vlMaterialGetCurretNode();

	if(VMTNode->GetType() != NODE_TYPE_GROUP)
		return;

	static_cast<Nodes::CVMTGroupNode *>(VMTNode)->AddSingleNode(cName, sValue);
}