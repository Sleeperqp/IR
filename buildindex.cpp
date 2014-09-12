#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <fstream> 
#include <map>
#include <string>
#include <vector>
#include "index.h"
#include "printIndex.h"
#define IndexMax 100010
using namespace std;

map<string ,int >hash;
Index indexs[IndexMax];
int main()
{
	//读取整个文件夹下的文件
	DIR *dp;
	struct dirent *dirp;
	if( (dp=opendir("C:/Users/sleeper/Documents/code/C++/doc") )==NULL )
		perror("open dir error");
	vector<std::string> filename;
	while( (dirp=readdir(dp) )!=NULL )
	{
		//cout<<dirp->d_name<<endl;
		if(dirp->d_name[0]!= '.')				//去掉. 与 ..
			filename.push_back(dirp->d_name);
	}
	closedir(dp);

	//Init Indexs
	for (int i = 0; i < IndexMax; ++i)
	{
		InitIndex(indexs+i);
	}
	int term=1;
	int DocID=1;
	string str;
	for (int i = 0; i < (int)filename.size(); ++i,DocID++)
	{
		string path="./doc/"+filename[i];
		cout<<path<<endl;

		ifstream fin((char *)path.c_str());
		while(fin>>str)
		{
			cout<<"\t\t"<<str<<endl;
			if(hash[str]==0)
			{
				indexs[term].term=str;
				hash[str]=term++;
			}
			//将DocID插入Index中
			cout<<"\t\t"<<hash[str]<<endl;
			InsertIndex(DocID,indexs+hash[str]);
		}
	}

	printIndex(term,indexs);

	cout<<"#####################################################"<<endl;
	List *tmp = OrIndex(indexs+4,indexs+8);


	tmp=tmp->next;
	while(tmp != NULL)
	{
		cout<<tmp->docID<<endl;
		tmp=tmp->next;
	}

	system("PAUSE");
	return 0;
}