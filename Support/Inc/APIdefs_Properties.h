// *********************************************************************************************************************
// API definitions - properties
//
// Module:			API
// Namespace:		-
// Contact person:	devsup@graphisoft.hu
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_PROPERTIES_H)
#define	APIDEFS_PROPERTIES_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"GSTime.hpp"

// from ARCHICAD
#include	"API_Guid.hpp"


// --- Compiler settings -----------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#if defined (macintosh)
	#pragma options align=natural
#endif

#if defined (_MSC_VER)
	#pragma pack(push, 8)
#endif


// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// IFC Properties & Attributes

typedef enum {
	API_IFCPropertySingleValueType,
	API_IFCPropertyListValueType,
	API_IFCPropertyBoundedValueType,
	API_IFCPropertyEnumeratedValueType,
	API_IFCPropertyTableValueType,
	API_IFCPropertyReferenceValueType
} API_IFCPropertyType;

typedef struct {
	GS::UniString					propertySetName;
	GS::UniString					propertyName;
	GS::UniString					propertyDescription;
	API_IFCPropertyType				propertyType;
	bool							readOnly;
} API_IFCPropertyHead;

typedef enum {
	API_IFCPropertyAnyValueIntegerType,
	API_IFCPropertyAnyValueRealType,
	API_IFCPropertyAnyValueBooleanType,
	API_IFCPropertyAnyValueLogicalType,
	API_IFCPropertyAnyValueStringType
} API_IFCPropertyValuePrimitiveType;

typedef struct {
	API_IFCPropertyValuePrimitiveType primitiveType;

	double							doubleValue;
	Int64							intValue;
	bool							boolValue;
	GS::UniString					stringValue;
} API_IFCPropertyAnyValue;

typedef struct {
	API_IFCPropertyAnyValue			value;
	GS::UniString					valueType;
} API_IFCPropertyValue;

typedef struct {
	API_IFCPropertyValue			nominalValue;
} API_IFCPropertySingleValue;

typedef struct {
	API_IFCPropertyValue			lowerBoundValue;
	API_IFCPropertyValue			upperBoundValue;
} API_IFCPropertyBoundedValue;

typedef struct {
	GS::Array<API_IFCPropertyValue>	listValues;
} API_IFCPropertyListValue;

typedef struct {
	GS::Array<API_IFCPropertyValue>	enumerationReference;
	GS::Array<API_IFCPropertyValue>	enumerationValues;
} API_IFCPropertyEnumeratedValue;

typedef struct {
	GS::Array<API_IFCPropertyValue>	definingValues;
	GS::Array<API_IFCPropertyValue>	definedValues;
} API_IFCPropertyTableValue;

typedef enum {
	CalendarDate
} API_IFCObjectReferenceType;

typedef struct {
	GS::UniString				usageName;
	API_IFCObjectReferenceType	type;

	short	day;	//for CalendarDate ReferenceValue
	short	month;	//for CalendarDate ReferenceValue
	short	year;	//for CalendarDate ReferenceValue
} API_IFCPropertyReferenceValue;

typedef struct {
	API_IFCPropertyHead				head;

	API_IFCPropertySingleValue		singleValue;
	API_IFCPropertyBoundedValue		boundedValue;
	API_IFCPropertyListValue		listValue;
	API_IFCPropertyEnumeratedValue	enumeratedValue;
	API_IFCPropertyTableValue		tableValue;
	API_IFCPropertyReferenceValue	referenceValue;
} API_IFCProperty;

typedef struct {
	GS::UniString					attributeName;
	GS::UniString					attributeType;
	GS::UniString					attributeValue;
	bool							hasValue;
	bool							readOnly;
} API_IFCAttribute;

typedef struct {
	short day;
	short month;
	short year;
} API_IFCCalendarDate;

typedef struct {
	GS::UniString					source;
	GS::UniString					edition;
	bool							hasEditionDate;
	API_IFCCalendarDate				editionDate;
	GS::UniString					name;
} API_IFCClassification;

typedef struct {
	GS::UniString					referenceName;

	GS::UniString					location;
	bool							hasLocation;
	GS::UniString					name;
	bool							hasName;
	GS::UniString					itemReference;
	bool							hasItemReference;

	API_IFCClassification			referencedSource;
} API_IFCClassificationReference;

// MEP ports

typedef enum {
	API_MEPConnectorShape_Circular,
	API_MEPConnectorShape_Oval,
	API_MEPConnectorShape_Rectangular,
	API_MEPConnectorShape_UShape
} API_MEPConnectorShape;

typedef struct {
	API_MEPConnectorShape			shape;
	double							width;
	double							height;
	double							length;
	bool							visible;
	short							mepSystem;
	GS::UniString					connectionType;
} API_MEPPortProperties;

