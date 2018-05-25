#include<iostream>
#include<cstdlib>
#include <queue>
#include <vector>
#include <algorithm>    // std::sort
#include <fstream>
#include <ctime>
#include <random>
#include <fstream>

using namespace std;

class pairirlu {
	public:
	int key;
	int value;
	pairirlu(int v, int k): value(v), key(k) {}
};

int main(int argc, char **argv) {
    
    // PQSortOrg
    vector<pairirlu> myVector;
    int n, k, v;
    auto cmpKeyForVector = 
		[](const pairirlu a, const pairirlu b) {
			return a.key < b.key;
		};
    
    for(int capacity = 0; capacity <= 100000; capacity+=10000) {
        // Calculate a mean value for each capacity
        double meanCap = 0;
        int meanCount = 10;
        double variance = 0;
        double stdDev = 0;
        double *varianceElapsedTimes = new double[meanCount];
        clock_t end, begin;
        for(int m = 0; m < meanCount; m++) {
            begin = clock(); // Measure time start  
            std::default_random_engine generator;
            std::uniform_int_distribution<int> distribution(1,capacity);
            for(int i = 0; i < capacity; i++) {
                int diceKey = distribution(generator);
                int diceValue = distribution(generator);
                // pq.emplace(diceValue, diceKey);
                myVector.emplace_back(diceValue, diceKey);
            }
            
            std::sort(myVector.begin(), myVector.end(), cmpKeyForVector);

            end = clock();
            double elapsed_secs = double( end - begin ) /  CLOCKS_PER_SEC; // Measure time end
            meanCap += elapsed_secs;
            varianceElapsedTimes[m] = elapsed_secs;
        }
        // Calculate mean
        double mean = meanCap / meanCount;
        // Calculate variance
        for(int m = 0; m < meanCount; m++) {
            variance += (varianceElapsedTimes[m] - mean) * (varianceElapsedTimes[m] - mean);        
        }
        variance = variance / meanCount;
        stdDev = variance * variance;
        // cout << "Time for capacity => " << capacity << " => " << elapsed_secs << endl;
        cout << "Time: " << (end - begin) / (double) (CLOCKS_PER_SEC / 1000) << ", capacity: " << capacity << ", mean: " << mean << ", variance: " << variance << ", stdDev: " << stdDev << endl;
    }
	// clock_t begin = clock(); // Measure time start
 //    cin >> n;
	// while (cin >> k >> v) {
	// 	myVector.emplace_back(v, k);
 //    }

 //    std::sort(myVector.begin(), myVector.end(), cmpKeyForVector);

 //    for ( pairirlu pair : myVector ){
 //    	cout << pair.value << endl;
 //    }

 //    clock_t end = clock();
 //  	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC; // Measure time end
 //    cout << "Time => " << elapsed_secs << endl;
}
