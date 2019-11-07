#include "../ActivationFunctions/ReluActivationFunction.h"
#include "../ActivationFunctions/LeakyReluActivationFunction.h"
#include "../ActivationFunctions/TanhActivationFunction.h"
#include "../ActivationFunctions/LinearActivationFunction.h"
#include "../ActivationFunctions/SigmoidActivationFunction.h"
#include "../LossFunctions/SquaredErrorLossFunction.h"
#include "../NeuronWeightInitializers/UniformlyRandomNeuronWeightInitializer.h"
#include "../Datasets/Dataset.h"
#include "../NeuralNetwork/NeuralNetwork.h"

using namespace std;

const int num_epochs = 5;

int main()
{
	srand(time(NULL)); rand();

	double l = 0.0, r = 0.01;
	Layer layers_array[2] = {
		Layer(400, 40, 0.1, make_shared<LeakyReluActivationFunction>(), make_shared<UniformlyRandomNeuronWeightInitializer>(l, r)),
		Layer(40, 1, 0.1, make_shared<SigmoidActivationFunction>(), make_shared<UniformlyRandomNeuronWeightInitializer>(l, r))
	};
	vector<Layer> layers(layers_array, layers_array + 2);

	NeuralNetwork neural_network(400, layers, make_shared<SquaredErrorLossFunction>());

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

	for(int i = 0; i < 10; ++i)
	{
		double label = test_dataset.getLabel(i);
		vector<double> feature_vector = test_dataset.getFeatureVector(i);
		double eval = neural_network.evaluate(feature_vector);

		cout<<"Test example #"<<i<<":: \n";
		cout<<"Prediction: "<<eval<<" Label: "<<label<<"\n";
		cout<<"--------\n";
		for(int x = 0; x < 20; ++x)
		{
			for(int y = 0; y < 20; ++y)
				cout<<feature_vector[20*x+y];
			cout<<"\n";
		}
		cout<<"--------\n";
	}
}