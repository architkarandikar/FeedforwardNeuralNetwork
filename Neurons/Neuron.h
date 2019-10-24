#include "../ActivationFunctions/ActivationFunction.h"
#include <vector>
#include <cassert>
#include <ctime>

using namespace std;

const double eps_ = 1.0e-10; // TODO: move to some kind of constants file

class Neuron
{
public:
	Neuron(int in_degree, double learning_rate, ActivationFunction& activation_function);

	double evaluate(const vector<double>& inputs) const;
	void backPropagate(double loss_derivative_wrt_output, const vector<double>& inputs);
	vector<double> getLossDerivativeWrtInputs(double loss_derivative_wrt_output, const vector<double>& inputs) const;

	void printWeights() const;

private:

	int in_degree_;
	double learning_rate_;
	vector<double> weights_;
	double bias_;
	ActivationFunction &activation_function_;

	double combine(const vector<double>& inputs) const;
};