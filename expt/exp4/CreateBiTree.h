#ifndef CREATEBITREE_H  
#define CREATEBITREE_H      
#define NODENUM  100       //定义最大结点数
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

// 二叉树节点定义
typedef char elementType;
typedef struct btNode {
    elementType data;
    struct btNode *lChild, *rChild;
} btNode;

typedef char eleType;

// 队列定义（简单版本）
typedef struct {
    btNode* data[100];
    int front, rear;
} seqQueue;

// 队列操作函数
void initialQueue(seqQueue *Q) { Q->front = Q->rear = 0; }
void enQueue(seqQueue *Q, btNode *x) { Q->data[Q->rear++] = x; }
int queueEmpty(seqQueue Q) { return Q.front == Q.rear; }
void getFront(seqQueue Q, btNode* &x) { x = Q.data[Q.front]; }
void outQueue(seqQueue *Q, btNode* &x) { x = Q->data[Q->front++]; }
void strLTrim(char* str);  //申明删除字符串左边空格

//先序层次遍历，BFS--因为结构定义及运算实现的次序关系，临时放在此处
void hieTraverse(btNode *T)
{
    btNode *p;  
    seqQueue Q;
    initialQueue(&Q);
    enQueue(&Q,T);
    while(!queueEmpty(Q))
    {
        getFront(Q,p);//获取队头元素
        cout<<p->data<<" ";         //访问根结点。打印当前结点元素值，替代visit(T)函数
        if(p->lChild)
            enQueue(&Q,p->lChild);
        if(p->rChild)
            enQueue(&Q,p->rChild);
        outQueue(&Q,p); //出队
    }
}

//键盘交互创建二叉树开始-------------------------------------------------------------------------
//键盘交互递归创建二叉树子树函数
void createSubTree(btNode *&p, int k)
{
    //k=1--左子树；k=2--右子树
    btNode *s;
    elementType x;
    cout<<"请输入结点元素数值，'/'表示无子树，x=";
    cin>>x;
    if(x!='/')
    {
        s=new btNode;
        s->data=x;
        s->lChild=NULL;
        s->rChild=NULL;
        if(k==1)
            p->lChild=s;     //s接到p的左孩子
        if(k==2)
            p->rChild=s;     //s接为p的右孩子
        createSubTree(s,1);  //递归创建s的左子树
        createSubTree(s,2);  //递归创建s的右子树    
    }
}

//键盘交互创建二叉树主控函数
void createBTConsole(btNode *&T)
{
    btNode *p;
    elementType x;
    cout<<"请按先序序列输入二叉树结点，（‘/’表示无子树）:"<<endl;
    cout<<"请输入结点元素数值，'/'表示无子树，x=";
    cin>>x;
    if(x=='/')
    {
        T = NULL; // 增加容错：如果是空树也要赋NULL
        return;    //空树，退出
    }
    T=new btNode;
    T->data=x;
    T->lChild=NULL;
    T->rChild=NULL;

    createSubTree(T,1);    //创建根结点的左子树
    createSubTree(T,2);    //创建根结点的右子树
}
//键盘交互创建二叉树开始-------------------------------------------------------------------------

//键盘交互完全二叉树方式创建二叉树开始-------------------------------------------------------------------------
void getCompleteArr(elementType *arr, int &num)
{
        //完全二叉树顺序存储方式创建二叉链表结构二叉树
        //缺少的结点数值用'/'代替
        //用'#'结束结点输入
        //arr为结点数组
        //num返回实际结点数
    elementType x;
    int i=1;   //arr[0]单元不用
    num=0;
    cout<<"请按完全二叉树方式输入二叉树结点，‘/’表示缺少结点，'#'结束输入。"<<endl;
    cout<<"请输入结点元素数值，'/'表示缺少结点，'#'结束输入，x=";
    cin>>x;
    while(x!='#')
    {
        *(arr+i)=x;
        i++;
        num++;

        cin>>x;
    }
}
//从完全二叉树顺序存储方式的数组创建二叉树
void createBtArr(btNode* &T, elementType* InArr, int i, int n)
{
    //T--为根结点指针
    //InArr--为按完全二叉树存储的树的结点数组
    //i--当前结点序号
    //n--二叉树结点总数
    
    // 必须明确给T赋空值，否则会产生野指针导致遍历崩溃
    if(i > n || InArr[i] == '/') 
    {
        T = NULL;
        return;
    }
    
    // 有效数据创建结点
    T=new btNode;       //创建根结点
    T->data=InArr[i];   //结点赋值
    T->lChild=NULL;
    T->rChild=NULL;
    
    createBtArr(T->lChild, InArr, 2*i, n);    //递归创建T的左子树
    createBtArr(T->rChild, InArr, 2*i+1, n);  //递归创建T的右子树
}
//键盘交互完全二叉树方式创建二叉树结束-------------------------------------------------------------------------


