#pragma once

#include <cstdio>
#include <string>
#include <random>
#include <vector>
#include "int.h"

#pragma warning(disable: 4996) 

// ---------------------------------------------------------------------

inline uint16 get_random(const uint16 min, const uint16 max)
{
	using namespace std;

	static random_device			 rn;
	static uint32					 seed = rn(); // fixed_seed;
	static mt19937_64			     rnd(seed);

	uniform_int_distribution<uint16> range(min, max);

	return range(rnd);
}

inline void probability_call(const uint16 factor, void(*callback)())
{
	!get_random(0, factor - 1) ? callback() : 0;
}

// ---------------------------------------------------------------------

using	  base_unit = char;
using	  strand	= std::string;

constexpr uint16 strand_duplication_failure_factor		{ 100 };
constexpr uint16 strand_duplication_base_error_factor	{ 1000 };

constexpr char base[]
{
	'A', 'T', 'G', 'C'
};

struct		   helix
{
	strand left;
	strand right;
};

class			lifeform
{
public:
	enum   chromosome  { one_one, one_two };
	enum   strand_type { left   , right };

		   lifeform				   (const uint16    pair_size, const uint16 chromosome_count);			    	// TODO :: ·£´ý ¿°»öÃ¼ ¹× »ý¸íÃ¼ »ý¼º
		   lifeform				   (lifeform&		paternal,  lifeform&    maternal);							// TODO :: ¿°»öÃ¼ À¯ÀüÀ» ÅëÇÑ »ý¸íÃ¼ »ý¼º
																								    
	inline uint16		get_chromosome_count   ();															    // TODO :: ¿°±â½ÖÀÇ °¹¼ö
	std::vector<helix>  create_haploid();       															    // TODO :: ·£´ý ¿°»öÃ¼ »ý¼º
    std::vector<helix>  get_genetic_code();
	void   kill_lifeform();

private:
	void   create_pair(helix& target_chromosome);

	std::vector<helix>  chromosomes;	
};

