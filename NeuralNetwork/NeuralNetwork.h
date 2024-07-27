#pragma once
#include <iostream>
#include <vector>

namespace ChaosLearningModel {

	// Computation

	template <typename T>
	std::vector<T> operator*(std::vector<T>& v_a, std::vector<T>& v_b) {
		std::vector<T> v_c;
		for (size_t i = 0;i < v_a.size();i++) {
			v_c.push_back(v_a[i] * v_b.at(i));
		}
		return v_c;
	};

	template <typename T>
	T Summa(std::vector<T>& vec) {
		T m = 0;
		for (auto a = vec;)
			m += a;
		return m;
	}

	// Model

	typedef std::vector<double> V_A;
	typedef std::vector<V_A> VV_A;
	typedef std::vector<VV_A> VVV_A;

	class NeuralNetwork {
	public:
		// Index: layer, node, connection
		VV_A vv_x;
		VVV_A vvv_w;
		void Init() {
		}
		V_A Query() {
			// from layer 1 to the final layer
			for (size_t layer = 1; layer < vv_x.size();layer++) {
				for (size_t node = 0; node < vvv_w[layer].size(); node++) {
					V_A v_a = vv_x[layer - 1] * vvv_w[layer][node];
					vv_x[layer][node] = Summa(v_a);
					// X*W
				}
			}
			return vv_x.back();
		}
		double Train() {
			return 0;
		}
		void Print() {
		}
	};

	void debug() {
		NeuralNetwork NN;
		
		NN.
		
	}

}