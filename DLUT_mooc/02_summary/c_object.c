#include <stdio.h>
#include <string.h>
#define MENU_NUM 3

void OkFun1();
void CancelFun1();
void OkFun2();
void CancelFun2();

/* 将菜单的属性和操作“封装”在一起，声明菜单项的“类” */
typedef struct tagSysMenu
{
    char *text; /* 菜单的文本 */
    int xPos; /* 菜单在LCD上的x坐标 */
    int yPos; /* 菜单在LCD上的y坐标 */
    void (*onOkFun)(); /* 在该菜单上按下ok键的处理函数指针 */
    void (*onCancelFun)(); /* 在该菜单上按下cancel键的处理函数指针 */
}SysMenu;

/* 用结构体数组来实现每一个菜单项 */
static SysMenu menu[MENU_NUM] =
{
    { "menu1", 0, 48, OkFun1, CancelFun1 } ,  // 后两项真实函数名
    { "menu2", 7, 48, OkFun2, CancelFun2 } ,
    { "menu3", 1, 48, OkFun1, CancelFun2 }
};

int currentFocusMenu = 0;

void OkFun1()
{
    printf("1 执行OK功能！\n");
}

void CancelFun1()
{
    printf("1 执行cancel功能！\n");
}

void OkFun2()
{
    printf("2 执行OK功能！\n");
}

void CancelFun2()
{
    printf("2 执行cancel功能！\n");
}

/* 按下OK键 */
void onOkKey()
{
    menu[currentFocusMenu].onOkFun();
}
/* 按下Cancel键 */
void onCancelKey()
{
    menu[currentFocusMenu].onCancelFun();
}



void main()
{
    for (int i = 0; i < 3; i++) {
        currentFocusMenu = i;
        onOkKey();
        onCancelKey();
    }
}
