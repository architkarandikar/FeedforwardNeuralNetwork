#include "ActivationFunction.h"

using namespace std;

ostream& operator <<(ostream &out, const ActivationFunction &activation_function)
{
	int status;
	string demangled = abi::__cxa_demangle(typeid(activation_function).name(), 0, 0, &status);

	return out<<demangled;
}