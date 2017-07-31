#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include "lifeform.h"

constexpr uint32					delay_rate           { 1000 };
constexpr uint32					pair_size            { 4 };
constexpr uint32					nuclear_phase        { 2 };
constexpr uint32					initial_pool_size    { 3 };
constexpr uint32					final_generation     { 5 };

static	  std::vector<lifeform>		genetic_pool;

void								shuffle(std::vector<lifeform>& list, const uint32 extract_size);
void								print_genetic_sequence(const std::string name, const lifeform& chromosomes);

using namespace std;

#define   POOL_EMPTY()									genetic_pool.size() == 0
#define	  INSUFFICIENT_POOL_SIZE()						prev_generation_genetic_pool.size() <= 1
#define	  INIT_LIFEFORM(uint_or_lf, uint_or_lf_2)		genetic_pool.push_back(lifeform(uint_or_lf, uint_or_lf_2)); \
														print_genetic_sequence(get_address_str(&genetic_pool.back()), genetic_pool.back())
#define	  MATE_CASE_SIZE(number)						number * (number - 1)



int main()
{
	cout << "Genetic Chaining"	         							    << endl
		 << "PGenetics Simulation Library By P.Knowledge, 2016-2017."   << endl;
	cout << "Initial Pool Size = " << initial_pool_size
		 << " Base Pair Size = " << pair_size
		 << " (Nuclear Phase 2n = " << nuclear_phase
		 << ") Last Generation = "  << final_generation                 << endl;
	int current_generation = 0;
	std::vector<lifeform> prev_generation_genetic_pool;
	std::vector<lifeform> curr_generation_genetic_pool;

	while (current_generation++ < final_generation)
	{	
		cout << "[ genetic pool of "
			 << current_generation
			 << (current_generation == 1 ? "st" :
			 	 current_generation == 2 ? "nd" :
			 	 current_generation == 3 ? "rd" :
			 	 "th")
			 << " generation ]" << endl;
		
		if (current_generation == 1 && POOL_EMPTY())
		{
			for (uint32 init_it = 0; init_it < initial_pool_size; ++init_it)
			{
				INIT_LIFEFORM(pair_size, nuclear_phase);
			}
			prev_generation_genetic_pool = genetic_pool;

			continue;
		}

		if (INSUFFICIENT_POOL_SIZE())
		{
			cout << "Species Extinct!" << endl;
			break;
		}
		
		uint32 random_mate_cases = get_random(0, MATE_CASE_SIZE(prev_generation_genetic_pool.size()));


		std::wstring num_str = std::to_wstring(random_mate_cases);
		MessageBoxW(NULL, num_str.c_str(), L"DEBUG_MSG", 0);

		for (uint32 rep_it = 0; rep_it < random_mate_cases; ++rep_it)
		{
			static std::vector<lifeform>	random_pool = prev_generation_genetic_pool;
			shuffle(random_pool, 2);

			INIT_LIFEFORM(*random_pool.rbegin(), *(random_pool.rbegin() + 1));

			curr_generation_genetic_pool.push_back(genetic_pool.back());
		}
		
		prev_generation_genetic_pool.clear();
		prev_generation_genetic_pool = curr_generation_genetic_pool;
		curr_generation_genetic_pool.clear();
	}

	cout << "Genetic Chaining Finished. ";
	cout << "Created Offsprings = " << genetic_pool.size() - initial_pool_size;
	getchar();
	return 0;
}

void shuffle(std::vector<lifeform>& list, uint32 extract_size)
{
	int	random_factor = list.size() - 2;
	
	while (extract_size-- > 0)
	{
		uint32	 random_accessor = get_random(0, random_factor);
		lifeform temp			 = list[random_accessor];
		list[random_accessor]    = list[random_factor + 1];
		list[random_factor + 1]  = temp;
		random_factor--;
	}
}

void print_genetic_sequence(const std::string name, const lifeform& _lifeform)
{
	cout << "==========================================" << endl;

	cout << "genetic sequences of lifeform '" << name << "'" << endl;

	for (helix chro : _lifeform.get_genetic_code())
	{
		cout << "5'-" << chro.left  << "-3'" << endl;
		cout << "3'-" << chro.right << "-5'" << endl << endl;
	}

	cout << "==========================================" << endl;
}