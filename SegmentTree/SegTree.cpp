/*
A generic implementation of Segment Tree data structure
with min/max/sum operations supported.
Supply a vector and an operation type to construct the SegTree.
Note: the vector supplied must be 'move'd (passed by rvalue ref)
      as the SegTree takes ownership of the vector. 
query(left, right) : returns value of segment [left:right] based on
                     operation type (min/max/sum)
update(index, val) : update the element at index of the vector used
                     to consturct the SegTree and update the tree.
*/
#include <iostream>
#include <ostream>
#include <vector>
#include <cassert>
#include <limits>

using namespace std;
// indicates if a node will hold the max/min/sum of its children
typedef enum { MAX, MIN, SUM } SegTreeAugmentType;
template <typename ValueType >
class SegTree {
    SegTreeAugmentType augType;
    vector<ValueType> tree;
    vector<ValueType> & arr;
    ValueType sentinel;
    ValueType augmentNodes(const ValueType v1, const ValueType v2) {
        switch (augType) {
        case SegTreeAugmentType::MAX:
            return std::max(v1, v2);
        case SegTreeAugmentType::MIN:
            return std::min(v1, v2);
        case SegTreeAugmentType::SUM:
            return v1 + v2;
        default:
            assert(0);
        }
        return ValueType();
    }
    void build(int start, int end, int node) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = ( start + end ) / 2;
            build( start, mid, 2*node );
            build( mid + 1, end, 2*node + 1 );
            tree[node] = augmentNodes( tree[ 2*node ], tree[ 2*node + 1 ]);
        }
    }
    void update( int start, int end, int idx, int val, int node ) {
        if (start == end) {
            // update leaf node
            tree[node] += val;
        } else {
            int mid = ( start + end ) / 2;
            if ( start <= idx && idx <= end ) {
                update( start, mid, idx, val, node*2 );
            } else {
                update( mid + 1, end, idx, val, node*2 + 1 );
            }
            // update node with left and right child values
            tree[node] = augmentNodes( tree[node*2], tree[node*2 + 1] );
        }
    }
    ValueType query(int start, int end, int left, int right, int node ) {
        // range represented by this node is [start : end ]
        // query range is [left : right]
        if ( right < start || left > end ) {
            // query range completeley outside node range
            // return value that won't affect the augmentation.
            return sentinel;
        }
        if ( start >= left && end <= right ) {
            // this node's range is fully inside query range
            return tree[node];
        }
        // node range is partially inside query range
        int mid = ( start + end ) / 2;
        ValueType t1 = query(start, mid, left, right, node*2);
        ValueType t2 = query(mid+1, end, left, right, node*2 +1 );
        return augmentNodes( t1, t2 ); 
    }
    public:
    SegTree(vector<ValueType> && arr, SegTreeAugmentType at)
    : arr(arr)
    , augType(at) {
        tree.resize(2*arr.size() + 1);
        build( 0, arr.size() - 1 , 1);
        switch (at) {
        case SegTreeAugmentType::MAX :
            sentinel = std::numeric_limits<ValueType>::min();
            break;
        case SegTreeAugmentType::MIN :
            sentinel = std::numeric_limits<ValueType>::max();
            break;
        case SegTreeAugmentType::SUM :
            sentinel = 0;
            break;
        default:
            assert(0);
        }
    }
    void update(int idx, ValueType val) {
        arr[idx] = val;
        update(0, arr.size() - 1, idx, val, 1);
    }
    ValueType query(int left, int right) {
        return query( 0, arr.size() - 1, left, right , 1);
    }
    template <typename VT >
    friend ostream& operator << (ostream& os, const SegTree<VT> & st);
};
template <typename VT >
ostream & operator<<(ostream &os, const SegTree<VT> & st) {
    for (auto e : st.tree) {
        os << e << " ";
    }
    os << endl;
    for (int i = 0; i < st.tree.size(); ++i) {
        os << "---";
    }
    os << endl;
    for (int i = 0; i < st.tree.size(); ++i) {
        os << i << " ";
    }
    os << endl;
    return os;
}

int main() {
    vector<int> arr = { 2, 3, 4, 1, 5, 6 };
    SegTree<int> st( std::move(arr) , SegTreeAugmentType::SUM);
    st.update(2, 4);
    cout << "sum (2, 5) = " << st.query( 2, 5 ) << endl;
    SegTree<int> st2( { 2, 3, 4, 1, 5, 6 } , SegTreeAugmentType::MAX);
    cout << "max (1, 4) = " << st2.query( 1, 4 ) << endl;
    SegTree<float> st3 ( {1.31, 3.56, 6.78, 0.99, 1.23}, SegTreeAugmentType::MIN);
    cout << "min (0, 2) = " << st3.query( 0, 2 ) << endl;
    return 0;
}
