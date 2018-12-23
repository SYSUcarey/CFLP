#include "Solution1.h"
#include <iostream>
#include <cstring>
#include <limits.h>
using namespace std;

Solution1::Solution1(int facilityNum, int customerNum, vector<double> capacity, vector<double> cost,
						 vector<double> demand, vector<vector<double>> assignment) {
	this -> facilityNum = facilityNum;
	this -> customerNum = customerNum;
	this -> capacity = capacity;
	this -> cost = cost;
	this -> demand = demand;
	this -> assignment = assignment;
	this -> open_status = new int[facilityNum];
	this -> assignment_list = new int[customerNum];
	this -> remain_capacity = new double[facilityNum];
	for(int i = 0; i < facilityNum; i++) {
		open_status[i] = 0;
		remain_capacity[i] = capacity[i];
	}
	for(int i = 0; i < customerNum; i++)
		assignment_list[i] = 0;
}

Solution1::~Solution1() {
	delete open_status;
	delete assignment_list;
	delete remain_capacity;
}

double Solution1::getResult() {
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
			remain_capacity[fac-1] -= demand[cus-1];
			assignment_list[cus-1] = fac;
		}
	}
	// 计算总共费用
	double totalCost = 0;
	// 设备启动费用
	for(int j = 0; j < facilityNum; j++) {
		if(open_status[j] == 1) {
			totalCost += cost[j];
		}
	}
	// customer 费用
	for(int i = 0; i < customerNum; i++) {
		totalCost += assignment[assignment_list[i]-1][i];
	}
	
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


int* Solution1::get_assignment_list() {
	return assignment_list;
}

void Solution1::showResult() {
	for(int j = 0; j < facilityNum; j++) {
		if(remain_capacity[j] != capacity[j]) {
			printf("1 ");
		}
		else printf("0 ")	;
	}
	printf("\n");
	for(int i = 0; i < customerNum; i++) {
		printf("%d ", assignment_list[i]);
	}
	printf("\n");
}