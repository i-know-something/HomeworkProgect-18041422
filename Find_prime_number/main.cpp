#include<stdio.h>

#include<iostream>

using namespace std;

int prime_1(int );				//My low program;
int prime_2(int );				//find a program Online,special one

int main()
{
	//prime_1(100);

	prime_2(200);

	return 0;
}


int prime_1( int NemberMax ){
								//Find prime nember which is smaller than NemberMax
	int NemberFind;				//the nember is being tested now
	int PrimeFlag;				

	NemberFind = 2;
	PrimeFlag = 1;

	while (NemberMax>0) {

		
		for (int i = NemberFind-1; i > 1; i--){

			if (NemberFind % i == 0){
				PrimeFlag=0;
				break;
			}
		}
		
		if (PrimeFlag)
			printf("%d ", NemberFind);
			

		if (NemberFind == NemberMax)
				break;
		else {
			NemberFind++;
			PrimeFlag = 1;
		}
	}
	return 0;
}


int prime_2(int n) {
	
	int i;
	bool * prime = new bool[n + 1];

	for (i = 2; i < n; i++) {
		prime[i] = true;
	}

	for (i = 2; i < n; i++) {
		if (prime[i]) {
			cout << i << " ";

			for (int j = i + i; j < n; j += i) {
				prime[j] = false;
			}
		}
	}

	cout << endl;

	return 0;

}