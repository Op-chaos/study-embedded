/* 将窗口元素、消息处理函数封装在窗口中 */
struct windows
{
    BYTE currentFocus;
    ELEMENT element[ELEMENT_NUM];
    void (*messageFun) (BYTE keyValue);
    …
};

/* 消息处理函数 */
void messageFunction(BYTE keyValue)
{
    BYTE i = 0;
    /* 获得焦点元素 */
    while ( (element [i].ID!= currentFocus && (i < ELEMENT_NUM) )
        i++;
    if(i < ELEMENT_NUM)  /* "消息映射" */
    {
        switch(keyValue)
        {
            case OK:
                element[i].OnOk();
                break;
            case NO:
                element[i].OnNO();
                break;
        }
    }
}



