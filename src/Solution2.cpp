#include "Solution2.h"
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <limits.h>
#include <time.h>
#include <cmath>
using namespace std;

Solution2::Solution2(int facilityNum, int customerNum, vector<double> capacity, vector<double> cost,
						 vector<double> demand, vector<vector<double>> assignment) {
	this -> facilityNum = facilityNum;
	this -> customerNum = customerNum;
	this -> capacity = capacity;
	this -> cost = cost;
	this -> demand = demand;
	this -> assignment = assignment;
	remain_capacity.assign(capacity.begin(), capacity.end());
	for(int i = 0; i < customerNum; i++)
		assignment_list.push_back(0);

	currentCost = -1;
	srand(time(NULL));
}

Solution2::~Solution2() {}

double Solution2::getResult() {

	double T = 2000;	// 初始温度
	double T0 = 0.1;	// 接受温度
	double q = 0.99;	// 退火速度
	int L = 1000;	// 迭代次数
	vector<int> new_assignment_list(assignment_list);
	vector<double> new_remain_capacity(remain_capacity);
	double new_cost;
	double df;

	// 初始化一个解
	while(!init_assignment_list(assignment_list));
	getRemainCapacity(remain_capacity, assignment_list);
	currentCost = get_totalCost(remain_capacity, assignment_list);

	while (T > T0) {
		//printf("------T:%lf------cost:%lf\n", T, currentCost);
		for(int i = 0; i < L; i++) {
			// 根据当前解产生邻居解
			while(!get_neighbor_assignment_list(assignment_list, new_assignment_list));
			// 非法解，跳过
			getRemainCapacity(new_remain_capacity, new_assignment_list);
			if(!isValid(new_remain_capacity, new_assignment_list)) continue;
			new_cost = get_totalCost(new_remain_capacity, new_assignment_list);
			df = new_cost - currentCost;
			// 如果新解更优，直接接受
			if(df < 0) {
				assignment_list.assign(new_assignment_list.begin(), new_assignment_list.end());
				remain_capacity.assign(new_remain_capacity.begin(), new_remain_capacity.end());
			}
			// 否则按概率接受
			if(new_cost < currentCost) {
				double r = (double)(rand() % 100000)/100000;
				double p = 1/(1+exp(-df/T));
				if(r > p) {
					assignment_list.assign(new_assignment_list.begin(), new_assignment_list.end());
					remain_capacity.assign(new_remain_capacity.begin(), new_remain_capacity.end());
				}
			}
		}
		T *= q;
		currentCost = get_totalCost(remain_capacity, assignment_list);
	}

	currentCost = get_totalCost(remain_capacity, assignment_list);
	showResult(remain_capacity, assignment_list);
	return currentCost;
}


// 初始一个解
bool Solution2::init_assignment_list(vector<int> &list) {
	vector<double> remain_capacity(capacity);
	// 随机开启工厂，然后往里面塞人，塞满后再开另一个工厂
	/*int j = (rand() % (facilityNum));
	for(int i = 0; i < customerNum; i++) {
		if(remain_capacity[j] >= demand[i]) {
			list[i] = j+1;
			remain_capacity[j] -= demand[i];
		}
		else {
			j = (rand() % (facilityNum));
			i--;
		}
	}*/
	for(int i = 0; i < customerNum; i++) {
		// 随机分配消费者到空闲设备
		while(true) {
			int j = (rand() % (facilityNum));
			if(remain_capacity[j] > demand[i]) {
				list[i] = j+1;
				remain_capacity[j] -= demand[i];
				break;
			}
		}
	}
	return isValid(remain_capacity, list);
}

// 根据当前解获得它的一个邻居解
bool Solution2::get_neighbor_assignment_list(vector<int> &old_list, vector<int> &new_list) {
	// 拷贝旧解
	new_list.assign(old_list.begin(), old_list.end());
	// 随机选择一个消费者i调离到设备j
	int i = (rand() % (customerNum)) + 1;
	int j = (rand() % (facilityNum)) + 1;
	new_list[i-1] = j;
	return true;
}

// 获得分配方案解对应的cost花费
double Solution2::get_totalCost(vector<double> &remain_capacity, vector<int> &assignment_list) {
	// 计算总共费用
	double totalCost = 0;
	// 设备启动费用
	for(int j = 0; j < facilityNum; j++) {
		if(remain_capacity[j] != capacity[j]) {
			totalCost += cost[j];
		}
	}
	for(int i = 0; i < customerNum; i++) {
		totalCost += assignment[assignment_list[i]-1][i];
	}
	return totalCost;
}


void Solution2::showResult(vector<double> &remain_capacity, vector<int> &assignment_list) {
	for(int j = 0; j < facilityNum; j++) {
		if(remain_capacity[j] != capacity[j]) {
			printf("1 ");
		}
		else printf("0 ");
	}
	printf("\n");
	/*for(int j = 0; j < facilityNum; j++) {
		printf("%0.lf ", remain_capacity[j]);
	}
	printf("\n");*/
	// customer 费用
	for(int i = 0; i < customerNum; i++) {
		printf("%d ", assignment_list[i]);
	}
	printf("\n");
}

// 根据分配方案得到各工厂的剩余空间
void Solution2::getRemainCapacity(vector<double> &remain_capacity, vector<int> &assignment_list) {
	// 重置容量
	remain_capacity.assign(capacity.begin(), capacity.end());
	// 计算剩余容量，并判断是否合法
	for(int i = 0; i < customerNum; i++) {
		remain_capacity[assignment_list[i]-1] -= demand[i]; 
	}
}

// 判断消费者分配方案是否合法
bool Solution2::isValid(vector<double> &remain_capacity, vector<int> &assignment_list) {
	for(int j = 0; j < facilityNum; j++) {
		if(remain_capacity[j] < 0) return false;
	}
	return true;
}