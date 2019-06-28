// Contact person : VS

#ifndef PROPERTY_OPERATIONS_EXPRESSIONLISTEVALUATOR_HPP
#define PROPERTY_OPERATIONS_EXPRESSIONLISTEVALUATOR_HPP

#pragma once

#include "PropertyOperationsExport.hpp"
#include "ExpressionList.hpp"
#include "IReportHandler.hpp"
#include "PropertyExpressionValueConverter.hpp"

// =====================================================================================================================

namespace Property {

PROPERTY_OPERATIONS_DLL_EXPORT
bool	IsExpressionListEvaluable (const ExpressionList& expressionList,
								   const EE::IExpressionEvaluationEnv& env);


PROPERTY_OPERATIONS_DLL_EXPORT
PropertyValue	EvaluateExpressionList (const IPropertyTypeInfo& propertyTypeInfo,
										const ExpressionList& expressionList, 
										const EE::IExpressionReferenceResolver& resolver, 
										const EE::IExpressionEvaluationEnv& env, 
										EE::IReportHandler* reportHandler = nullptr);

PROPERTY_OPERATIONS_DLL_EXPORT
EE::ExpressionValue		EvaluateSingleExpression (	const IPropertyTypeInfo& propertyTypeInfo,
													const EE::Expression& expression, 
													const EE::IExpressionReferenceResolver& resolver, 
													const EE::IPropertyIdResolverPtr& idResolver,
													const EE::IExpressionEvaluationEnv& env,
													GS::UniString& errorMessageOut);
}

#endif
