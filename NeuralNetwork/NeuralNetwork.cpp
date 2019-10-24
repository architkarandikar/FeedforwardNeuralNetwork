#include "NeuralNetwork.h"

using namespace std;

NeuralNetwork::NeuralNetwork(int in_degree, vector<Layer> layers, LossFunction& loss_function):
	in_degree_(in_degree), layers_(layers), loss_function_(loss_function)
{
	assert(in_degree > 0);

	num_layers_ = (int)layers.size();
	assert(num_layers_ > 0);

	assert(layers[0].getInDegree() == in_degree);
	assert(layers.back().getOutDegree() == 1);
}

double NeuralNetwork::evaluate(const vector<double>& inputs) const
{
	assert((int)inputs.size() == in_degree_);

	vector<double> current = inputs;
	for(int i = 0; i < num_layers_; ++i)
	{
		current = layers_[i].evaluate(current);
	}

	assert((int)current.size() == 1);
	return current[0];
}

void NeuralNetwork::backPropagate(double expected_output, const vector<double>& inputs)
{
	assert((int)inputs.size() == in_degree_);

	vector<vector<double> > all_inputs = vector<vector<double> >(1, inputs);
	for(int i = 0; i < num_layers_; ++i)
	{
		vector<double> current = all_inputs.back();
		all_inputs.push_back(layers_[i].evaluate(current));
	}

	assert((int)all_inputs.back().size() == 1);
	double output = all_inputs.back()[0];
	double loss_derivative_wrt_output = loss_function_.getDerivative(output, expected_output);
	//cerr<<"loss_derivative_wrt_output: "<<loss_derivative_wrt_output<<" "<<output<<" "<<expected_output<<"\n";

	vector<double> loss_derivative_wrt_outputs = vector<double>(1, loss_derivative_wrt_output);
	for(int i = num_layers_ - 1; i >= 0; --i)
	{
		vector<double> loss_derivative_wrt_inputs =
			layers_[i].getLossDerivativeWrtInputs(loss_derivative_wrt_outputs, all_inputs[i]);
		layers_[i].backPropagate(loss_derivative_wrt_outputs, all_inputs[i]);
		loss_derivative_wrt_outputs = loss_derivative_wrt_inputs;
	}
}

vector<double> NeuralNetwork::train(const Dataset& training_data_set, int num_epochs)
{
	vector<double> losses;
	for(int i = 0; i < num_epochs; ++i)
	{
		cout<<"### Start of Epoch #"<<i<<"\n";
		double loss = trainEpoch(training_data_set);
		losses.push_back(loss);
		cout<<"### End of Epoch #"<<i<<", Loss: "<<loss<<"\n";
		cout<<"--------\n";
	}
	return losses;
}

int randomGen(int i)
{
	return rand() % i;
}

double NeuralNetwork::trainEpoch(const Dataset& training_data_set)
{
	int num_samples = training_data_set.getNumSamples();
	int num_dimensions = training_data_set.getNumDimensions();

	assert(num_dimensions == in_degree_);

	vector<int> permutation(num_samples);
	for(int i = 0; i < num_samples; ++i)
		permutation[i] = i;
	random_shuffle(permutation.begin(), permutation.end(), randomGen);

	double total_loss = 0.0;
	for(int i = 0; i < num_samples; ++i)
	{
		int index = permutation[i];
		vector<double> feature_vector = training_data_set.getFeatureVector(index);
		double label = training_data_set.getLabel(index);

		double eval = evaluate(feature_vector);
		double loss = loss_function_.getLoss(eval, label);
		total_loss += loss;
		//cout<<"-----\n### Sample #"<<i<<" :: "<<eval<<" "<<label<<" :: "<<loss<<"\n-----\n";
		//printWeights();

		backPropagate(label, feature_vector);
	}

	double average_loss = total_loss / ((double)(num_samples));
	return average_loss;
}

double NeuralNetwork::test(const Dataset& test_data_set)
{
	int num_samples = test_data_set.getNumSamples();
	int num_dimensions = test_data_set.getNumDimensions();

	assert(num_dimensions == in_degree_);

	double total_loss = 0.0;
	for(int i = 0; i < num_samples; ++i)
	{
		vector<double> feature_vector = test_data_set.getFeatureVector(i);
		double label = test_data_set.getLabel(i);

		double eval = evaluate(feature_vector);
		total_loss += loss_function_.getLoss(eval, label);
	}

	double average_loss = total_loss / ((double)(num_samples));
	return average_loss;
}

void NeuralNetwork::printWeights() const
{
	for(int i = 0; i < num_layers_; ++i)
	{
		cout<<"Layer #"<<i<<":::\n";
		layers_[i].printWeights();
	}
}