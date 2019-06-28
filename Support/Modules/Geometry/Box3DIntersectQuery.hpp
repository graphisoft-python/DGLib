// *********************************************************************************************************************
// Description:		3D axis aligned box intersection custom query for KDTree
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	BeA
//
// SG compatible
// *********************************************************************************************************************

#if !defined (BOX3D_INTERSECT_QUERY_HPP)
#define BOX3D_INTERSECT_QUERY_HPP

#pragma once

// from GSRoot
#include "TypeTraits.hpp"

namespace Geometry {


template <typename TreeType, typename AdapterType>
class Box3DIntersectQuery;


template <typename TreeType, typename AdapterType>
void	QueryBox3DIntersects (const TreeType& tree, const typename TreeType::KeyType& key, AdapterType adapter)
{
	static_assert (TreeType::NodeBoundsModeValue == Geometry::KDTreeNodeBoundsDisabled, "boundsModeCheck"); // use OrthogonalRangeQuery when KDTreeNodeBoundEnabled
	Box3DIntersectQuery<QueryTypes<TreeType, TreeType::ElemSetTypeValue, true>, AdapterType> query (key, adapter);
	tree.CustomQuery (query);
}

template <typename TreeType, typename AdapterType>
void	QueryBox3DIntersects (TreeType& tree, const typename TreeType::KeyType& key, AdapterType adapter)
{
	static_assert (TreeType::NodeBoundsModeValue == Geometry::KDTreeNodeBoundsDisabled, "boundsModeCheck"); // use OrthogonalRangeQuery when KDTreeNodeBoundEnabled
	Box3DIntersectQuery<QueryTypes<TreeType, TreeType::ElemSetTypeValue, false>, AdapterType> query (key, adapter);
	tree.CustomQuery (query);
}


template <typename QueryTypes, typename AdapterType>
class Box3DIntersectQuery {
private:

	template <typename TreeType_, typename AdapterType_>
	friend void	QueryBox3DIntersects (const TreeType_& tree, const typename TreeType_::KeyType& key, AdapterType_ adapter);

	template <typename TreeType_, typename AdapterType_>
	friend void	QueryBox3DIntersects (TreeType_& tree, const typename TreeType_::KeyType& key, AdapterType_ adapter);

	typedef typename QueryTypes::Tree	TreeType;

	typedef typename TreeType::KeyType	KeyType;
	typedef typename KeyType::DimType	DimType;

	typedef typename QueryTypes::NodeBase	NodeBase;
	typedef typename QueryTypes::Node		Node;
	typedef typename QueryTypes::Leaf		Leaf;

	const KeyType	key;
	AdapterType&	adapter;

	Box3DIntersectQuery (const KeyType& key, AdapterType& adapter) : key (key), adapter (adapter)
	{
		static_assert (KeyType::DimCnt == 6, "KeyType::DimCnt == 6");
	}

