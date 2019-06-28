// *********************************************************************************************************************
// Description:		RationalImp.hpp
//
// Module:			Modeler
// Contact person:	HK, PP
//
// *********************************************************************************************************************

template<typename Int>
void Rational<Int>::CopyLessAdd (const Rational &a, const Rational &b)
{
	if (a.denom == b.denom) {
		nom.CopyLessAdd (a.nom, b.nom);
		denom = a.denom;
	} else {
		nom = a.nom * b.denom + b.nom * a.denom;
		if (this == &a || this == &b) {
			Integer<Int> temp;
			temp.CopyLessMultiply (a.denom, b.denom);
			denom = temp;
		} else
			denom.CopyLessMultiply (a.denom, b.denom);
	}

	if (nom.IsZero ())
		denom = 1;
}

template<typename Int>
void Rational<Int>::CopyLessSubtract (const Rational &a, const Rational &b)
{
	if (a.denom == b.denom) {
		nom.CopyLessSubtract (a.nom, b.nom);
		denom = a.denom;
	} else {
		nom = a.nom * b.denom - b.nom * a.denom;
		if (this == &a || this == &b) {
			Integer<Int> temp;
			temp.CopyLessMultiply (a.denom, b.denom);
			denom = temp;
		} else
			denom.CopyLessMultiply (a.denom, b.denom);
	}

	if (nom.IsZero ())
		denom = 1;
}

template<typename Int>
void Rational<Int>::CopyLessMultiply (const Rational &a, const Rational &b)
{
	nom.CopyLessMultiply (a.nom, b.nom);

	if (nom.IsZero ())
		denom = 1;
	else
		denom.CopyLessMultiply (a.denom, b.denom);
}

template<typename Int>
void Rational<Int>::CopyLessDivide (const Rational &a, const Rational &b)
{
	if (DBERROR (b.nom.IsZero ())) {
		// what the...
		throw GS::Exception (nullptr, __FILE__, __LINE__);
	}

	if (a.nom.IsZero ()) {
		*this = 0;
		return;
	}

	if (a.denom == b.denom) {
		nom = a.nom;
		denom = b.nom;
	} else {
		nom.CopyLessMultiply (a.nom, b.denom);
		denom.CopyLessMultiply (a.denom, b.nom);
	}

	if (b.nom.IsNegative ()) {
		nom.InvertSign ();
		denom.InvertSign ();
	}
}

template<typename Int>
GS_FORCE_INLINE Rational<Int>::Rational () :
	nom (0),
	denom (1)
{
}

template<typename Int>
GS_FORCE_INLINE Rational<Int>::Rational (const Rational& op) :
	nom (op.nom),
	denom (op.denom)
{
}

template<typename Int>
GS_FORCE_INLINE Rational<Int>::Rational (Rational&& op) :
	nom (std::move (op.nom)),
	denom (std::move (op.denom))
{
}

template<typename Int>
GS_FORCE_INLINE Rational<Int>::Rational (const Integer<Int>& op) :
	nom (op),
	denom (1)
{
}

template<typename Int>
GS_FORCE_INLINE Rational<Int>::Rational (Integer<Int>&& op) :
	nom (std::move (op)),
	denom (1)
{
}

template<typename Int>
GS_FORCE_INLINE Rational<Int>::Rational (Int op) :
	nom (op),
	denom (1)
{
}

template<typename Int>
Rational<Int>::Rational (Int n, Int dn) :
	nom (n),
	denom (dn)
{
	if (dn == 0)
		throw GS::Exception (nullptr, __FILE__, __LINE__);

	if (dn < 0) {
		nom = -n;
		denom = -dn;
	}
}

template<typename Int>
Rational<Int>::Rational (double n, double dn)
{
	if (dn == 0.0)
		throw GS::Exception (nullptr, __FILE__, __LINE__);

	if (dn < 0.0) {
		n *= -1.0;
		dn *= -1.0;
	}

	int dnExp, nExp; 
	double dnMant = frexp (dn, &dnExp); 
	double nMant = frexp (n, &nExp); 
	//scale so n, dn gets to be integer!
	int minExp = GS::Min (nExp, dnExp);
	nExp  += DBL_MANT_DIG - minExp;
	dnExp += DBL_MANT_DIG - minExp;
	int maxExp = GS::Max (nExp, dnExp);
	if (maxExp > DBL_MAX_EXP) {
		DBBREAK_STR ("Rational form two doubles will loose accuracy!"); 
		int diffExp = maxExp - DBL_MAX_EXP;
		nExp -= diffExp; 
		dnExp -= diffExp; 
	}

	dn = ldexp (dnMant, dnExp);
	n = ldexp (nMant, nExp);


	nom.ConvertFromDouble (n);
	denom.ConvertFromDouble (dn);

	Simplify ();
}

