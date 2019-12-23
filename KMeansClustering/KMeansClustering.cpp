// KMeansClustering.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
class Centroid {
private:
	//vector<double> distances; //distnce from centroid to all points
	vector<double> self_coord; //centroid's coordinates
	vector<vector<double>> my_points; //points associated with centroid
	//vector<double> my_distances; //distances between centroid's points and centroid
	vector<double> my_gradients;
	static double eta; //learning rate
	static double max;
public:
	Centroid(int dimensions);
	double getDistance(vector<double> &point);
	void addPoint(vector<double> &point);
	void clearPoints();
	void getGradient();
	void changePosition();
	vector<double> getCentroidPoint() { return self_coord; };
	void getClassPoints();
};
double Centroid::eta = 0.75;
double Centroid::max = 10.0;
Centroid::Centroid(int dimensions) {
	for (int i = 0; i < dimensions; i++) {
		self_coord.push_back((rand() / double(RAND_MAX)) * max);
	}
}
void Centroid::getClassPoints() {
	for (int i = 0; i < my_points.size(); i++) {
		cout << "(";
		for (int j = 0; j < my_points[i].size(); j++) {
			cout << my_points[i][j] << " ";
		}
		cout << "), ";
	}
}
double Centroid::getDistance(vector<double> &point) {
	double sum = 0.0;
	for (int i = 0; i < point.size(); i++) {
		sum += (self_coord[i] - point[i])*(self_coord[i] - point[i]);
	}
	return sqrt(sum);
}
void Centroid::addPoint(vector<double> &point) {
	my_points.push_back(point);
}
void Centroid::clearPoints() {
	my_points.clear();
}
void Centroid::getGradient() {
	my_gradients.clear();
	for (int i = 0; i < self_coord.size(); i++) {
		my_gradients.push_back(0.0);
		for (int j = 0; j < my_points.size(); j++) {
			my_gradients[i] += (self_coord[i] - my_points[j][i]) / getDistance(my_points[j]);
		}
		my_gradients[i] /= my_points.size();
	}
}
void Centroid::changePosition() {
	for (int i = 0; i < self_coord.size(); i++) {
		self_coord[i] -= (my_gradients[i] * eta);
	}
}
class Data {
private:
	vector<Centroid> centroids;
	vector<vector<double>> dataPoints;
	static int max;
public:
	Data(int centroidNum, vector<vector<double>> &data);
	void classifyPoints();
	void changeCentroids();
	void displayCentroids();
	void displayCentroid_Points();
	double classifyNewPoint(vector<double> &point);
};
Data::Data(int centroidNum, vector<vector<double>> &data) {
	for (int i = 0; i < centroidNum; i++) {
		centroids.push_back(Centroid(data[i].size()));
	}
	for (int i = 0; i < data.size(); i++) {
		dataPoints.push_back(data[i]);
	}
}
double Data::classifyNewPoint(vector<double> &point){
	vector<double> storeDistances;
	for (int j = 0; j < centroids.size(); j++) {
		storeDistances.push_back(centroids[j].getDistance(point));
	}
	double min = storeDistances[0];
	int pos = 0;
	for (int k = 1; k < storeDistances.size(); k++) {
		if (storeDistances[k] < min) {
			min = storeDistances[k];
			pos = k;
		}
	}
	return pos;
}
void Data::displayCentroids() {
	vector<vector<double>> storePoints;
	for(int i = 0; i < centroids.size(); i++) {
		storePoints.push_back(centroids[i].getCentroidPoint());
	}
	for (int j = 0; j < storePoints.size(); j++) {
		cout << "Centroid " << j << ": ";
		for (int i = 0; i < storePoints[j].size(); i++) {
			cout << storePoints[j][i] << " ";
		}
		cout << endl;
	}
}
void Data::displayCentroid_Points() {
	for (int i = 0; i < centroids.size(); i++) {
		cout << "Centroid " << i << ": ";
		centroids[i].getClassPoints();
		cout << endl;
	}
}
void Data::classifyPoints() {
	for (int i = 0; i < centroids.size(); i++) {
		centroids[i].clearPoints();
	}
	for (int i = 0; i < dataPoints.size(); i++) {
		vector<double> storeDistances;
		for (int j = 0; j < centroids.size(); j++) {
			storeDistances.push_back(centroids[j].getDistance(dataPoints[i]));
		}
		double min = storeDistances[0];
		int pos = 0;
		for (int k = 1; k < storeDistances.size(); k++) {
			if (storeDistances[k] < min) {
				min = storeDistances[k];
				pos = k;
			}
		}
		centroids[pos].addPoint(dataPoints[i]);
	}
}
void Data::changeCentroids() {
	for (int i = 0; i < centroids.size(); i++) {
		centroids[i].getGradient();
		centroids[i].changePosition();
	}
}
int main()
{
	double coordPoints[45][2] = {
	{1.5,4},
	{2.6,3},
	{1.7,1.5},
	{2.7,2.2},
	{1.4,3.2},
	{2.4,1.6},
	{1.6,2.2},
	{2.4,3.7},
	{2.1,2.9},
	{3.7,2.4},
	{1,2},
	{3.5,2.1},
	{3.9,3.2},
	{3.6,3.9},
	{8,4.0},
	{8.3,4.1},
	{7.6,3.7},
	{9.2,3.4},
	{8.7,2.9},
	{8.0,2.3},
	{6.7,2.2},
	{7.8,3.6},
	{10.0,3.0},
	{9.2,3.4},
	{7.7,2.8},
	{6.9,3.8},
	{7.1,3.3},
	{7.6,2.3},
	{9.2,2.7},
	{2.0,2.0},
	{6,8},
	{6.3,9.2},
	{5.8,8.2},
	{6.4,7.6},
	{4.7,7.1},
	{5.9,9.5},
	{4.8,9.2},
	{7.6,8.2},
	{6.1,6.7},
	{5.5,7.3},
	{4.6,8.2},
	{6.3,8.3},
	{6.6,8.7},
	{5.8,9},
	{5.4,8.7}
	};
	int dataNum = 45; //number of data points
	int dimensions = 2; //dimensions of points
	vector<vector<double>> data;
	for (int i = 0; i < dataNum; i++) {
		data.push_back(vector<double>());
		for (int j = 0; j < dimensions; j++) {
			data.back().push_back(coordPoints[i][j]);
		}
	}
	Data myData(3, data);
	for (int i = 0; i < 2000; i++) {
		myData.classifyPoints();
		myData.changeCentroids();
		myData.displayCentroids();
	}
	myData.displayCentroid_Points();
	vector<double> testPoint = { 2.0, 3.0 };
	double cat = myData.classifyNewPoint(testPoint);
	cout << "Point is part of " << cat << " category" << endl;
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
