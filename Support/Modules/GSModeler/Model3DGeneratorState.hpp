// *****************************************************************************
// Data for 3D model generators.
// GSModeler, platform-independent
//
// Namespaces:        Contact person:
//    Modeler          PCS
//
// SG compatible
// *****************************************************************************

#if !defined (MODEL3DGENERATORSTATE_HPP)
#define MODEL3DGENERATORSTATE_HPP

// ----------------------- Includes --------------------------------------------

// from GSRoot
#include "SharedPtr.hpp"

//from GSUtils
#include "comProc.h"

// from GSModeler
#include "Model3D/Model3D.hpp"
#include "Model3D/Model3DStateDescriptor.hpp"
#include "CandidateElem.hpp"
#include "MBRC.hpp"

namespace GS {
	class ProcessControl;
}

namespace Modeler {
	class IAttributeReader;
}

// ----------------------- Class declaration -----------------------------------

class Model3DGeneratorState : public GS::Object {
private:

	GS::ProcessControl*					processControl;

	UInt32						nextGroupId;
	
	Modeler::AttributesPtr		localAttributes;
	Modeler::Attributes::Viewer	attrViewer;	

	Modeler::CandidateElem		generatedCandElem;			// The final generated elem, which can be built here from the beginning of the generation or
															// be copied as the result of an Out_PlaceGroup calling.

	GS::HashTable<GS::Guid, Modeler::ConstElemPtr>		groups;
	GS::HashTable<GS::Guid, GS::PagedArray<GS::Guid> >	mainGroupIdToGroupIdMap;

	struct OpenGroupStackEntry {
		GS::Guid					groupId;
		Modeler::CandidateElem*		candElem;

		OpenGroupStackEntry (const GS::Guid& groupId, Modeler::CandidateElem* candElem) : groupId (groupId), candElem (candElem) {}
	};
	GS::Array<OpenGroupStackEntry> openGroupStack;		

	Modeler::CandidateElem*		workCandElem;				// It points to generatedCandElem if openGroupStack is empty.
															// Otherwise it points to the end of openGroupStack. I.e. it points to the most recent
															// working candidate elem.

	const Modeler::IAttributeReader*	attReader;

	void ClearCSGCandElemStack (void);

	Model3DGeneratorState& operator= (const Model3DGeneratorState&);

	GS::Guid			elemGuidForReport;
	GetLocStrProc_UStr*	checkLocStrProc;
	MessageProc_UStr*	checkWarningProc;

public:
	MBR::MemBlockRecyclerForThread<32> memBlocks; 
#ifdef	DEBUVERS
	bool	printDebug;
#endif

	

	Model3DStateDescriptor stateVars;

	Model3DGeneratorState (GS::ProcessControl&					processControl, 
						   const Modeler::ConstAttributesPtr&	targetAttributes,
						   const Modeler::IAttributeReader*		ar);

	virtual ~Model3DGeneratorState ();

	void					OpenNewGroup (const GS::Guid& mainGroupId, const GS::Guid& groupId);

	enum CloseMode {
		Commit,
		Abort
	};
	void					CloseGroup (CloseMode closeMode = Commit);

	void					DeleteGroup (const GS::Guid& groupId);
	void					DeleteGroupsByMainGroupId (const GS::Guid& mainGroupId);
	void					DeleteAllGroups ();

	GS::ProcessControl&				GetProcessControl (void);
	void							SetProcessControl (GS::ProcessControl& newProcessControl);
	Modeler::CandidateElem*			GetWorkCandElem (void);
	Modeler::CandidateElem*			GetGeneratedCandElem (void);

	const Modeler::ConstElemPtr		GetGroupById (const GS::Guid& groupId);

	void							AddGroup (const Modeler::ConstElemPtr& groupElem, const GS::Guid& mainGroupId, const GS::Guid& groupId);

	inline void			SetCheckLocStrProc	(GetLocStrProc_UStr*	checkLocStrProc);
	inline void			SetCheckWarningProc	(MessageProc_UStr*		checkWarningProc);
	inline void			SetElemGuidForReport (const GS::Guid& guid) { elemGuidForReport = guid; }

	inline GetLocStrProc_UStr*	GetCheckLocStrProc	() const;
	inline MessageProc_UStr*	GetCheckWarningProc	() const;
	inline const GS::Guid&		GetElemGuidForReport () const { return elemGuidForReport; }

	UInt32						NextGroupId () { return ++nextGroupId; }

	const Modeler::Attributes::Viewer&	GetAttrViewer () const	{ return attrViewer; }
	const Modeler::AttributesPtr&		GetAttr ()				{ return localAttributes; }

	bool								WasGroupDefs () const	{ return !groups.IsEmpty (); }

	const Modeler::IAttributeReader*	GetAttributeReader (void) const								{ return attReader;	}
};


// ----------------------- Class implementation --------------------------------

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------




// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline void	Model3DGeneratorState::DeleteGroup (const GS::Guid& groupId)
{
	groups.Delete (groupId);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline void	Model3DGeneratorState::DeleteGroupsByMainGroupId (const GS::Guid& mainGroupId)
{
	const GS::PagedArray<GS::Guid>* mappedGroups = mainGroupIdToGroupIdMap.GetPtr (mainGroupId);
	if (mappedGroups != nullptr) {
		for (UInt32 i = 0; i < mappedGroups->GetSize (); ++i) {
			DeleteGroup ((*mappedGroups) [i]);
		}
		mainGroupIdToGroupIdMap.Delete (mainGroupId);
	}
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline void	Model3DGeneratorState::DeleteAllGroups ()
{
	mainGroupIdToGroupIdMap.Clear ();
	groups.Clear ();
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline void	Model3DGeneratorState::ClearCSGCandElemStack (void) 
{
	for (ULong i = 0; i < openGroupStack.GetSize (); i++) {
		delete openGroupStack [i].candElem;
	}
	openGroupStack.Clear ();
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline GS::ProcessControl& Model3DGeneratorState::GetProcessControl (void)
{
	DBASSERT (processControl != nullptr);
	return *processControl;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline void Model3DGeneratorState::SetProcessControl (GS::ProcessControl& newProcessControl)
{
	processControl = &newProcessControl;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline Modeler::CandidateElem*	Model3DGeneratorState::GetWorkCandElem (void) 
{
	return workCandElem;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline Modeler::CandidateElem*	Model3DGeneratorState::GetGeneratedCandElem (void) 
{
	return &generatedCandElem;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline const Modeler::ConstElemPtr		Model3DGeneratorState::GetGroupById (const GS::Guid& groupId)
{
	Modeler::ConstElemPtr group;
	groups.Get (groupId, &group);
	return group;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline void	Model3DGeneratorState::AddGroup (const Modeler::ConstElemPtr& groupElem, const GS::Guid& mainGroupId, const GS::Guid& groupId)
{
	DBVERIFY (groups.Add (groupId, groupElem));
	mainGroupIdToGroupIdMap.Retrieve (mainGroupId).Push (groupId);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline void	Model3DGeneratorState::SetCheckLocStrProc	(::GetLocStrProc_UStr*	checkLocStrProc)
{
	this->checkLocStrProc = checkLocStrProc;
}

inline void Model3DGeneratorState::SetCheckWarningProc	(MessageProc_UStr*	checkWarningProc)
{
	this->checkWarningProc = checkWarningProc;
}

inline GetLocStrProc_UStr*	Model3DGeneratorState::GetCheckLocStrProc () const
{
	return checkLocStrProc;
}

inline MessageProc_UStr*		Model3DGeneratorState::GetCheckWarningProc () const
{
	return checkWarningProc;
}

#endif
