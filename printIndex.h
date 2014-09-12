#include <iostream>
#include <string>
using namespace std;

void printIndex(int num,Index *index)
{
	cout<<"NUM"<<num<<endl;
	for (int i = 1; i < num; ++i)
	{
		List *Doc = (index[i]).node;
		cout<<index[i].term<<endl;
		Doc=Doc->next;
		while(Doc != NULL)
		{
			cout<<Doc->docID<<"\t";
			Doc=Doc->next;
		}
		cout<<endl;
	}
}