	GS_FORCE_INLINE void ProcessLeaf (Leaf* leaf)
	{
		const KeyType& elemKey = leaf->GetAssoc ().GetKey ();
		if (key.GetDimVal (0) > elemKey.GetDimVal (1) ||
			key.GetDimVal (1) < elemKey.GetDimVal (0) ||
			key.GetDimVal (2) > elemKey.GetDimVal (3) ||
			key.GetDimVal (3) < elemKey.GetDimVal (2) ||
			key.GetDimVal (4) > elemKey.GetDimVal (5) ||
			key.GetDimVal (5) < elemKey.GetDimVal (4))
		{
			return;
		}
		leaf->LeafFound ();
		adapter (leaf->GetAssoc ().GetElem ());
	}

public:
	void operator () (NodeBase* nodeBase)
	{

		const UInt32 NUM_STACK = 64;

		struct NodeItem {
			short			dimIdx;
			NodeBase*		nb;
			void Set (short dimIdx, NodeBase* nb)
			{
				this->dimIdx = dimIdx;
				this->nb = nb;
			}
		};

		NodeItem stack [NUM_STACK];
		stack [0].Set (0, nodeBase);

		UInt32 stackSize = 1;

		while (stackSize != 0)  {
			--stackSize;
			NodeBase*	nb = stack [stackSize].nb;

			switch (stack [stackSize].dimIdx) {
			default:
				DBBREAK ();
	start:
			case 0:
				if (nb->IsLeaf ()) {
					Leaf* leaf = nb->ToLeaf ();
					ProcessLeaf (leaf);
					break;
				} else {
					Node* node = nb->ToNode ();
					if (key.GetDimVal (1) >= node->GetSeparatorVal ()) {
						stack[stackSize].Set (1, node->GetRight ());
						++stackSize;
					}
					nb = node->GetLeft ();
				}
			case 1:
				if (nb->IsLeaf ()) {
					Leaf* leaf = nb->ToLeaf ();
					ProcessLeaf (leaf);
					break;
				} else {
					Node* node = nb->ToNode ();
					if (key.GetDimVal (0) <= node->GetSeparatorVal ()) {
						stack[stackSize].Set (2, node->GetLeft ());
						++stackSize;
					}
					nb = node->GetRight ();
				}
			case 2:
				if (nb->IsLeaf ()) {
					Leaf* leaf = nb->ToLeaf ();
					ProcessLeaf (leaf);
					break;
				} else {
					Node* node = nb->ToNode ();
					if (key.GetDimVal (3) >= node->GetSeparatorVal ()) {
						stack[stackSize].Set (3, node->GetRight ());
						++stackSize;
					}
					nb = node->GetLeft ();
				}
			case 3:
				if (nb->IsLeaf ()) {
					Leaf* leaf = nb->ToLeaf ();
					ProcessLeaf (leaf);
					break;
				} else {
					Node* node = nb->ToNode ();
					if (key.GetDimVal (2) <= node->GetSeparatorVal ()) {
						stack[stackSize].Set (4, node->GetLeft ());
						++stackSize;
					}
					nb = node->GetRight ();
				}
			case 4:
				if (nb->IsLeaf ()) {
					Leaf* leaf = nb->ToLeaf ();
					ProcessLeaf (leaf);
					break;
				} else {
					Node* node = nb->ToNode ();
					if (key.GetDimVal (5) >= node->GetSeparatorVal ()) {
						stack[stackSize].Set (5, node->GetRight ());
						++stackSize;
					}
					nb = node->GetLeft ();
				}
			case 5:
				if (nb->IsLeaf ()) {
					Leaf* leaf = nb->ToLeaf ();
					ProcessLeaf (leaf);
					break;
				} else {
					Node* node = nb->ToNode ();
					if (key.GetDimVal (4) <= node->GetSeparatorVal ()) {
						stack[stackSize].Set (0, node->GetLeft ());
						++stackSize;
					}
					nb = node->GetRight ();
				}
				goto start;
			}
		}

	}
};


template <typename TreeType1, typename TreeType2, typename AdapterType, typename DimType>
class AllBoundBoxIntersectsQuery;


template <typename TreeType1, typename TreeType2, typename AdapterType, typename DimType>
void	QueryAllBoundBoxIntersects (const TreeType1& tree1, const TreeType2& tree2, AdapterType& adapter, const DimType& eps)
{
	AllBoundBoxIntersectsQuery<QueryTypes<TreeType1, TreeType1::ElemSetTypeValue, true>,
							   QueryTypes<TreeType2, TreeType2::ElemSetTypeValue, true>,
							   AdapterType, DimType> (tree1, tree2, adapter, eps).Run ();
}


template <typename TreeType1, typename TreeType2, typename AdapterType, typename DimType>
void	QueryAllBoundBoxIntersects (TreeType1& tree1, TreeType2& tree2, AdapterType& adapter, const DimType& eps)
{
	AllBoundBoxIntersectsQuery<QueryTypes<TreeType1, TreeType1::ElemSetTypeValue, false>,
							   QueryTypes<TreeType2, TreeType2::ElemSetTypeValue, false>,
							   AdapterType, DimType> (tree1, tree2, adapter, eps).Run ();
}

template <bool>
class AddLeaf;

template <>
class AddLeaf<true>
{
public:
	template <typename AdapterType, typename LeafType1, typename LeafType2>
	AddLeaf (AdapterType& adapter, LeafType1 leaf1, LeafType2 leaf2)
	{
		adapter (leaf1->GetAssoc ().GetElem (), leaf2->GetAssoc ().GetElem ());
	}
};

template <>
class AddLeaf<false>
{
public:
	template <typename AdapterType, typename LeafType1, typename LeafType2>
	AddLeaf (AdapterType& adapter, LeafType2 leaf2, LeafType1 leaf1)
	{
		adapter (leaf1->GetAssoc ().GetElem (), leaf2->GetAssoc ().GetElem ());
	}
};


template <bool>
class ConditionalProcessNode;

template <>
class ConditionalProcessNode<true>
{
public:
	template <typename QueryType>
	ConditionalProcessNode (QueryType& query, typename QueryType::Node1* node)
	{
		query.ProcessNode (node);
	}
};

template <>
class ConditionalProcessNode<false>
{
public:
	template <typename QueryType>
	ConditionalProcessNode (QueryType& /*query*/, typename QueryType::Node1* /*node*/)
	{
	}
};


template <typename QueryTypes1, typename QueryTypes2, typename AdapterType, typename DimType>
class AllBoundBoxIntersectsQuery {
public:
	typedef typename QueryTypes1::Tree TreeType1;
	typedef typename QueryTypes2::Tree TreeType2;

private:
	template <typename TreeType1_, typename TreeType2_, typename AdapterType_, typename DimType_>
	friend
	void	QueryAllBoundBoxIntersects (const TreeType1_& tree1, const TreeType2_& tree2, AdapterType_& adapter, const DimType_& eps);

