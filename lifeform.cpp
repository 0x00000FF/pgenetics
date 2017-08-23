#include "lifeform.h"


lifeform::lifeform(const uint64 pair_size, const uint64 chromosome_count = 2)
{
    for (uint64 i = 0; i < chromosome_count; ++i)
    {
        helix new_helix;
        this->chromosomes.push_back(std::move(new_helix));
    }

    for (helix& chromosome : chromosomes)
    {
        for (uint64 i = 0; i < pair_size; ++i)
        {
            base_unit new_base = base[get_random(0, 3)];
            chromosome.left.push_back(std::move(new_base));
        }

        create_pair(chromosome);
    }
}

lifeform::lifeform(const std::vector<helix>& initial_set)
{
    if (initial_set.size() % 2 != 0) return;

    this->chromosomes = std::move(initial_set);
}

lifeform::lifeform(const lifeform& paternal, const lifeform& maternal)
{
    if (paternal.get_chromosome_count() != maternal.get_chromosome_count())
    {
        return;
    }

    std::vector<helix> paternal_heritance = paternal.create_haploid();
    std::vector<helix> maternal_heritance = maternal.create_haploid();

    for (uint64 i = 0; i < paternal_heritance.size() && i < maternal_heritance.size(); ++i)
    {
        chromosomes.push_back(helix(paternal_heritance[i]));
        chromosomes.push_back(helix(maternal_heritance[i]));
    }

    if (this->get_chromosome_count() != paternal.get_chromosome_count() ||
        this->get_chromosome_count() != maternal.get_chromosome_count())
    {
        return;
    }
}

inline uint64       lifeform::get_chromosome_count() const
{
    return (uint64)chromosomes.size();
}

std::vector<helix>  lifeform::create_haploid() const
{
    uint64 chromosome_count = this->chromosomes.size();
    
    if (chromosome_count % 2 != 0)
    {
        return std::vector<helix>();
    }

    std::vector<helix> meiosis_byproduct;
    helix              temp_helix;
    
    for (uint64 i = 0; i < chromosome_count - 1; i += 2)
    {
        temp_helix.left.clear();

        for (uint64 base_it = 0; base_it < chromosomes[i].left.size(); ++base_it)
        {
            temp_helix.left.push_back(chromosomes[i + get_random(0, 1)].left[base_it]);
        }

        create_pair(temp_helix);
        meiosis_byproduct.push_back(temp_helix);
    }

    return meiosis_byproduct;
}

std::vector<helix>  lifeform::get_gene_list() const
{
    return chromosomes;
}

void                lifeform::create_pair(helix& target_chromosome) const
{
    strand& target_strand = target_chromosome.right;
    target_strand.clear();

    for (base_unit unit : target_chromosome.left)
        switch (unit)
        {
        case 'A':
            target_strand.push_back('T');
            break;

        case 'T':
            target_strand.push_back('A');
            break;

        case 'G':
            target_strand.push_back('C');
            break;

        case 'C':
            target_strand.push_back('G');
            break;
        }
}

bool                lifeform::modify_gene(const uint64 start_index, const uint64 chromosome_index, const strand& replacement)
{
    uint64 end_index = replacement.size() + start_index;
    if (chromosome_index >= this->chromosomes.size() || 
        end_index >= this->chromosomes[chromosome_index].left.size())
    {
        return false;
    }

    for (uint64 rep_it = 0, it = start_index; it < end_index; ++it)
    {
        this->chromosomes[chromosome_index].left[it] = std::move(replacement[rep_it++]);
    }

    create_pair(this->chromosomes[chromosome_index]);
    return true;
}