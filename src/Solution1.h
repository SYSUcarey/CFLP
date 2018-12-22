#ifndef SOLUTION1_H
#define SOLUTION1_H

#include <vector>
using namespace std;  

class Solution1 {
public:
   	Solution1(int facilityNum, int customerNum, vector<double> capacity, vector<double> cost, vector<double> demand, vector<vector<double>> assignment);
   	~Solution1();
   	double getResult();
   	int* get_assignment_list();
	void showResult();
private:
	double getCost(int facilityNum, int customerNum);
	int facilityNum;
	int customerNum;
	vector<double> capacity;
	vector<double> cost;
	vector<double> demand;
	vector<vector<double>> assignment;
	int *open_status;	
	int *assignment_list;
	double *remain_capacity;

};
#endif