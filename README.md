This is an end-to-end implementation of a deep feedforward neural network framework. The API is very similar to the Keras API. The framework itself is designed to have clean object-oriented abstractions that make semantic sense. It should be easy to read and use.

A note about coding practices. All of the ..Test.cpp, datagen.cpp and Classifer.cpp are not core framework files. These are all like test scripts and intentionally don't follow any coding practices. The rest of the files should be clean in terms of abstractions and object-oriented design but will not follow production C++ standards and practices. Since most of my production coding has not been in C++, I'm not yet familiar with C++ 11 features and coding practices and adhering to those is not the objective here. Accordingly, you will not see C++11 loops, the auto keyword, the move keyword, futures etc. that are typical of large-scale production codebases.

Tests and documentation haven't been added yet, since this is a toy project. There are a bunch of sanity-check tests which are really scripts which are not meant to be clean code. The repository will evolve over time.

Use the READMEs in each folder for detailed instructions. The networks as of now are not robust to a veriety of initial conditions and converge only for very specific initial conditions

Demo:
* MNISTDataset/IntegratedGradientsVisualization/integrated_gradients_plot_3_five_epoch.png
* MNISTDataset/Three/MNISTThreeVideo.mov

![Integrated Gradients for a binary classifier trained to recognize 4s in the MNIST dataset](https://github.com/architkarandikar/FeedforwardNeuralNetwork/blob/master/MNISTDataset/IntegratedGradientsVisualization/integrated_gradients_plot_4_one_epoch.png)

Framework components are in the following folders:
* ActivationFunctions
* LossFunctions
* Neurons
* Layers
* NeuralNetwork
* Datasets
* NeuronWeightInitializers
The following folders contain datasets and classifiers for those datasets:
* PlusDataset
* MNISTDataset