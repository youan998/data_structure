#ifndef CREATE_TREE_H
#define CREATE_TREE_H
#include <iostream>
#include <cstring>  // 字符串处理函数 strlen, strtok, strstr 等函数所在头文件
#include <cstdio>   // 补充：用于 FILE, fopen, fgets, printf 等文件I/O函数
//树（森林）的双亲表示定义和算法
#define MAXLEN 100

typedef char elementType;

//树的结点结构
typedef struct pNode
{
	elementType data;   //结点数据域
	int parent;         //父节点索引

}PTNode;

//树的双亲表示存储结构
typedef struct pTree
{
	PTNode node[MAXLEN];   //树的结点数组
	int n;              //树中结点数
}pTree;


//初始化树
void initialTree(pTree &T)
{
	T.n=0;   //初始化树中结点数为0
}

//求祖先
bool getAncestor(pTree &T, elementType x)
{
	int w=0;
	elementType y;
	y=x;
	
	for(w=0;w<T.n;w++)
	{
		if(T.node[w].data==y)
		{
			w=T.node[w].parent;     //找到x的双亲节点
			y=T.node[w].data;
			std::cout<<y<<"\t";
			break;
		}
	}
	if(w>=T.n)    //x不在树中，返回false
		return false;
	
	             //继续求x的双亲节点的双亲节点
	while(w!=-1)
	{
		if(T.node[w].data==y)
		{
			w=T.node[w].parent;     //找到w的双亲节点
			y=T.node[w].data;
			std::cout<<y<<"\t";	
		}
		else
			w=(w+1)%T.n;
	}
	return true;
}

//求孩子
void getChildren(pTree &T, elementType x)
{
	int i,w;
	for(w=0;w<T.n;w++)     //找到x在结点数组中的下标
	{
		if(T.node[w].data==x)
			break;
	}
	if(w>=T.n)  //x不在树中
		return;
	for(i=0;i<T.n;i++)
	{
		if(T.node[i].parent==w)   //输出所有孩子节点
			std::cout<<T.node[i].data<<"\t";	
	}
	std::cout<<std::endl;
}

//先根遍历
int firstChild(pTree &T,int v)    //求下标为v的结点的第一个孩子的下标
{
	int w;
	if(v==-1)
		return -1;

	for(w=0;w<T.n;w++)
	{
		if(T.node[w].parent==v)
			return w;
	}
	return -1;
}
int nextSibling(pTree &T,int v,int w)  //求结点v的下标为w的孩子结点的下一个兄弟的下标
{
	int i;
	for(i=w+1;i<T.n;i++)
		if(T.node[i].parent==v)
			return i;
	return -1;
}
void preOrder(pTree &T,int v)//先根遍历以节点v为根的子树
{
	int w;
	std::cout<<T.node[v].data<<"\t";

	w=firstChild(T,v);
	while(w!=-1)
	{

		preOrder(T,w);
		w=nextSibling(T,v,w);	
	}
}


void preTraverse(pTree &T)//先根遍历整个树（森林）T
{
	int i;
	int visited[MAXLEN];
	for(i=0;i<T.n;i++)
	{
		visited[i]=0;	
	}
	    //遍历每个根节点（双亲为-1的结点）
	for(i=0;i<T.n;i++)
	{
		if(T.node[i].parent==-1)
			preOrder(T,i);
	}	
}

void postOrder(pTree &T,int v)//后根遍历以节点v为根的子树

{
	int w;
	w=firstChild(T,v);
	while(w!=-1)
	{
		postOrder(T,w);
		w=nextSibling(T,v,w);	
	}
	std::cout<<T.node[v].data<<"\t";   //访问根节点
}

void postTraverse(pTree &T)//后根遍历整个树（森林）T
{
	int i;
	int visited[MAXLEN];
	for(i=0;i<T.n;i++)
	{
		visited[i]=0;	
	}
	    //遍历每个根节点（双亲为-1的结点）
	for(i=0;i<T.n;i++)
	{
		if(T.node[i].parent==-1)
			postOrder(T,i);
	}
}

//打印树
void printTree(pTree &T)
{
	int i;
	std::cout<<"下标\t数据\t双亲"<<std::endl;
	for(i=0;i<T.n;i++)
		std::cout<<i<<"\t"<<T.node[i].data<<"\t"<<T.node[i].parent<<std::endl;
}

//孩子兄弟表示法的定义-----------------------------------------

//从文件创建树（双亲表示法）的函数-----------------------------------
    //孩子兄弟表示法的存储结构
typedef char elementType;

typedef struct csNode
{
	elementType data;
	struct csNode *firstChild, *nextSibling;
}csNode,*csTree;

//去掉字符串左边的空格
void strLTrim(char* str)
{
	int i,j;
	int n=0;
	n=strlen(str)+1;
	for(i=0;i<n;i++)
	{
		if(str[i]!=' ')  //找到第一个非空格字符的位置
			break;
	}
	    //把字符串左移，去掉左边空格
	for(j=0;j<n;j++)
	{
		str[j]=str[i];
		i++;
	}
}


