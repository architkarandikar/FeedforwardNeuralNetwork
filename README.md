This is an end-to-end implementation of a deep feedforward neural network framework with interpretability support via integrated gradients. The API is very similar to the Keras API. The framework itself is designed to have clean object-oriented abstractions that make semantic sense. It should be easy to read and use. The framework provides support to serialize / store-to-file and deserialize / load-from-file trained neural networks.

A note about coding practices. All of the `..Test.cpp`, `datagen.cpp` and `Classifer.cpp` are not core framework files. These are all like test scripts and intentionally don't follow any coding practices. The rest of the files should be clean in terms of abstractions and object-oriented design but will not follow production C++ standards and practices. Since most of my production coding has not been in C++, I'm not yet familiar with several C++ 11 features and coding practices and adhering to those is not the objective here. Accordingly, you will not see C++11 loops, the auto keyword, the move keyword, futures etc. that are typical of large-scale production codebases.

Tests and documentation haven't been added yet, since this is a toy project. There are a bunch of sanity-check tests which are really scripts not meant to be clean code. The repository will evolve over time.

Use the `README.md` in each folder for detailed instructions. The networks as of now are not robust to a variety of initial conditions and converge only for very specific initial conditions. Support for optimizers such as ADAM hasn't been added yet.

Demo:
* MNISTDataset/IntegratedGradientsVisualization/integrated_gradients_plot_3_five_epoch.png
* MNISTDataset/Three/MNISTThreeVideo.mov

The binary classifier used in the figure which follows was trained to recognize the digit 4 (as positive, 1.0) from the MNIST datasets (all other digits are negative, 0.0). As can be seen, the prediction closely matches the label for the test dataset. The integrated gradient plots are meant to distinguish the parts of the image important to the prediction from the unimportant ones so as to provide some interpretability of the model prediction. The dark regions are the most important and the light regions are the least important. Importance is measured as contribution to change in prediction as image gradually changes from a blank image to test image. All digits except 4 and 1 have some horizontal stroke at the top, and accordingly the model shows that the most important part of all five negative instances shown here is some part of the top horizontal stroke. The most important part of the positive instances is the middle horizontal stroke of the 4 and the stem of its two vertical offshoots, which also makes sense.

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