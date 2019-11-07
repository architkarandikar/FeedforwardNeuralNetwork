#include "NeuronWeightInitializerIO.h"

using namespace std;

ostream& operator <<(ostream &out, const shared_ptr<NeuronWeightInitializer> &neuron_weight_initialzer_ptr)
{
	out<<neuron_weight_initialzer_ptr->getName()<<" ";
	return neuron_weight_initialzer_ptr->outputAdditional(out);
}

istream& operator >>(istream &in, shared_ptr<NeuronWeightInitializer> &neuron_weight_initialzer_ptr)
{
	string identifier;
	in>>identifier;

	if (identifier == UniformlyRandomNeuronWeightInitializer::name) {
		neuron_weight_initialzer_ptr = make_shared<UniformlyRandomNeuronWeightInitializer>();
	}
	else {
		assert(false);
	}

	return neuron_weight_initialzer_ptr->inputAdditional(in);
}