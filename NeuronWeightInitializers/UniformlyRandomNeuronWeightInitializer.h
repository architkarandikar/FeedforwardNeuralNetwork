#include "NeuronWeightInitializer.h"

using namespace std;

class UniformlyRandomNeuronWeightInitializer: public NeuronWeightInitializer
{
public:
	UniformlyRandomNeuronWeightInitializer(double left_range, double right_range);

	double getWeight() const;
	double getBias() const;
private:
	double left_range_, right_range_;

	double uniformlyRandomInRange() const;
};