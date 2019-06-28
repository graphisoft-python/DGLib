// Contact person :	KiP

#ifndef GDLPARAM_ACCESSOR_HPP
#define GDLPARAM_ACCESSOR_HPP

#pragma once

// === Includes ========================================================================================================

// from GDL
#include "GDLPars.h"

// from VBElements
#include "GDLBasedElem.hpp"
#include "GDLBasedElemDefault.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"

// =====================================================================================================================

namespace GDLOperations {

DECLARE_EXCEPTION_CLASS (GDLParamAccessorException, GS::LogicErrorException, Error, VB_ELEM_OPERATIONS_DLL_EXPORT)


class VB_ELEM_OPERATIONS_DLL_EXPORT ModifyGDLParamPostProcess
{
public:
	virtual ~ModifyGDLParamPostProcess ();
	virtual void Execute (const EDB::GeneralElemRef& generalElem, const GS::UniString& modifiedParamName) = 0;
};

typedef GS::Ref<ModifyGDLParamPostProcess> ModifyGDLParamPostProcessRef;



class VB_ELEM_OPERATIONS_DLL_EXPORT GDLParamAccessor
{
public:
	GDLParamAccessor (const VBElem::GDLBasedElemConstRef& gdlBasedElem);
	GDLParamAccessor (const VBElem::GDLBasedElemRef& gdlBasedElem, const ModifyGDLParamPostProcessRef& modifyPostProcess);
	GDLParamAccessor (const VBElem::GDLBasedElemDefault* gdlBasedElemDef);

	virtual ~GDLParamAccessor ();

	bool	IsExistingParam		(const GS::UniString& paramName) const;
	bool	IsHiddenParam		(const GS::UniString& paramName) const;
	bool	IsDisabledParam		(const GS::UniString& paramName) const;

	template <typename ParamType>
	ParamType	GetParamValue	(const GS::UniString& paramName) const;
	template <typename ParamType>
	ParamType	GetParamValueWithFallback (const GS::UniString& paramName, ParamType fallbackValue) const;

	template <typename ParamType>
	void		SetParamValue	(const GS::UniString& paramName, const ParamType& newValue) const;

private:
	class VB_ELEM_OPERATIONS_DLL_EXPORT AddParPtr
	{
	public:
		AddParPtr (const VBElem::GDLBasedElemConstRef& gdlBasedElem);
		AddParPtr (const VBElem::GDLBasedElemDefault* gdlBasedElemDef);

		const GSPtr		GetPtr () const;
		Int32			GetParamIdx (const GS::UniString& paramName) const;
		unsigned char	GetParamFlags (Int32 paramIndex) const;

	private:
		const GSPtr addParPtr;
	};

	class VB_ELEM_OPERATIONS_DLL_EXPORT AddParHdlScope
	{
	public:
		AddParHdlScope (const VBElem::GDLBasedElemConstRef& gdlBasedElem);
		AddParHdlScope (const VBElem::GDLBasedElemDefault* gdlBasedElemDef);
		~AddParHdlScope ();

		GSHandle		GetHandle () const;
		Int32			GetParamIdx (const GS::UniString& paramName);
		unsigned char	GetParamFlags (Int32 paramIndex);

	private:
		GSHandle addParHdl;
	};	

	AddParPtr		GetAddParPtr () const;
	AddParHdlScope	CreateAddParHdlScope () const;

private:
	VBElem::GDLBasedElemConstRef gdlBasedElem;
	VBElem::GDLBasedElemRef editableGdlBasedElem;
	const VBElem::GDLBasedElemDefault* gdlBasedElemDef;
	ModifyGDLParamPostProcessRef modifyPostProcess;

	template <typename ParamType>
	static ParamType GetValueFromAddPar (const GSPtr addParPtr, Int32 paramIndex, GSErr& errCode);

	template <typename ParamType>
	static GSErr SetValueToAddPar (GSHandle addParHdl, Int32 paramIndex, const ParamType& newValue);

	enum class GetParamValueResult {
		Succeeded,
		MissingParameter,
		TypeIncompatibility
	};

