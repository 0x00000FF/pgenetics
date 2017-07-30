#include "lifeform.h"


lifeform::lifeform(const uint32 pair_size, const uint32 chromosome_count = 2)
{
	for (uint32 i = 0; i < chromosome_count; ++i)
	{
		std::unique_ptr<helix> helix_uptr = std::make_unique<helix>();
		this->chromosomes.push_back(*helix_uptr);
	}

	for (helix& chromosome : chromosomes)
	{
		for (uint32 i = 0; i < pair_size; ++i)
		{
			base_unit new_base = base[get_random(0, 3)];
			chromosome.left.push_back(new_base);
		}

		create_pair(chromosome);
	}
}

lifeform::lifeform(lifeform& paternal, lifeform& maternal)
{
	if (paternal.get_chromosome_count() != maternal.get_chromosome_count())
	{
		this->kill_lifeform();
		return;
	}

	std::vector<helix> paternal_heritance = paternal.create_haploid();
	std::vector<helix> maternal_heritance = maternal.create_haploid();

	for (uint32 i = 0; i < paternal_heritance.size() && i < maternal_heritance.size(); ++i)
	{
		std::unique_ptr<helix> helix_uptr = std::make_unique<helix>(paternal_heritance[i]);
		chromosomes.push_back(*helix_uptr);

		helix_uptr = std::make_unique<helix>(maternal_heritance[i]);
		chromosomes.push_back(*helix_uptr);
	}

	if (this->get_chromosome_count() != paternal.get_chromosome_count() ||
		this->get_chromosome_count() != maternal.get_chromosome_count())
	{
		this->kill_lifeform();
		return;
	}
}

inline uint32		lifeform::get_chromosome_count()
{
	return (uint32)chromosomes.size();
}

std::vector<helix>  lifeform::create_haploid()
{
	if (this->chromosomes.size() % 2 != 0)
	{
		return std::vector<helix>();
	}

	std::vector<helix> meiosis_byproduct;
	helix temp_helix;

	for (uint32 i = 0; i < chromosomes.size() - 1; i += 2)
	{
		temp_helix.left.clear();

		for (uint32 base_iter = 0; base_iter < chromosomes[i].left.size(); ++base_iter)
		{
			temp_helix.left.push_back(chromosomes[i + get_random(0, 1)].left[base_iter]);
		}

		create_pair(temp_helix);
		meiosis_byproduct.push_back(temp_helix);
	}

	return meiosis_byproduct;
}

std::vector<helix>  lifeform::get_genetic_code()
{
	return chromosomes;
}

void				lifeform::create_pair(helix& target_chromosome)
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

void				lifeform::kill_lifeform()
{
	if (!chromosomes.empty())
		for (helix& chromosome : chromosomes)
		{
			delete &chromosome;
		}

	delete this;
}
