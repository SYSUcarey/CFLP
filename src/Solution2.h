#ifndef SOLUTION2_H
#define SOLUTION2_H

#include <vector>
using namespace std;  

class Solution2 {
public:
   	Solution2(int facilityNum, int customerNum, vector<double> capacity, vector<double> cost, vector<double> demand, vector<vector<double>> assignment);
   	~Solution2();
   	double getResult();
private:
	bool init_assignment_list(vector<int> &list);
	bool get_neighbor_assignment_list(vector<int> &old_list, vector<int> &new_list);
	double get_totalCost(vector<double> &remain_capacity, vector<int> &assignment_list);
	void showResult(vector<double> &remain_capacity, vector<int> &assignment_list);
	void getRemainCapacity(vector<double> &remain_capacity, vector<int> &assignment_list);
	bool isValid(vector<double> &remain_capacity, vector<int> &assignment_list); 

	int* new_assignment_list;
	int facilityNum;
	int customerNum;
	vector<double> capacity;
	vector<double> cost;
	vector<double> demand;
	vector<vector<double>> assignment;
	vector<int> assignment_list;
	vector<double> remain_capacity;
	double currentCost;
};
#endif