template<typename Int>
Rational<Int>::Rational (double n, Int dn)
{
	if (dn == 0)
		throw GS::Exception (nullptr, __FILE__, __LINE__);

	if (dn < 0) {
		n *= -1.0;
		dn *= -1;
	}

	denom = dn; 

	int nExp; 
	double nMant = frexp (n, &nExp); 
	if (nExp < DBL_MANT_DIG) {
		//scale so n gets to be integer!
		nom.ConvertFromDouble (ldexp (nMant, DBL_MANT_DIG)); 
		denom.ShiftLeftExpand (DBL_MANT_DIG - nExp); 
	}
	else {
		nom.ConvertFromDouble (n);
	}

	Simplify ();
}

template<typename Int>
template<class LeftOp, class RightOp, class Evaluator>
GS_FORCE_INLINE Rational<Int>::Rational (const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int>& op) :
	nom (0),
	denom (1)
{
	op.Evaluate (*this);
}

template<typename Int>
GS_FORCE_INLINE const Rational<Int>& Rational<Int>::operator= (const Rational& op)
{
	if (this != &op) {
		nom = op.nom;
		denom = op.denom;
	}

	return *this;
}

template<typename Int>
GS_FORCE_INLINE const Rational<Int>& Rational<Int>::operator= (Rational&& op)
{
	if (this != &op) {
		nom = std::move (op.nom);
		denom = std::move (op.denom);
	}

	return *this;
}

template<typename Int>
GS_FORCE_INLINE const Rational<Int>& Rational<Int>::operator= (const Integer<Int>& op)
{
	nom = op;
	denom = 1;

	return *this;
}

template<typename Int>
GS_FORCE_INLINE const Rational<Int>& Rational<Int>::operator= (Integer<Int>&& op)
{
	nom = std::move (op);
	denom = 1;

	return *this;
}

template<typename Int>
GS_FORCE_INLINE const Rational<Int>& Rational<Int>::operator= (Int op)
{
	nom = op;
	denom = 1;

	return *this;
}

template<typename Int>
template<class LeftOp, class RightOp, class Evaluator>
GS_FORCE_INLINE const Rational<Int>& Rational<Int>::operator= (const BinaryRatOperator<LeftOp, RightOp, Evaluator, Int> &op)
{
	Rational temp;
	op.Evaluate (temp);
	return *this = temp;
}

template<typename Int>
bool Rational<Int>::operator== (const Rational& op) const
{
	short sg = nom.Sgn ();
	if (sg != op.nom.Sgn ())
		return false;

	if (sg == 0)
		return true;

	if (denom == op.denom)
		return nom == op.nom;

	return nom * op.denom == op.nom * denom;
}

template<typename Int>
GS_FORCE_INLINE bool Rational<Int>::operator!= (const Rational& op) const
{
	return !(*this == op);
}

template<typename Int>
bool Rational<Int>::operator< (const Rational& op) const
{
	short sg1 = nom.Sgn ();
	short sg2 = op.nom.Sgn ();

	if (sg1 < sg2)
		return true;
	if (sg1 > sg2 || sg1 == 0)
		return false;

	if (denom == op.denom)
		return nom < op.nom;

	return nom * op.denom < op.nom * denom;
}

template<typename Int>
bool Rational<Int>::operator> (const Rational& op) const
{
	short sg1 = nom.Sgn ();
	short sg2 = op.nom.Sgn ();

	if (sg1 > sg2)
		return true;
	if (sg1 < sg2 || sg1 == 0)
		return false;

	if (denom == op.denom)
		return nom > op.nom;

	return nom * op.denom > op.nom * denom;
}


template<typename Int>
GS_FORCE_INLINE bool Rational<Int>::operator<= (const Rational& op) const
{
	return !(*this > op);
}

template<typename Int>
GS_FORCE_INLINE bool Rational<Int>::operator>= (const Rational& op) const
{
	return !(*this < op);
}

template<typename Int>
GS_FORCE_INLINE bool Rational<Int>::InZeroToOne () const
{
	if (nom.Sgn () < 1) return false; //less equal zero!
	return nom < denom;				  //true if less than one!
}

template<typename Int>
inline Rational<Int> Rational<Int>::operator- () const
{
	Rational retVal;

	retVal.nom = nom;
	retVal.denom = denom;
	retVal.nom.InvertSign ();
	return retVal;
}

template<typename Int>
template<class RightOpType>
GS_FORCE_INLINE BinaryRatOperator<Rational<Int>, RightOpType, BinaryRatAdder, Int> Rational<Int>::operator+ (const RightOpType& op) const
{
	return BinaryRatOperator<Rational<Int>, RightOpType, BinaryRatAdder, Int> (*this, op);
}

