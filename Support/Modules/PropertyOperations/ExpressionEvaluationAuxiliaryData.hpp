
#ifndef EXPRESSIONEVALUATIONAUXILIARYDATA_HPP
#define EXPRESSIONEVALUATIONAUXILIARYDATA_HPP
#pragma once

#include "PropertyOperationsExport.hpp"
#include "Md5.hpp"
#include "CalcUnitSettings.hpp"

namespace PropertyOperations {


class PROPERTY_OPERATIONS_DLL_EXPORT ExpressionEvaluationAuxiliaryData {

public:
	struct PROPERTY_OPERATIONS_DLL_EXPORT WorkingUnitSettings {
		Int32				nonUnitDigits;

		WorkingUnitSettings (Int32 nonUnitDigits);
	};


	ExpressionEvaluationAuxiliaryData ();
	ExpressionEvaluationAuxiliaryData (const WorkingUnitSettings& workingUnitSettings, const EE::CalcUnitSettings& calcUnitSettings);
	ExpressionEvaluationAuxiliaryData& operator= (const ExpressionEvaluationAuxiliaryData& source) = default;

	EE::CalcUnitSettings				GetCalcUnitSettings () const;
	WorkingUnitSettings					GetWorkingUnitSettings () const;
	MD5::FingerPrint					GetCheckSum () const;

private:
	WorkingUnitSettings					workingUnitSettings;
	EE::CalcUnitSettings				calcUnitSettings;
};

}

#endif // EXPRESSIONEVALUATIONAUXILIARYDATA_HPP
