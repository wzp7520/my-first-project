#include<iostream>
#include<stdlib.h>
#include<conio.h>
using namespace std;

// -------------------- 数据设计 --------------------
/*
    棋盘:
        board[i][j]表示坐标(i,j)的值
        0表示空地
        1表示黑子
        2表示白子
    如: board[3][6] = 1  表示(3,6)的位置是黑子
*/
int board[19][19];

// 表示当前回合数  偶数表示黑棋落子  奇数表示白棋落子
// 如: flag = 20 表示当前是第[20]次落子  由黑方落子
int flag;

// -------------------- 数据设计 --------------------


// -------------------- service --------------------
/*
    负责人: 张三
    功能: init: 初始化游戏数据
        将棋盘的值初始化为0
        当前回合设为黑棋(flag设为0)
    参数: void
    返回值: void
*/
void init();

/*
    *难点1
    负责人: 张三
    功能: isWin: 根据传入的坐标(board对应位置)和flag值 判断落点后是否获胜
    参数:
        x: 当前回合落子的x坐标
        y: 当前回合落子的y坐标
    返回值:
        0表示没有获胜
        1表示黑子胜利
        2表示白子胜利
*/
int isWin(int x, int y);

/*
    负责人: 张三
    功能: playerMove: 在指定位置落子
        如果board[x][y]是空地 则修改board[x][y]的值:改为相应颜色(flag对应颜色)        否则不操作
    参数:
        x: 当前回合落子的x坐标
        y: 当前回合落子的y坐标
    返回值:
        0表示落子失败 (棋盘已经有子)
        1表示落子成功

*/
int playerMove(int x, int y);
// -------------------- service --------------------



// -------------------- view --------------------
/*
    负责人: 张三
    功能: menuView: 展示选项, 玩家可以在这里选择进入游戏, 进入设置或退出游戏
        while(1){
            1. 展示选项
            2. 用户输入
            3. 根据输入进行对应处理
                进入游戏: 调用游戏界面函数gameView();
                进入设置: 打印敬请期待... 重新循环
                退出游戏: 调用exit(0);
        }
    参数: void
    返回值: void
*/
void menuView();

/*
    负责人: 张三
    功能: gameView_ShowBoard: 根据board数组 打印游戏棋盘
    参数: void
    返回值: void
*/
void gameView_ShowBoard();

/*
    负责人: 张三
    功能: winView:
        根据flag的值  打印游戏胜利界面  用户可以按任意键(使用getch函数)退出当前界面
    参数: void
    返回值: void
*/
void winView();

/*
    *难点2
    负责人: 张三
    功能: gameView: 游戏界面整合
        初始化游戏数据(调用函数init())
        while(1){
            打印游戏界面(调用函数gameView_ShowBoard())
            接收玩家坐标输入

            落子(调用落子函数playerMove())
                (如果落子失败 重新开始循环)

            判断游戏是否胜利(调用胜利判断函数isWin())
                (如果游戏胜利 调用胜利界面函数 然后结束当前界面)
            切换玩家(修改flag值)
        }
    参数: void
    返回值: void
*/
void gameView();
// -------------------- view --------------------

int main()
{
    menuView();
    return 0;
}

void init() {
    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19; j++) {
            board[i][j] = 0;
        }
    }
    int flag = 0;
}

int isWin(int x, int y)
{
    /* 只允许在此函数体内写代码，不允许修改任何外部声明 */
    if (x < 0 || x>19 || y < 0 || y>19) return 0;
    int who = board[x][y];              // 刚下的子颜色
    if (who == 0) return 0;             // 空位直接返回

    int dx[4] = { 1,0,1,1 };
    int dy[4] = { 0,1,1,-1 };             // 四个方向：横、竖、主对角、副对角

    for (int d = 0; d < 4; ++d)         // 每个方向单独统计
    {
        int cnt = 1;                    // 包含自身
        // 正向
        for (int k = 1; k < 5; ++k)
        {
            int nx = x + k * dx[d];
            int ny = y + k * dy[d];
            if (nx < 0 || nx>19 || ny < 0 || ny>19 || board[nx][ny] != who) break;
            ++cnt;
        }
        // 反向
        for (int k = 1; k < 5; ++k)
        {
            int nx = x - k * dx[d];
            int ny = y - k * dy[d];
            if (nx < 0 || nx>19 || ny < 0 || ny>19 || board[nx][ny] != who) break;
            ++cnt;
        }
        if (cnt >= 5) return who;       // 五子连线
    }
    return 0;                           // 未分胜负
}

int playerMove(int x, int y) {
    if (x < 0 || x > 19 || y < 0 || y > 19) {
        return 0;
    }
    if (board[x][y] == 0) {
        board[x][y] = (flag % 2 == 0) ? 1 : 2;
        return 1;
    }return 0;
}

void menuView() {
    int choice;
    system("cls");
    while (1) {
        printf("1.开始游戏\n");
        printf("2.游戏设置\n");
        printf("3.退出游戏\n");
        cin >> choice;
        switch (choice) {
        case 1:
            gameView();
            break;
        case 2:
            cout << ("还没做好^-^\n");
            _getch();
            break;
        case 3:
            cout << ("欢迎游玩\n");
            exit(0);
        default:
            cout << ("没有这个选项\n");
            _getch();
            break;
        }
    }
}

void gameView_ShowBoard() {
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if (board[i][j] == 0) {
                cout << "+ ";
            }
            else if (board[i][j] == 1) {
                cout << "● ";
            }
            else {
                cout << "○ ";
            }
        }cout << endl;
    }
}

void winView() {
    system("cls");
    if (flag % 2 == 0) {
        cout << "恭喜！黑棋胜利\n";
    }
    else {
        cout << "恭喜！白棋胜利\n";
    }
    _getch();
}

void gameView() {
    init();
    int x, y;
    int result;
    while (1) {
        system("cls");
        gameView_ShowBoard();
        if (flag % 2 == 0) {
            cout << "黑棋出发" << endl;
        }
        else {
            cout << "白棋出发" << endl;
        }cout << "请输入坐标(格式x空格y)";
        cin >> x >> y;
        if (playerMove(x, y)) {
            result = isWin(x, y);
            if (result != 0) {
                winView();
                break;
            }
            flag++;
        }
        else {
            cout << "落子失败" << endl;
            _getch();
        }
    }
}