template<typename Int>
template<class RightOpType>
GS_FORCE_INLINE BinaryRatOperator<Rational<Int>, RightOpType, BinaryRatSubtractor, Int> Rational<Int>::operator- (const RightOpType& op) const
{
	return BinaryRatOperator<Rational<Int>, RightOpType, BinaryRatSubtractor, Int> (*this, op);
}

template<typename Int>
template<class RightOpType>
GS_FORCE_INLINE BinaryRatOperator<Rational<Int>, RightOpType, BinaryRatMultiplier, Int> Rational<Int>::operator* (const RightOpType& op) const
{
	return BinaryRatOperator<Rational<Int>, RightOpType, BinaryRatMultiplier, Int> (*this, op);
}

template<typename Int>
template<class RightOpType>
GS_FORCE_INLINE BinaryRatOperator<Rational<Int>, RightOpType, BinaryRatDivider, Int> Rational<Int>::operator/ (const RightOpType& op) const
{
	return BinaryRatOperator<Rational<Int>, RightOpType, BinaryRatDivider, Int> (*this, op);
}

template<typename Int>
GS_FORCE_INLINE const Rational<Int>& Rational<Int>::operator+= (const Rational& op)
{
	CopyLessAdd (*this, op);
	return *this;
}

template<typename Int>
GS_FORCE_INLINE const Rational<Int>& Rational<Int>::operator-= (const Rational& op)
{
	CopyLessSubtract (*this, op);
	return *this;
}

template<typename Int>
GS_FORCE_INLINE const Rational<Int>& Rational<Int>::operator*= (const Rational& op)
{
	Rational retVal;
	retVal.CopyLessMultiply (*this, op);
	return *this = retVal;
}

template<typename Int>
GS_FORCE_INLINE const Rational<Int>& Rational<Int>::operator/= (const Rational& op)
{
	Rational retVal;
	retVal.CopyLessDivide (*this, op);
	return *this = retVal;
}

template<typename Int>
GS_FORCE_INLINE const Integer<Int>& Rational<Int>::Nom () const
{
	return nom;
}

template<typename Int>
GS_FORCE_INLINE const Integer<Int>& Rational<Int>::Denom () const
{
	return denom;
}

template<typename Int>
GS_FORCE_INLINE short Rational<Int>::Sgn () const
{
	return nom.Sgn ();
}

template<typename Int>
inline Rational<Int> Rational<Int>::Abs () const
{
	if (!nom.IsNegative ())
		return *this;

	Rational retVal (*this);
	retVal.nom.ToAbs ();
	return retVal;
}

template<typename Int>
inline void Rational<Int>::ToAbs ()
{
	nom.ToAbs ();
}

template<typename Int>
inline void Rational<Int>::InvertSign ()
{
	nom.InvertSign ();
}

template<typename Int>
short Rational<Int>::Compare (const Rational& op) const
{
	short sg1 = nom.Sgn ();
	short sg2 = op.nom.Sgn ();

	if (sg1 < sg2)
		return -1;
	if (sg1 > sg2)
		return 1;
	if (sg1 == 0)
		return 0;

	if (denom == op.denom)
		return nom.Compare (op.nom);

	return (nom * op.denom).Compare (op.nom * denom);
}

template<typename Int>
GS_FORCE_INLINE short Rational<Int>::CompareAbs (const Rational& op) const
{
	if (denom == op.denom)
		return nom.CompareAbs (op.nom);

	return (nom * op.denom).CompareAbs (op.nom * denom);
}

template<typename Int>
Integer<Int> Rational<Int>::Round () const
{
	if (denom == 1)
		return nom;

	Integer<Int> temp = nom + nom;
	if (!nom.IsNegative ())
		temp += denom;
	else
		temp -= denom - 1;

	return temp / (denom + denom);
}

template<typename Int>
Integer<Int> Rational<Int>::Floor () const
{
	if (denom == 1)
		return nom;

	return (!nom.IsNegative () ? nom : nom - denom + 1) / denom;
}

template<typename Int>
Integer<Int> Rational<Int>::Ceil () const
{
	if (denom == 1)
		return nom;

	return (!nom.IsNegative () ? nom + denom - 1 : nom) / denom;
}

#ifdef DEBUVERS
inline Int64 GetExponent (double a)
{
	int e; 
	frexp (a, &e); 
	return e;
}
#endif

template<typename Int>
double Rational<Int>::ConvertToDouble () const
{
	if (denom == 1)
		return nom.ConvertToDouble();

	DBASSERT (denom.Sgn () != 0);

	Int64 eNom, eDenom;
	const double rat = nom.Frexp (eNom) / denom.Frexp (eDenom);
	const Int64 exponent = eNom - eDenom;

	DBASSERT (DBL_MAX_EXP >= exponent + GetExponent(rat)); 
	DBASSERT (DBL_MIN_EXP <= exponent + GetExponent(rat)); 

	return ldexp (rat, (Int32)exponent); 
}

