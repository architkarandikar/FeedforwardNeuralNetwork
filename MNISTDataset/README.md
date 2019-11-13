download the 4 files from http://yann.lecun.com/exdb/mnist/
uncompress them and copy-paste the data into .txt files named according to the corresponding string constants in datagen.cpp
	(renaming doesn't work because of some weird formatting, copy pasting works)
run the following:
bash> ./datagen x training.data test.data
bash> ./datagen 3 Three/training.data Three/test.data
bash> cd Three/
bash> make
bash> mkdir ModelStorage/ TestDataResults/ IntegratedGradients/
bash> ./Classifier
	(To see some instructions on parameters)
bash> ./Classifier 5 x ModelStorage/FiveEpochStorageV0.txt TestDataResults/FiveEpochTestResultsV0.txt x
	(Takes about 5 minutes per Epoch, will output test results into tmp_op.txt)
bash> ./Classifier 0 ModelStorage/FiveEpochStorageV0.txt x TestDataResults/FiveEpochTestResultsV0.txt IntegratedGradients/FiveEpochIntegratedGradientsV0.txt
	(Can be combined with previous one as well)
bash> cd IntegratedGradientsVisualization/
bash> python integrated_gradients_plot.py FiveEpochIntegratedGradientsV0.txt