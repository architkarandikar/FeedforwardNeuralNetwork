#include <iostream>
#include "NeuronWeightInitializer.h"
#include "UniformlyRandomNeuronWeightInitializer.h"

using namespace std;

ostream& operator <<(ostream &out, const shared_ptr<NeuronWeightInitializer> &neuron_weight_initialzer_ptr);
istream& operator >>(istream &in, shared_ptr<NeuronWeightInitializer> &neuron_weight_initialzer_ptr);