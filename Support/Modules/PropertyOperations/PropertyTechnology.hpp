#ifndef PROPERTYTECHNOLOGY_HPP
#define PROPERTYTECHNOLOGY_HPP

#pragma once

// from GSRoot
#include "Array.hpp"

// from Property
#include "PropertyOperationsExport.hpp"

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT Technology
{
public:
	enum class ActionType {
		Get,
		Set
	};

	Technology (GS::Guid guid);
	Technology (const Technology& other);

	const GS::Guid&			GetGuid () const;

private:
	GS::Guid	guid;
};



class PROPERTY_OPERATIONS_DLL_EXPORT TechnologyList
{
public:
	TechnologyList (std::initializer_list<Technology> technologyList);

	bool	Contains (const Technology& technology) const;

private:
	GS::Array<Technology>	technologies;
};

}

#endif