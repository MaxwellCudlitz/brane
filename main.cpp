#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

#include "brane/structures/perceptron.h"
#include "brane/structures/factories/neuron_factory.h"
#include "brane/algs/neuron/connection/general.h"

using namespace structures;
using namespace structures::factories;
using namespace algs::neuron::connection;

void run()
{
	auto rand_01 = []() {
		float randVal = rand() / 10000.0f;
		return (randVal - static_cast<uint>(randVal));
	};

	auto rand_bias = [&rand_01](std::vector<neuron<std::tanh>> neurons) {
		std::for_each(
				neurons.begin(), neurons.end(),
				[&rand_01](neuron<std::tanh> &n) {
					n.m_bias = rand_01();
				});
	};

	size_t layerSize = 128;

	auto neuronFac = neuron_factory();

	// layers
	auto layer1 = neuronFac.get_neurons<std::tanh>(layerSize);
	auto layer2 = neuronFac.get_neurons<std::tanh>(layerSize);

	// connect all of 1 to all of 2 (convolution)
	fully_connect(layer1, layer2);

	// set rand biases
	rand_bias(layer1);
	rand_bias(layer2);

	// print connections
	for (auto &&root : layer1)
	{
		std::cout << root.m_id << "  |  ";
		for (auto &&branch : *root.m_output_connected)
		{
			std::cout << std::setw(4) << branch.m_id << ",";
		}
		std::cout << "\n";
	}

}

int main()
{
	run();
	return 0;
}