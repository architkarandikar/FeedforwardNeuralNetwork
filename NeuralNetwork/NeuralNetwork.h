#include "../Layers/Layer.h"
#include "../LossFunctions/LossFunction.h"
#include "../LossFunctions/LossFunctionIO.h"
#include "../Datasets/Dataset.h"
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

class NeuralNetwork
{
public:
	NeuralNetwork();
	NeuralNetwork(int in_degree, vector<Layer> layers, shared_ptr<LossFunction> loss_function_ptr);

	double evaluate(const vector<double>& inputs) const;
	void backPropagate(double expected_output, const vector<double>& inputs);

	vector<double> train(const Dataset& training_dataset, int num_epochs);
	double test(const Dataset& test_dataset);

	void printWeights() const;

	friend ostream& operator <<(ostream &out, const NeuralNetwork &neural_network);
	friend istream& operator >>(istream &in, NeuralNetwork &neural_network);

private:
	int in_degree_;
	int num_layers_;
	vector<Layer> layers_;
	shared_ptr<LossFunction> loss_function_ptr_;

	double trainEpoch(const Dataset& training_dataset);
};

ostream& operator <<(ostream &out, const NeuralNetwork &neural_network);
istream& operator >>(istream &in, NeuralNetwork &neural_network);