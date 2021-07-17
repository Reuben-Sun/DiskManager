#include <iostream>
using namespace std;

int A[3][4];
//A[0]是超级快
//A[n][0]用来存放栈指针（就是现在这个组里有几个空闲块）
//A[n][n]用来存放块号

int pointer;    //指针，用来指示现在谁是超级快

void show(){    //展示
    cout << "--------空闲块---------" << endl;
    for(int i = pointer; i < 3; i++){
        cout << "第" << i+1 << "组，空闲块数：" << A[i][0] << endl;
        for(int j = A[i][0] ; j > 0; j--){
            cout << "空闲块号：" << A[i][j] << endl;
        }
    }
    cout << "----------------------" << endl;
}

void allocate(int _len){    //分配，就是按顺序删掉空闲块
    for(int i = 0; i < _len; i++){
        if(pointer >= 3){
            cout << "空间已空，分配失败" << endl;
            return;
        }
        if(A[pointer][0] <= 0){
            pointer++;
        }
        else{
            int num = A[pointer][0];
            cout << "空闲块" << A[pointer][num] << "已被分配" <<endl;
            A[pointer][0]--;
            if(A[pointer][0] <= 0){
                pointer++;
            }
        }
    }
}

void recovery(int _id){    //回收，就是向里面插入新的空闲块
    if(pointer >= 3){
        pointer--;
    }
    if(pointer < 0){
        cout << "空心块过多，回收失败！" << endl;
        return;
    }
    if(A[pointer][0] < 3){     //如果这个组还没满了
        A[pointer][0]++;
        int num = A[pointer][0];
        A[pointer][num] = _id;
        cout << "空闲块" << A[pointer][num] << "已被回收" <<endl;
    }
    else{
        pointer--;
        if(pointer < 0){
            cout << "空心块过多，回收失败！" << endl;
            return;
        }
    }

}

int main() {
    //初始化空闲块
    pointer = 0;
    A[0][0] = 3;    //初始空闲块数
    A[0][1] = 1;
    A[0][2] = 2;
    A[0][3] = 3;
    A[1][0] = 3;    //初始空闲块数
    A[1][1] = 4;
    A[1][2] = 5;
    A[1][3] = 6;
    A[2][0] = 3;    //初始空闲块数+1，因为是最后一个
    A[2][1] = 0;    //用0表示没有
    A[2][2] = 7;
    A[2][3] = 8;

    int index = 0;  //第几次命令
    char a;
    while (true) {
        cout << "-------成组链接法磁盘管理-------" << endl;
        cout << "输入q退出，输入a分配，输入r回收，输入s展示空余空间" << endl;
        cout << index++ << ": ";
        cin >> a;
        switch (a) {
            case 'q':
                goto L1;
            case 'a':
                cout << "分配，请输入长度:";
                int size;
                cin >> size;
                allocate(size);
                break;
            case 'r':
                cout << "回收，请输入块号:";
                int id;
                cin >> id;
                recovery(id);
                break;
            case 's':
                cout << "展示" << endl;
                show();
                break;
            default:
                break;
        }
    }
L1:
    cout << "退出成功！" << endl;
    return 0;
}
