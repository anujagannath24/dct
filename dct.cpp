#include <iostream>
#include <fstream>
#include <complex>
#include <iomanip>
using namespace std;

#define PI 3.1415926535897932384


int main()
{
	int N;
	int samlp_rate, freq_resl;
	fstream myfile;
	myfile.open("C:\\Anu\\academics\\Computer_Audio\\A2\\sin_20000Hz_-3dBFS_3s.dat", std::ios_base::in);
	fstream outfile;
	outfile.open("C:\\Anu\\academics\\Computer_Audio\\A2\\sin_20000Hz_-3dBFS_3s_out.csv", std::ios_base::out);
	printf("Enter sample rate\n");
	scanf("%d", &samlp_rate);
	
	printf("Enter the frequency resolution required in the frequency spectrum\n");
	scanf("%d", &freq_resl);

	N = samlp_rate / freq_resl;

	float a, b[150000], c1, c2, *dct;
	float out, max=0;
	int num =0, temp, i, k,n;

	std::cout << std::setprecision(6) << std::fixed;

	dct = (float *)malloc(sizeof(float)*N/2);


	while (myfile >> a >> b[num])
	{
		num++;
	}

	for (k = 0; k < N; k++)
	{
		out = 0;
		for (n = 0; n < num; n++)
		{
			out += b[n] * cos((PI*k / (2 * N)) *(2 * n + 1));
		}
		c1 = 2 * out;

		out = 0;
		k++;
		for (n = 0; n < num; n++)
		{
			out += b[n] * cos((PI*k / (2 * N)) *(2 * n + 1));
		}
		c2 = 2 * out;
		dct[k/2] = sqrt(pow(c1, 2) + pow(c2, 2));
		if (max < dct[k / 2])
			max = dct[k / 2];
	}
	outfile << "Frequency(Hz)" << "," << "Amplitude (dB)" << endl;
	for (k = 0; k < N / 2; k++)
	{
		outfile << (k * freq_resl) << "," << 20*log10(dct[k]/max) << endl;
	}
	return 0;
}
