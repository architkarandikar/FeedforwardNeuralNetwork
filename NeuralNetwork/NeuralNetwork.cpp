#include "NeuralNetwork.h"

using namespace std;

NeuralNetwork::NeuralNetwork() {}

NeuralNetwork::NeuralNetwork(int in_degree, vector<Layer> layers, shared_ptr<LossFunction> loss_function_ptr):
	in_degree_(in_degree), layers_(layers), loss_function_ptr_(loss_function_ptr)
{
	assert(in_degree > 0);

	num_layers_ = (int)layers.size();
	assert(num_layers_ > 0);

	assert(layers[0].getInDegree() == in_degree);
	for(int i = 0; i < num_layers_ - 1; ++i)
	{
		assert(layers[i].getOutDegree() == layers[i + 1].getInDegree());
	}
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
	
	double loss_derivative_wrt_output = loss_function_ptr_->getDerivative(output, expected_output);
	vector<double> loss_derivative_wrt_outputs = vector<double>(1, loss_derivative_wrt_output);
	for(int i = num_layers_ - 1; i >= 0; --i)
	{
		vector<double> loss_derivative_wrt_inputs =
			layers_[i].getLossDerivativeWrtInputs(loss_derivative_wrt_outputs, all_inputs[i]);
		layers_[i].backPropagate(loss_derivative_wrt_outputs, all_inputs[i]);
		loss_derivative_wrt_outputs = loss_derivative_wrt_inputs;
	}
}

vector<double> NeuralNetwork::getPredictionDerivativeWrtInputs(const vector<double>& inputs)
{
	assert((int)inputs.size() == in_degree_);

	vector<vector<double> > all_inputs = vector<vector<double> >(1, inputs);
	for(int i = 0; i < num_layers_; ++i)
	{
		vector<double> current = all_inputs.back();
		all_inputs.push_back(layers_[i].evaluate(current));
	}
	assert((int)all_inputs.back().size() == 1);
	
	vector<double> prediction_derivative_wrt_outputs = vector<double>(1, 1.0);
	vector<double> prediction_derivative_wrt_inputs;
	for(int i = num_layers_ - 1; i >= 0; --i)
	{
		prediction_derivative_wrt_inputs = layers_[i].getLossDerivativeWrtInputs(prediction_derivative_wrt_outputs, all_inputs[i]);
		prediction_derivative_wrt_outputs = prediction_derivative_wrt_inputs;
	}
	assert((int)prediction_derivative_wrt_inputs.size() == in_degree_);
	return prediction_derivative_wrt_inputs;
}

vector<double> NeuralNetwork::getIntegratedGradients(const vector<double>& inputs, const vector<double>& baseline)
{
	assert((int)inputs.size() == in_degree_);
	assert((int)baseline.size() == in_degree_);

	int steps = 1000;
	double delta = 1.0/((double)(steps));

	vector<double> current = baseline;
	vector<double> integrated_gradients = vector<double>(in_degree_, 0.0);
	for(int z = 0; z < steps; ++z)
	{
		vector<double> loss_derivative_wrt_inputs = getPredictionDerivativeWrtInputs(current);
		for(int i = 0; i < in_degree_; ++i)
			integrated_gradients[i] += delta * loss_derivative_wrt_inputs[i];

		for(int i = 0; i < in_degree_; ++i)
			current[i] += (inputs[i] - baseline[i]) * delta;
	}
	for(int i = 0; i < in_degree_; ++i)
	{
		integrated_gradients[i] *= (inputs[i] - baseline[i]);
	}
	return integrated_gradients;
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

void trainingStatusUpdate(int i)
{
	int frequency = 1000;
	if (i % frequency == frequency - 1)
	{
		cout<<"Here, finished model training for the first "<<i + 1<<" training samples\n";
	}
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
		double loss = loss_function_ptr_->getLoss(eval, label);
		total_loss += loss;

		backPropagate(label, feature_vector);

		trainingStatusUpdate(i);
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
		total_loss += loss_function_ptr_->getLoss(eval, label);
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

ostream& operator <<(ostream &out, const NeuralNetwork &neural_network)
{
	out<<neural_network.in_degree_<<" "<<neural_network.loss_function_ptr_<<" "<<neural_network.num_layers_;
	for(int i = 0; i < neural_network.num_layers_; ++i)
	{
		out<<"\n"<<neural_network.layers_[i];
	}
	return out;
}

istream& operator >>(istream &in, NeuralNetwork &neural_network)
{
	in>>neural_network.in_degree_>>neural_network.loss_function_ptr_>>neural_network.num_layers_;
	neural_network.layers_.resize(neural_network.num_layers_);
	for(int i = 0; i < neural_network.num_layers_; ++i)
	{
		in>>neural_network.layers_[i];
	}
	return in;
}