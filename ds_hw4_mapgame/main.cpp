//
//  main.cpp
//  ds_cpp_practice
//
//  Created by Chang Chung Che on 2020/5/15.
//  Copyright © 2020 Chang Chung Che. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
//#include <stack>
#include <algorithm>
#include <iterator>

int escapemindis = -1;        //最短路徑
int firemindis = -1;

using namespace std;

struct node
{
    short d;
    short r;
    bool check;
    node* road[8];
};

//取得insert的地圖
pair<int, int> getmap(vector<vector<node> > &data, int length, int width) {
    int i, j;
    pair<int, int> pos;
    for (i = 0; i <= length + 1; i++) {
        vector<node> v1;
        for (j = 0; j <= width + 2; j++)
        {
            node n1;
            if (i == 0 || i == length + 1 || j == 0 || j == width + 1) {
                if (i == 0 && j == width + 2) {
                    n1.d = '\n';
                }
//                else if(i == length + 1 && j == width + 1) {     //修正多一項的問題
//                    v1.pop_back();
//                }
                else {
                    n1.d = 0;
                }
            }
            else
            {
                n1.d = getchar();
            }
            n1.r = 0;
            if (n1.d == '%') {              //儲存起始位置
                pos.first = i;
                pos.second = j;
            }
            v1.push_back(n1);
        }
        data.push_back(v1);
    }
    return pos;
}

//處理資料(1,輸出 2,轉換sym為int -1, 0, 1
vector<vector<node> > vecprocess(vector<vector<node> > &data, int control) {
    vector<vector<node> > data1;
    for (vector<vector<node> >::iterator it = data.begin(); it != data.end(); it++) {
        vector<node> ita = *it, itb;
        for (vector<node>::iterator it1 = ita.begin(); it1 != ita.end(); it1++) {
            node n1;
            switch (control)
            {
                case 1:                         //輸出元素編號
                    if (it1->d == '\n') {
                        cout << '\n';
                    }
                    else if(it1->d != '#') {
                        cout << setw(3) << (short)it1->d;
                    }
                    break;
                case 2:                         //轉換為-1, 0, 1
                    switch (it1->d)
                    {
                        case '+':
                            n1.d = 1;
                            break;
                        case '$':
                            n1.d = 0;
                            break;
                        case '%':
                            n1.d = -1;
                            break;
                        case '\n':
                            n1.d = '\n';
                            break;
                        case 0:
                            n1.d = '#';
                            break;
                        default:
                            break;
                    }
                    n1.r = 0;
                    itb.push_back(n1);
                    break;
                case 3:                         //輸出路徑編號
                    if (it1->d == '\n') {
                        cout << '\n';
                    }
                    else if(it1->d != '#') {
                        cout << setw(3) << (short)it1->r;
                    }
                    break;
                default:
                    break;
            }
        }
        if (control == 2) {
            data1.push_back(itb);
        }
    }
    cout << '\n';
    return data1;
}

//初始化二維vector。8個方向、road歸零、check歸零
void setdata(vector<vector<node> > &data, int length, int width) {
    int i, j;
    
    for (i = 1; i < length + 1; i++) {
        for (j = 1; j < width + 2; j++) {
            data[i][j].road[0] = &data[i-1][j];         //上
            data[i][j].road[1] = &data[i-1][j+1];       //右上
            data[i][j].road[2] = &data[i][j+1];         //右
            data[i][j].road[3] = &data[i+1][j+1];       //右下
            
            data[i][j].road[4] = &data[i+1][j];         //下
            data[i][j].road[5] = &data[i+1][j-1];       //左下
            data[i][j].road[6] = &data[i][j-1];         //左
            data[i][j].road[7] = &data[i-1][j-1];       //左上
            
            data[i][j].r = 0;
            data[i][j].check = false;
        }
    }
}

//設定road的編號，以相連的road拓展(黏菌)
void setroad(node* center, int num) {
    queue<node*> road;
    
    int i;
    for (i = 0; i < 8; i+=2) {
        if(center->road[i] != NULL && (center->road[i]->d == 0 || center->road[i]->d == -1)) {
            road.push(center->road[i]);
        }
    }
    
    center->r = num;
    while (!road.empty()) {
        if (!road.front()->check) {
            road.front()->check = true;
            setroad(road.front(), num);
        }
        road.pop();
    }
}

//計算角色逃脫所需的時間
void escapedis(node* center, int num){
    queue<node*> road;
    int i;
    for (i = 0; i < 8; i+=2) {              //只能走上下左右
        if (center->road[i] != NULL) {          //記錄最短時間
            if (center->road[i]->d == '#') {
                if (escapemindis == -1) {
                    escapemindis = num;
                }
                else if (num < escapemindis) {
                    escapemindis = num;
                }
            }
            if(center->road[i]->d == 0 || center->road[i]->d == -1) {
                road.push(center->road[i]);
            }
        }
    }
    center->r = num++;
    while (!road.empty()) {
        if (!road.front()->check || (road.front()->check && road.front()->r > num)) {   //若沒走過，或是路徑較短
            road.front()->check = true;
            escapedis(road.front(), num);
        }
        road.pop();
    }
}

