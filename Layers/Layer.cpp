#include "Layer.h"

using namespace std;

Layer::Layer(int in_degree, int out_degree, double learning_rate, ActivationFunction& activation_function, NeuronWeightInitializer& neuron_weight_initializer):
	in_degree_(in_degree), out_degree_(out_degree)
{
	assert(0.0 - eps_ < learning_rate and learning_rate < 1.0 + eps_);
	assert(in_degree > 0);
	assert(out_degree > 0);

	neurons_.clear();
	for(int i = 0; i < out_degree_; ++i)
	{
		neurons_.push_back(Neuron(in_degree, learning_rate, activation_function, neuron_weight_initializer));
	}
}

vector<double> Layer::evaluate(const vector<double>& inputs) const
{
	assert((int)inputs.size() == in_degree_);

	vector<double> outputs = vector<double>(out_degree_);
	for(int i = 0; i < out_degree_; ++i)
	{
		outputs[i] = neurons_[i].evaluate(inputs);
	}
	return outputs;
}

void Layer::backPropagate(const vector<double>& loss_derivative_wrt_outputs, const vector<double>& inputs)
{
	assert((int)inputs.size() == in_degree_);
	assert((int)loss_derivative_wrt_outputs.size() == out_degree_);

	for(int i = 0; i < out_degree_; ++i)
	{
		neurons_[i].backPropagate(loss_derivative_wrt_outputs[i], inputs);
	}
	return;
}

vector<double> Layer::getLossDerivativeWrtInputs(const vector<double>& loss_derivative_wrt_outputs, const vector<double>& inputs) const
{
	assert((int)inputs.size() == in_degree_);
	assert((int)loss_derivative_wrt_outputs.size() == out_degree_);

	vector<double> loss_derivative_wrt_inputs = vector<double>(in_degree_, 0.0);
	for(int i = 0; i < out_degree_; ++i)
	{
		vector<double> loss_derivative_wrt_inputs_for_current_output =
			neurons_[i].getLossDerivativeWrtInputs(loss_derivative_wrt_outputs[i], inputs);
		for (int j = 0; j < in_degree_; ++j)
		{
			loss_derivative_wrt_inputs[j] += loss_derivative_wrt_inputs_for_current_output[j];
		}
	}
	return loss_derivative_wrt_inputs;
}

void Layer::printWeights() const
{
	for(int i = 0; i < out_degree_; ++i)
	{
		cout<<"Neuron #"<<i<<":: ";
		neurons_[i].printWeights();
	}
}

int Layer::getInDegree() const
{
	return in_degree_;
}

int Layer::getOutDegree() const
{
	return out_degree_;
}