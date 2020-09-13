/******************************************
/* 函数名称: MessageBox
/* 功能说明: 弹出式对话框,显示提醒用户的信息
/* 参数说明: lpStr --- 提醒用户的字符串输出信息
/* TYPE --- 输出格式(ID_OK = 0, ID_OKCANCEL = 1)
/* 返回值: 返回对话框接收的键值,只有两种 KEY_OK, KEY_CANCEL
******************************************/
typedef enum TYPE { ID_OK,ID_OKCANCEL }MSG_TYPE;
extern BYTE MessageBox(LPBYTE lpStr, BYTE TYPE)
{
    BYTE keyValue = -1;
    ClearScreen(); /* 清除屏幕 */
    DisplayString(xPos, yPos, lpStr, TRUE); /*显示字符串*/

    /* 根据对话框类型决定是否显示确定、取消 */
    switch (TYPE)
    {
    case ID_OK:
        DisplayString(13,yPos+High+1, " 确定 ", 0);
        break;
    case ID_OKCANCEL:
        DisplayString(8, yPos+High+1, " 确定 ", 0);
        DisplayString(17,yPos+High+1, " 取消 ", 0);
        break;
    default:
        break;
    }

    DrawRect(0, 0, 23, yPos+High+16+4); /* 绘制外框 */
    /* MessageBox是模式对话框，阻塞运行，等待按键 */
    while( (keyValue != KEY_OK) || (keyValue != KEY_CANCEL) )
    {
        keyValue = getSysKey();
    }
    /* 返回按键类型 */
    if(keyValue== KEY_OK)
    {
        return ID_OK;
    } else {
        return ID_CANCEL;
    }
}