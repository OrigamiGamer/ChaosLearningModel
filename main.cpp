#pragma once
#include "NeuralNetwork/NeuralNetwork.h"

using namespace std;

int main(int, char**){

	ChaosLearningModel::NeuralNetwork NN;
	
	NN.Initialize({ 10,30,10 });

	NN.vv_a[0][0] = 1;
	NN.vv_a[0][1] = 2;

	double a = NN.Summa(1, 0);

	cout << a << endl << endl;

	NN.Print();


}
