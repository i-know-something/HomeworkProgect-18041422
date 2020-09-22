#include<iostream>

//find a better program online,copy it here.

using namespace std;


int main()
{
	int NemberMax = 100;
    bool* prime = new bool[NemberMax + 1];
    int i;

    for (i = 2; i < NemberMax; i++) {
        prime[i] = true;
    }


    for (i = 2; i < NemberMax; i++) {
        if (prime[i]){
            cout << i << " ";
            for (int j = i + i; j < NemberMax; j += i) {
                prime[j] = false;
            }
        }
    }

    cout << endl;

    return 0;
}
