#include "NeuronWeightInitializer.h"
#include <cxxabi.h>

using namespace std;

class UniformlyRandomNeuronWeightInitializer: public NeuronWeightInitializer
{
public:
	UniformlyRandomNeuronWeightInitializer(double left_range, double right_range);

	double getWeight() const;
	double getBias() const;

	ostream& print(ostream &out) const;
	//friend ostream& operator<<(ostream &out, const UniformlyRandomNeuronWeightInitializer &uniformly_random_neuron_weight_initializer);
private:
	double left_range_, right_range_;

	double uniformlyRandomInRange() const;
};