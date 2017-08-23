#pragma once

#include <string>
#include <random>
#include <vector>
#include <memory>
#include "types.h"

#pragma warning(disable: 4996) 

// ---------------------------------------------------------------------

inline uint64 get_random(const uint64 min, const uint64 max)
{
    using namespace std;

    static random_device             rn;
    static uint64                     seed = rn();
    static mt19937_64                 rnd(seed);

    uniform_int_distribution<uint64> range(min, max);

    return range(rnd);
}

inline std::string get_address_str(void* pointer)
{
    char buffer[32];
    sprintf(buffer, "0x%p", pointer);

    return std::string(buffer);
}

// ---------------------------------------------------------------------

using      base_unit = char;
using      strand    = std::string;

constexpr char base[]
{
    'A', 'T', 'G', 'C'
};

struct           helix
{
    strand left;
    strand right;
};

class            lifeform
{
public:
                         lifeform                   (const uint64              pair_size, const uint64       chromosome_count);
                         lifeform                   (const std::vector<helix>& initial_set);
                         lifeform                   (const lifeform&              paternal , const lifeform&    maternal);
                                                                
    inline uint64        get_chromosome_count()     const;
    std::vector<helix>   create_haploid()           const;           
    std::vector<helix>   get_gene_list()            const;

    bool                 modify_gene(const uint64 start_index, const uint64 chromosome_index, const strand& replacement);
    
private:
    void                create_pair(helix& target_chromosome) const;

    std::vector<helix>  chromosomes;    
};
