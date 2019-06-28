// *********************************************************************************************************************
// Description:		GDLParamInterface.hpp
//
// Module:			GDL
// Namespace:		GDL
// Contact person:	KV
// *********************************************************************************************************************

#ifndef GDLPARAMINTERFACE_HPP
#define GDLPARAMINTERFACE_HPP

#include "GDLPars.h"
#include "GDLExport.h"

namespace GDLParam
{

/****************************************************************************/
/*																			*/
/*					Interface for access GDL parameters.					*/
/*																			*/
/****************************************************************************/
class GDL_CPP_DLL_EXPORT ParamInterface
{
public:
	virtual ~ParamInterface ();

	virtual Int32			GetIndexOfName	(const char* name) const = 0;
	virtual GSErr			GetVarName		(Int32 index, char* name, Int32 buffSize) const = 0;
	virtual short			GetVarType		(Int32 index, bool* isArray = nullptr, Int32* dim1 = nullptr, Int32* dim2 = nullptr,
											 GSErr* err = nullptr) const = 0;	
	virtual unsigned char	GetVarFlags		(Int32 index, GSErr* err = nullptr) const = 0;
	virtual Int32			GetVarNumber	() const = 0;

	virtual double	GetNumVar		(Int32 index, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr) const = 0;
	virtual Int32	GetIntVar		(Int32 index, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr) const = 0;
	virtual GSErr	GetUStrVar		(Int32 index, GS::UniString& retVal) const = 0;


	virtual double	GetNumArrayVal	(Int32 index, Int32 ind1, Int32 ind2, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr) const = 0;
	virtual Int32	GetIntArrayVal	(Int32 index, Int32 ind1, Int32 ind2, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr) const = 0;
	virtual GSPtr   GetUArrayVar (Int32 index, Int32 *len = nullptr, short *type = nullptr, Int32 *dim1 = nullptr,
								  Int32 *dim2 = nullptr) const = 0;	
	virtual GSPtr	GetUArrayDescription (Int32 index, Int32 *len = nullptr, short *type = nullptr, Int32 *dim1 = nullptr,
										  Int32 *dim2 = nullptr) const = 0;
};

/****************************************************************************/
/*																			*/
/*				Class for access parameters from handle.					*/
/*																			*/
/****************************************************************************/
class GDL_CPP_DLL_EXPORT ParamList : public ParamInterface
{
public:
	ParamList (const GSConstHandle& varHdl);
	ParamList (const GSConstPtr& varPtr);
	
	virtual Int32			GetIndexOfName	(const char* name) const override;
	virtual GSErr			GetVarName		(Int32 index, char* name, Int32 buffSize) const override;
	virtual short			GetVarType		(Int32 index, bool* isArray, Int32* dim1, Int32* dim2,
											 GSErr* err) const override;
	virtual unsigned char	GetVarFlags		(Int32 index, GSErr* err) const override;
	virtual Int32			GetVarNumber () const override;

	virtual double	GetNumVar		(Int32 index, GSErr* err, GS::UniString* numValDescription) const override;
	virtual Int32	GetIntVar		(Int32 index, GSErr* err, GS::UniString* numValDescription) const override;
	virtual GSErr	GetUStrVar		(Int32 index, GS::UniString& retVal) const override;


	virtual double	GetNumArrayVal	(Int32 index, Int32 ind1, Int32 ind2, GSErr* err, GS::UniString* numValDescription) const override;
	virtual Int32	GetIntArrayVal	(Int32 index, Int32 ind1, Int32 ind2, GSErr* err, GS::UniString* numValDescription) const override;
	virtual GSPtr   GetUArrayVar (Int32 index, Int32 *len, short *type, Int32 *dim1,
								  Int32 *dim2) const override;
	virtual GSPtr	GetUArrayDescription (Int32 index, Int32 *len, short *type, Int32 *dim1,
										  Int32 *dim2) const override;

protected:
	GSConstPtr varPtr;
};

}

#endif
