#pragma once

#include <string>
#include <random>
#include <vector>
#include <memory>
#include "int.h"

#pragma warning(disable: 4996) 

// ---------------------------------------------------------------------

inline uint32 get_random(const uint32 min, const uint32 max)
{
	using namespace std;

	static random_device			 rn;
	static uint32					 seed = rn();
	static mt19937_64			     rnd(seed);

	uniform_int_distribution<uint32> range(min, max);

	return range(rnd);
}

inline std::string get_address_str(void* pointer)
{
	char buffer[32];
	sprintf(buffer, "0x%p", pointer);

	return std::string(buffer);
}

// ---------------------------------------------------------------------

using	  base_unit = char;
using	  strand	= std::string;

constexpr uint32 strand_duplication_failure_factor		{ 100 };
constexpr uint32 strand_duplication_base_error_factor	{ 1000 };

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
						lifeform				   (const uint32    pair_size,  const uint32 chromosome_count);
						lifeform				   (lifeform&		paternal ,  lifeform&    maternal);
																								    
	inline uint32		get_chromosome_count   ();
	std::vector<helix>  create_haploid();       	
    std::vector<helix>  get_genetic_code() const;

private:
	void   create_pair(helix& target_chromosome);

	std::vector<helix>  chromosomes;	
};
