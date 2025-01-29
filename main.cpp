// #include "NeuralNetwork.h"

#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

// immature Ideas

class Node {
public:
	std::vector<Node*> forwardNodes;
	std::vector<Node*> backwardNodes;
	double signal = 0;
	double sensitivity = 1.0;

	Node(double initialSensitivity)
	{
		sensitivity = initialSensitivity;
	}
	void connnect(Node& targetNode)
	{
		forwardNodes.push_back(&targetNode);
		targetNode.backwardNodes.push_back(this);
	}
	double getSignal()
	{
		for (auto& backwardNode : backwardNodes) {
			signal += backwardNode->signal * sensitivity;
		}
		// for (auto& forwardNode : forwardNodes) {
		// 	forwardNode->signal += signal * sensitivity;
		// }
		return signal;
	}
};


// functions
void connect(vector<Node>& nodes1, vector<Node>& nodes2)
{
	for (auto& node1 : nodes1) {
		for (auto& node2 : nodes2) {
			node1.connnect(node2);
		}
	}
}

void setSignals(vector<Node>& nodes, vector<double> signals)
{
	for (size_t i = 0;i < nodes.size(); i++) {
		if (i < signals.size()) nodes[i].signal = signals[i];
	}
}

void clearSignals(vector<Node>& nodes)
{
	for (auto& node : nodes) {
		node.signal = 0;
	}
}

void getSignals(vector<Node>& nodes)
{
	for (auto& node : nodes) {
		node.getSignal();
	}
}

void printSignals(vector<Node>& nodes)
{
	std::cout << "print signals:" << std::endl;
	for (auto& node : nodes) {
		std::cout << node.signal << " ";
	}
	std::cout << std::endl << std::endl;
}


int main(int, char**)
{
	vector<Node> nodes1 = { 1,1,1 };
	vector<Node> nodes2 = { 1,1,1 };
	vector<Node> nodes3 = { 1,1,1 };

	connect(nodes1, nodes2);
	connect(nodes2, nodes3);

	clearSignals(nodes1);
	setSignals(nodes1, { 1,1,1 });

	clearSignals(nodes2);
	getSignals(nodes2);

	clearSignals(nodes3);
	getSignals(nodes3);

	printSignals(nodes3);

	return 0;
}




// Model based on mathematics

typedef std::vector<double> V_NODE;
typedef std::vector<V_NODE> VV_NODE;
typedef std::vector<VV_NODE> VVV_NODE;

// addition of two Vectors
template <typename T>
void operator+=(std::vector<T>& vec1, std::vector<T> const& vec2)
{
	for (size_t i = 0; i < vec1.size();i++) {
		vec1.at(i) += vec2.at(i);
	}
};

// add delta Quantity to every node of Vector
template <typename T>
void operator+=(std::vector<T>& vec, T const& num)
{
	for (size_t i = 0; i < vec.size();i++) {
		vec.at(i) += num;
	}
};

// product of Vector and Quantity
template <typename T>
std::vector<T> operator*(std::vector<T> const& vec, T const& num)
{
	std::vector<T> v_result;
	for (size_t i = 0;i < vec.size();i++) {
		v_result.push_back(vec.at(i) * num);
	}
	return v_result;
};

// product of Matrix and Vector
template <typename T>
std::vector<T> operator*(std::vector<std::vector<T>> const& matrix, std::vector<T> const& vec)
{
	std::vector<T> v_result;
	for (size_t m = 0;m < matrix.size();m++) {
		if (m < vec.size())
			v_result += matrix.at(m) * vec.at(m);
	}
	return v_result;
};

template <typename T>
void resize_vector(std::vector<std::vector<T>>& vv_a, std::vector<size_t> assign_map)
{
	vv_a.resize(assign_map.size());
	for (size_t i = 0;i < assign_map.size();i++) {
		vv_a.at(i).resize(assign_map.at(i));
	}
};

int main2(int, char**)
{
	// using namespace ChaosLearningModel;
	std::vector<VV_NODE> v_matrix_W;
	std::vector<V_NODE> v_v_A;

	// resize Matrix_Signal
	v_v_A.resize(3);
	v_v_A[0].resize(2);
	v_v_A[1].resize(5);
	v_v_A[2].resize(1);
	for (auto& v_a : v_v_A) {
		for (auto& a : v_a) {
			a = 0.0;
		}
	}
	// resize Matrix_Weight
	v_matrix_W.resize(2);
	resize_vector(v_matrix_W[0], { 5,5 });// layer 1 with 2 neurons of 5 connections
	resize_vector(v_matrix_W[1], { 1,1,1,1,1 });//	layer 2 with 5 neurons of 1 connection
	int b = 0;
	for (auto& matrix_W : v_matrix_W) {
		b += 0.01;
		for (auto& v_w : matrix_W) {
			for (auto& w : v_w) {
				w = 1.0 + b;
			}
		}
	}

	// forward
	v_v_A[0] = { 1,1 };
	v_v_A[1] = v_matrix_W[0] * v_v_A[0];
	v_v_A[2] = v_matrix_W[1] * v_v_A[1];
	std::cout << "final signals: " << std::endl;
	for (auto& a : v_v_A[2]) {
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

	return 0;
}
