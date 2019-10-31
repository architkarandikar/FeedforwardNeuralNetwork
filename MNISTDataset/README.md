download the 4 files from http://yann.lecun.com/exdb/mnist/
uncompress them and copy-paste the data into .txt files named according to the corresponding string constants in datagen.cpp
	renaming doesn't work because of some weird formatting, copy pasting works
run the following:
bash> ./datagen x training.data test.data
bash> ./datagen 3 Three/training.data Three/test.data
bash> cd Three/
bash> make
bash> ./Classifier
	(Takes about 3-4 minutes per Epoch, will output test results into tmp_op.txt)