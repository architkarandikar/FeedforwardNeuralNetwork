download the 4 files from http://yann.lecun.com/exdb/mnist/
uncompress them and copy-paste the data into .txt files named according to the corresponding string constants in datagen.cpp
	renaming doesn't work because of some weird formatting, copy pasting works
run the following:
bash> ./datagen x training.data test.data
bash> ./datagen 3 Three/training.data Three/test.data
bash> cd Three/
bash> make
bash> ./Classifier 5 x ModelStorage/FiveEpochStorageV0.txt TestDataResults/FiveEpochTestResultsV0.tx
	(Takes about 5 minutes per Epoch, will output test results into tmp_op.txt)