//****************** 从文件创建树（双亲表示法）********************//
//* 函数功能：从文本文件创建树                                    *//
//* 参数：  char fileName[]：文件名                               *//
//* 返回值：pTree &T：生成的树                                    *//
//* 返 回 值：bool类型，true表示创建成功，false表示创建失败         *//
//* 函数名称：CreateTreeFromFile(const char fileName[], pTree &T)       *//
//* 主要步骤：从文件中读取树结构数据并建立双亲表示法的树             *//
//*******************************************************************//
int CreateTreeFromFile(const char fileName[], pTree &T)//从文件创建树（双亲表示法）
{
	FILE* pFile;     //文件指针变量
	char str[1000];  //用于存放文件读取的一行字符串
	char strTemp[10]; //临时字符串

    int i=0,j=0;


	pFile=fopen(fileName,"r");
	if(!pFile)
	{
		printf("打开文件%s失败！\n",fileName);
		return false;
	}
	
	while(fgets(str,1000,pFile)!=NULL)  //跳过前面的注释行
	{
		//去掉字符串左边的空格
		strLTrim(str);
		if (str[0]=='\n')  //空行，继续读取下一行
			continue;

		strncpy(strTemp,str,2);
		if(strstr(strTemp,"//")!=NULL)  //注释行
			continue;
		else  //不是空行或注释行，结束循环
			break;
	}

    //检查字符串str中是否包含"Tree or Forest"
	if(strstr(str,"Tree or Forest")==NULL)
	{
		printf("文件格式不正确！\n");
		fclose(pFile); //关闭文件
		return false;
	}


	//读取下一行数据字符串str
	while(fgets(str,1000,pFile)!=NULL)
	{
		//去掉字符串左边的空格
		strLTrim(str);
		if (str[0]=='\n')  //空行，继续读取下一行
			continue;

		strncpy(strTemp,str,2);
		if(strstr(strTemp,"//")!=NULL)  //如果是注释行，则继续读取下一行
			continue;		
		else  //如果是数据行，则跳出循环
			break;
	}

	//处理结点数据行		
	char* token=strtok(str," ");
	int nNum=0;	
	while(token!=NULL)
	{
		T.node[nNum].data=*token;
		T.node[nNum].parent=-1;       //暂时将双亲节点设为-1
		
		token = strtok( NULL, " ");
        
		nNum++;
	}
	
    //处理边的数据行
	int nP;  //父节点下标
	int nC;  //子节点下标

	elementType Nf,Ns; //父节点和子节点数据
	while(fgets(str,1000,pFile)!=NULL)
	{
		//去掉字符串左边的空格
		strLTrim(str);
		if (str[0]=='\n')  //空行，继续读取下一行
			continue;
		
		strncpy(strTemp,str,2);
		if(strstr(strTemp,"//")!=NULL)  //如果是注释行，则继续读取下一行
			continue;

		char* token=strtok(str," ");  //将str按空格分割，依次取出父节点和子节点
		
		if(token==NULL)  //如果没有数据，则退出
		{
			printf("文件数据格式错误！\n");
			fclose(pFile); //关闭文件
			return false;
		}
		Nf=*token;  //父节点数据
		
		token = strtok( NULL, " ");  //取出第二个字符串（子节点）
		if(token==NULL)  //如果没有数据，则退出
		{
			printf("文件数据格式错误！\n");
			fclose(pFile); //关闭文件
			return false;
		}

		Ns=*token;  //得到子节点数据
		   //查找父节点下标		
		for(nP=0;nP<nNum;nP++)
		{
			if(T.node[nP].data==Nf)  //在节点列表中查找父节点
				break;
		}
           //查找子节点下标		
		for(nC=0;nC<nNum;nC++)
		{
			if(T.node[nC].data==Ns)  //在节点列表中查找子节点
				break;
		}

		T.node[nC].parent=nP;        //nC的双亲节点为nP
	}

    T.n=nNum;  //设置树的结点数

	fclose(pFile); //关闭文件
	return true;
}

//返回结点下标为w的结点的下一个兄弟结点的下标
int next(pTree T,int w)  
{
	int i;
	for(i=w+1;i<T.n;i++)
	{
		if(T.node[w].parent==T.node[i].parent)
			return i;	
	}
	return -1;
}

//根据双亲表示法创建孩子兄弟表示法
void create(csNode *&T,pTree &T1,int v)
{
	int w;
	T=new csNode;
	T->data=T1.node[v].data;
	T->firstChild=NULL;
	T->nextSibling=NULL;
	w=firstChild(T1,v);  //找到v的第一个孩子
	if(w!=-1)
	{
		create(T->firstChild,T1,w);
	}
	
	w=next(T1,v);       //找到v的下一个兄弟
	if(w!=-1)
	{
		create(T->nextSibling,T1,w);
	}	
}

//根据双亲表示法创建孩子兄弟链表
void createCsTree(csNode *&T,pTree T1)
{
	int i;
	//找到T1的根节点
	for(i=0;i<T1.n;i++)
	{
		if(T1.node[i].parent==-1)   //双亲为-1的为根结点
			break;		
	}
	if(i<T1.n)
		create(T,T1,i);
}


//孩子兄弟表示法相关定义和算法-----------------------------------
#endif // CREATE_TREE_H