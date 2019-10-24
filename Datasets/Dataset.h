#pragma once

#include <vector>
#include <fstream>

using namespace std;

class Dataset
{
public:
	Dataset(string file_name);

	vector<double> getFeatureVector(int index) const;
	double getLabel(int index) const;
	int getNumSamples() const;
	int getNumDimensions() const;

private:
	int num_samples_;
	int num_dimensions_;
	vector<vector<double> > feature_vectors_;
	vector<double> labels_;
};