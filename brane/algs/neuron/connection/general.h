//
// Created by max on 3/27/18.
//

#pragma once

#include <algorithm>
#include "../../../structures/neuron.h"

namespace algs
{
namespace neuron
{
namespace connection
{

using structures::neuron;
using std::pair;

/**
 * Connects lhs and rhs so that lhs outputs to rhs.
 * Initializes weight to 0.
 * @param lhs neuron sending signals to rhs
 * @param rhs neuron receiving signals from lhs
 */
template<structures::ActivationFunctor AFunc>
static void connect_neurons(
		neuron<AFunc> &lhs,
		neuron<AFunc> &rhs)
{
	lhs.add_output_connected(rhs);
	rhs.add_input_connected(pair<float, neuron<AFunc>>(0, lhs));
}

template<structures::ActivationFunctor AFunc>
static void fully_connect(
		std::vector<neuron<AFunc>> &lhss,
		std::vector<neuron<AFunc>> &rhss)
{
	std::for_each(lhss.begin(), lhss.end(), [&rhss](auto lhs) {
		std::for_each(rhss.begin(), rhss.end(), [&lhs](auto rhs) {
			connect_neurons(lhs, rhs);
		});
	});
}


}
}
}