	template <typename TreeType1_, typename TreeType2_, typename AdapterType_, typename DimType_>
	friend
	void	QueryAllBoundBoxIntersects (TreeType1_& tree1, TreeType2_& tree2, AdapterType_& adapter, const DimType_& eps);

	template <bool>
	friend class ConditionalProcessNode;

	typedef typename TreeType1::KeyType		KeyType1;
	typedef typename KeyType1::DimType		DimType1;

	typedef typename QueryTypes1::NodeBase	NodeBase1;
	typedef typename QueryTypes1::Node		Node1;
	typedef typename QueryTypes1::Leaf		Leaf1;
	typedef typename TreeType1::Bounds		Bounds1;

	typedef typename TreeType2::KeyType		KeyType2;
	typedef typename KeyType2::DimType		DimType2;

	typedef typename QueryTypes2::NodeBase	NodeBase2;
	typedef typename QueryTypes2::Node		Node2;
	typedef typename QueryTypes2::Leaf		Leaf2;
	typedef typename TreeType2::Bounds		Bounds2;

	AdapterType&	adapter;

	NodeBase1* root1;
	NodeBase2* root2;

	const DimType& eps;

	template<typename NodeBaseType>
	struct GetRootNodeAdapter
	{
		NodeBaseType*& rootPtr;
		GetRootNodeAdapter (NodeBaseType*& rootPtr) : rootPtr (rootPtr)
		{
			rootPtr = nullptr;
		}

		void operator () (NodeBaseType* nb)
		{
			rootPtr = nb;
		}
	};


	template <typename BoundsAType, typename BoundsBType>
	bool BoundsIntersect (const BoundsAType& boundsA, const BoundsBType& boundsB)
	{
		for (short i = 0; i < KeyType1::DimCnt; i+= 2) {
			if (boundsA.GetMin (i) - eps > boundsB.GetMax (i + 1) ||
				boundsA.GetMax (i + 1) < boundsB.GetMin (i) - eps)
			{
				return false;
			}
		}
		return true;
	}


