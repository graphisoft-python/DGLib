#ifndef PROPERTYSTATISTICSDATA_HPP
#define PROPERTYSTATISTICSDATA_HPP

#pragma once

// === Includes ========================================================================================================

#include "PropertyOperations.hpp"


// =====================================================================================================================

namespace Property {


class PROPERTY_OPERATIONS_DLL_EXPORT PropertyEvaluationStatisticsData {
private:
	UInt64	userDefinedPropertyGetEvaluatedValueCallCount;
	UInt64	userDefinedPropertyEvaluateExpressionListCallCount;

	PropertyEvaluationStatisticsData ();

	static PropertyEvaluationStatisticsData theInstance;

public:
	~PropertyEvaluationStatisticsData ();

	static PropertyEvaluationStatisticsData& Instance ();

	UInt64	GetUserDefinedPropertyGetEvaluatedValueCallCount () const;
	void	IncUserDefinedPropertyGetEvaluatedValueCallCount ();

	UInt64	GetuserDefinedPropertyEvaluateExpressionListCallCount () const;
	void	IncUserDefinedPropertyEvaluateExpressionListCallCount ();

	void	Reset ();
};


}

#endif
