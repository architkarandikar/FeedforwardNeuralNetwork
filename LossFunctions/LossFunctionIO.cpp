#include "LossFunctionIO.h"

using namespace std;

ostream& operator <<(ostream &out, const shared_ptr<LossFunction> &loss_function_ptr)
{
	return out<<loss_function_ptr->getName();
}

istream& operator >>(istream &in, shared_ptr<LossFunction> &loss_function_ptr)
{
	string identifier;
	in>>identifier;

	if (identifier == LogCoshLossFunction::name) {
		loss_function_ptr = make_shared<LogCoshLossFunction>();
	}
	else if(identifier == SquaredErrorLossFunction::name) {
		loss_function_ptr = make_shared<SquaredErrorLossFunction>();
	}
	else {
		assert(false);
	}

	return in;
}