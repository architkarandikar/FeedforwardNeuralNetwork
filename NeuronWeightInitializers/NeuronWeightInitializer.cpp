#include "NeuronWeightInitializer.h"

using namespace std;

ostream& operator <<(ostream &out, const NeuronWeightInitializer &neuron_weight_initializer)
{
	return neuron_weight_initializer.print(out);
}