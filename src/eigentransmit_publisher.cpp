#include "ros/ros.h"
#include "eigentransmit/msgeigentransmit.h"
#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

void MatrixToMsg(eigentransmit::msgeigentransmit &msg, Eigen::MatrixXd &A) {
	int k=A.rows()*A.cols();
	int ii=2;
	msg.data.resize(k+2);
	for(int i=0; i<A.rows(); i++) {
		for(int j=0; j<A.cols(); j++) {
			msg.data[ii++]=A.coeff(i, j);
		}
	}
	msg.data[0]=A.rows();
	msg.data[1]=A.cols();
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "eigentransmit_publisher");
	ros::NodeHandle nh;

	ros::Publisher eigentransmit_pub = nh.advertise<eigentransmit::msgeigentransmit>("eigentransmit", 1000);

	ros::Rate loop_rate(1);

	int count = 0;
	Eigen::MatrixXd A(3, 2);
	A << 1, 2,
	     3, 4,
	     5, 6;
	while(ros::ok()) {
		eigentransmit::msgeigentransmit msg;
	/*	int k=A.rows()*A.cols();
		int ii=2;
		msg.data.resize(k+2);
		for(int i=0; i<A.rows(); i++) {
			for(int j=0; j<A.cols(); j++) {
				msg.data[ii++]=A.coeff(i, j);
			}
		}
		msg.data[0]=A.rows();
		msg.data[1]=A.cols();*/
		MatrixToMsg(msg, A);
		std::cout << "count : " << count << std::endl;
		count++;
		std::cout << "Publishing Matrix A : \n" << A << std::endl;
		eigentransmit_pub.publish(msg);

		loop_rate.sleep();
	}
	return 0;
}



