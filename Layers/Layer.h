#include "../Neurons/Neuron.h"
#include <vector>
#include <cassert>

using namespace std;

class Layer
{
public:
	Layer(int in_degree_, int out_degree_, double learning_rate, ActivationFunction& activation_function);

	vector<double> evaluate(const vector<double>& inputs) const;
	void backPropagate(const vector<double>& loss_derivative_wrt_outputs, const vector<double>& inputs);
	vector<double> getLossDerivativeWrtInputs(const vector<double>& loss_derivative_wrt_outputs, const vector<double>& inputs) const;

	int getInDegree() const;
	int getOutDegree() const;

	void printWeights() const;

private:
	int in_degree_;
	int out_degree_;
	vector<Neuron> neurons_;
};