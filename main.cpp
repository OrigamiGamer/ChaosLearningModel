#include "NeuralNetwork.h"

#include <iostream>
#include <chrono>

using namespace std;

typedef std::vector<double> V_NODE;
typedef std::vector<V_NODE> VV_NODE;
typedef std::vector<VV_NODE> VVV_NODE;

template <typename T>
void operator+=(std::vector<T>& v1, std::vector<T> const& v2) {
	for (size_t i = 0; i < v1.size();i++) {
		v1.at(i) += v2.at(i);
	}
};

template <typename T>
void operator+=(std::vector<T>& v1, T const& a) {
	for (size_t i = 0; i < v1.size();i++) {
		v1.at(i) += a;
	}
};

template <typename T>
std::vector<T> operator*(VVV_NODE const& matrix_W, V_NODE const& v_a) {
	V_NODE v_result;
	for (size_t m = 0;m < matrix_W.size();m++) {
		v_result += matrix_W.at(m) * v_a.at(m);
	}
	return v_result;
};


int main(int, char**) {
	// using namespace ChaosLearningModel;


}
