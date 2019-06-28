#ifndef FLAGS_HPP
#define FLAGS_HPP


namespace GS {

template <typename FlagType>
class Flags {
public:
	Flags ();
	explicit Flags (FlagType initFlags);
	~Flags ();

	FlagType	GetFlags () const;
	bool		IsFlagSet (FlagType flag) const;

	void		AddFlag (FlagType flagToAdd);
	void		SetFlags (FlagType inFlags);
	void		ClearFlag (FlagType flagToClear);

private:
	FlagType	flags;
};

} // namespace GS


template <typename FlagType>
GS::Flags<FlagType>::Flags () :
	flags {}
{
}


template <typename FlagType>
GS::Flags<FlagType>::Flags (FlagType initFlags) :
	flags (initFlags)
{
}


template <typename FlagType>
GS::Flags<FlagType>::~Flags ()
{
}


template <typename FlagType>
FlagType	GS::Flags<FlagType>::GetFlags () const
{
	return flags;
}


template <typename FlagType>
bool	GS::Flags<FlagType>::IsFlagSet (FlagType flag) const
{
	return ((flags & flag) != 0);
}


template <typename FlagType>
void	GS::Flags<FlagType>::AddFlag (FlagType flagToAdd)
{
	flags |= flagToAdd;
}


template <typename FlagType>
void	GS::Flags<FlagType>::SetFlags (FlagType inFlags)
{
	flags = inFlags;
}


template <typename FlagType>
void	GS::Flags<FlagType>::ClearFlag (FlagType flagToClear)
{
	flags &= ~flagToClear;
}


#endif
