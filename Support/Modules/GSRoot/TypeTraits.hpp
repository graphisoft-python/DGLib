// *********************************************************************************************************************
// Description:		Type traits
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, BIM
//
// *********************************************************************************************************************

#ifndef TYPETRAITS_HPP
#define TYPETRAITS_HPP

#pragma once


#include <type_traits>
#include <utility>
#include "Definitions.hpp"


namespace GS {


// === IsIntegral ======================================================================================================

template <class T>
constexpr bool	IsIntegral = std::is_integral<T>::value;


// === IsFloatingPoint =================================================================================================

template <class T>
constexpr bool	IsFloatingPoint = std::is_floating_point<T>::value;


// === IsArithmetic ====================================================================================================

template <class T>
constexpr bool	IsArithmetic = std::is_arithmetic<T>::value;


// === IsSigned ========================================================================================================

template <class T>
constexpr bool	IsSigned = std::is_signed<T>::value;


// === IsUnsigned ======================================================================================================

template <class T>
constexpr bool	IsUnsigned = std::is_unsigned<T>::value;


// === IsArray =========================================================================================================

template <class T>
constexpr bool	IsArray = std::is_array<T>::value;


// === IsEnum ==========================================================================================================

template <class T>
constexpr bool	IsEnum = std::is_enum<T>::value;


// === IsUnion =========================================================================================================

template <class T>
constexpr bool	IsUnion = std::is_union<T>::value;


// === IsClass =========================================================================================================

template <class T>
constexpr bool	IsClass = std::is_class<T>::value;


// === IsPolymorphic ===================================================================================================

template <class T>
constexpr bool	IsPolymorphic = std::is_polymorphic<T>::value;


// === IsFinal =========================================================================================================

template <class T>
constexpr bool	IsFinal = std::is_final<T>::value;


// === IsAbstract ======================================================================================================

template <class T>
constexpr bool	IsAbstract = std::is_abstract<T>::value;


// === IsFunction ======================================================================================================

template <class T>
constexpr bool	IsFunction = std::is_function<T>::value;


// === IsPointer =======================================================================================================

template <class T>
constexpr bool	IsPointer = std::is_pointer<T>::value;


// === IsLValueReference ===============================================================================================

template <class T>
constexpr bool	IsLValueReference = std::is_lvalue_reference<T>::value;


// === IsRValueReference ===============================================================================================

template <class T>
constexpr bool	IsRValueReference = std::is_rvalue_reference<T>::value;


// === IsReference =====================================================================================================

template <class T>
constexpr bool	IsReference = std::is_reference<T>::value;


// === IsConst =========================================================================================================

template <class T>
constexpr bool	IsConst = std::is_const<T>::value;


// === IsVolatile ======================================================================================================

template <class T>
constexpr bool	IsVolatile = std::is_volatile<T>::value;


// === IsTrivial =======================================================================================================

template <class T>
constexpr bool	IsTrivial = std::is_trivial<T>::value;


// === IsTriviallyCopyable =============================================================================================

template <class T>
constexpr bool	IsTriviallyCopyable = std::is_trivially_copyable<T>::value;


// === IsStandardLayout ================================================================================================

template <class T>
constexpr bool	IsStandardLayout = std::is_standard_layout<T>::value;


// === IsPod ===========================================================================================================

template <class T>
constexpr bool	IsPod = std::is_pod<T>::value;


// === IsConstructible =================================================================================================

template <class T, class... Args>
constexpr bool	IsConstructible = std::is_constructible<T, Args...>::value;


// === IsTriviallyConstructible ========================================================================================

template <class T, class... Args>
constexpr bool	IsTriviallyConstructible = std::is_trivially_constructible<T, Args...>::value;


// === IsDefaultConstructible ==========================================================================================

template <class T>
constexpr bool	IsDefaultConstructible = std::is_default_constructible<T>::value;


// === IsTriviallyDefaultConstructible =================================================================================

template <class T>
constexpr bool	IsTriviallyDefaultConstructible = std::is_trivially_default_constructible<T>::value;


// === IsCopyConstructible =============================================================================================

template <class T>
constexpr bool	IsCopyConstructible = std::is_copy_constructible<T>::value;


// === IsTriviallyCopyConstructible ====================================================================================

template <class T>
constexpr bool	IsTriviallyCopyConstructible = std::is_trivially_copy_constructible<T>::value;


// === IsMoveConstructible =============================================================================================

template <class T>
constexpr bool	IsMoveConstructible = std::is_move_constructible<T>::value;


// === IsTriviallyMoveConstructible ====================================================================================

template <class T>
constexpr bool	IsTriviallyMoveConstructible = std::is_trivially_move_constructible<T>::value;


// === IsAssignable ====================================================================================================

template <class T, class SourceType>
constexpr bool	IsAssignable = std::is_assignable<T, SourceType>::value;


// === IsTriviallyAssignable ===========================================================================================

template <class T, class SourceType>
constexpr bool	IsTriviallyAssignable = std::is_trivially_assignable<T, SourceType>::value;


// === IsCopyAssignable ================================================================================================

template <class T>
constexpr bool	IsCopyAssignable = std::is_copy_assignable<T>::value;


// === IsTriviallyCopyAssignable =======================================================================================

template <class T>
constexpr bool	IsTriviallyCopyAssignable = std::is_trivially_copy_assignable<T>::value;


// === IsMoveAssignable ================================================================================================

template <class T>
constexpr bool	IsMoveAssignable = std::is_move_assignable<T>::value;


// === IsTriviallyMoveAssignable =======================================================================================

template <class T>
constexpr bool	IsTriviallyMoveAssignable = std::is_trivially_move_assignable<T>::value;


// === IsDestructible ==================================================================================================

template <class T>
constexpr bool	IsDestructible = std::is_destructible<T>::value;


// === IsTriviallyDestructible =========================================================================================

template <class T>
constexpr bool	IsTriviallyDestructible = std::is_trivially_destructible<T>::value;


// === HasVirtualDestructor ============================================================================================

template <class T>
constexpr bool	HasVirtualDestructor = std::has_virtual_destructor<T>::value;


// === RemovePointer ===================================================================================================

template <class T>
using RemovePointer = typename std::remove_pointer<T>::type;


// === RemoveReference =================================================================================================

template <class T>
using RemoveReference = typename std::remove_reference<T>::type;


// === RemoveConst =====================================================================================================

template <class T>
using RemoveConst = typename std::remove_const<T>::type;


// === RemoveVolatile ==================================================================================================

template <class T>
using RemoveVolatile = typename std::remove_volatile<T>::type;


// === RemoveCV ========================================================================================================

template <class T>
using RemoveCV = typename std::remove_cv<T>::type;


// === UnderlyingType ==================================================================================================

template <class Enum>
using UnderlyingType = typename std::underlying_type<Enum>::type;


// === Decay ===========================================================================================================

template <class T>
using Decay = typename std::decay<T>::type;


// === EnableIf ========================================================================================================

template <bool B, class T = void>
using EnableIf = typename std::enable_if<B, T>::type;


// === Conditional =====================================================================================================

template <bool Condition, class TrueType, class FalseType>
using Conditional = typename std::conditional<Condition, TrueType, FalseType>::type;


// === VoidT ===========================================================================================================

namespace Imp {

template <class...>
struct VoidHelper {
	typedef void Type;
};

}


template <class... Ts>
using VoidT = typename Imp::VoidHelper<Ts...>::Type;


// === IsSame ==========================================================================================================

template <class T1, class T2>
constexpr bool	IsSame = std::is_same<T1, T2>::value;


// === IsDecayed =======================================================================================================

template <class T>
constexpr bool	IsDecayed = IsSame<T, Decay<T>>;


// === IsCompatible ====================================================================================================

template <class From, class To>
constexpr bool	IsCompatible = std::is_base_of<To, From>::value;			// To is base of From, From is a To


// === AreRelated ======================================================================================================

template <class T1, class T2>
constexpr bool	AreRelated = std::is_base_of<T1, T2>::value || std::is_base_of<T2, T1>::value;


// === ParameterPackSize ===============================================================================================

template <class... Ts>
constexpr USize	ParameterPackSize = sizeof... (Ts);


// === ParameterPackType ===============================================================================================

namespace Imp {

template <UIndex I, class... Ts>
struct ParameterPackTypeHelper;

template <UIndex I, class T, class... Ts>
struct ParameterPackTypeHelper<I, T, Ts...>		{ using Type = typename ParameterPackTypeHelper<I - 1, Ts...>::Type; };

template <class T, class... Ts>
struct ParameterPackTypeHelper<0, T, Ts...>		{ using Type = T; };

}


template <UIndex I, class... Ts>
using ParameterPackType = typename Imp::ParameterPackTypeHelper<I, Ts...>::Type;


// === IsConvertible ===================================================================================================

namespace Imp {

template <class From, class To>
static std::true_type	TestConvertible (decltype (To {std::declval<From> ()})*);

template <class From, class To>
static std::false_type	TestConvertible (...);

template <class From, class To> struct EnableConversion { static constexpr bool Value = false; };
template <> struct EnableConversion<Int8,   float>  { static constexpr bool Value = true; };
template <> struct EnableConversion<UInt8,  float>  { static constexpr bool Value = true; };
template <> struct EnableConversion<Int16,  float>  { static constexpr bool Value = true; };
template <> struct EnableConversion<UInt16, float>  { static constexpr bool Value = true; };
template <> struct EnableConversion<Int8,   double> { static constexpr bool Value = true; };
template <> struct EnableConversion<UInt8,  double> { static constexpr bool Value = true; };
template <> struct EnableConversion<Int16,  double> { static constexpr bool Value = true; };
template <> struct EnableConversion<UInt16, double> { static constexpr bool Value = true; };
template <> struct EnableConversion<Int32,  double> { static constexpr bool Value = true; };
template <> struct EnableConversion<UInt32, double> { static constexpr bool Value = true; };

}


template <class From, class To>
constexpr bool	IsConvertible = (std::is_arithmetic<From>::value && std::is_arithmetic<To>::value) ?
								decltype (Imp::TestConvertible<From, To> (nullptr))::value || Imp::EnableConversion<RemoveCV<From>, RemoveCV<To>>::Value :
								std::is_convertible<From, To>::value;


// === IsFunctor =======================================================================================================

namespace Imp {
struct TestFunctor {
	template <class T>
	static std::true_type	Test (decltype (&T::operator()));

