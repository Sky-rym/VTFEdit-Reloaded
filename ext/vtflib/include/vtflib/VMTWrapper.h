/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#ifndef VTFWRAPPER_H
#define VTFWRAPPER_H

#include "stdafx.h"

#ifdef __cplusplus
extern "C" {
#endif

//
// Memory managment routines.
//

VTFLIB_API vlBool vlMaterialIsBound();
VTFLIB_API vlBool vlBindMaterial(vlUInt uiMaterial);

VTFLIB_API vlBool vlCreateMaterial(vlUInt *uiMaterial);
VTFLIB_API vlVoid vlDeleteMaterial(vlUInt uiMaterial);

//
// Library routines.  (Basically class wrappers.)
//

VTFLIB_API vlBool vlMaterialCreate(const vlChar *cRoot);
VTFLIB_API vlVoid vlMaterialDestroy();

VTFLIB_API vlBool vlMaterialIsLoaded();

VTFLIB_API vlBool vlMaterialLoad(const vlChar *cFileName);
VTFLIB_API vlBool vlMaterialLoadLump(const vlVoid *lpData, vlUInt uiBufferSize);
VTFLIB_API vlBool vlMaterialLoadProc(vlVoid *pUserData);

VTFLIB_API vlBool vlMaterialSave(const vlChar *cFileName);
VTFLIB_API vlBool vlMaterialSaveLump(vlVoid *lpData, vlUInt uiBufferSize, vlUInt *uiSize);
VTFLIB_API vlBool vlMaterialSaveProc(vlVoid *pUserData);

//
// Node routines.
//

VTFLIB_API vlBool vlMaterialGetFirstNode();
VTFLIB_API vlBool vlMaterialGetLastNode();
VTFLIB_API vlBool vlMaterialGetNextNode();
VTFLIB_API vlBool vlMaterialGetPreviousNode();

VTFLIB_API vlBool vlMaterialGetParentNode();
VTFLIB_API vlBool vlMaterialGetChildNode(const vlChar *cName);

VTFLIB_API const vlChar *vlMaterialGetNodeName();
VTFLIB_API vlVoid vlMaterialSetNodeName(const vlChar *cName);

VTFLIB_API VMTNodeType vlMaterialGetNodeType();

VTFLIB_API const vlChar *vlMaterialGetNodeString();
VTFLIB_API vlVoid vlMaterialSetNodeString(const vlChar *cValue);

VTFLIB_API vlUInt vlMaterialGetNodeInteger();
VTFLIB_API vlVoid vlMaterialSetNodeInteger(vlUInt iValue);

VTFLIB_API vlFloat vlMaterialGetNodeSingle();
VTFLIB_API vlVoid vlMaterialSetNodeSingle(vlFloat sValue);

VTFLIB_API vlVoid vlMaterialAddNodeGroup(const vlChar *cName);
VTFLIB_API vlVoid vlMaterialAddNodeString(const vlChar *cName, const vlChar *cValue);
VTFLIB_API vlVoid vlMaterialAddNodeInteger(const vlChar *cName, vlUInt iValue);
VTFLIB_API vlVoid vlMaterialAddNodeSingle(const vlChar *cName, vlFloat sValue);

#ifdef __cplusplus
}
#endif

#endif