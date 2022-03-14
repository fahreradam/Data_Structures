#pragma once

/// <summary>
/// S.S.U.D.S. (SSU Data Structures) is meant to be a crude, not terribly optimized, 
/// but general-purpose collections of general-purpose data structures and algorithms to work
/// with those data structures.
/// </summary>
namespace ssuds
{
	/// <summary>
	/// When a data structure can be thought of as sorted, we can use these to indicate
	/// which type of sort (ASCENDING = small values => high values, 
	/// DESCENDING = high values => low values). 
	/// </summary>
	enum class SortOrder { ASCENDING, DESCENDING };
}
