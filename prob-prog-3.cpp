#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

bool isInsideCircle(double x, double y, double cx, double cy, double radius) // checks if point is inside circle
{
    return (pow(x - cx, 2) + pow(y - cy, 2)) <= pow(radius, 2);
}

// Monte-Carlo Method: Area of region / Bounding rectangle area = Number of points inside region / Total number of points
double monteCarloMethod(int no_samples, double cx[], double cy[], double radius[], int n)
{
    double minX = cx[0] - radius[0];
    double maxX = cx[0] + radius[0];
    double minY = cy[0] - radius[0];
    double maxY = cy[0] + radius[0];

    for (int i = 1; i < n; ++i)
    {
        minX = min(minX, cx[i] - radius[i]);
        maxX = max(maxX, cx[i] + radius[i]);
        minY = min(minY, cy[i] - radius[i]);
        maxY = max(maxY, cy[i] + radius[i]);
    }

    double boundingRectArea = (maxX - minX) * (maxY - minY);

    int inside = 0;
    for (int i = 0; i < no_samples; i++)
    {
        double x = minX + (double)rand() / RAND_MAX * (maxX - minX);
        double y = minY + (double)rand() / RAND_MAX * (maxY - minY);

        for (int j = 0; j < n; j++)
        {
            if (isInsideCircle(x, y, cx[j], cy[j], radius[j]))
            {
                inside++;
                break;
            }
        }
    }

    return ((double)inside / no_samples) * boundingRectArea;
}

int main()
{
    srand(time(0));
    double cx[3] = {2.0, 2.0, 2.0};
    double cy[3] = {2.0, 4.0, 0.0};
    double radius[3] = {2.0, 1.0, 1.0};
    // The circles are centered at: [2,2] with radius 2; [2,4] with radius 1; [2,0] with radius 1

    for (int no_samples = 10; no_samples <= 1000; no_samples += 10)
    {
        cout << "Number of samples: " << no_samples << " & Area of region: " << monteCarloMethod(no_samples, cx, cy, radius, 3) << endl;
    }

    return 0;
}