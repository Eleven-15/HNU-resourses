
void bomb()
{
}

void phase_1()
{
    string s_ori = "I am for medical liability at the federal level.";
    string s_input;
    scanf("%s", &s_input);
    if (strings_not_equal(s_input, s_ori))
        bomb();
}

void phase_2()
{
    int m[6];
    scanf("%d %d %d %d %d %d", &m[0], &m[1], &m[2], &m[3], &m[4], &m[5]);
    if (m[0] != 0)
        bomb();
    if (m[1] != 1)
        bomb();
    for (int i = 2; i <= 5; i++)
    {
        int temp = m[i - 1] + m[i - 2];
        if (temp != m[i])
            bomb();
    }
}

void phase_3()
{
    int n;
    char c;
    int m;
    if (scanf("%d %c %d", n, c, m) <= 2)
        bomb();
    if (n > 7)
        bomb();
    char temp;

    switch (n)
    {
    case 0:
        if (m != 0x80)
            bomb();
        temp = 0x64;
        break;
    case 1:
        if (m != 0x135)
            bomb();
        temp = 0x6f;
        break;
    case 2:
        if (m != 0x348)
            bomb();
        temp = 0x67;
        break;
    case 3:
        if (m != 0x16d)
            bomb();
        temp = 0x6b;
        break;
    case 4:
        if (m != 0x1d7)
            bomb();
        temp = 0x75;
        break;
    case 5:
        if (m != 0x31b)
            bomb();
        temp = 0x72;
        break;
    case 6:
        if (m != 0x204)
            bomb();
        temp = 0x6e;
        break;
    case 7:
        if (m != 0xb0)
            bomb();
        temp = 0x6f;
        break;
    }
    if (temp != c)
        bomb();
}

int func4(int n, int x)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return x;
    return (result(n - 1, x) + result(n - 2, x) + x);
}

void phase_4()
{
    int check, x;
    if (scanf("%d %d", check, x) != 2)
        bomb();
    if (x <= 1)
        bomb();
    if (x > 4)
        bomb();
    if (func4(9, x) != check)
        bomb();
}
void phase_5()
{
    string s;
    scanf("%s", s);
    if (string_length(s) != 6)
        bomb();
    int total = 0;
    for (int i = 0; i < 6; i++)
    {
        total += [s[i] & 0xf];
    }
    if (total != 0x38)
        bomb();
}

void phase_6()
{
    int a[6];
    scanf("%d %d %d %d %d %d", &a[0], &a[1], &a[2], &a[3], &a[4], &a[5]);

    //  第一阶段：合规性检验
    if (a[0] > 6)
        bomb();
    for (int i = 1; i < 6; i++)
    {
        if (a[i] > 6)
            bomb();
        for (int j = i; j < 6; j++)
        {
            if (a[j] == a[i - 1])
                bomb();
        }
    }

    // 第二阶段：排序
    struct node
    {
        int data;
        int number;
        node *next;
    } struct node head;

    for (int i = 0; i < 6; i++)
    {
        if (a[i] > 1) // 实际上这句可以不要，放这里可以看得更清晰一点
        {
            for (int j = 1; j < a[i]; j++)
            {
                head = head->next;
            }
            b[i] = &head;
        }
    }

    // 第三阶段：复写下一状态
    *b[0]->next = *b[1];
    *b[1]->next = *b[2];
    *b[2]->next = *b[3];
    *b[3]->next = *b[4];
    *b[4]->next = *b[5];

    // 第四阶段：检验数据域递增性
    struct node *head;
    for (int i = 5; i > 0; i--)
    {
        if (head->data > head->next->data)
            bomb();
    }
}

int fun7(int *x, int input)
{
    if (x == 0)
        return -1;
    if (*x > input)
        return 2 * fun7(x + 4, input); // 在左孩子中寻找
    else
    {
        if (*x == input) // 寻找到了
            return 0;
        else                                   //*x<input
            return 2 * fun7(x + 8, input) + 1; // 在右孩子中寻找
    }
}

void secret_phase()
{
    readline();
    long input = strtol(readline(), 0x0, 0xa);
    if (input > 1000)
        bomb();
    if (fun7(0x804c088, input))
        bomb();
}
