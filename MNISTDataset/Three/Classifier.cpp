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

int random_func(int j) 
{ 
    return rand() % j; 
}

int main(int argc, char** argv)
{
	string invocation_string = argv[0];

	if (argc != 6)
	{
		cout<<"Unexpected set of parameters.";
		cout<<"Format: "<<invocation_string<<" <num_training_epochs> <model_load_file_name> <model_storage_file_name> <test_output_file_name> <integrated_gradient_file_name>\n";
		cout<<"Use 'x' for <model_load_file_name> if you want to train model from initialization.\n";
		cout<<"Use 'x' for <model_storage_file_name> if you do not want to store model.\n";
		cout<<"Use 0 for <num_training_epochs> if you want to test already loaded model.\n";
		cout<<"Use 'x' for <integrated_gradient_file_name> if you do not want any integrated gradient analysis.\n";
		cout<<"Example: "<<invocation_string<<" 0 ModelStorage/OneEpochStorageV0.txt x TestDataResults/OneEpochTestResultsV0.txt x\n";
		cout<<"Example: "<<invocation_string<<" 1 ModelStorage/OneEpochStorageV0.txt ModelStorage/TwoEpochStorageV0.txt TestDataResults/TwoEpochTestResultsV0.txt x\n";
		cout<<"Example: "<<invocation_string<<" 5 x ModelStorage/FiveEpochStorageV0.txt TestDataResults/FiveEpochTestResultsV0.txt x\n";
		cout<<"Example: "<<invocation_string<<" 0 ModelStorage/FiveEpochStorageV0.txt x TestDataResults/FiveEpochTestResultsV0.txt IntegratedGradients/FiveEpochIntegratedGradientsV0.txt\n";
		return 0;
	}

	int num_epochs = atoi(argv[1]);
	string model_load_file_name = argv[2];
	string model_storage_file_name = argv[3];
	string test_output_file_name = argv[4];
	string integrated_gradient_file_name = argv[5];
	cout<<"--------\n";
	cout<<"Number of Epochs: "<<num_epochs<<"\nLoad model from file: "<<model_load_file_name<<"\nStore model in file: "<<model_storage_file_name<<"\nOutput test labels in file: "<<test_output_file_name<<"\nIntegrated gradients file name: "<<integrated_gradient_file_name<<"\n";
	cout<<"--------\n";

	srand(time(NULL)); rand();

	NeuralNetwork neural_network;
	if (model_load_file_name == "x")
	{
		cout<<"--------\n";
		cout<<"### Model initialized\n";
		cout<<"--------\n";
		double l = 0.0, r = 0.0001;
		Layer layers_array[2] = {
			Layer(784, 200, 0.001, make_shared<LeakyReluActivationFunction>(), make_shared<UniformlyRandomNeuronWeightInitializer>(l, r)),
			Layer(200, 1, 0.001, make_shared<SigmoidActivationFunction>(), make_shared<UniformlyRandomNeuronWeightInitializer>(l, r))
		};
		vector<Layer> layers(layers_array, layers_array + 2);

		neural_network = NeuralNetwork(784, layers, make_shared<SquaredErrorLossFunction>());
	}
	else
	{
		cout<<"--------\n";
		cout<<"### Model loaded from "<<model_load_file_name<<"\n";
		cout<<"--------\n";
		ifstream fin_load_model;
		fin_load_model.open(model_load_file_name);
		fin_load_model>>neural_network;
		fin_load_model.close();
	}

	Dataset training_dataset("training.data");
	cout<<"--------\n";
	cout<<"### Dataset loaded\n";
	cout<<"--------\n";
	vector<double> training_losses = neural_network.train(training_dataset, num_epochs);
	cout<<"--------\n";
	for(int i = 0; i < num_epochs; ++i)
	{
		cout<<"Average Loss for Epoch #"<<i<<": "<<training_losses[i]<<"\n";
	}
	cout<<"--------\n";
	Dataset test_dataset("test.data");
	cout<<"Test Loss: "<<neural_network.test(test_dataset)<<"\n";
	cout<<"--------\n";

	vector<double> thresholds(0);
	int num_thresholds = 0;
	for(double threshold = threshold_increment; threshold < 1.0 - eps_; threshold += threshold_increment)
	{
		thresholds.push_back(threshold);
		++num_thresholds;
	}
	vector<int> true_positives(num_thresholds, 0), true_negatives(num_thresholds, 0), false_positives(num_thresholds, 0), false_negatives(num_thresholds, 0);
	vector<int> positive_label_indices(0), negative_label_indices(0);

	ofstream fout_test_output;
	fout_test_output.open(test_output_file_name);
	for(int i = 0; i < test_dataset.getNumSamples(); ++i)
	{
		double label = test_dataset.getLabel(i);
		vector<double> feature_vector = test_dataset.getFeatureVector(i);
		double eval = neural_network.evaluate(feature_vector);

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

		if (label > 0.5)
		{
			positive_label_indices.push_back(i);
		}
		else
		{
			negative_label_indices.push_back(i);
		}
	}

	if (integrated_gradient_file_name != "x")
	{
		cout<<"--------\n";
		cout<<"### Start of integrated gradient analysis\n";
		cout<<"--------\n";
		int integrated_gradients_analysis_count = 5;
		random_shuffle(positive_label_indices.begin(), positive_label_indices.end(), random_func);
		random_shuffle(negative_label_indices.begin(), negative_label_indices.end(), random_func);
		ofstream fout_integrated_gradients;
		fout_integrated_gradients.open(integrated_gradient_file_name);
		for (int i = 0; i < 2 * integrated_gradients_analysis_count; ++i)
		{
			int index = ((i & 1) == 0) ? positive_label_indices[i/2] : negative_label_indices[i/2];
			double label = test_dataset.getLabel(index);
			vector<double> feature_vector = test_dataset.getFeatureVector(index);

			double eval = neural_network.evaluate(feature_vector);
			fout_integrated_gradients<<"--------\n";
			fout_integrated_gradients<<"Eval for Test Image: "<<eval<<"\n";
			fout_integrated_gradients<<"Label for Test Image: "<<label<<"\n";
			fout_integrated_gradients<<"Test Image:\n";
			fout_integrated_gradients<<"--------\n";

			for(int x = 0; x < 28; ++x)
			{
				for(int y = 0; y < 28; ++y)
				{
					fout_integrated_gradients<<setfill(' ')<<setw(3)<<(int)(feature_vector[28 * x + y] + 0.1)<<" ";
				}
				fout_integrated_gradients<<"\n";
			}
			fout_integrated_gradients<<"--------\n";

			eval = neural_network.evaluate(vector<double>(784, 0.0));
			fout_integrated_gradients<<"Eval for all zeroes: "<<eval<<"\n";
			vector<double> integrated_gradients = neural_network.getIntegratedGradients(feature_vector, vector<double>(784, 0.0));
			fout_integrated_gradients<<"Integrated gradients wrt all zeroes:\n";
			fout_integrated_gradients<<"--------\n";
			for(int x = 0; x < 28; ++x)
			{
				for(int y = 0; y < 28; ++y)
				{
					int op = ((int)(integrated_gradients[28 * x + y] * 999.0));
					fout_integrated_gradients<<setfill(' ')<<setw(3)<<op<<" ";
				}
				fout_integrated_gradients<<"\n";
			}
			fout_integrated_gradients<<"--------\n\n\n\n";
		}
		fout_integrated_gradients.close();
		cout<<"### End of integrated gradient analysis\n";
		cout<<"--------\n";
	}

	cout<<"\n----------\n";
	fout_test_output<<"--------\nAggregate Results:\n--------\n";
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
		cout<<"    accuracy: "<<fixed<<setw(7)<<setprecision(5)<<accuracy<<"\n";

		fout_test_output<<"threshold: "<<fixed<<setw(4)<<setprecision(2)<<thresholds[i];
		fout_test_output<<"    precision: "<<fixed<<setw(7)<<setprecision(5)<<precision;
		fout_test_output<<"    recall: "<<fixed<<setw(7)<<setprecision(5)<<recall;
		fout_test_output<<"    f1: "<<fixed<<setw(7)<<setprecision(5)<<f1;
		fout_test_output<<"    accuracy: "<<fixed<<setw(7)<<setprecision(5)<<accuracy<<"\n";
	}
	fout_test_output<<"--------\n";
	fout_test_output.close();

	if (model_storage_file_name != "x")
	{
		ofstream fout_store_model;
		fout_store_model.open(model_storage_file_name);
		fout_store_model<<neural_network<<"\n";
		fout_store_model.close();

		cout<<"--------\n";
		cout<<"### Model stored in "<<model_storage_file_name<<"\n";
		cout<<"--------\n";
	}
}