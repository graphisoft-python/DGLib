// *********************************************************************************************************************
// Description:		Rational.hpp
//
// Module:			Modeler
// Contact person:	HK, PP
//
// *********************************************************************************************************************

#pragma once

#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include "Integer.hpp"


namespace QXTools {

template<typename Int>
class Rational;

/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/

template<class LeftOp, class RightOp, class Evaluator, class Int>
class BinaryRatOperator;

struct BinaryRatAdder
{
	template<typename Int>
	static void Evaluate (const Rational<Int> &lOp, const Rational<Int> &rOp, Rational<Int> &result)
	{
		result.CopyLessAdd (lOp, rOp);
	}

	template<typename Int1, typename Int2>
	static void Evaluate (const Rational<Int1> &lOp, const Int2 &rOp, Rational<Int1> &result)
	{
		result.CopyLessAdd (lOp, rOp);
	}

	template<typename Int1, typename Int2>
	static void Evaluate (const Int2 &lOp, const Rational<Int1> &rOp, Rational<Int1> &result)
	{
		result.CopyLessAdd (lOp, rOp);
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int1, class Int2>
	static void Evaluate (const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int2> &lOp, const Int1 &rOp, Rational<Int2> &result)
	{
		lOp.Evaluate (result);
		result += rOp;
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int1, class Int2>
	static void Evaluate (const Int1 &lOp, const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int2> &rOp, Rational<Int2> &result)
	{
		rOp.Evaluate (result);
		result += lOp;
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int>
	static void Evaluate (const Rational<Int> &lOp, const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int> &rOp, Rational<Int> &result)
	{
		rOp.Evaluate (result);
		result += lOp;
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int>
	static void Evaluate (const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int> &lOp, const Rational<Int> &rOp, Rational<Int> &result)
	{
		lOp.Evaluate (result);
		result += rOp;
	}

	template<class LO1, class RO1, class Eval1, class LO2, class RO2, class Eval2, class Int>
	static void Evaluate (const BinaryRatOperator<LO1, RO1, Eval1, Int> &lOp, const BinaryRatOperator<LO2, RO2, Eval2, Int> &rOp, Rational<Int> &result)
	{
		lOp.Evaluate (result);
		Rational<Int> temp;
		rOp.Evaluate (temp);
		result += temp;
	}
};


struct BinaryRatSubtractor
{
	template<typename Int>
	static void Evaluate (const Rational<Int> &lOp, const Rational<Int> &rOp, Rational<Int> &result)
	{
		result.CopyLessSubtract (lOp, rOp);
	}

	template<typename Int1, typename Int2>
	static void Evaluate (const Rational<Int1> &lOp, const Int2 &rOp, Rational<Int1> &result)
	{
		result.CopyLessSubtract (lOp, rOp);
	}

	template<typename Int1, typename Int2>
	static void Evaluate (const Int2 &lOp, const Rational<Int1> &rOp, Rational<Int1> &result)
	{
		result.CopyLessSubtract (lOp, rOp);
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int1, class Int2>
	static void Evaluate (const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int2> &lOp, const Int1 &rOp, Rational<Int2> &result)
	{
		lOp.Evaluate (result);
		result -= rOp;
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int1, class Int2>
	static void Evaluate (const Int1 &lOp, const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int2> &rOp, Rational<Int2> &result)
	{
		Rational<Int2> temp;
		rOp.Evaluate (temp);
		result.CopyLessSubtract (lOp, temp);
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int>
	static void Evaluate (const Rational<Int> &lOp, const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int> &rOp, Rational<Int> &result)
	{
		Rational<Int> temp;
		rOp.Evaluate (temp);
		result.CopyLessSubtract (lOp, temp);
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int>
	static void Evaluate (const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int> &lOp, const Rational<Int> &rOp, Rational<Int> &result)
	{
		lOp.Evaluate (result);
		result -= rOp;
	}

	template<class LO1, class RO1, class Eval1, class LO2, class RO2, class Eval2, class Int>
	static void Evaluate (const BinaryRatOperator<LO1, RO1, Eval1, Int> &lOp, const BinaryRatOperator<LO2, RO2, Eval2, Int> &rOp, Rational<Int> &result)
	{
		lOp.Evaluate (result);
		Rational<Int> temp;
		rOp.Evaluate (temp);
		result -= temp;
	}
};


struct BinaryRatMultiplier
{
	template<typename Int>
	static void Evaluate (const Rational<Int> &lOp, const Rational<Int> &rOp, Rational<Int> &result)
	{
		result.CopyLessMultiply (lOp, rOp);
	}

	template<typename Int1, typename Int2>
	static void Evaluate (const Rational<Int1> &lOp, const Int2 &rOp, Rational<Int1> &result)
	{
		result.CopyLessMultiply (lOp, rOp);
	}

	template<typename Int1, typename Int2>
	static void Evaluate (const Int2 &lOp, const Rational<Int1> &rOp, Rational<Int1> &result)
	{
		result.CopyLessMultiply (lOp, rOp);
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int1, class Int2>
	static void Evaluate (const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int2> &lOp, const Int1 &rOp, Rational<Int2> &result)
	{
		lOp.Evaluate (result);
		result *= rOp;
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int1, class Int2>
	static void Evaluate (const Int1 &lOp, const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int2> &rOp, Rational<Int2> &result)
	{
		rOp.Evaluate (result);
		result *= lOp;
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int>
	static void Evaluate (const Rational<Int> &lOp, const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int> &rOp, Rational<Int> &result)
	{
		rOp.Evaluate (result);
		result *= lOp;
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int>
	static void Evaluate (const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int> &lOp, const Rational<Int> &rOp, Rational<Int> &result)
	{
		lOp.Evaluate (result);
		result *= rOp;
	}

	template<class LO1, class RO1, class Eval1, class LO2, class RO2, class Eval2, class Int>
	static void Evaluate (const BinaryRatOperator<LO1, RO1, Eval1, Int> &lOp, const BinaryRatOperator<LO2, RO2, Eval2, Int> &rOp, Rational<Int> &result)
	{
		lOp.Evaluate (result);
		Rational<Int> temp;
		rOp.Evaluate (temp);
		result *= temp;
	}
};


struct BinaryRatDivider
{
	template<typename Int>
	static void Evaluate (const Rational<Int> &lOp, const Rational<Int> &rOp, Rational<Int> &result)
	{
		result.CopyLessDivide (lOp, rOp);
	}

	template<typename Int1, typename Int2>
	static void Evaluate (const Rational<Int1> &lOp, const Int2 &rOp, Rational<Int1> &result)
	{
		result.CopyLessDivide (lOp, rOp);
	}

	template<typename Int1, typename Int2>
	static void Evaluate (const Int2 &lOp, const Rational<Int1> &rOp, Rational<Int1> &result)
	{
		result.CopyLessDivide (lOp, rOp);
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int1, class Int2>
	static void Evaluate (const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int2> &lOp, const Int1 &rOp, Rational<Int2> &result)
	{
		lOp.Evaluate (result);
		result /= rOp;
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int1, class Int2>
	static void Evaluate (const Int1 &lOp, const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int2> &rOp, Rational<Int2> &result)
	{
		Rational<Int2> temp;
		rOp.Evaluate (temp);
		result.CopyLessDivide (lOp, temp);
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int>
	static void Evaluate (const Rational<Int> &lOp, const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int> &rOp, Rational<Int> &result)
	{
		Rational<Int> temp;
		rOp.Evaluate (temp);
		result.CopyLessDivide (lOp, temp);
	}

	template<class LeftOp, class RightOp, class Evaluator, class Int>
	static void Evaluate (const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int> &lOp, const Rational<Int> &rOp, Rational<Int> &result)
	{
		lOp.Evaluate (result);
		result /= rOp;
	}

	template<class LO1, class RO1, class Eval1, class LO2, class RO2, class Eval2, class Int>
	static void Evaluate (const BinaryRatOperator<LO1, RO1, Eval1, Int> &lOp, const BinaryRatOperator<LO2, RO2, Eval2, Int> &rOp, Rational<Int> &result)
	{
		lOp.Evaluate (result);
		Rational<Int> temp;
		rOp.Evaluate (temp);
		result /= temp;
	}
};


template<class LeftOp, class RightOp, class Evaluator, class Int>
class BinaryRatOperator
{
	typedef	Rational<Int>	RationalInt;

	public:
				BinaryRatOperator (const LeftOp &lOp, const RightOp &rOp) : leftOp (lOp), rightOp (rOp) {}

		void	Evaluate (RationalInt &result) const
		{
			Evaluator::Evaluate (leftOp, rightOp, result);
		}

		// rational functionality


		short	Sgn (void) const
		{
			RationalInt temp;
			Evaluate (temp);
			return temp.Sgn ();
		}

		RationalInt	Abs (void) const
		{
			RationalInt temp;
			Evaluate (temp);
			temp.ToAbs ();
			return temp;
		}

		template<class RightOpType>
		short Compare (const RightOpType& op) const
		{
			RationalInt temp;
			Evaluate (temp);
			return temp.Compare (op);
		}

		Integer<Int> Round () const
		{
			RationalInt temp;
			Evaluate (temp);
			return temp.Round ();
		}

		Integer<Int> Floor () const
		{
			RationalInt temp;
			Evaluate (temp);
			return temp.Floor ();
		}

		Integer<Int> Ceil () const
		{
			RationalInt temp;
			Evaluate (temp);
			return temp.Ceil ();
		}

		// operators

		template<class RightOpType>
		BinaryRatOperator<BinaryRatOperator, RightOpType, BinaryRatAdder, Int> operator+ (const RightOpType& op) const
		{
			return BinaryRatOperator<BinaryRatOperator, RightOpType, BinaryRatAdder, Int> (*this, op);
		}

		template<class RightOpType>
		BinaryRatOperator<BinaryRatOperator, RightOpType, BinaryRatSubtractor, Int> operator- (const RightOpType& op) const
		{
			return BinaryRatOperator<BinaryRatOperator, RightOpType, BinaryRatSubtractor, Int> (*this, op);
		}

		template<class RightOpType>
		BinaryRatOperator<BinaryRatOperator, RightOpType, BinaryRatMultiplier, Int> operator* (const RightOpType& op) const
		{
			return BinaryRatOperator<BinaryRatOperator, RightOpType, BinaryRatMultiplier, Int> (*this, op);
		}

		template<class RightOpType>
		BinaryRatOperator<BinaryRatOperator, RightOpType, BinaryRatDivider, Int> operator/ (const RightOpType& op) const
		{
			return BinaryRatOperator<BinaryRatOperator, RightOpType, BinaryRatDivider, Int> (*this, op);
		}

		bool operator== (const BinaryRatOperator& op) const
		{
			RationalInt temp, opTemp;
			Evaluate (temp);
			op.Evaluate (opTemp);
			return temp == opTemp;
		}

		bool operator== (const RationalInt &op) const
		{
			RationalInt temp;
			Evaluate (temp);
			return temp == op;
		}

		bool operator!= (const BinaryRatOperator& op) const
		{
			RationalInt temp, opTemp;
			Evaluate (temp);
			op.Evaluate (opTemp);
			return temp != opTemp;
		}

		bool operator!= (const RationalInt &op) const
		{
			RationalInt temp;
			Evaluate (temp);
			return temp != op;
		}

		bool operator< (const BinaryRatOperator& op) const
		{
			RationalInt temp, opTemp;
			Evaluate (temp);
			op.Evaluate (opTemp);
			return temp < opTemp;
		}

		bool operator< (const RationalInt &op) const
		{
			RationalInt temp;
			Evaluate (temp);
			return temp < op;
		}

		bool operator> (const BinaryRatOperator& op) const
		{
			RationalInt temp, opTemp;
			Evaluate (temp);
			op.Evaluate (opTemp);
			return temp > opTemp;
		}

		bool operator> (const RationalInt &op) const
		{
			RationalInt temp;
			Evaluate (temp);
			return temp > op;
		}

		bool operator<= (const BinaryRatOperator& op) const
		{
			RationalInt temp, opTemp;
			Evaluate (temp);
			op.Evaluate (opTemp);
			return temp <= opTemp;
		}

		bool operator<= (const RationalInt &op) const
		{
			RationalInt temp;
			Evaluate (temp);
			return temp <= op;
		}

		bool operator>= (const BinaryRatOperator& op) const
		{
			RationalInt temp, opTemp;
			Evaluate (temp);
			op.Evaluate (opTemp);
			return temp >= opTemp;
		}

		bool operator>= (const RationalInt &op) const
		{
			RationalInt temp;
			Evaluate (temp);
			return temp >= op;
		}

	private:
		const LeftOp	&leftOp;
		const RightOp	&rightOp;
};


template<typename Int>
class Rational
{
	friend struct BinaryRatAdder;
	friend struct BinaryRatSubtractor;
	friend struct BinaryRatMultiplier;
	friend struct BinaryRatDivider;

	void	CopyLessAdd (const Rational &, const Rational &);
	void	CopyLessSubtract (const Rational &, const Rational &);
	void	CopyLessMultiply (const Rational &, const Rational &);
	void	CopyLessDivide (const Rational &, const Rational &);

	Integer<Int> nom, denom;

public:
	Rational ();
	Rational (const Rational&);
	Rational (Rational&&);
	Rational (const Integer<Int>&);
	Rational (Integer<Int>&&);
	Rational (Int);
	Rational (Int, Int);
	Rational (double, double);
	Rational (double, Int);
	template<class LeftOp, class RightOp, class Evaluator>
	Rational (const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int> &);

	const Rational& operator= (const Rational&);
	const Rational& operator= (Rational&&);
	const Rational& operator= (const Integer<Int>&);
	const Rational& operator= (Integer<Int>&&);
	const Rational& operator= (Int);
	template<class LeftOp, class RightOp, class Evaluator>
	const Rational& operator= (const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int> &);

	bool operator== (const Rational&) const;
	bool operator!= (const Rational&) const;
	bool operator< (const Rational&) const;
	bool operator> (const Rational&) const;
	bool operator<= (const Rational&) const;
	bool operator>= (const Rational&) const;
	bool InZeroToOne () const; 

	Rational operator- () const;

	template<class RightOpType>
	BinaryRatOperator<Rational<Int>, RightOpType, BinaryRatAdder, Int> operator+ (const RightOpType&) const;
	template<class RightOpType>
	BinaryRatOperator<Rational<Int>, RightOpType, BinaryRatSubtractor, Int> operator- (const RightOpType&) const;
	template<class RightOpType>
	BinaryRatOperator<Rational<Int>, RightOpType, BinaryRatMultiplier, Int> operator* (const RightOpType&) const;
	template<class RightOpType>
	BinaryRatOperator<Rational<Int>, RightOpType, BinaryRatDivider, Int> operator/ (const RightOpType&) const;

	const Rational& operator+= (const Rational&);
	const Rational& operator-= (const Rational&);
	const Rational& operator*= (const Rational&);
	const Rational& operator/= (const Rational&);

	const Integer<Int>& Nom () const;
	const Integer<Int>& Denom () const;

	short Sgn () const;
	Rational Abs () const;

	void	ToAbs ();
	void	InvertSign ();

	short Compare (const Rational&) const;
	short CompareAbs (const Rational &) const;

	Integer<Int> Round () const;
	Integer<Int> Floor () const;
	Integer<Int> Ceil () const;
	double ConvertToDouble () const; 

	void Simplify ();

	void DBDump () const;
};

template<typename Int>
GS_FORCE_INLINE bool Solve2X2 (Rational<Int> (&rhs_x)[2], Rational<Int> (&M)[2][2]); //Attention, M gets destroyed! Result is returned in rhs_x

template<typename Int>
GS_FORCE_INLINE bool Solve3X3 (Rational<Int> (&rhs_x)[3], Rational<Int> (&M)[3][3]); //Attention, M gets destroyed! Result is returned in rhs_x

#include "RationalImp.hpp"

}

#endif
