#include <iostream>
#include "LossFunction.h"
#include "LogCoshLossFunction.h"
#include "SquaredErrorLossFunction.h"

using namespace std;

ostream& operator <<(ostream &out, const shared_ptr<LossFunction> &loss_function_ptr);
istream& operator >>(istream &in, shared_ptr<LossFunction> &loss_function_ptr);