#include "UniformlyRandomNeuronWeightInitializer.h"

using namespace std;

UniformlyRandomNeuronWeightInitializer::UniformlyRandomNeuronWeightInitializer(double left_range, double right_range):
	left_range_(left_range), right_range_(right_range) {}

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

ostream& UniformlyRandomNeuronWeightInitializer::print(ostream &out) const
{
	return out<<"UniformlyRandomNeuronWeightInitializer "<<left_range_<<" "<<right_range_;
}