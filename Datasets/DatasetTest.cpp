#include "Dataset.h"
#include <iostream>

using namespace std;

int main()
{
	Dataset dataset("../PlusDataset/training.data");

	cout<<"Number of samples: "<<dataset.getNumSamples()<<"\n";
	cout<<"Number of dimensions: "<<dataset.getNumDimensions()<<"\n";

	for(int i = 0; i < 5; ++i)
	{
		cout<<"Label "<<i<<": "<<dataset.getLabel(i)<<"\n";
		cout<<"Feature vector "<<i<<" (first 5 elements): ";
		vector<double> feature_vector = dataset.getFeatureVector(i);
		for(int j = 0; j < 5; ++j)
			cout<<feature_vector[j]<<" ";
		cout<<"\n";
	}
}