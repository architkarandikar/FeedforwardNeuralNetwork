import matplotlib.pyplot as plt
import numpy as np
import math
import sys

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False

def logarithmic_scale(i):
	return math.floor(math.log(i + 1))

def get_ig_for_label(i, label):
	if label > 0.5:
		return logarithmic_scale(max(i, 0))
	else:
		return logarithmic_scale(-1 * min(i, 0))

fp = open(sys.argv[1], 'r')
seperator_count = 0;
input_data = []
ig_data = []
predictions = []
labels = []
line = fp.readline()
while line != "":
	if line.startswith("---"):
		if seperator_count % 5 == 0:
			input_data.append([])
			ig_data.append([])
			read_prediction = False
		seperator_count += 1
	elif seperator_count % 5 == 1:
		for token in line.strip().split():
			if is_number(token):
				if read_prediction:
					labels.append(float(token))
				else:
					predictions.append(float(token))
					read_prediction = True
	elif seperator_count % 5 == 2:
		input_data[-1].append([int(x) for x in line.strip().split()])
	elif seperator_count % 5 == 4:
		ig_data[-1].append([get_ig_for_label(int(x), labels[-1]) for x in line.strip().split()])
	line = fp.readline()
fp.close()
input_data = [np.array(input_data_instance) for input_data_instance in input_data]
ig_data = [np.array(ig_data_instance) for ig_data_instance in ig_data]
rows,cols = input_data[0].shape

fig, widgets = plt.subplots(nrows = len(input_data) // 2, ncols = 4, figsize = (14, 8))

for z in range(len(input_data)):
	widgets.flat[2 * z].imshow(input_data[z], interpolation = 'nearest', 
	                 extent = [0.5, 0.5 + cols, 0.5, 0.5 + rows],
	                 cmap = 'Greys')
	widgets.flat[2 * z].set_title("prediction: " + str(predictions[z]) + ", label: " + str(labels[z]))

	widgets.flat[2 * z + 1].imshow(ig_data[z], interpolation = 'nearest', 
	                 extent = [0.5, 0.5 + cols, 0.5, 0.5 + rows],
	                 cmap = 'Greys')
	widgets.flat[2 * z + 1].set_title("Integrated Gradients wrt all 0s")
plt.tight_layout()
plt.show()