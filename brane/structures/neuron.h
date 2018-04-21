//
// Created by max on 3/27/18.
//

#pragma once

#include <vector>
#include <memory>
#include <cassert>
#include <numeric>

namespace structures
{

// TODO: cluster TYPES of transformation on the data, make said transformations modular (Translation (bias), output filters(dropout/in-net focus))

// functor that will be fed scalar dot product of inputs and weights
typedef float (*ActivationFunctor)(float);

template<ActivationFunctor ActivationFunc>
class neuron
{

public:

	// UID of this neuron
	size_t m_id = 0;

	// output value of this neuron
	float m_output = 0;

	// bias of this neuron
	float m_bias;

	// neurons this neuron will pass data to
	std::shared_ptr<std::vector<neuron>> m_output_connected = {};

	// neurons this neuron will receive data from + the weight of the connection
	std::shared_ptr<std::vector<std::pair<float, neuron>>> m_input_connected = {};

	/**
	 * Initializes a new neuron with no inputs or outputs, and
	 * bias/ID set to 0.
	 */
	neuron() :
			m_bias(0),
			m_id(0),
			m_output_connected(std::make_shared<std::vector<neuron>>()),
			m_input_connected(std::make_shared<std::vector<std::pair<float, neuron>>>())
	{
	}

	inline void init(size_t id)
	{
		m_id = id;
	}

	inline void init(size_t id, float bias)
	{
		m_bias = bias;
		init(id);
	}

	inline void init(
			size_t id,
			float bias,
			const std::vector<std::pair<float, neuron>> &ins,
			const std::vector<neuron> &outs
	)
	{
		m_output_connected = std::make_shared<std::vector<neuron>>(outs);
		m_input_connected = std::make_shared<std::vector<std::pair<float, neuron>>>(ins);

		init(id, bias);
	};


	/**
	 * Adds a neuron this neuron will send signals to.
	 * @param out neuron being connected to
	 */
	inline void add_output_connected(const neuron &out)
	{
		m_output_connected->push_back(out);
	}

	/**
	 * Adds a neuron this neuron will receive signals from.
	 * @param in neuron connecting to this neuron
	 * @param wt weight of this connection
	 */
	inline void add_input_connected(const std::pair<float, neuron> &in)
	{
		m_input_connected->push_back(in);
	}

	void calculate_output()
	{
		// scalar dot product + bias
		m_output = ActivationFunc(
				std::accumulate(
						m_input_connected->begin(),
						m_input_connected->end(),
						m_bias,
						[](float lhs, const std::pair<float, neuron> &pair) {
							return (pair.first) * (pair.second.m_output);
						}
				)
		);
	}


};

}
