#ifndef	VBELEMSURFACEDESCRIPTOR_HPP
#define	VBELEMSURFACEDESCRIPTOR_HPP

#pragma once

#include "HashCommon.hpp"

#include "attributeset.hpp"
#include "BuildingMaterial.hpp"
#include "VBElemOperationsExport.hpp"

class VB_ELEM_OPERATIONS_DLL_EXPORT VBElemSurfaceDescriptor {
private:
	short buildingMaterialIndex;
	short surfaceIndex;

	VBElemSurfaceDescriptor (short buildingMaterialIndex, short surfaceIndex) : buildingMaterialIndex (buildingMaterialIndex), surfaceIndex (surfaceIndex)
	{
	}

public:

	VBElemSurfaceDescriptor (): buildingMaterialIndex (0), surfaceIndex (0) {}

	static VBElemSurfaceDescriptor FromSurface (short surfaceIndex);
	static VBElemSurfaceDescriptor FromBuildingMaterialCutSurface (short buildingMaterialIndex, const ADB::AttributeSetConstRef& attributeSet);

	bool IsSurfaceOfBuildingMaterial () const
	{
		return buildingMaterialIndex > 0;
	}

	short GetBuildMatIndex () const
	{
		DBASSERT (IsSurfaceOfBuildingMaterial ());
		return buildingMaterialIndex;
	}

	short GetSurfaceIndex () const
	{
		return surfaceIndex;
	}

	GSErrCode		QuickRead (GS::IChannel& ic);
	GSErrCode		QuickWrite (GS::OChannel& oc) const;

	operator GS::HashValue () const 
	{
		return GS::GenerateHashValue (buildingMaterialIndex, surfaceIndex);
	}

	bool operator== (const VBElemSurfaceDescriptor& rhs) const 
	{
		return this->buildingMaterialIndex == rhs.buildingMaterialIndex && this->surfaceIndex == rhs.surfaceIndex;
	}

	bool operator != (const VBElemSurfaceDescriptor& rhs) const
	{
		return !this->operator == (rhs);
	}
};


#endif // VBELEMSURFACEDESCRIPTOR_HPP