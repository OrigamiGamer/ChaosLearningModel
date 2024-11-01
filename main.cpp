#include "NeuralNetwork.h"

#include <iostream>
#include <vector>
#include <string>
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
std::vector<T> operator*(std::vector<T> const& v_a, T const& b) {
	std::vector<T> v_result;
	for (size_t i = 0;i < v_a.size();i++) {
		v_result.push_back(v_a.at(i) * b);
	}
	return v_result;
};

template <typename T>
std::vector<T> operator*(std::vector<std::vector<T>> const& matrix_W, std::vector<T> const& v_a) {
	std::vector<T> v_result;
	for (size_t m = 0;m < matrix_W.size();m++) {
		if(m<v_a.size())
		v_result += matrix_W.at(m) * v_a.at(m);
	}
	return v_result;
};

template <typename T>
void resize_vector(std::vector<std::vector<T>>& vv_a, std::vector<size_t> assign_map) {
	vv_a.resize(assign_map.size());
	for (size_t i = 0;i < assign_map.size();i++) {
		vv_a.at(i).resize(assign_map.at(i));
	}
};

int main(int, char**) {
	// using namespace ChaosLearningModel;
	std::vector<VV_NODE> v_matrix_W;
	std::vector<V_NODE> v_v_a;

	v_v_a.resize(3);
	v_v_a[0].resize(2);
	v_v_a[1].resize(5);
	v_v_a[2].resize(1);
	for (auto& v_a : v_v_a) {
		for (auto& a : v_a) {
			a = 0.0;
		}
	}
	v_matrix_W.resize(2);
	resize_vector(v_matrix_W[0], { 5,5 });// layer 1 with 2 neurons of 5 connections
	resize_vector(v_matrix_W[1], { 1,1,1,1,1 });//	layer 2 with 5 neurons of 1 connection
	for (auto& matrix_W : v_matrix_W) {
		for (auto& v_w : matrix_W) {
			for (auto& w : v_w) {
				w = 1.0;
			}
		}
	}

	// forward
	v_v_a[0] = { 1,1 };
	v_v_a[1] = v_matrix_W[0] * v_v_a[0];
	v_v_a[2] = v_matrix_W[1] * v_v_a[1];
	std::cout << "final signals: " << std::endl;
	for (auto& a : v_v_a[2]) {
		std::cout << std::to_string(a) << " ";
	}
	std::cout << std::endl;

	// print weights
	for (auto& matrix_W : v_matrix_W) {
		for (auto& v_w : matrix_W) {
			for (auto& w : v_w) {
				std::cout << std::to_string(w) << " ";
			}
			std::cout << std::endl;
		}
	}

}
