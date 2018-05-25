#include<iostream>
#include<cstdlib>
#include <queue>
#include <vector>
#include <algorithm>    // std::sort
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
	// PQSort
	int n;
	int k, v;
	auto cmpKey = 
		[](const pairirlu a, const pairirlu b) {
			return b.key < a.key;
		};
	priority_queue <pairirlu, vector<pairirlu>, decltype(cmpKey)>
					pq(cmpKey);
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
				pq.emplace(diceValue, diceKey);
			}
		    
		    while(!pq.empty()) {
		        // std::cout << pq.top().value << std::endl;
		        pq.pop();
		    }
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
	// cin >> n;
	// while (cin >> k >> v) {
	// 	pq.emplace(v, k);
 //    }


}
