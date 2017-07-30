#pragma once

#include <cstdio>
#include <memory>
#include <string>
#include <random>
#include <vector>
#include "int.h"

#pragma warning(disable: 4996) 

// ---------------------------------------------------------------------

inline uint32 get_random(const uint16 min, const uint16 max)
{
	using namespace std;

	static random_device		 rn;
	static uint32				 seed = rn();
	static mt19937_64			 rnd(seed);

	uniform_int_distribution<uint16>         range(min, max);

	return range(rnd);
}

inline void probability_call(const uint32 factor, void(*callback)())
{
	!get_random(0, factor - 1) ? callback() : 0;
}

// ---------------------------------------------------------------------

using	  base_unit = char;
using	  strand    = std::string;

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
	       lifeform		(const uint16    pair_size, const uint16 chromosome_count);			    	
	       lifeform		(lifeform&		paternal,  lifeform&    maternal);				
																								    
	inline uint32	    get_chromosome_count   ();
	std::vector<helix>  create_haploid();
    std::vector<helix>  get_genetic_code();
	void                kill_lifeform();

private:
	void                create_pair(helix& target_chromosome);

	std::vector<helix>  chromosomes;	
};

