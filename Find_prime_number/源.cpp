#include<stdio.h>

int main()
{
	int NemberMax;				//Find prime nember which is smaller than NemberMax
	int NemberFind;				//the nember is being tested now
	int PrimeFlag;				


	NemberMax = 100;
	NemberFind = 1;
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