#include "ActivationFunctionIO.h"

using namespace std;

ostream& operator <<(ostream &out, const shared_ptr<ActivationFunction> &activation_function_ptr)
{
	return out<<activation_function_ptr->getName();
}

istream& operator >>(istream &in, shared_ptr<ActivationFunction> &activation_function_ptr)
{
	string identifier;
	in>>identifier;

	if (identifier == LeakyReluActivationFunction::name) {
		activation_function_ptr = make_shared<LeakyReluActivationFunction>();
	}
	else if(identifier == LinearActivationFunction::name) {
		activation_function_ptr = make_shared<LinearActivationFunction>();
	}
	else if(identifier == ReluActivationFunction::name) {
		activation_function_ptr = make_shared<ReluActivationFunction>();
	}
	else if(identifier == SigmoidActivationFunction::name) {
		activation_function_ptr = make_shared<SigmoidActivationFunction>();
	}
	else if(identifier == TanhActivationFunction::name) {
		activation_function_ptr = make_shared<TanhActivationFunction>();
	}
	else {
		assert(false);
	}

	return in;
}