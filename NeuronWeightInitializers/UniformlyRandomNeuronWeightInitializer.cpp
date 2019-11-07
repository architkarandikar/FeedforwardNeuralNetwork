#include "UniformlyRandomNeuronWeightInitializer.h"

using namespace std;

const string UniformlyRandomNeuronWeightInitializer::name = "UniformlyRandomNeuronWeightInitializer";

UniformlyRandomNeuronWeightInitializer::UniformlyRandomNeuronWeightInitializer(double left_range, double right_range):
	left_range_(left_range), right_range_(right_range) {}

UniformlyRandomNeuronWeightInitializer::UniformlyRandomNeuronWeightInitializer(): left_range_(0.0), right_range_(0.0) {}

double UniformlyRandomNeuronWeightInitializer::getWeight() const
{
	return uniformlyRandomInRange();
}

double UniformlyRandomNeuronWeightInitializer::getBias() const
{
	return uniformlyRandomInRange();
}

double UniformlyRandomNeuronWeightInitializer::uniformlyRandomInRange() const
{
	return left_range_ + ((double)(rand())) / ((double)(RAND_MAX)) * (right_range_ - left_range_);
}

string UniformlyRandomNeuronWeightInitializer::getName() const
{
	return UniformlyRandomNeuronWeightInitializer::name;
}

ostream& UniformlyRandomNeuronWeightInitializer::outputAdditional(ostream &out) const
{
	return out<<left_range_<<" "<<right_range_;
}

istream& UniformlyRandomNeuronWeightInitializer::inputAdditional(istream &in)
{
	return in>>left_range_>>right_range_;
}