	template <typename LeafAType, typename LeafBType>
	void ProcessLeaves (LeafAType* leafA, LeafBType* leafB)
	{
		for (short i = 0; i < KeyType1::DimCnt; i+=2) {
			if (leafA->GetAssoc ().GetKey ().GetDimVal (i) - eps > leafB->GetAssoc ().GetKey ().GetDimVal (i + 1) ||
				leafA->GetAssoc ().GetKey ().GetDimVal (i + 1) < leafB->GetAssoc ().GetKey ().GetDimVal (i) - eps)
			{
				return;
			}
		}
		leafA->LeafFound ();
		leafB->LeafFound ();
		AddLeaf<GS::IsSame<Leaf1, LeafAType>> (adapter, leafA, leafB);
	}


	template <typename QueryTypesA, typename QueryTypesB>
	void ProcessLeafNode (typename QueryTypesA::Leaf* leaf, const typename QueryTypesA::Tree::Bounds& bounds, typename QueryTypesB::Node* node)
	{
		if (!BoundsIntersect (bounds, node->GetBounds ())) {
			return;
		}
		if (node->GetLeft ()->IsLeaf ()) {
			typename QueryTypesB::Leaf* otherLeaf = node->GetLeft ()->ToLeaf ();
			ProcessLeaves (leaf, otherLeaf);
		} else {
			typename QueryTypesB::Node* otherNode = node->GetLeft ()->ToNode ();
			ProcessLeafNode<QueryTypesA, QueryTypesB> (leaf, bounds, otherNode);
		}
		if (node->GetRight ()->IsLeaf ()) {
			typename QueryTypesB::Leaf* otherLeaf = node->GetRight ()->ToLeaf ();
			ProcessLeaves (leaf, otherLeaf);
		} else {
			typename QueryTypesB::Node* otherNode = node->GetRight ()->ToNode ();
			ProcessLeafNode<QueryTypesA, QueryTypesB> (leaf, bounds, otherNode);
		}
	}


	void ProcessNodes (Node1* n1, Node2* n2)
	{

		if (!BoundsIntersect (n1->GetBounds (), n2->GetBounds ())) {
			return;
		}
		if (n1->GetTotalLeafCount () > n2->GetTotalLeafCount ()) {
			if (n1->GetLeft ()->IsLeaf ()) {
				Leaf1* leaf = n1->GetLeft ()->ToLeaf ();
				ProcessLeafNode<QueryTypes1, QueryTypes2> (leaf, leaf->GetAssoc ().GetKey (), n2);
			} else  {
				Node1* node = n1->GetLeft ()->ToNode ();
				ProcessNodes (node, n2);
			}

			if (n1->GetRight ()->IsLeaf ()) {
				Leaf1* leaf = n1->GetRight ()->ToLeaf ();
				ProcessLeafNode<QueryTypes1, QueryTypes2> (leaf, leaf->GetAssoc ().GetKey (), n2);
			} else  {
				Node1* node = n1->GetRight ()->ToNode ();
				ProcessNodes (node, n2);
			}

		} else {
			if (n2->GetLeft ()->IsLeaf ()) {
				Leaf2* leaf = n2->GetLeft ()->ToLeaf ();
				ProcessLeafNode<QueryTypes2, QueryTypes1> (leaf, leaf->GetAssoc ().GetKey (), n1);
			} else  {
				Node2* node = n2->GetLeft ()->ToNode ();
				ProcessNodes (n1, node);
			}

			if (n2->GetRight ()->IsLeaf ()) {
				Leaf2* leaf = n2->GetRight ()->ToLeaf ();
				ProcessLeafNode<QueryTypes2, QueryTypes1> (leaf, leaf->GetAssoc ().GetKey (), n1);
			} else  {
				Node2* node = n2->GetRight ()->ToNode ();
				ProcessNodes (n1, node);
			}
		}
	}

