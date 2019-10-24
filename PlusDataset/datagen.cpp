#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

const int s = 20;
const int qmin = 2;
const int qmax = 5;

const string training_file_name = "training.data";
const string test_file_name = "test.data";

const int ntraining = 10000;
const int ntest = 10000;

int getRand(int l, int r)
{
	assert(l <= r);
	return (l + rand() % (r - l + 1));
}

void makePlus(bool grid[s][s])
{
	int qu = getRand(qmin, qmax), qd = getRand(qmin, qmax);
	int ql = getRand(qmin, qmax), qr = getRand(qmin, qmax);

	int ci,cj;
	while (true)
	{
		ci = getRand(qu, s - qd - 1);
		cj = getRand(ql, s - qr - 1);

		if(not grid[ci][cj])
			break;
	}

	for(int i = ci - qu; i <= ci + qd; ++i)
		grid[i][cj] = true;
	for(int j = cj - ql; j <= cj + qr; ++j)
		grid[ci][j] = true;
}

void generatePositiveSample(bool grid[s][s])
{
	for(int i = 0; i < s; ++i)
		for(int j = 0; j < s; ++j)
			grid[i][j] = false;

	int crange = s - (qmin + qmax);
	int sz = crange * crange;
	int r = getRand(1, sz + sz * sz + sz * sz * sz);

	int nplus = (r <= sz ? 1 : (r - sz <= sz * sz ? 2 : 3));
	for(int k = 0; k < nplus; ++k)
		makePlus(grid);
}

void generateNegativeSample(bool grid[s][s])
{
	int r = getRand(10,90);

	for(int i = 0; i < s; ++i)
		for(int j = 0; j < s; ++j)
			grid[i][j] = (getRand(1,100) <= r);
}

void printSampleAsGrid(bool grid[s][s], ostream& fout)
{
	for(int i = 0; i < s; ++i)
	{
		for(int j = 0; j < s; ++j)
		{
			fout<<grid[i][j];
		}
		fout<<"\n";
	}
}

void printSampleAsList(bool grid[s][s], ostream& fout)
{
	for(int i = 0; i < s; ++i)
	{
		for(int j = 0; j < s; ++j)
		{
			fout<<grid[i][j]<<" ";
		}
	}
	fout<<"\n";
}

void generateFile(string file_name, int nsamples)
{
	bool grid[s][s];

	ofstream fout;
	fout.open(file_name);
	fout<<nsamples<<" "<<s * s<<"\n";
	for(int i = 0; i < nsamples; ++i)
	{
		if (rand() % 2 == 1)
		{
			generatePositiveSample(grid);
			fout<<"1 ";
		}
		else
		{
			generateNegativeSample(grid);
			fout<<"0 ";
		}
		printSampleAsList(grid, fout);
	}
	fout.close();
}

int main()
{
	srand(time(NULL)); rand();

	generateFile(training_file_name, ntraining);
	generateFile(test_file_name, ntest);

	return 0;
}