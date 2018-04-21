cmake_minimum_required(VERSION 3.9)
project(brane)

set(CMAKE_CXX_STANDARD 17)

add_executable(brane main.cpp brane/structures/neuron.h brane/structures/perceptron.h brane/structures/factories/neuron_factory.h brane/algs/neuron/activation/square.h brane/algs/neuron/connection/general.h brane/structures/neuron.cpp brane/structures/factories/neuron_factory.cpp brane/algs/neuron/activation/sigmoid.h brane/algs/neuron/activation/tanh.h)