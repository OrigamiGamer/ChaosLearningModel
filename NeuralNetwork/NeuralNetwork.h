#pragma once
#include <iostream>
#include <vector>

namespace ChaosLearningModel {

	namespace Type {
		//typedef std::vector<double> V_NODES;
		typedef std::vector<std::vector<double>> VV_NODES;
		typedef std::vector<std::vector<std::vector<double>>> VVV_WEIGHT;
	}

	class NeuralNetwork {
	public:
		//Type::V_NODES v_a_in;	// input nodes
		//Type::V_NODES v_a_out;	// output nodes

		Type::VV_NODES vv_a;	// all nodes
		Type::VVV_WEIGHT vvv_w;	// all connection weights of nodes, the [0] layer is empty

		void Initialize(std::vector<size_t> v_layer_nodeCount) {
			std::vector<size_t>& v_l_n = v_layer_nodeCount;
			size_t n = v_l_n.size();
			vv_a.clear(); vvv_w.clear();
			vv_a.resize(n);
			vvv_w.resize(n);

			double num = 0;

			for (size_t i = 0; i < n; i++) {
				// index of layer | count of nodes
				vv_a[i].resize(v_l_n[i]);
				vvv_w[i].resize(v_l_n[i]);
				if (i > 0) {
					for (size_t j = 0; j < vvv_w[i].size(); j++) {
						// node[j] of layer[i] | count of nodes on last layer
						vvv_w[i][j].resize(vvv_w[i - 1].size());

						// initialize weights
						for (size_t m = 0; m < vvv_w[i][j].size(); m++) {
							num += 0.01;
							vvv_w[i][j][m] = num;
						}
					}
				}
			}

		}

		void SetNetwork(Type::VV_NODES& init_vv_a, Type::VVV_WEIGHT& init_vvv_w) {
			vv_a = init_vv_a;
			vvv_w = init_vvv_w;
		}

		// !!! Notice: Index is all beginning from [0] !!!
		// layer: Index from hidden layer to output layer.
		// node: Index of the node from the layer.
		double Summa(size_t layer, size_t node) {
			if (!(layer > 0)) return 0;

			double a = 0;
			
			// foreach connections
			for (size_t i = 0; i < vvv_w[layer][node].size(); i++) {
				a += vvv_w[layer][node][i] * vv_a[layer - 1][i];
			}

			return a;
		}
		
		void Print() {
			for (size_t layer = 0; layer < vvv_w.size(); layer++) {
				std::cout << "<" << layer << ">" << std::endl;

				for (size_t node = 0; node < vvv_w[layer].size(); node++) {
					std::cout << "[" << node << "] ";

					for (size_t connection = 0; connection < vvv_w[layer][node].size(); connection++) {
						std::cout << vvv_w[layer][node][connection] << " ";

					}
					std::cout << std::endl;
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}

	};

}