//数据文件创建二叉树开始-------------------------------------------------------------------------
//从文本文件数据读入到数组中，同时返回实际结点数量
bool ReadFileToArray(const char fileName[], char strLine[NODENUM][3], int & nArrLen)
{
    FILE* pFile;      //定义二叉树的文件指针
    char str[1000];   //存放读出一行文本的字符串
    char strTemp[10]; //判断是否注释行

    pFile=fopen(fileName,"r");
    if(!pFile)
    {
        cout<<"错误：文件"<<fileName<<"打开失败。"<<endl;
        return false;
    }

    while(fgets(str,1000,pFile)!=NULL)  //跳过空行和注释行
    {
           //删除字符串左边空格
        strLTrim(str);
        if (str[0]=='\n')               //空行，继续读取下一行
            continue;

        strncpy(strTemp,str,2);
        strTemp[2] = '\0'; // 增加安全截断
        if(strstr(strTemp,"//")!=NULL)  //跳过注释行
            continue;
        else                            //非注释行、非空行，跳出循环
            break;
    }
            //循环结束，str中应该已经是二叉树数据标识"BinaryTree"，判断文件格式
    if(strstr(str,"BinaryTree")==NULL)
    {
        printf("错误：打开的文件格式错误！\n");
        fclose(pFile);           //关闭文件
        return false;
    }

    nArrLen=0;     //数组行号初始化为0
    while(fgets(str,1000,pFile)!=NULL)
    {
            //删除字符串左边空格
        strLTrim(str);
        if (str[0]=='\n')  //空行，继续读取下一行
            continue;
        
        strncpy(strTemp,str,2);
        strTemp[2] = '\0';
        if(strstr(strTemp,"//")!=NULL)  //注释行，跳过，继续读取下一行
            continue;

        char* token=strtok(str," \r\n");   // 以空格和换行符为分隔符，更加安全
        if(token==NULL)  //分割为空串，失败退出
        {
            printf("错误：读取二叉树结点数据失败！\n");
            fclose(pFile); //关闭文件
            return false;
        }
        
        strLine[nArrLen][0]=*token;  //获取结点数据
        token = strtok( NULL, " \r\n");  //读取下一个子串，即此结点的左子树信息
        if(token==NULL) 
        {
            printf("错误：读取二叉树结点数据失败！\n");
            fclose(pFile); 
            return false;
        }
        strLine[nArrLen][1]=*token;  //获取此结点的左子树信息数据
        
        token = strtok( NULL, " \r\n");  //读取下一个子串，即此结点的右子树信息
        if(token==NULL) 
        {
            printf("错误：读取二叉树结点数据失败！\n");
            fclose(pFile); 
            return false;
        }
        strLine[nArrLen][2]=*token;  //获取此结点的右子树信息数据

        nArrLen++;  //数组行号加1   
    }

    fclose(pFile); //关闭文件
    return true;
}


//从数组创建二叉树--数组中保存的是二叉树的先序序列，及每个结点的子树信息
bool CreateBiTreeFromFile(btNode* & pBT, char strLine[NODENUM][3],int nLen, int & nRow)
{
    if((nRow>=nLen) || (nLen==0)) {
        pBT = NULL; // 同样增加容错赋空
        return false;  
    }

    //根据数组数据递归创建子树
    pBT=new btNode;
    pBT->data=strLine[nRow][0];
    pBT->lChild=NULL;
    pBT->rChild=NULL;
    
    int nRowNext=nRow;  //保留本次递归的行号    

    if(strLine[nRowNext][1]=='1')  //当前结点有左子树，递归创建左子树，读下一行数据
    {
        nRow++;
        CreateBiTreeFromFile(pBT->lChild, strLine,nLen,nRow);
    }

    if(strLine[nRowNext][2]=='1')  //当前结点有右子树，递归创建右子树，读下一行数组
    {
        nRow++;
        CreateBiTreeFromFile(pBT->rChild, strLine,nLen,nRow);       
    }

    return true;
}
//数据文件创建二叉树结束------------------------------------------------------------------------

//删除字符串、字符数组左边空格
void strLTrim(char* str)
{
    int i,j;
    int n=0;
    n=strlen(str)+1;
    for(i=0;i<n;i++)
    {
        if(str[i]!=' ')  //找到左起第一个非空格位置
            break;
    }
    //以第一个非空格字符为首字符移动字符串
    if (i > 0) {
        for(j = 0; i < n; j++, i++) 
        {
            str[j]=str[i];
        }
    }
}
#endif