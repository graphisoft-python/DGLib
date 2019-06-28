#ifndef GS_IMPLIES_HPP
#define GS_IMPLIES_HPP

namespace GS {

inline bool Implies (bool a, bool b)
{
	return !a || b;
}

} // namespace GS

#endif
