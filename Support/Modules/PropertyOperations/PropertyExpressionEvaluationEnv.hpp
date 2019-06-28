#ifndef PROPERTYEXPRESSIONEVALUATIONENV_HPP
#define PROPERTYEXPRESSIONEVALUATIONENV_HPP

#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"
#include "PropertyOwner.hpp"
#include "ExpressionEvaluationEnv.hpp"
#include "ExpressionLocaleSettings.hpp"
#include "VariantConversionRules.hpp"
#include "ExpressionUnitConverter.hpp"
#include "PropertyStatusCache.hpp"

namespace PropertyOperations
{

class PROPERTY_OPERATIONS_DLL_EXPORT ExpressionEvaluationEnv : public EE::IExpressionEvaluationEnv
{
public:
	ExpressionEvaluationEnv (const Property::PropertyEvaluationEnvironmentSourceConstPtr& propEvalEnv,
							 const Property::PropertyOwner& propertyOwner,
							 const PropertyStatusCachePtr& statusCache);
	virtual ~ExpressionEvaluationEnv ();

	virtual EE::PropertyStatus						GetPropertyStatus (const GS::Guid& propertyGuid) const override;
	virtual EE::ExpressionValue						GetPropertyValue (const GS::Guid& propertyGuid) const override;
	virtual const EE::IExpressionUnitConverter&		GetUnitConverter () const override;
	virtual const EE::IEvaluationLocaleSettings&	GetLocaleSettings () const override;
	virtual bool									IsEvaluationForAnalysisReasons (void) const override;

	void											ClearStatusCache () const;

private:
	CachedPropertyStatus							GetCachedPropertyStatus (const GS::Guid& propertyGuid) const;
	void											SetCachedPropertyStatus (const GS::Guid& propertyGuid, CachedPropertyStatus status) const;
	Property::PropertyDefinitionExtensionConstPtr	GetPropertyExtension (const GS::Guid& propertyGuid) const;

protected:
	const Property::PropertyEvaluationEnvironmentSourceConstPtr&	propEvalEnv;
	const Property::PropertyOwner&									propertyOwner;
	EE::ExpressionUnitConverter										unitConverter;
	EE::SystemLocaleSettings										localeSettings;
	GS::Owner<GS::VariantConversionRules>							variantConversionRules;
	PropertyStatusCachePtr											statusCache;
};

typedef GS::Ref<ExpressionEvaluationEnv> ExpressionEvaluationEnvPtr;
typedef GS::Ref<const ExpressionEvaluationEnv> ExpressionEvaluationEnvConstPtr;

}

#endif
