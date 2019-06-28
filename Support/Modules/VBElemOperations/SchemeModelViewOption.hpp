// *********************************************************************************************************************
// Description:		SchemeModelViewOptions
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	NYD, JG, CSP, KG, NAD
//
// SG compatible
// *********************************************************************************************************************
#if !defined (_SchemeModelViewOption_HPP_)
#define _SchemeModelViewOption_HPP_

#include "VBElemOperationsExport.hpp"

// from GSRoot
#include "Object.hpp"

// from VBAttrubtes
#include "generalattribute.hpp"

class VB_ELEM_OPERATIONS_DLL_EXPORT SchemeModelViewOption : public GS::Object {
	DECLARE_CLASS_INFO
protected:
	short	surfaceIndex;
	short	cutLineIndex;
	short	cutLinePen;
	short	uncutLineIndex;
	short	uncutLinePen;

public:
	bool operator== (const SchemeModelViewOption& rhs) const;
	bool operator!= (const SchemeModelViewOption& rhs) const;

protected:
	SchemeModelViewOption ();
	SchemeModelViewOption (short surfaceIndex, short cutLineIndex, short cutLinePen, short uncutLineIndex, short uncutLinePen);

public:
	inline short		GetSurfaceAttributeIndex (void) const { return surfaceIndex; }
	inline short		GetCutLineAttributeIndex (void) const { return cutLineIndex; }
	inline short		GetCutLinePenIndex (void) const { return cutLinePen; }
	inline short		GetUncutLineAttributeIndex (void) const { return uncutLineIndex; }
	inline short		GetUncutLinePenIndex (void) const { return uncutLinePen; }

	void				SetSurfaceAttributeIndex (short index);
	void				SetCutLineAttributeIndex (short index);
	void				SetCutLinePenIndex (short index);
	void				SetUncutLineAttributeIndex (short index);
	void				SetUncutLinePenIndex (short index);

	// ----- Attribute reindexing ----------------------------------------------------

 	virtual void		CollectUsedAttrs (IUsedAttrCollection& usedAttrCollection) const;
	virtual void		ReindAttr (ADB::IAttributeNewIndexTable* newIndexTable);

	// ----- GS::Object --------------------------------------------------------------

public:
	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const override;

	// ----- Other Serialization -----------------------------------------------------

	virtual GSErrCode			ReadXML (GS::XMLIChannel& ic) = 0;
	virtual GSErrCode			WriteXML (GS::XMLOChannel& oc) const = 0;

	// ----- Auxilary functions ------------------------------------------------------

private:
	GSErrCode ReadVersion10 (GS::IChannel& ic);
	GSErrCode WriteVersion10 (GS::OChannel& oc) const;
};

#endif // _STAIRSCHEMEMODELVIEWOPTION_HPP_
