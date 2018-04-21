//
// Created by max on 3/27/18.
//

#pragma once

#include "../neuron.h"

namespace structures
{
namespace factories
{

class neuron_factory
{

public:

	neuron_factory() = default;

	template<structures::ActivationFunctor AFunc>
	std::vector<neuron<AFunc>> get_neurons(size_t num)
	{
		auto outVec = std::vector<neuron<AFunc>>();
		outVec.reserve(num);

		for (int i = 0; i < num; ++i)
		{
			outVec.push_back(get_neuron<AFunc>());
		}

		return outVec;
	};

	template<structures::ActivationFunctor AFunc>
	neuron<AFunc> get_neuron()
	{
		// Ids must never repeat (overflow)
		assert(id_ticker != std::numeric_limits<size_t>::max());

		auto n = neuron<AFunc>();
		n.init(++id_ticker, 0);
		return n;
	}

protected:

	size_t id_ticker;

};


}
}

