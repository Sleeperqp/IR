#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

struct list{
	int docID;
	struct list *next;
};
typedef struct list List;


struct Index
{
	int num;
	string term;
	List *node;
};
typedef struct Index Index;

void InitIndex(Index *index)
{
	index->num=0;
	//表头
	index->node=(List *)malloc(sizeof(List));
	index->node->docID=-1;
	index->node->next=NULL;
}

int InsertIndex(int docID,Index *index)
{
	List *Node = (List *)malloc(sizeof(List));
	Node->docID=docID;
	List *head = index->node;
	List *pre = NULL;

	while(head != NULL)
	{
		if( head->docID == docID)
			return -1;
		else if(head->docID < docID){
			pre=head;
			head=head->next;
		}
		else{
			break;
		}
	}
	index->num=(index->num)+1;
	if(pre == NULL)
	{
		head->next=Node;
	}
	else{
		Node->next=head;
		pre->next=Node;
	}
	return 1;
}



List * mergeIndex(Index *first,Index *second)
{
	List *mIndex=(List *)malloc(sizeof(List));
	mIndex->next=NULL;
	mIndex->docID=-1;
	List *tail=mIndex;

	List *firstNode = first->node;
	firstNode=firstNode->next;
	List *secondNode = second->node;
	secondNode=secondNode->next;

	while(firstNode!=NULL&&secondNode!=NULL)
	{
		if(firstNode->docID < secondNode->docID)
		{
			firstNode=firstNode->next;
		}
		else if(firstNode->docID > secondNode->docID)
		{
			secondNode=secondNode->next;
		}
		else{

			List *node = (List *)malloc(sizeof(List));
			node->docID=secondNode->docID;
			node->next=NULL;

			tail->next=node;
			tail=node;
			firstNode=firstNode->next;
			secondNode=secondNode->next;
		}
	}

	return mIndex;
}

List * OrIndex(Index *first,Index *second)
{
	List *mIndex=(List *)malloc(sizeof(List));
	mIndex->next=NULL;
	mIndex->docID=-1;
	List *tail=mIndex;

	List *firstNode = first->node;
	firstNode=firstNode->next;
	List *secondNode = second->node;
	secondNode=secondNode->next;

	while(firstNode!=NULL&&secondNode!=NULL)
	{
		List *node = (List *)malloc(sizeof(List));
		node->next=NULL;
		if(firstNode->docID < secondNode->docID)
		{
			node->docID=firstNode->docID;
			firstNode=firstNode->next;
		}
		else if(firstNode->docID > secondNode->docID)
		{
			node->docID=secondNode->docID;
			secondNode=secondNode->next;
		}
		else{
			node->docID=secondNode->docID;
			firstNode=firstNode->next;
			secondNode=secondNode->next;
		}
		tail->next=node;
		tail=node;
	}
	while(firstNode != NULL)
	{
		List *node = (List *)malloc(sizeof(List));
		node->next=NULL;
		node->docID=firstNode->docID;
		firstNode=firstNode->next;
		tail->next=node;
		tail=node;
	}
	while(secondNode != NULL)
	{
		List *node = (List *)malloc(sizeof(List));
		node->next=NULL;
		node->docID=secondNode->docID;
		secondNode=secondNode->next;
		tail->next=node;
		tail=node;
	}
	return mIndex;
}