//計算火蔓延時間
void firedis(node* center, int num) {
    queue<node*> road;
    int i;
    for (i = 0; i < 8; i++) {               //8個方向皆可
        if (center->road[i] != NULL) {
            if(center->road[i]->d == 0 || center->road[i]->d == -1) {
                road.push(center->road[i]);
            }
        }
    }
    
    center->r = num++;
    while (!road.empty()) {
        if (!road.front()->check || (road.front()->check && road.front()->r > num)) {
            road.front()->check = true;
            firedis(road.front(), num);
        }
        road.pop();
    }
}

int main() {
    int length = 0, width = 0;
    int firey = 0, firex = 0;
    int i, j;
    
    int p = 1;
    while (p)                                   //取得長寬、火焰資料
    {
        cout << "please insert data\n";
        cin >> length >> width;
        cin >> firey >> firex;
        
        p = 0;
        if (length > 20 || width > 20 || firey >= length || firex >= width)
        {
            cout << "error insert";
            p = 0;
        }
    }
    getchar();
    firex ++;
    firey ++;
    
    
    //prob.0
    vector<vector<node> > data;
    pair<int, int> position;
    position = getmap(data, length, width);     //取得地圖資料
    
    
    //-------prob.1
    data = vecprocess(data, 2);                 //轉換地圖 ('2'為symbol轉為0, 1, -1
    
    cout << "\n  [1] show th map:\n";
    vecprocess(data, 1);                        //print地圖 ('1'為單純int輸出
    setdata(data, length, width);               //初始化資料
    
    vector<vector<node> > data2, data3, data4;
    
    //data未知原因，原與新的data會互相影響
//    vector<vector<node> > data2 (data);
    
//    data3.assign(data.begin(), data.end());
    
//    data2.resize(data.size());
//    copy(data.begin(), data.end(), data2.begin());
    
    //(上述令法皆失敗，只好傻瓜複製) 拷貝data到data2、data3
    for (i = 0; i <= length + 1; i++) {
        vector<node> v1;
        for (j = 0; j <= width + 2; j++) {
            node n1;
            n1.d = data[i][j].d;
            n1.check = false;
            n1.r = 0;
            v1.push_back(n1);
        }
        data2.push_back(v1);
        data3.push_back(v1);
        data4.push_back(v1);
    }
    setdata(data2, length, width);    //初始化資料
    setdata(data3, length, width);
    setdata(data4, length, width);
    
    //-------prob.2
    cout << "====================================================\n";
    int num = 0;
    for (i = 1; i < length + 1; i++) {
        for (j = 1; j < width + 1; j++) {
            if (data[i][j].check == false && data[i][j].d != 1) {
                num++;
                setroad(&data[i][j], num);          //對每個位置做road拓展
            }
        }
    }
    
    cout << "\n  [2] show the map:\n";
    vecprocess(data, 3);                            //輸出路徑編號
    cout << "  The number of region is : " << num << "\n";
//    cout << "position of the charactor : " << position.first << ", " << position.second << '\n';
    cout << "====================================================\n";
    
    //-------prob.3
    cout << "\n  [3] show the escape map:\n";
    escapedis(&data2[position.first][position.second], 0);      //計算逃脫路徑時長
    data2[position.first][position.second].r = -1;
    vecprocess(data2, 3);            //輸出路徑編號
    cout << "  minimun escape path : " << escapemindis << "\n";
    cout << "====================================================\n";
    
    //-------prob.4
    cout << "\n  [4] show the fire map:\n";
    firedis(&data3[firey][firex], 0);                           //計算火焰蔓延時長
    data3[firey][firex].r = -1;
    vecprocess(data3, 3);            //輸出路徑編號
    
    int escapemin = -1;                                 //比較角色與火燄時間差，推論是否可以順利逃脫
    for (i = 1; i < length + 1; i++) {
        for (j = 1; j < width + 1; j++) {
            if (data2[i][j].r != 0) {
                data4[i][j].d = data2[i][j].r - data3[i][j].r;          //人-火，若<0 則人可逃出
            }
            else {
                data4[i][j].d = 0;
            }
            if (i == 1 || j == 1 || i == length || j == width) {
                if (data2[i][j].r != 0 && data4[i][j].d < 0) {
                    if (escapemin == -1) {
                        escapemin = data2[i][j].r;
                    }
                    else if (escapemin > data2[i][j].r) {
                        escapemin = data2[i][j].r;
                    }
                }
            }
        }
    }
//    vecprocess(data4, 1);            //輸出時間差
    cout << "  minimun escape path : " << escapemin << "\n";
    cout << "====================================================\n\n";
    
    return 0;
}
