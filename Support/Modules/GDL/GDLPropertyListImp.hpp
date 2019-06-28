// *********************************************************************************************************************
// Description:		GDLPropertyListImp.hpp
//
// Module:			GDL
// Namespace:		GDL
// Contact person:	HK
//
// *********************************************************************************************************************

#include	"GSRoot.hpp"

#include "GDLDefs.h"
#include "GDLPars.h"
#include "CommonSize.h"

namespace GDL {

template<class UserDataType>
void PropertyList<UserDataType>::Create (ULong nr)
{
	this->Clear ();
	while (nr--)
		PushEntry ("", GS::PropertyList<UserDataType>::Integer, GS::PropertyList<UserDataType>::Scalar, 0, 0);
}

template<class UserDataType>
GSHandle PropertyList<UserDataType>::WriteToAddParHandle () const
{
	struct VarDataHead {
		Int32			varNr;			// number of variables in the handle
		short			version;
		short			dummy_1;
		Int32			dummy_2;
		Int32			dummy_3;
	};

	struct VarDataRec {
		short			dataType;		// data type: ParT_Integer, ParT_Length...	 etc.
		char			isArray;
		unsigned char	flags;			// status flags
		Int32			dim1;			// 1st dimension of array
		Int32			dim2;			// 2nd dimension of array
		char			isFix;
		char			filler0[3];
		union {
			struct {
				Int32	lng;			// if dataType is integer (see function GDLIsIntType)
				Int32	filler1;
			} lng;
			double		dbl;			// if dataType is numeric but not integer
		} value;
		char			name[MAXNAM];	// name
		ULong			valOffs;		// string/array offset, if data is string/array
		ULong			valLen;			// string/array length
		ULong			valDescriptionLen;		// length of value description(s)
	};

	const ULong enNum = this->GetEntryNum ();
	ULong alloc = sizeof (VarDataHead) + enNum * sizeof (VarDataRec);

	for (ULong i = 0; i < enNum; i++) {
		typename GS::PropertyList<UserDataType>::ArrayType at;
		ULong d1, d2;
		typename GS::PropertyList<UserDataType>::StorageType st = this->GetEntryType (i, &at, &d1, &d2);

		if (at != GS::PropertyList<UserDataType>::Scalar || st == GS::PropertyList<UserDataType>::String) {
			ULong len;
			this->GetArray (i, &len);
			alloc += len;
		}
		if (st != GS::PropertyList<UserDataType>::String) {
			ULong len;
			if (at != GS::PropertyList<UserDataType>::Scalar) {
				len = GS::RoundUp8 (at == GS::PropertyList<UserDataType>::OneDimensional ? d1 * (ULong) sizeof (GS::uchar_t) : d1 * d2 * (ULong) sizeof (GS::uchar_t));		// empty value descriptions for numerical array elements
			} else {
				len = GS::RoundUp8 (1 * (ULong) sizeof (GS::uchar_t));  // empty value description for simple numerical element
			}
			alloc += len;
		}
	}

	GSHandle addPar = BMhAllClear (alloc);
	if (addPar == nullptr)
		throw GS::GSException ();

	VarDataHead* const head = (VarDataHead*) *addPar;
	VarDataRec* rec = (VarDataRec*) (head + 1);

	head->varNr = enNum;
	head->version = 24;
	// TODO VS: Curr_SyParVersion-re static assert!
	// Up-to-date raw structure must be filled correctly
	//static_assert (Curr_SyParVersion == 24, "Needs to be implemented when incrementing SyParVersion");

	for (ULong i = 0, offset = sizeof (VarDataHead) + enNum * sizeof (VarDataRec); i < enNum; i++, rec++) {
		this->GetEntryName (i, rec->name, sizeof (rec->name));

		typename GS::PropertyList<UserDataType>::ArrayType at;
		ULong d1, d2;
		typename GS::PropertyList<UserDataType>::StorageType st = this->GetEntryType (i, &at, &d1, &d2);

		rec->valOffs = offset;
		if (at != GS::PropertyList<UserDataType>::Scalar || st == GS::PropertyList<UserDataType>::String) {
			const void* val = this->GetArray (i, &rec->valLen);
			memcpy (*addPar + offset, val, rec->valLen);
		}
		if (st != GS::PropertyList<UserDataType>::String) {
			if (at != GS::PropertyList<UserDataType>::Scalar) {
				rec->valDescriptionLen = GS::RoundUp8 (at == GS::PropertyList<UserDataType>::OneDimensional ? d1 * (ULong) sizeof (GS::uchar_t) : d1 * d2 * (ULong) sizeof (GS::uchar_t));		// empty value descriptions for numerical array elements
				rec->valLen += rec->valDescriptionLen;
			} else {
				rec->valDescriptionLen = GS::RoundUp8 (1 * (ULong) sizeof (GS::uchar_t));  // empty value description for simple numerical element
				rec->valLen = rec->valDescriptionLen;
			}
		}
		offset += rec->valLen;

		switch (st) {
			case GS::PropertyList<UserDataType>::Integer:
				rec->dataType = ParT_Integer;
				break;
			case GS::PropertyList<UserDataType>::Numeric:
				rec->dataType = ParT_RealNum;
				break;
			case GS::PropertyList<UserDataType>::String:
				rec->dataType = ParT_CString;
				break;
		}

		switch (at) {
			case GS::PropertyList<UserDataType>::Scalar:
				switch (st) {
					case GS::PropertyList<UserDataType>::Integer:
						rec->value.lng.lng = this->GetIntEntry (i);
						break;
					case GS::PropertyList<UserDataType>::Numeric:
						rec->value.dbl = this->GetNumEntry (i);
						break;
					case GS::PropertyList<UserDataType>::String:
						break;
				}
				d1 = 0;
				d2 = 0;
				break;
			case GS::PropertyList<UserDataType>::OneDimensional:
				d2 = 0;
				break;
			case GS::PropertyList<UserDataType>::TwoDimensional:
				// nothing to do - dimensions are set
				break;
		}

		rec->isArray = d1 != 0 ? 1 : 0;
		rec->dim1 = d1;
		rec->dim2 = d2;
		rec->isFix = this->IsEntryFix (i) ? 1 : 0;
	}

	return addPar;

	//GSHandle addPar = GDLCreateVarHandle (this->GetEntryNum ());
	//if (addPar == nullptr)
	//	throw GS::GSException ();

	//try {
	//	for (ULong i = 0; i < this->GetEntryNum (); i++) {
	//		char name[MAXNAM];
	//		this->GetEntryName (i, name, sizeof (name));

	//		this->ThrowErr (GDLModifyVarName (addPar, i, name));

	//		typename GS::PropertyList<UserDataType>::ArrayType at;
	//		ULong d1, d2;
	//		typename GS::PropertyList<UserDataType>::StorageType st = this->GetEntryType (i, &at, &d1, &d2);
	//		switch (at) {
	//			case GS::PropertyList<UserDataType>::Scalar:
	//				switch (st) {
	//					case GS::PropertyList<UserDataType>::Integer:
	//						this->ThrowErr (GDLModifyVarType (addPar, i, ParT_Integer, false, 0, 0));
	//						this->ThrowErr (GDLModifyIntVar (addPar, i, this->GetIntEntry (i)));
	//						break;
	//					case GS::PropertyList<UserDataType>::Numeric:
	//						this->ThrowErr (GDLModifyVarType (addPar, i, ParT_RealNum, false, 0, 0));
	//						this->ThrowErr (GDLModifyNumVar (addPar, i, this->GetNumEntry (i)));
	//						break;
	//					case GS::PropertyList<UserDataType>::String:
	//						this->ThrowErr (GDLModifyVarType (addPar, i, ParT_CString, false, 0, 0));
	//						this->ThrowErr (GDLModifyUStrVar (addPar, i, this->GetStringEntry (i)));
	//						break;
	//				}
	//				break;
	//			case GS::PropertyList<UserDataType>::OneDimensional:
	//				d2 = 0;
	//			case GS::PropertyList<UserDataType>::TwoDimensional:
	//				switch (st) {
	//					case GS::PropertyList<UserDataType>::Integer:
	//						this->ThrowErr (GDLModifyVarType (addPar, i, ParT_Integer, true, d1, d2));
	//						this->ThrowErr (GDLModifyIntArray (addPar, i, this->GetIntArray (i)));
	//						break;
	//					case GS::PropertyList<UserDataType>::Numeric:
	//						this->ThrowErr (GDLModifyVarType (addPar, i, ParT_RealNum, true, d1, d2));
	//						this->ThrowErr (GDLModifyNumArray (addPar, i, this->GetNumArray (i)));
	//						break;
	//					case GS::PropertyList<UserDataType>::String:
	//						this->ThrowErr (GDLModifyVarType (addPar, i, ParT_CString, true, d1, d2));
	//						this->ThrowErr (GDLModifyUStrArray (addPar, i, this->GetStringArray (i)));
	//						break;
	//				}
	//				break;
	//		}

	//		this->ThrowErr (GDLSetVarFix (addPar, i, this->IsEntryFix (i)));
	//	}

	//	return addPar;
	//} catch (...) {
	//	BMhFree (addPar);
	//	throw;
	//}
}

template<class UserDataType>
void PropertyList<UserDataType>::ReadFromAddParHandle (GSConstHandle addPar)
{
	for (ULong i = 0; i < this->GetEntryNum (); i++)
		this->SetEntryFix (i, false);
	this->DeleteEntries (0, this->GetEntryNum () - 1);

	try {
		for (ULong i = 0; i < ULong (GDLGetVarNumber (addPar)); i++) {
			bool isArray;
			Int32 dim1, dim2;
			char name[MAXNAMUTF8];
			short dataType = GDLGetVarType (addPar, i, &isArray, &dim1, &dim2);
			GDLGetVarName (addPar, i, name, sizeof (name));

			typename GS::PropertyList<UserDataType>::ArrayType at;
			typename GS::PropertyList<UserDataType>::StorageType st;

			if (!isArray)
				at = GS::PropertyList<UserDataType>::Scalar;
			else if (dim2 <= 0)
				at = GS::PropertyList<UserDataType>::OneDimensional;
			else
				at = GS::PropertyList<UserDataType>::TwoDimensional;

			if (GDLIsIntType (dataType))
				st = GS::PropertyList<UserDataType>::Integer;
			else if (GDLIsNumType (dataType))
				st = GS::PropertyList<UserDataType>::Numeric;
			else
				st = GS::PropertyList<UserDataType>::String;
			this->PushEntry (name, st, at, dim1, dim2);

			switch (at) {
				case GS::PropertyList<UserDataType>::Scalar:
					switch (st) {
						case GS::PropertyList<UserDataType>::Integer:
							this->SetIntEntry (i, GDLGetIntVar (addPar, i));
							break;
						case GS::PropertyList<UserDataType>::Numeric:
							this->SetNumEntry (i, GDLGetNumVar (addPar, i));
							break;
						case GS::PropertyList<UserDataType>::String:
							this->SetStringEntry (i, GDLGetUStrVarRef (addPar, i));
							break;
					}
					break;
				case GS::PropertyList<UserDataType>::OneDimensional:
				case GS::PropertyList<UserDataType>::TwoDimensional:
					switch (st) {
						case GS::PropertyList<UserDataType>::Integer:
							this->SetIntArray (i, (const Int32*) GDLGetUArrayRef (addPar, i));
							break;
						case GS::PropertyList<UserDataType>::Numeric:
							this->SetNumArray (i, (const double*) GDLGetUArrayRef (addPar, i));
							break;
						case GS::PropertyList<UserDataType>::String:
							this->SetStringArray (i, (const GS::uchar_t*) GDLGetUArrayRef (addPar, i));
							break;
					}
					break;
			}

			this->SetEntryFix (i, GDLIsVarFix (addPar, i));
		}
	} catch (...) {
		this->Clear ();
		throw;
	}
}

}

