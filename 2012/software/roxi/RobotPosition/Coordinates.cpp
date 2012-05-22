#include "Coordinates.hpp"
/*Returns a Matrix M such that M*<coordinates in robot frame>=<coordinates in world frame>*/
CvMat* getRobotToWorldMat(){
	return getRobotToWorldMat(RobotPosition::getInstance());
}

/*Returns a Matrix M such that M*<coordinates in world frame>=<coordinates in robot frame>*/
CvMat* getWorldToRobotMat(){
	return getWorldToRobotMat(RobotPosition::getInstance());
}

CvMat* getRobotToWorldMat(RobotPosition pos){
	double move[9]={1,0,pos.getX(),
			   0,1,pos.getY(),
			   0,0,1};
	double rotate[9]={cos(pos.getAngle()-90),cos(pos.getAngle()),0,
			     sin(pos.getAngle()-90),sin(pos.getAngle()),0,
			     0,0,1};
	CvMat moveMat=cvMat(3,3,CV_64FC1,move);
	CvMat rotateMat=cvMat(3,3,CV_64FC1,rotate);
	CvMat* result=cvCreateMat(3,3,CV_64FC1);
	cvMatMul(&moveMat,&rotateMat,result);
	return result;
}

CvMat* getWorldToRobotMat(RobotPosition pos){
	CvMat* inverseMat=getRobotToWorldMat(pos);
	CvMat* resultMat=cvCreateMat(3,3,CV_64FC1);
	cvInv(inverseMat, resultMat, CV_LU);
	return resultMat;
}

void convertRobotToWorld(double *x, double *y, RobotPosition pos){
	int coordinates[]={*x, *y, 1};
	CvMat posMat=cvMat(3,1,CV_64FC1,coordinates);
	CvMat* result=cvCreateMat(3,1,CV_64FC1);
	cvMatMul(getRobotToWorldMat(pos),&posMat,result);
	*x =cvmGet(result,0,0);
	*y=cvmGet(result,1,0);
}

void convertWorldToRobot(double *x, double *y, RobotPosition pos){
	int coordinates[]={*x, *y, 1};
	CvMat posMat=cvMat(3,1,CV_64FC1,coordinates);
	CvMat* result=cvCreateMat(3,1,CV_64FC1);
	cvMatMul(getWorldToRobotMat(pos),&posMat,result);
	*x =cvmGet(result,0,0);
	*y=cvmGet(result,1,0);
}

void convertRobotToWorld(double *x, double *y){
	convertRobotToWorld(x,y,RobotPosition::getInstance());
}

void convertWorldToRobot(double *x, double *y){
	convertWorldToRobot(x,y,RobotPosition::getInstance());
}