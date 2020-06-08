
#ifndef PATHC_H
#define PATHC_H



#include <vector>
#include <math.h>
#include <time.h>
#include <opencv2/opencv.hpp>

class pathC
{

public:
    int id;
    std::vector<double> Xs;
    std::vector<double> Ys;
    std::vector<clock_t> Clocks;
    double predictY(int x)
    {
        return k * x + b;
    }
    double predictX(int y)
    {
        return (y - b) / k;
    }
    cv::Point getPoint()
    {
        leastSquare();

        // ROS_INFO("k:%f\tb:%f", k, b);

        // int dx = 40 * cos(atan(k));
        // if(k>0)
        //     int x = Xs.back() + abs(dx);
        // if(k<0)
        //     int x = Xs.back() - abs(dx);
        // int y = predictY(x);
        int i = 0;
        if (Xs.size() > 5)
        {
            i = Xs.size() - 4;
        }
        if(abs(Xs[Xs.size()-1]-Xs[i])>abs(Ys[Ys.size()-1]-Ys[i]))
        {
            int x = Xs[Xs.size() - 1] + (Xs[Xs.size() - 1] - Xs[i]) / (Xs.size() - i - 1) + 20;
            int y = predictY(x);
            // ROS_INFO("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
            return cv::Point(x, y);
        }
        else
        {
            int y = Ys[Ys.size() - 1] + (Ys[Ys.size() - 1] - Ys[i]) / (Ys.size() - i - 1) + 30;
            int x = predictX(y);
            // ROS_INFO("YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY");
            return cv::Point(x, y);
        }
    }

    

    pathC(int _id)
    {
        id = _id;
    }
    ~pathC(){};
private:
    double k=1,b=1;
    void leastSquare()
    {
        double A = 0;
        double B = 0;
        double C = 0;
        double D = 0;

        for (int i = 0; i < Xs.size();i++)
        {
            A += Xs[i] * Xs[i];
            B += Xs[i];
            C += Xs[i] * Ys[i];
            D += Ys[i];
        }
        double temp = 0;
        
        if (temp = (Xs.size() * A - B * B))
        {
            k = (Xs.size() * C - B * D) / temp;
            b = (A * D - B * C) / temp;
        }else
        {
            k = 1;
            b = 0;
        }
        // k = -(1 / k);
        b = Ys[Ys.size() - 1] - k * Xs[Xs.size() - 1];
        ROS_INFO("k:%f\tb:%f", k, b);
    }
};




#endif 