// GS Properties

typedef enum {
	API_PropertyStaticBuiltInGroupType,
	API_PropertyDynamicBuiltInGroupType,
	API_PropertyCustomGroupType
} API_PropertyGroupType;

typedef enum {
	API_PropertyStaticBuiltInDefinitionType,
	API_PropertyDynamicBuiltInDefinitionType,
	API_PropertyCustomDefinitionType
} API_PropertyDefinitionType;

typedef enum {
	API_PropertyUndefinedCollectionType,
	API_PropertySingleCollectionType,
	API_PropertyListCollectionType,
	API_PropertySingleChoiceEnumerationCollectionType,
	API_PropertyMultipleChoiceEnumerationCollectionType
} API_PropertyCollectionType;

typedef enum {
	API_PropertyUndefinedMeasureType,
	API_PropertyDefaultMeasureType,
	API_PropertyLengthMeasureType,
	API_PropertyAreaMeasureType,
	API_PropertyVolumeMeasureType,
	API_PropertyAngleMeasureType
} API_PropertyMeasureType;

typedef enum {
	API_PropertyUndefinedValueType,
	API_PropertyIntegerValueType,
	API_PropertyRealValueType,
	API_PropertyStringValueType,
	API_PropertyBooleanValueType,
	API_PropertyGuidValueType
} API_VariantType;

typedef enum {
	API_VariantStatusNull,
	API_VariantStatusUserUndefined,
	API_VariantStatusNormal
} API_VariantStatus;

struct API_Variant {
	API_VariantType		type;

	Int32			intValue;
	double			doubleValue;
	bool			boolValue;
	GS::UniString	uniStringValue;
	API_Guid		guidValue;

	API_Variant () :
		type (API_PropertyUndefinedValueType),
		intValue (0),
		doubleValue (0.0),
		boolValue (false),
		guidValue (APINULLGuid)
	{ }
};

struct API_SingleVariant {
	API_Variant	variant;
};

struct API_ListVariant {
	GS::Array<API_Variant> variants;
};

struct API_SingleEnumerationVariant {
	API_Variant		keyVariant;
	API_Variant		displayVariant;
};

struct API_MultipleEnumerationVariant {
	GS::Array<API_SingleEnumerationVariant>	variants;
};

struct API_PropertyValue {
	API_SingleVariant				singleVariant;
	API_ListVariant					listVariant;
	API_SingleEnumerationVariant	singleEnumVariant;
	API_MultipleEnumerationVariant	multipleEnumVariant;
	API_VariantStatus				variantStatus;

	API_PropertyValue ():
		variantStatus (API_VariantStatusNormal)
	{ }
};

struct API_PropertyDefaultValue {
	API_PropertyValue			basicValue;
	GS::Array<GS::UniString>	propertyExpressions;
	bool						hasExpression;

	API_PropertyDefaultValue () :
		hasExpression (false)
	{ }
};

struct API_PropertyGroup {
	API_PropertyGroupType	groupType;
	API_Guid				guid;
	GS::UniString			name;

	API_PropertyGroup () :
		groupType (API_PropertyCustomGroupType),
		guid (APINULLGuid)
	{ }
};

struct API_PropertyDefinition {
	API_PropertyDefinitionType					definitionType;
	API_Guid									guid;
	API_Guid									groupGuid;
	GS::UniString								name;
	GS::UniString								description;
	API_PropertyCollectionType					collectionType;
	API_VariantType								valueType;
	API_PropertyMeasureType						measureType;
	API_PropertyDefaultValue					defaultValue;
	GS::Array<API_Guid>							availability;
	GS::Array<API_SingleEnumerationVariant>		possibleEnumValues;
	bool										canValueBeEditable;

	API_PropertyDefinition () :
		definitionType (API_PropertyCustomDefinitionType),
		guid (APINULLGuid),
		groupGuid (APINULLGuid),
		collectionType (API_PropertyUndefinedCollectionType),
		valueType (API_PropertyUndefinedValueType),
		measureType (API_PropertyDefaultMeasureType),
		canValueBeEditable (false)
	{ }
};

typedef enum
{
	API_PropertyDefinitionFilter_UserDefined,
	API_PropertyDefinitionFilter_BuiltIn,
	API_PropertyDefinitionFilter_All
} API_PropertyDefinitionFilter;

struct API_Property {
	API_PropertyDefinition	definition;
	API_PropertyValue		value;
	bool					isDefault;
	bool					isEvaluated;

	API_Property () : isDefault (true), isEvaluated (false) {}
};

// ---------------------------------------------------------------------------------------------------------------------

#if defined (_MSC_VER)
	#pragma pack(pop)
#endif

#if defined (macintosh)
	#pragma options align=reset
#endif

#ifdef __cplusplus
}
#endif

#endif
