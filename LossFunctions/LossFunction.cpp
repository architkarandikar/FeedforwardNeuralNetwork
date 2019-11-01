#include "LossFunction.h"

using namespace std;

ostream& operator <<(ostream &out, const LossFunction &loss_function)
{
	int status;
	string demangled = abi::__cxa_demangle(typeid(loss_function).name(), 0, 0, &status);

	return out<<demangled;
}