/// \file VeryFastSearchableSortingNetwork.h
/// \brief Interface for the sorting network class CSearchableSortingNetworkWithNearsort.

#pragma once

#include "FastSearchableSortingNetwork.h"

#if defined NEARSORT || defined SUPERNEARSORT

/// \brief Searchable sorting network with nearsort.
///
/// CSearchableSortingNetworkWithNearsort is a version of 
/// CSearchableSortingNetworkWithAutocomplete that uses the nearsort heuristic, 
/// which is based on reachability, to prune one level from the end.

class CSearchableSortingNetworkWithNearsort: public CSearchableSortingNetworkWithAutocomplete{
  protected:
    bool m_bReachableFrom[n][n]; ///< Reachable from.
    int m_nReachCountFrom[n]; ///< Count of channels reachable from.

    bool m_bReachableTo[n][n]; ///< Reachable to.
    int m_nReachCountTo[n]; ///< Count of channels reachable to.

    bool m_bReachable[n][n]; ///< Reachable from or to.
    int m_nReachCount[n]; ///< Count of channels reachable from or to.

    bool stillnearsorts(const int delta); ///< Does it still nearsort with this input change?
    bool evennearsorts(); ///< Does it nearly sort, even number of inputs?
    bool nearsorts(); ///< Does it nearly sort?
 
    void process(); ///< Process a candidate comparator network.
}; //CSearchableSortingNetworkWithNearsort

#endif