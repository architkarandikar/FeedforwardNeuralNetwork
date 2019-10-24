#include "Dataset.h"

using namespace std;

Dataset::Dataset(string file_name)
{
	ifstream fin;
	fin.open(file_name);

	fin>>num_samples_>>num_dimensions_;
	feature_vectors_.resize(num_samples_, vector<double>(num_dimensions_, 0.0));
	labels_.resize(num_samples_, 0.0);
	for(int i = 0; i < num_samples_; ++i)
	{
		fin>>labels_[i];
		for(int j = 0; j < num_dimensions_; ++j)
		{
			fin>>feature_vectors_[i][j];
		}
	}

	fin.close();
}

vector<double> Dataset::getFeatureVector(int index) const
{
	return feature_vectors_[index];
}

double Dataset::getLabel(int index) const
{
	return labels_[index];
}

int Dataset::getNumSamples() const
{
	return num_samples_;
}

int Dataset::getNumDimensions() const
{
	return num_dimensions_;
}