template<typename Int>
void Rational<Int>::Simplify ()
{
	if (nom.Sgn () == 0 || denom == 1)
		return;

	Integer<Int> gcd = nom.GCD (denom);

	nom /= gcd;
	denom /= gcd;
}

template<typename Int>
void Rational<Int>::DBDump () const
{
	DBPrintf ("["); 
	nom.DBDump (); 
	DBPrintf ("] / [");
	denom.DBDump (); 
	DBPrintf ("] ~ %g", nom.ConvertToDouble () / denom.ConvertToDouble () ); 
}

template<typename Int>
GS_FORCE_INLINE bool Solve2X2 (Rational<Int> (&rhs_x)[2], Rational<Int> (&M)[2][2]) //Attention, M gets destroyed! Result is returned in rhs_x
{
	if (M[0][0].Sgn () == 0 || M[1][1].Sgn () == 0) {
		if (M[1][0].Sgn () == 0 || M[0][1].Sgn () == 0) {
			return false;
		}

		//swap rows
		GS::Swap (M[0][0], M[1][0]); 
		GS::Swap (M[0][1], M[1][1]); 
		GS::Swap (rhs_x[0], rhs_x[1]); 
	}

	Rational<Int> mul = M[1][0]; 
	mul /= M[0][0]; 

	M[1][1] -= M[0][1] * mul; 
	if (M[1][1].Sgn () == 0) { 
		return false; 
	}

	rhs_x[1] -= rhs_x[0] * mul; 
	//mul = M[0][1] / M[1][1]; 
	//M[0][1] -= M[1][1] * mul; 
	rhs_x[0] -= rhs_x[1] * M[0][1] / M[1][1];

	rhs_x[0] /= M[0][0];
	rhs_x[1] /= M[1][1];

	return true;
}

template<typename Int>
GS_FORCE_INLINE bool Solve3X3 (Rational<Int> (&rhs_x)[3], Rational<Int> (&M)[3][3]) //Attention, M gets destroyed! Result is returned in rhs_x
{
	if (M[0][0].Sgn () == 0) {
		if (M[1][0].Sgn () == 0) {
			if (M[2][0].Sgn () == 0) {
				return false;
			}
			//swap row 0,2
			GS::Swap (M[0][0], M[2][0]); 
			GS::Swap (M[0][1], M[2][1]); 
			GS::Swap (M[0][2], M[2][2]);
			GS::Swap (rhs_x[0], rhs_x[2]); 
		}
		else {
			//swap row 0,1: 
			GS::Swap (M[0][0], M[1][0]); 
			GS::Swap (M[0][1], M[1][1]); 
			GS::Swap (M[0][2], M[1][2]);
			GS::Swap (rhs_x[0], rhs_x[1]); 
		}
	}

	Rational<Int> mul;

	//eliminate under the diagonal, first column: 
	mul = M[1][0] / M[0][0];
	//M[1][0] = 0
	M[1][1] -= M[0][1] * mul;
	M[1][2] -= M[0][2] * mul;
	rhs_x[1] -= rhs_x[0] * mul;

	mul = M[2][0] / M[0][0];
	//M[2][0] = 0
	M[2][1] -= M[0][1] * mul;
	M[2][2] -= M[0][2] * mul;
	rhs_x[2] -= rhs_x[0] * mul;

	if (M[1][1].Sgn () == 0) {
		if (M[2][1].Sgn () == 0) {
			return false;
		}
		//swap rows 1, 2
		//GS::Swap (M[1][0], M[2][0]); 
		GS::Swap (M[1][1], M[2][1]); 
		GS::Swap (M[1][2], M[2][2]);
		GS::Swap (rhs_x[1], rhs_x[2]); 
	}


	//eliminate under the diagonal second column: 
	mul = M[2][1] / M[1][1];
	//M[2][1] = 0
	M[2][2] -= M[1][2] * mul;
	if (M[2][2].Sgn () == 0) {
		return false; 
	}
	rhs_x[2] -= rhs_x[1] * mul;

	//back elimination (upper triangular!)
	rhs_x[2] /= M[2][2];
	//rhs_x[2].Simplify ();

	rhs_x[1] -= rhs_x[2] * M[1][2]; 
	rhs_x[1] /= M[1][1];
	//rhs_x[1].Simplify ();

	rhs_x[0] -= rhs_x[2] * M[0][2] + rhs_x[1] * M[0][1]; 
	rhs_x[0] /= M[0][0];
	//rhs_x[0].Simplify ();

	return true;
}
