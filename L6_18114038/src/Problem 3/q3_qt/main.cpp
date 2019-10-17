#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <set>
#include <vector>
#include <queue>

using namespace std;

bool intersect(Segment* seg1, Segment* seg2, float* x, float *y)
{
    if (seg1->m == seg2->m)
    {
        return false;
    }
    else
    {
        float m1,m2,c1,c2;
        m1 = seg1->m;
        c1 = seg1->c;
        m2 = seg2->m;
        c2 = seg2->c;
        *x = (c2-c1)/(m1-m2);
        *y = m1*(*x) + c1;
        if (seg1->check(*x,*y) && seg2->check(*x,*y))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}


void linearFit(float* x,float* y,int n, float* a, float* b)
{
    float sumx = 0,sumy = 0;
    for (int i = 0; i < n; ++i)
    {
        sumx += x[i];
        sumy += y[i];
    }


    float ybar = sumy/n;
    float xbar = sumx/n;

    float m = 0;
    float temp = 0;
    for (int i = 0; i < n; ++i)
    {
        m += (x[i] - xbar)*(y[i]-ybar);
        temp += (x[i] - xbar) * (x[i] - xbar);
    }

    *a = m/temp;
    *b = ybar - (*a) * xbar;
}

int main(int argc, char *argv[])
{
    int n;
        cout << "Enter the number of lines : ";
        cin >> n;
        Segment** segments = new Segment*[n];

        priority_queue <Vertex, vector<Vertex> , CompareQueue> que;
        cout << "Enter the coordinates space separated" << endl;
        for (int i = 0; i < n; ++i)
        {
            float x1,y1,x2,y2;
            cin >> x1 >> y1 >> x2 >> y2;
            segments[i] = new Segment(x1,y1,x2,y2);
            que.push(*(segments[i]->left));
            que.push(*(segments[i]->right));
        }

        set<Vertex,CompareSet> output;
        set<Segment*> active;

        while(que.empty() == false)
        {
            Vertex v = que.top();
            if (v.isLeft == true)
            {
                Segment* curr = (Segment*)v.segment;
                for (auto it = active.begin() ; it != active.end() ; ++it)
                {
                    Segment* temp = *it;
                    float x,y;
                    bool intersection = intersect(curr, temp,&x,&y);
                    if (intersection)
                    {
                        Vertex ins(x,y);
                        output.insert(ins);
                    }
                }
                active.insert((Segment*)v.segment);
            }
            else
            {
                active.erase((Segment*)v.segment);
            }
            que.pop();
        }

        cout << "No. of intersection points: "<< output.size() << endl;
        for (auto it = output.begin(); it != output.end(); it++)
        {
            cout << "(" << it->x << "," << it->y << ")" << endl;
        }

        int n2 = output.size();
        float* x = new float[n2];
        float* y = new float[n2];
        int i = 0;
        for (auto it = output.begin(); it != output.end(); it++)
        {
            x[i] = it->x;
            y[i] = it->y;
            i++;
        }

        float a;
        float b;

        linearFit(x,y,n2,&a,&b);

//        cout << "Linear Fit : " << a << "x + " << b << endl;



    QApplication app(argc, argv);
    MainWindow w(nullptr,x,y,n,n2,segments,a,b);
    w.show();
    return app.exec();
}
