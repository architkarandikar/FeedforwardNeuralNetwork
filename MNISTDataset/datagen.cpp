#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>

using namespace std;

const string training_images_input_file = "train-images-idx3-ubyte.txt";
const string training_labels_input_file = "train-labels-idx1-ubyte.txt";

const string test_images_input_file = "t10k-images-idx3-ubyte.txt";
const string test_labels_input_file = "t10k-labels-idx1-ubyte.txt";

void parse_and_format_image(int focus_digit, int label, int num_rows, int num_columns, ifstream& fin_images, ofstream& fout)
{
	int print_label = label;
	if (focus_digit != -1)
	{
		print_label = (label == focus_digit ? 1 : 0);
	}
	fout<<print_label<<"\n";
	for(int z = 0; z < num_rows * num_columns; z += 2)
	{
		int x;
		fin_images>>hex>>x;

		fout<<setfill('0')<<setw(3)<<x / 256<<" ";
		fout<<setfill('0')<<setw(3)<<x % 256<<" ";
		if((z + 2) % num_columns == 0)
		{
			fout<<"\n";
		}
	}
	fout<<"\n";
}

void parse_and_format(int focus_digit, const string& images_input_file, const string& labels_input_file, const string& formatted_output_file)
{
	ifstream fin_images, fin_labels;
	ofstream fout;
	fin_images.open(images_input_file);
	fin_labels.open(labels_input_file);
	fout.open(formatted_output_file);

	int zero, magic_number, num_images, num_rows, num_columns;
	fin_images>>hex>>zero>>magic_number>>zero>>num_images>>zero>>num_rows>>zero>>num_columns;

	int num_images_redundant;
	fin_labels>>hex>>zero>>magic_number>>zero>>num_images_redundant;
	assert(num_images == num_images_redundant);

	fout<<num_images<<" "<<num_rows * num_columns<<"\n\n";
	
	for(int y = 0; y < num_images; y += 2)
	{
		int w;
		fin_labels>>w;

		parse_and_format_image(focus_digit, w / 256, num_rows, num_columns, fin_images, fout);
		parse_and_format_image(focus_digit, w % 256, num_rows, num_columns, fin_images, fout);
	}
}

int main(int argc, char** argv)
{
	assert(argc >= 4);

	int focus_digit = focus_digit = argv[1][0]-'0';
	if(focus_digit < 0 or focus_digit > 9)
	{
		focus_digit = -1;
	}

	string training_formatted_output_file = argv[2];
	string test_formatted_output_file = argv[3];

	parse_and_format(focus_digit, training_images_input_file, training_labels_input_file, training_formatted_output_file);
	parse_and_format(focus_digit, test_images_input_file, test_labels_input_file, test_formatted_output_file);
}