	template <class T>
	static std::false_type	Test (...);
};
}


template <class T>
constexpr bool	IsFunctor = decltype (Imp::TestFunctor::Test<T> (nullptr))::value;


// === HasOperatorLess =================================================================================================

namespace Imp {
struct TestOperatorLess {
	template <class T>
	static std::true_type	Test (decltype (bool {std::declval<T> () < std::declval<T> ()})*);

	template <class T>
	static std::false_type	Test (...);
};
}


template <class T>
constexpr bool	HasOperatorLess = decltype (Imp::TestOperatorLess::Test<T> (nullptr))::value;


// === HasOperatorEquals ===============================================================================================

namespace Imp {
struct TestOperatorEquals {
	template <class T>
	static std::true_type	Test (decltype (bool {std::declval<T> () == std::declval<T> ()})*);

	template <class T>
	static std::false_type	Test (...);
};
}


template <class T>
constexpr bool	HasOperatorEquals = decltype (Imp::TestOperatorEquals::Test<T> (nullptr))::value;


// === HasOperatorNotEquals ============================================================================================

namespace Imp {
struct TestOperatorNotEquals {
	template <class T>
	static std::true_type	Test (decltype (bool {std::declval<T> () != std::declval<T> ()})*);

	template <class T>
	static std::false_type	Test (...);
};
}


template <class T>
constexpr bool	HasOperatorNotEquals = decltype (Imp::TestOperatorNotEquals::Test<T> (nullptr))::value;


// === FirstArgumentType ===============================================================================================

namespace Imp {

template <class Ret, class Arg, class... Rest>
Arg		GetFirstArgument (Ret (*) (Arg, Rest...));

template <class Ret, class T, class Arg, class... Rest>
Arg		GetFirstArgument (Ret (T::*) (Arg, Rest...));

template <class Ret, class T, class Arg, class... Rest>
Arg		GetFirstArgument (Ret (T::*) (Arg, Rest...) const);

template <class T>
decltype (GetFirstArgument (&T::operator()))	GetFirstArgument (T);

}


template <class Function>
using FirstArgumentType = decltype (Imp::GetFirstArgument (std::declval<Function> ()));


// === DecayedFirstArgumentType ========================================================================================

namespace Imp {

template <class F>
auto	GetDecayedFirstArgumentType () -> Decay<typename F::DecayedFirstArgumentType>;


template <class F>
auto	GetDecayedFirstArgumentType () -> Decay<FirstArgumentType<F>>;

}


template <class Function>
using DecayedFirstArgumentType = decltype (Imp::GetDecayedFirstArgumentType<Function> ());


// === Enable ==========================================================================================================

template <bool B>
struct Enable {
	typedef bool FalseCondition;
};

template <>
struct Enable<true> {
	typedef bool TrueCondition;
};


// === EnumType and NotEnumType ========================================================================================

template <class T>
using EnumType = typename Enable<IsEnum<T>>::TrueCondition;

template <class T>
using NotEnumType = typename Enable<IsEnum<T>>::FalseCondition;


}	// namespace GS


using GS::EnableIf;


#endif