	template <typename ParamType>
	GetParamValueResult	GetParamValueNoThrow (const GS::UniString& paramName, ParamType& paramOut) const;
};

template <typename ParamType>
ParamType	GDLParamAccessor::GetParamValue (const GS::UniString& paramName) const
{
	ParamType retVal;
	switch (GetParamValueNoThrow (paramName, retVal)) {
		case GetParamValueResult::Succeeded:
			return retVal;
		case GetParamValueResult::MissingParameter:
			DBBREAK_STR_GUID ("GDL parameter with this name does not exists!", "{0EE2C56C-3884-4E5C-9F02-60EFC3006BA1}");
			throw GDLParamAccessorException ();
		case GetParamValueResult::TypeIncompatibility:
			DBBREAK_STR_GUID ("Probably the type of the GDL parameter is not compatible with ParamType template argument!", "{F79A6251-DCFD-46A4-8862-722250E3E9F1}");
			throw GDLParamAccessorException ();
		default:
			DBBREAK ();
			throw GDLParamAccessorException ();
	}
}


template <typename ParamType>
GDLParamAccessor::GetParamValueResult GDLParamAccessor::GetParamValueNoThrow (const GS::UniString& paramName, ParamType& paramOut) const
{
	AddParPtr addPar = GetAddParPtr ();
	const Int32 paramIndex = addPar.GetParamIdx (paramName.ToCStr ().Get ());
	if (paramIndex < 0) {
		return GetParamValueResult::MissingParameter;
	}
	GSErr errCode;
	paramOut = GDLParamAccessor::GetValueFromAddPar<ParamType> (addPar.GetPtr (), paramIndex, errCode);
	if (errCode == NoError) {
		return GetParamValueResult::Succeeded;
	} else {
		return GetParamValueResult::TypeIncompatibility;
	}
}

template <typename ParamType>
ParamType GDLParamAccessor::GetParamValueWithFallback (const GS::UniString& paramName, ParamType fallbackValue) const
{
	ParamType retValue;
	if (GetParamValueNoThrow (paramName, retValue) == GetParamValueResult::Succeeded) {
		return retValue;
	} else {
		return fallbackValue;
	} 
}

template <>
VB_ELEM_OPERATIONS_DLL_EXPORT double GDLParamAccessor::GetValueFromAddPar<double> (const GSPtr addParPtr, Int32 paramIndex, GSErr& errCode);

template <>
VB_ELEM_OPERATIONS_DLL_EXPORT bool GDLParamAccessor::GetValueFromAddPar<bool> (const GSPtr addParPtr, Int32 paramIndex, GSErr& errCode);

template <>
VB_ELEM_OPERATIONS_DLL_EXPORT Int32 GDLParamAccessor::GetValueFromAddPar<Int32> (const GSPtr addParPtr, Int32 paramIndex, GSErr& errCode);

template <>
VB_ELEM_OPERATIONS_DLL_EXPORT GS::UniString GDLParamAccessor::GetValueFromAddPar<GS::UniString> (const GSPtr addParPtr, Int32 paramIndex, GSErr& errCode);

template <typename ParamType>
void GDLParamAccessor::SetParamValue (const GS::UniString& paramName, const ParamType& newValue) const
{
	if (editableGdlBasedElem == nullptr) {
		DBBREAK_STR_GUID ("GDLBasedElem is not editable!", "{B243FDDC-29DC-48E1-8500-6213F2E64D5E}");
		return;
	}

	AddParHdlScope addParScope = CreateAddParHdlScope ();
	const Int32 paramIndex = addParScope.GetParamIdx (paramName.ToCStr ().Get ());
	if (paramIndex < 0) {
		DBBREAK_STR_GUID ("GDL parameter with this name does not exists!", "{3B911F33-8115-4941-BEE6-415B46C4073F}");
		throw GDLParamAccessorException ();
	}
	GSHandle addParHdl = addParScope.GetHandle ();
	GSErr errCode = GDLParamAccessor::SetValueToAddPar<ParamType> (addParHdl, paramIndex, newValue);
	if (errCode != NoError) {
		DBBREAK_STR_GUID ("Probably the type of the GDL parameter is not compatible with ParamType template argument!", "{C000BFBE-8DDC-4BCD-A59C-7E30688D03A6}");
		throw GDLParamAccessorException ();
	}
	const bool success = VBElem::GDLBasedElem::SetAddParHdl (editableGdlBasedElem, &addParHdl);
	if (DBERROR (!success)) {
		throw GDLParamAccessorException ();
	}
	if (modifyPostProcess != nullptr) {
		modifyPostProcess->Execute (editableGdlBasedElem.As<EDB::GeneralElem> (), paramName);
	}
}

template <>
VB_ELEM_OPERATIONS_DLL_EXPORT GSErr GDLParamAccessor::SetValueToAddPar<double> (GSHandle addParHdl, Int32 paramIndex, const double& newValue);

template <>
VB_ELEM_OPERATIONS_DLL_EXPORT GSErr GDLParamAccessor::SetValueToAddPar<Int32> (GSHandle addParHdl, Int32 paramIndex, const Int32& newValue);

template <>
VB_ELEM_OPERATIONS_DLL_EXPORT GSErr GDLParamAccessor::SetValueToAddPar<bool> (GSHandle addParHdl, Int32 paramIndex, const bool& newValue);

template <>
VB_ELEM_OPERATIONS_DLL_EXPORT GSErr GDLParamAccessor::SetValueToAddPar<GS::UniString> (GSHandle addParHdl, Int32 paramIndex, const GS::UniString& newValue);

}

#endif
