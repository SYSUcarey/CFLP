#ifndef SOLUTION1_H
#define SOLUTION1_H

#include <vector>
using namespace std;  

class Solution1 {
public:
   	Solution1(int facilityNum, int customerNum, vector<double> capacity, vector<double> cost, vector<double> demand, vector<vector<double>> assignment);
   	double getResult();
private:
	double getCost(int facilityNum, int customerNum);
	int facilityNum;
	int customerNum;
	vector<double> capacity;
	vector<double> cost;
	vector<double> demand;
	vector<vector<double>> assignment;
	//int open_statusd[];
	//int assignment_listd[];

};
#endif