#include "Solution1.h"
#include <iostream>
#include <cstring>
#include <limits.h>
#include <time.h>
using namespace std;

Solution1::Solution1(int facilityNum, int customerNum, vector<double> capacity, vector<double> cost,
						 vector<double> demand, vector<vector<double>> assignment) {
	this -> facilityNum = facilityNum;
	this -> customerNum = customerNum;
	this -> capacity = capacity;
	this -> cost = cost;
	this -> demand = demand;
	this -> assignment = assignment;
	
}

double Solution1::getResult() {
	clock_t start,stop;
    start = clock();
	int open_status[facilityNum] = {0};
	int assignment_list[customerNum] = {0};
	double remain_capacity[facilityNum];
	for(int i = 0; i < capacity.size(); i++)
		remain_capacity[i] = capacity[i];
	
	// 按照贪心算法预估的cost值，选取最小的cost去安排设备
	for(int count = 0; count < customerNum; count++) {
		// 获取最高性价比，评估cost最小的分配
		double leastCost = INT_MAX;
		int fac = -1;
		int cus = -1;
		for(int j = 0; j < facilityNum; j++) {
			for(int i = 0; i < customerNum; i++) {
				// customer 已经分配
				if(assignment_list[i] != 0) continue;
				// 设备容量不足
				if(demand[i] > remain_capacity[j]) continue;
				// 有容量，获取贪心算法评估代价Cost
				double cost_j_i = getCost(j, i);
				//cout << j+1 << " " << i+1 << " " << cost_j_i << endl; 
				if(cost_j_i < leastCost) {
					leastCost = cost_j_i;
					fac = j+1;
					cus = i+1;
				}
			}
		}
		// 没有可进行的分配
		if(fac == -1 || cus == -1 || leastCost == INT_MAX) {
			cout << "[ERROR]" << endl;
		}
		else {
			// 进行分配
			open_status[fac-1] = 1;
			remain_capacity[fac-1] -= demand[cus];
			assignment_list[cus-1] = fac;
		}
	}
	// 计算总共费用
	int totalCost = 0;
	// 设备启动费用
	for(int j = 0; j < facilityNum; j++) {
		//printf("%d ", open_status[j]);
		if(open_status[j] == 1) {
			totalCost += cost[j];
		}
	}
	//printf("\n");
	// customer 费用
	for(int i = 0; i < customerNum; i++) {
		//printf("%d ", assignment_list[i]);
		totalCost += assignment[assignment_list[i]-1][i];
	}
	//printf("\n");
	stop = clock();
	double dur = (double)stop-start;
	printf("[Time]---%.0lfms\n", dur);
	return totalCost;
}

// 返回贪心算法中评估Cost的值
double Solution1::getCost(int facilityNum, int customerNum) {
	// 开启设备分摊平均占用费用
	double facilityCost = cost[facilityNum] * demand[customerNum] / capacity[facilityNum];
	// 消费者使用费用
	double assignmentCost = assignment[facilityNum][customerNum];
	// 返回总评估费用
	return facilityCost + assignmentCost;
}