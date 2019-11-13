download the 4 files from http://yann.lecun.com/exdb/mnist/
uncompress them and copy-paste the data into .txt files named according to the corresponding string constants in datagen.cpp
	(renaming doesn't work because of some weird formatting, copy pasting works)
run the following:
bash> ./datagen x training.data test.data
bash> ./datagen 3 Three/training.data Three/test.data
bash> mkdir Three/ModelStorage/ Three/TestDataResults/ Three/IntegratedGradients/
bash> make
bash> ./Classifier
	(To see some instructions on parameters)
bash> ./Classifier Three/training.data Three/test.data 5 x Three/ModelStorage/FiveEpochStorageV0.txt Three/TestDataResults/FiveEpochTestResultsV0.txt x
	(Takes about 5 minutes per Epoch, will output test results into tmp_op.txt)
bash> ./Classifier Three/training.data Three/test.data 0 Three/ModelStorage/FiveEpochStorageV0.txt x Three/TestDataResults/FiveEpochTestResultsV0.txt Three/IntegratedGradients/FiveEpochIntegratedGradientsV0.txt
	(Can be combined with previous one as well)
bash> python3 IntegratedGradientsVisualization/integrated_gradients_plot.py Three/IntegratedGradients/FiveEpochIntegratedGradientsV0.txt