#include "Neuron.h"

using namespace std;

Neuron::Neuron(int in_degree, double learning_rate, ActivationFunction& activation_function, NeuronWeightInitializer& neuron_weight_initializer):
	in_degree_(in_degree), learning_rate_(learning_rate), activation_function_(activation_function), neuron_weight_initializer_(neuron_weight_initializer)
{
	assert(0.0 - eps_ < learning_rate and learning_rate < 1.0 + eps_);
	assert(in_degree > 0);

	weights_ = vector<double>(in_degree);
	for(int i = 0; i < in_degree_; ++i)
	{
		weights_[i] = neuron_weight_initializer_.getWeight();
	}
	bias_ = neuron_weight_initializer_.getBias();
}

double Neuron::evaluate(const vector<double>& inputs) const
{
	assert((int)inputs.size() == in_degree_);

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
		weights_[i] -= learning_rate_ * loss_derivative_wrt_weight;
	}
	double loss_derivative_wrt_bias = loss_derivative_wrt_combination;
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

ostream& operator <<(ostream &out, const Neuron &neuron)
{
	out<<neuron.in_degree_<<" "<<neuron.learning_rate_<<"\n"<<neuron.activation_function_<<"\n"<<neuron.neuron_weight_initializer_<<"\n"<<neuron.bias_<<"\n";
	for(int i = 0; i < neuron.in_degree_; ++i)
	{
		if (i > 0)
		{
			cout<<" ";
		}
		out<<neuron.weights_[i];
	}
	return out;
}