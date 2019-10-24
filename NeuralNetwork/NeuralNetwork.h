#include "../Layers/Layer.h"
#include "../LossFunctions/LossFunction.h"
#include "../Datasets/Dataset.h"
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

class NeuralNetwork
{
public:
	NeuralNetwork(int in_degree, vector<Layer> layers, LossFunction& loss_function);

	double evaluate(const vector<double>& inputs) const;
	void backPropagate(double expected_output, const vector<double>& inputs);

	vector<double> train(const Dataset& training_dataset, int num_epochs);
	double test(const Dataset& test_dataset);

	void printWeights() const;

private:
	int in_degree_;
	int num_layers_;
	vector<Layer> layers_;
	LossFunction &loss_function_;

	double trainEpoch(const Dataset& training_dataset);
};