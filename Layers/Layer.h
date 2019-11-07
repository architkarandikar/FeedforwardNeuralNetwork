#include "../Neurons/Neuron.h"
#include "../NeuronWeightInitializers/NeuronWeightInitializer.h"
#include <vector>
#include <cassert>

using namespace std;

class Layer
{
public:
	Layer();
	Layer(int in_degree, int out_degree, double learning_rate, shared_ptr<ActivationFunction> activation_function, shared_ptr<NeuronWeightInitializer> neuron_weight_initializer);

	vector<double> evaluate(const vector<double>& inputs) const;
	void backPropagate(const vector<double>& loss_derivative_wrt_outputs, const vector<double>& inputs);
	vector<double> getLossDerivativeWrtInputs(const vector<double>& loss_derivative_wrt_outputs, const vector<double>& inputs) const;

	int getInDegree() const;
	int getOutDegree() const;

	void printWeights() const;

	friend ostream& operator <<(ostream &out, const Layer &layer);
	friend istream& operator >>(istream &in, Layer &layer);

private:
	int in_degree_;
	int out_degree_;
	vector<Neuron> neurons_;
};

ostream& operator <<(ostream &out, const Layer &layer);
istream& operator >>(istream &in, Layer &layer);