	void ProcessNode (Node1* node)
	{
		if (node->GetLeft ()->IsLeaf ()) {
			Leaf1* leftLeaf = node->GetLeft ()->ToLeaf ();
// 			leftLeaf->LeafFound ();
// 			leftLeaf->LeafFound ();
// 			adapter (leftLeaf->GetAssoc ().GetElem (), leftLeaf->GetAssoc ().GetElem ());

			if (node->GetRight ()->IsLeaf ()) {
				Leaf1* rightLeaf = node->GetRight ()->ToLeaf ();
// 				rightLeaf->LeafFound ();
// 				rightLeaf->LeafFound ();
// 				adapter (rightLeaf->GetAssoc ().GetElem (), rightLeaf->GetAssoc ().GetElem ());

				ProcessLeaves (leftLeaf, rightLeaf);
			} else {
				Node1* rightNode = node->GetRight ()->ToNode ();
				ProcessNode (rightNode);

				ProcessLeafNode<QueryTypes1, QueryTypes1> (leftLeaf, leftLeaf->GetAssoc ().GetKey (), rightNode);
			}
		} else {
			Node1* leftNode = node->GetLeft ()->ToNode ();

			ProcessNode (leftNode);

			if (node->GetRight ()->IsLeaf ()) {
				Leaf1* rightLeaf = node->GetRight ()->ToLeaf ();
// 				rightLeaf->LeafFound ();
// 				rightLeaf->LeafFound ();
// 				adapter (rightLeaf->GetAssoc ().GetElem (), rightLeaf->GetAssoc ().GetElem ());

				ProcessLeafNode<QueryTypes1, QueryTypes1> (rightLeaf, rightLeaf->GetAssoc ().GetKey (), leftNode);
			} else {
				Node1* rightNode = node->GetRight ()->ToNode ();
				ProcessNode (rightNode);

				ProcessNodes (leftNode, rightNode);
			}
		}

	}

	AllBoundBoxIntersectsQuery (TreeType1& tree1, TreeType2& tree2, AdapterType& adapter, const DimType& eps) : adapter (adapter), eps (eps)
	{
		static_assert ((KeyType1::DimCnt & 0x1) == 0 && KeyType2::DimCnt == KeyType1::DimCnt, "(KeyType1::DimCnt & 0x1) == 0 && KeyType2::DimCnt == KeyType1::DimCnt");

		GetRootNodeAdapter<NodeBase1> getRootNode1 (root1);
		tree1.CustomQuery (getRootNode1);
		GetRootNodeAdapter<NodeBase2> getRootNode2 (root2);
		tree2.CustomQuery (getRootNode2);
	}

public:
	void Run ()
	{
		if (root1 != nullptr && root2 != nullptr) {
			if (reinterpret_cast<const void*>(root1) == reinterpret_cast<const void*>(root2)) {
				if (root1->IsLeaf ()) {
//					ProcessLeaves (root1->ToLeaf (), root2->ToLeaf ());
				} else {
					ConditionalProcessNode<GS::IsSame<TreeType1, TreeType2>> (*this, root1->ToNode ());
				}
			} else if (root1->IsLeaf ()) {
				Leaf1* leaf = root1->ToLeaf();
				if (root2->IsLeaf ()) {
					ProcessLeaves (leaf, root2->ToLeaf ());
				} else {
					ProcessLeafNode<QueryTypes1, QueryTypes2> (leaf, leaf->GetAssoc ().GetKey (), root2->ToNode ());
				}
			} else if (root2->IsLeaf ()) {
				Leaf2* leaf = root2->ToLeaf ();
				ProcessLeafNode<QueryTypes2, QueryTypes1> (leaf, leaf->GetAssoc ().GetKey (), root1->ToNode ());
			} else {
				ProcessNodes (root1->ToNode (), root2->ToNode ());
			}
		}
	}
};

} // namespace Geometry

#endif