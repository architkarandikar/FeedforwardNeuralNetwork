#include <iostream>
#include "ActivationFunction.h"
#include "LeakyReluActivationFunction.h"
#include "LinearActivationFunction.h"
#include "ReluActivationFunction.h"
#include "SigmoidActivationFunction.h"
#include "TanhActivationFunction.h"

using namespace std;

ostream& operator <<(ostream &out, const shared_ptr<ActivationFunction> &activation_function_ptr);
istream& operator >>(istream &in, shared_ptr<ActivationFunction> &activation_function_ptr);