void Neuron::backPropagate(double loss_derivative_wrt_output, const vector<double>& inputs)
{
	assert((int)inputs.size() == in_degree_);

	double loss_derivative_wrt_combination = loss_derivative_wrt_output * activation_function_.getDerivative(combine(inputs));
	for(int i = 0; i < in_degree_; ++i)
	{
		double loss_derivative_wrt_weight = loss_derivative_wrt_combination * inputs[i];
		weights_[i] -= learning_rate_ * loss_derivative_wrt_weight;

		cout<<"here actual backPropagate: "
			<<(int)inputs.size()<<" "
			<<learning_rate_ * loss_derivative_wrt_weight<<" "
			<<loss_derivative_wrt_weight<<" "
			<<loss_derivative_wrt_output<<" "
			<<combine(inputs)<<" "
			<<activation_function_.getDerivative(combine(inputs))<<"\n";
	}
	double loss_derivative_wrt_bias = loss_derivative_wrt_combination;
	bias_ -= learning_rate_ * loss_derivative_wrt_bias;
	return;
}

