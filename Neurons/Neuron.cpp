#include "Neuron.h"

using namespace std;

Neuron::Neuron(int in_degree, double learning_rate, ActivationFunction& activation_function):
	in_degree_(in_degree), learning_rate_(learning_rate), activation_function_(activation_function)
{
	assert(0.0 - eps_ < learning_rate and learning_rate < 1.0 + eps_);
	assert(in_degree > 0);

	weights_ = vector<double>(in_degree);
	for(int i = 0; i < in_degree_; ++i)
	{
		weights_[i] = 0.01 * ((double)(rand())) / ((double)(RAND_MAX));
		//weights_[i] = -1.0 + 2.0 * ((double)(rand())) / ((double)(RAND_MAX));
	}
	bias_ = ((double)(rand())) / ((double)(RAND_MAX));
}

double Neuron::evaluate(const vector<double>& inputs) const
{
	assert((int)inputs.size() == in_degree_);

	double c = combine(inputs);
	//cout<<"@@ "<<c<<" "<<activation_function_.getActivation(c)<<"\n";
	//cout<<"@@ "; printWeights();

	return activation_function_.getActivation(combine(inputs));
}

double Neuron::combine(const vector<double>& inputs) const
{
	assert((int)inputs.size() == in_degree_);

	double combination = bias_;
	for(int i = 0; i < in_degree_; ++i)
	{
		combination += (inputs[i] * weights_[i]);
	}
	return combination;
}

void Neuron::backPropagate(double loss_derivative_wrt_output, const vector<double>& inputs)
{
	assert((int)inputs.size() == in_degree_);

	double loss_derivative_wrt_combination = loss_derivative_wrt_output * activation_function_.getDerivative(combine(inputs));
	for(int i = 0; i < in_degree_; ++i)
	{
		double loss_derivative_wrt_weight = loss_derivative_wrt_combination * inputs[i];
		//loss_derivative_wrt_weight = min(loss_derivative_wrt_weight, 200.0);
		//loss_derivative_wrt_weight = max(loss_derivative_wrt_weight, -200.0);
		weights_[i] -= learning_rate_ * loss_derivative_wrt_weight;
	}
	double loss_derivative_wrt_bias = loss_derivative_wrt_combination;
	//loss_derivative_wrt_bias = min(loss_derivative_wrt_bias, 200.0);
	//loss_derivative_wrt_bias = max(loss_derivative_wrt_bias, -200.0);
	bias_ -= learning_rate_ * loss_derivative_wrt_bias;
	return;
}

vector<double> Neuron::getLossDerivativeWrtInputs(double loss_derivative_wrt_output, const vector<double>& inputs) const
{
	assert((int)inputs.size() == in_degree_);

	double loss_derivative_wrt_combination = loss_derivative_wrt_output * activation_function_.getDerivative(combine(inputs));
	vector<double> loss_derivative_wrt_inputs(in_degree_);
	for(int i = 0; i < in_degree_; ++i)
	{
		double loss_derivative_wrt_input = loss_derivative_wrt_combination * weights_[i];
		loss_derivative_wrt_inputs[i] = loss_derivative_wrt_input;
	}

	return loss_derivative_wrt_inputs;
}

void Neuron::printWeights() const
{
	cout<<"bias: "<<bias_<<", weights:";
	for(int i = 0; i < in_degree_; ++i)
	{
		cout<<" "<<weights_[i];
	}
	cout<<"\n";
	return;
}