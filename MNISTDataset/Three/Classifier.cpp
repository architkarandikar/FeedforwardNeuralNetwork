#include "../../ActivationFunctions/ReluActivationFunction.h"
#include "../../ActivationFunctions/LeakyReluActivationFunction.h"
#include "../../ActivationFunctions/TanhActivationFunction.h"
#include "../../ActivationFunctions/LinearActivationFunction.h"
#include "../../ActivationFunctions/SigmoidActivationFunction.h"
#include "../../LossFunctions/SquaredErrorLossFunction.h"
#include "../../NeuronWeightInitializers/UniformlyRandomNeuronWeightInitializer.h"
#include "../../Datasets/Dataset.h"
#include "../../NeuralNetwork/NeuralNetwork.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

const double threshold_increment = 0.05;

int main(int argc, char** argv)
{
	assert(argc >= 4);

	int num_epochs = atoi(argv[1]);
	string model_storage_file_name = argv[2];
	string test_output_file_name = argv[3];
	cout<<"--------\n";
	cout<<"Number of Epochs: "<<num_epochs<<"\nStore model in file: "<<model_storage_file_name<<"\nOutput test labels in file: "<<test_output_file_name<<"\n";
	cout<<"--------\n";

	srand(time(NULL)); rand();

	ReluActivationFunction relu_activation_function;
	LeakyReluActivationFunction leaky_relu_activation_function;
	TanhActivationFunction tanh_activation_function;
	LinearActivationFunction linear_activation_function;
	SigmoidActivationFunction sigmoid_activation_function;
	SquaredErrorLossFunction squared_error_loss_function;
	UniformlyRandomNeuronWeightInitializer uniformly_random_neuron_weight_initializer(0.0, 0.0001);

	Layer layers_array[2] = {
		Layer(784, 200, 0.001, leaky_relu_activation_function, uniformly_random_neuron_weight_initializer),
		Layer(200, 1, 0.001, sigmoid_activation_function, uniformly_random_neuron_weight_initializer)
	};
	vector<Layer> layers(layers_array, layers_array + 2);

	NeuralNetwork neuralNetwork(784, layers, squared_error_loss_function);

	Dataset training_dataset("training.data");
	cout<<"--------\n";
	cout<<"### Dataset loaded\n";
	cout<<"--------\n";
	vector<double> training_losses = neuralNetwork.train(training_dataset, num_epochs);
	cout<<"--------\n";
	for(int i = 0; i < num_epochs; ++i)
	{
		cout<<"Average Loss for Epoch #"<<i<<": "<<training_losses[i]<<"\n";
	}
	cout<<"--------\n";
	Dataset test_dataset("test.data");
	cout<<"Test Loss: "<<neuralNetwork.test(test_dataset)<<"\n";
	cout<<"--------\n";

	vector<double> thresholds(0);
	int num_thresholds = 0;
	for(double threshold = threshold_increment; threshold < 1.0 - eps_; threshold += threshold_increment)
	{
		thresholds.push_back(threshold);
		++num_thresholds;
	}
	vector<int> true_positives(num_thresholds, 0), true_negatives(num_thresholds, 0), false_positives(num_thresholds, 0), false_negatives(num_thresholds, 0);

	ofstream fout_test_output;
	fout_test_output.open(test_output_file_name);
	for(int i = 0; i < test_dataset.getNumSamples(); ++i)
	{
		double label = test_dataset.getLabel(i);
		vector<double> feature_vector = test_dataset.getFeatureVector(i);
		double eval = neuralNetwork.evaluate(feature_vector);

		fout_test_output<<"Test example #"<<i<<":: \n";
		fout_test_output<<"Prediction: "<<eval<<" Label: "<<label<<"\n";
		fout_test_output<<"--------\n";
		for(int x = 0; x < 28; ++x)
		{
			for(int y = 0; y < 28; ++y)
			{
				fout_test_output<<setfill('0')<<setw(3)<<(int)(feature_vector[28 * x + y] + 0.1);
			}
			fout_test_output<<"\n";
		}
		fout_test_output<<"--------\n";

		for(int j = 0; j < num_thresholds; ++j)
		{
			if(eval >= thresholds[j])
			{
				if(label)
					++true_positives[j];
				else
					++false_positives[j];
			}
			else
			{
				if(label)
					++false_negatives[j];
				else
					++true_negatives[j];
			}
		}
	}
	fout_test_output.close();

	cout<<"\n----------\n";
	for(int i = 0; i < num_thresholds; ++i)
	{
		double precision = 1.0 * true_positives[i] / (true_positives[i] + false_positives[i]);
		double recall = 1.0 * true_positives[i] / (true_positives[i] + false_negatives[i]);
		double accuracy = 1.0 * (true_positives[i] + true_negatives[i]) / test_dataset.getNumSamples();
		double f1 = 2.0 / (1.0 / precision + 1.0 / recall);
		cout<<"threshold: "<<fixed<<setw(4)<<setprecision(2)<<thresholds[i];
		cout<<"    precision: "<<fixed<<setw(7)<<setprecision(5)<<precision;
		cout<<"    recall: "<<fixed<<setw(7)<<setprecision(5)<<recall;
		cout<<"    f1: "<<fixed<<setw(7)<<setprecision(5)<<f1;
		cout<<"    accuracy: "<<fixed<<setw(7)<<setprecision(5)<<f1<<"\n";
	}

	ofstream fout_store_model;
	fout_store_model.open(model_storage_file_name);
	fout_store_model<<neuralNetwork<<"\n";
	fout_store_model.close();
}