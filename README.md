IR
==

学习信息检索，以争实现其中的所有算法。

下一步加入token化以及研究更高效的倒排索引的数据结构

本周研究关于文本到token的处理过程。
跳表的压缩技术。

===========================================================
	倒排索引的建立过程：token化->语言处理->建立索引。
	beta版基于以下假设：
		输入：某个文件下多个文本(doc)，每个文本由多个单词(term)组成，每个单词间有且仅有一个空格。
		即简化token化，省略语言处理，直接建立索引。
	索引数据结构:
		struct Index
		{
			int num;			//索引包含doc的个数
			string term;		//索引的term
			List *node;			//索引包含的doc链表。
		};
		其包含操作：
			void InitIndex(Index *index)
			输入索引指针进行初始化，此过程会建立list表头，num初始化为0；
			int InsertIndex(int docID,Index *index)
			将docID插入index中，Index中的list的docID为升序。
			List * mergeIndex(Index *first,Index *second)
			输入两个index指针，返回其docID的交集
			List * OrIndex(Index *first,Index *second)
			输入两个index指针，返回其docID的并集。

	索引建立过程：
		读取文件下中的多个文本，对于每个文本，依次读取单词，此处即为term。
		对整个过程中读取到的term建立hash,映射至一个termid，方便Index操作。
		对于每读取到的term，向Index[termid]插入该文本(doc)的docID
	