#include "../ActivationFunctions/ActivationFunction.h"
#include "../ActivationFunctions/ActivationFunctionIO.h"
#include "../NeuronWeightInitializers/NeuronWeightInitializer.h"
#include "../NeuronWeightInitializers/NeuronWeightInitializerIO.h"
#include <vector>
#include <cassert>
#include <ctime>

using namespace std;

const double eps_ = 1.0e-10; // TODO: move to some kind of constants file

class Neuron
{
public:
	Neuron();
	Neuron(int in_degree, double learning_rate, shared_ptr<ActivationFunction> activation_function_ptr, shared_ptr<NeuronWeightInitializer> neuron_weight_initializer_ptr);

	double evaluate(const vector<double>& inputs) const;
	void backPropagate(double loss_derivative_wrt_output, const vector<double>& inputs);
	vector<double> getLossDerivativeWrtInputs(double loss_derivative_wrt_output, const vector<double>& inputs) const;

	void printWeights() const;

	friend ostream& operator <<(ostream &out, const Neuron &neuron);
	friend istream& operator >>(istream &in, Neuron &neuron);

private:
	int in_degree_;
	double learning_rate_;
	vector<double> weights_;
	double bias_;
	shared_ptr<ActivationFunction> activation_function_ptr_;

	double combine(const vector<double>& inputs) const;
};

ostream& operator <<(ostream &out, const Neuron &neuron);
istream& operator >>(istream &in, Neuron &neuron);