#include "ros/ros.h"
#include "eigentransmit/msgeigentransmit.h"
#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

void MsgToMatrix(const eigentransmit::msgeigentransmit::ConstPtr &msg, Eigen::MatrixXd &A) {
	int m=msg->data[0];
	int n=msg->data[1];
	A.resize(m, n);
	int ik=2;
	for(int k=0; k<m; k++) {
		for(int l=0; l<n; l++) {
			A(k, l) = msg->data[ik++];
		}
	}
}	

void callback(const eigentransmit::msgeigentransmit::ConstPtr &msg) {
	/*int m=msg->data[0];
	int n=msg->data[1];
	Eigen::MatrixXd A(m, n);
	int ik=2;
	for(int k=0; k<m; k++) {
		for(int l=0; l<n; l++) {
			A(k, l) = msg->data[ik++];
		}
	}*/
	Eigen::MatrixXd A;
	MsgToMatrix(msg, A);
	std::cout << "receiving Matrix A : \n" << A << std::endl;
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "eigentransmit_subscriber");
	ros::NodeHandle nh;

	ros::Subscriber eigentransmit_sub = nh.subscribe("eigentransmit", 1000, callback);

	ros::spin();
	return 0;
}


	

