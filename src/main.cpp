#include <fstream>  
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Solution1.h"
using namespace std;  
  
int main() {
	cout << "BEGIN" << endl;
	// 计数读取71个数据集
	int count = 1;
	// 文件路径
	string baseFileName = "../Instances/";
	

	// 循环读取71个数据集
	while(count <= 71) {
		// 获取文件名
		stringstream sstream;
		sstream << count;
		string pNum;
		sstream >> pNum;
		string fileName = "p" + pNum;

		// 流读取文件
	    ifstream in(baseFileName+fileName);
	    ofstream out("../result/result.txt");

	  	// 有该文件
	    if(in) {
	    	vector<double> sample;
	    	double d;
	    	while(in >> d) {
	    		sample.push_back(d);
	    	}
	    	
	    	
	    	// fac 和 cus 数量数据
	    	int facilityNum = sample[0];
	    	int customerNum = sample[1];

	    	// fac 的 capacity 和 cost 数据
	    	vector<double> capacity;
	    	vector<double> cost;
	    	int begin = 2;
	    	for(int i = 0; i < facilityNum; i++) {
	    		capacity.push_back(sample[2*i+begin]);
	    		cost.push_back(sample[2*i+begin+1]);
	    	}

	    	// cus 的 demand 数据
	    	vector<double> demand;
	    	begin = 2+facilityNum*2;
	    	for(int i = 0; i < customerNum; i++) 
	    		demand.push_back(sample[i+begin]);

	    	// cus 的 assignment 数据
	    	vector<vector<double>> assignment;
	    	begin = 2+facilityNum*2+customerNum;
	    	for(int j = 0; j < facilityNum; j++) {
	    		vector<double> temp;
	    		for(int i = 0; i < customerNum; i++)
	    			temp.push_back(sample[j*customerNum+i+begin]);
	    		assignment.push_back(temp);
	    	}
	    	// 方法类
			printf("------%s------fac:%d------cus:%d---\n", fileName.c_str(), facilityNum, customerNum);
			Solution1 s1 = Solution1(facilityNum, customerNum, capacity, cost, demand, assignment);
	    	double result = s1.getResult();
	    	printf("[Result]---%lf\n", result);
	    }
	    // 没有该文件
	    else cout <<"No Test Data Files" << endl;
	    count++;
	}

	cout << "END" << endl;
	
    return 0;
}