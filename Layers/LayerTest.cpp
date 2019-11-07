#include "../ActivationFunctions/ReluActivationFunction.h"
#include "../NeuronWeightInitializers/UniformlyRandomNeuronWeightInitializer.h"
#include "Layer.h"
#include <fstream>

using namespace std;

int main()
{
	srand(time(NULL));

	double l = 0.0, r = 1.0;
	Layer layer(5, 3, 0.1, make_shared<ReluActivationFunction>(), make_shared<UniformlyRandomNeuronWeightInitializer>(l, r));

	cout<<"--------\n";
	cout<<"In Degree: "<<layer.getInDegree()<<", Out Degree: "<<layer.getOutDegree()<<"\n";
	cout<<"Layer weights:\n"; layer.printWeights();
	cout<<"--------\n";

	vector<double> evaluation = layer.evaluate(vector<double>(5, -1.0));
	cout<<"Evaluate all -1s: ";
	for(int i = 0; i < 3; ++i)
	{
		cout<<evaluation[i]<<" ";
	}
	cout<<"\n";
	evaluation = layer.evaluate(vector<double>(5, 1.0));
	cout<<"Evaluate all 1s: ";
	for(int i = 0; i < 3; ++i)
	{
		cout<<evaluation[i]<<" ";
	}
	cout<<"\n";
	evaluation = layer.evaluate(vector<double>(5, 2.0));
	cout<<"Evaluate all 2s: ";
	for(int i = 0; i < 3; ++i)
	{
		cout<<evaluation[i]<<" ";
	}
	cout<<"\n";
	cout<<"Layer weights:\n"; layer.printWeights();
	cout<<"--------\n";

	cout<<"Loss derivative wrt inputs with all 1s input and Loss WRT Outputs set to all 1s: ";
	vector<double> losses = layer.getLossDerivativeWrtInputs(vector<double>(3, 1.0), vector<double>(5, 1.0));
	for(int i = 0; i < 5; ++i)
	{
		cout<<losses[i]<<" ";
	}
	cout<<"\n";
	cout<<"Backpropagate with all 1s input and Loss WRT Outputs set to all 1s.\n";
	layer.backPropagate(vector<double>(3, 1.0), vector<double>(5, 1.0));
	cout<<"Layer weights:\n"; layer.printWeights();
	cout<<"--------\n";

	cout<<"Layer output:\n";
	cout<<layer<<"\n";
	cout<<"--------\n";

	ofstream fout;
	fout.open("tmp.txt");
	fout<<layer<<"\n";
	fout.close();

	Layer deserialized_layer;
	ifstream fin;
	fin.open("tmp.txt");
	fin>>deserialized_layer;
	cout<<"Deserialized Layer output:\n";
	cout<<deserialized_layer<<"\n";
	cout<<"--------\n";
	fin.close();

	return 0;
}