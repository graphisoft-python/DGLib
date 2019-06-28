#ifndef	MODELELEM_COMPONENT_ID_HPP
#define	MODELELEM_COMPONENT_ID_HPP

#pragma once

// === Includes ========================================================================================================

// from GSRoot
#include "ClassInfo.hpp"
#include "HashCommon.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"

// === Predeclarations =================================================================================================

namespace GS {
	class OutputFrame;
	class InputFrame;
}

// =====================================================================================================================

namespace VBEO {

class VB_ELEM_OPERATIONS_DLL_EXPORT ModelElemComponentId
{
	static GS::ClassInfo classInfo;
public:
	class VB_ELEM_OPERATIONS_DLL_EXPORT SubElementId
	{
		static GS::ClassInfo classInfo;
	public:
		SubElementId ();
		SubElementId (const GS::Guid& guid);

		bool operator== (const SubElementId& other) const;
		bool operator!= (const SubElementId& other) const;

		operator GS::HashValue () const;

		const GS::Guid&	GetGuid () const;

		GSErrCode	Write (GS::OChannel& oc) const;
		GSErrCode	Read (GS::IChannel& ic);
	
	private:
		GSErrCode	WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
		GSErrCode	ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);

		GS::Guid guid;
	};

	static const Int32 MissingComponentIndex = -1;
	static const Int32 BasicComponentIndex = 0;
	static const Int32 ColumnCoreComponentIndex = 0;
	static const Int32 ColumnVeneerComponentIndex = 1;

	ModelElemComponentId ();
	explicit ModelElemComponentId (Int32 componentIndex);
	explicit ModelElemComponentId (Int32 componentIndex, const SubElementId& subElementId);
	
	bool operator== (const ModelElemComponentId& other) const;
	bool operator!= (const ModelElemComponentId& other) const;

	operator GS::HashValue () const;
	
	bool					IsValid () const;
	Int32					GetComponentIndex () const;
	bool					HasSubElementId () const;
	const SubElementId&		GetSubElementId () const;

	ModelElemComponentId	ExtendWithSubElementId (const SubElementId& subElementId) const;

	GSErrCode	Write (GS::OChannel& oc) const;
	GSErrCode	Read (GS::IChannel& ic);

private:
	GSErrCode	WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode	ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);

	Int32 componentIndex;
	SubElementId subElementId;
};


VB_ELEM_OPERATIONS_DLL_EXPORT
ModelElemComponentId CreateBasicComponentId (const ModelElemComponentId::SubElementId& subElemId = ModelElemComponentId::SubElementId ());

}

#endif
