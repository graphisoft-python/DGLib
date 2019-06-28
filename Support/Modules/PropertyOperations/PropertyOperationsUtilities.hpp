// Contact person : KiP

#ifndef PROPERTY_OPERATIONS_UTILITIES_HPP
#define PROPERTY_OPERATIONS_UTILITIES_HPP

#pragma once

#include "PropertyOperationsExport.hpp"
#include "Variant.hpp"
#include "ODBReference.hpp"
#include "PropertyMeasure.hpp"
#include "GeneralElem.hpp"
#include "Project.hpp"
#include "ReferenceElem.hpp"
#include "ReferenceElemNode.hpp"
#include "ModuleSingleton.hpp"

// =====================================================================================================================

#define RWCHK(f) { err = (f); if (err != NoError) return err; }		// Read/Write check macro


namespace EDB
{
	class FloorStructure;
	typedef ODB::ConstRef<FloorStructure> FloorStructureConstRef;
}


namespace Property {

void			ConvertAttributeIndexMeasureToDisplayValue (const ADB::AttributeSetConstRef& attributeSet, Property::Measure::MeasureType measureType, const GS::Variant* value, GS::AutoPtr<GS::Variant>& displayValue);

PROPERTY_OPERATIONS_DLL_EXPORT
GS::UniString	ComposeNonEmptyFloorName (const EDB::FloorStructureConstRef& floorStructure, short floorNum);

template <class ContainerType, class ContainerSetType>
ODB::ConstRef<ContainerType> GetContainerToElemTemplate (const EDB::GeneralElemConstRef& elem,
														 std::function<ODB::ConstRef<ContainerSetType> (EDB::ProjectConstRef&)> getContainerSet)
{
	VBElem::ReferenceElemConstRef refElem = VBElem::ReferenceElem::GetOwnerReferenceElem (elem);

	if (refElem == nullptr) {
		EDB::ProjectConstRef project = elem->GetProject ();
		if (DBERROR (project == nullptr)) {
			return nullptr;
		}

		ODB::ConstRef<ContainerSetType> containerSet = getContainerSet (project);

		if (DBERROR (containerSet == nullptr)) {
			return nullptr;
		}

		return containerSet->GetInternalContainer ();
	}
	else {
		SRM::ReferenceElemNodeConstRef node = SRM::ReferenceElemNode::GetReferenceElemConstNode (refElem);
		if (DBERROR (node == nullptr)) {
			return nullptr;
		}
		REM::ModuleSingletonConstRef ms = REM::ModuleSingleton::GetByReferenceElemNode (node);
		if (ms == nullptr) {
			return nullptr;
		}
		ODB::ConstRefList<ContainerType> containers = REM::ModuleSingleton::GetCommonProxyObjectsByType<ContainerType> (ms);
		DBASSERT (containers.GetSize () <= 1);	//old nested hotlinks may have no PropertyContainer
		typename ODB::ConstRefList<ContainerType>::ConstIterator it = containers.Begin ();
		if (it == nullptr) {
			return nullptr;
		}
		return *it;
	}
}

}

#endif
