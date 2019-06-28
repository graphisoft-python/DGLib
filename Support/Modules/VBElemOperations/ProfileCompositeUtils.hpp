#ifndef PROFILECOMPOSITEUTILS_HPP
#define PROFILECOMPOSITEUTILS_HPP

#pragma once

#include "VBElemOperationsExport.hpp"
#include "VBElemSurfaceDescriptor.hpp"
#include "ProfileTypes.hpp"


void VB_ELEM_OPERATIONS_DLL_EXPORT GetMinMaxMaterial (const ADB::AttributeSetConstRef& attrSet, 
													  const VBElem::ProfileDescriptorRef& profileDescriptior, 
													  double height,
													  const VBElemSurfaceDescriptor& defaultSurfaceDescriptor,
													  VBElemSurfaceDescriptor& minMat, VBElemSurfaceDescriptor& maxMat);


#endif
