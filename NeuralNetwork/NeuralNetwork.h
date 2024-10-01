#pragma once
#include <iostream>
#include <vector>

namespace ChaosLearningModel {

	// Computation

	template <typename T>
	std::vector<T> operator*(std::vector<T>& v_a, std::vector<T>& v_b) {
		std::vector<T> v_c(v_a.size());
		for (size_t i = 0;i < v_a.size();i++)
			v_c.at(i) = v_a[i] * v_b.at(i);
		return v_c;
	};

	template <typename T>
	T Summa(std::vector<T>& vec) {
		T sum = 0;
		for (auto a : vec)
			sum += a;
		return sum;
	}

	// Model
	typedef std::vector<double> V_A;
	typedef std::vector<V_A> VV_A;
	typedef std::vector<VV_A> VVV_A;

	class NeuralNetwork {
	public:
		// [layer][node][connection]
		VV_A vv_a;
		VVV_A vvv_w;

		void Initialize(VV_A initial_vv_a, VVV_A initial_vvv_w) {
			vv_a = initial_vv_a;
			vvv_w = initial_vvv_w;
		}
		void Initialize(size_t layer_count, std::vector<size_t> v_node_count_of_each_layer) {
			vv_a.resize(layer_count);
			vvv_w.resize(layer_count);
			for (size_t layer = 0; layer < layer_count; layer++) {
				vv_a[layer].resize(v_node_count_of_each_layer[layer]);
				vvv_w[layer].resize(v_node_count_of_each_layer[layer]);
				for (size_t node = 0; node < v_node_count_of_each_layer[layer]; node++) {

				}
			}
		}

		V_A Query() {
			for (size_t layer = 0; layer < vv_a.size();layer++) {
				for (size_t node = 0; node < vvv_w[layer].size(); node++) {
					V_A v_a = vv_a[layer] * vvv_w[layer][node];
					vv_a[layer][node] = Summa(v_a);
					// X*W
				}
			}
			return vv_a.back();
		}
	};

	void debug() {
		NeuralNetwork NN;
		NN.Initialize(3, { 2,10,4 });



	}

}