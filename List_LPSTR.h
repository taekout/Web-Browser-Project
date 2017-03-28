#ifndef		LIST_LPSTR_H__
#define		LIST_LPSTR_H__
/*
	���踦 ��ȭ��ų ��..
	malloc(CList) ==> X
	malloc(struct _list) ==> O

  POSITION �� �̿��� ���� ��ī���� ����
  typedef	PVOID	POSITION;
*/
class List
{
	char	*key;
	class List	*prev,	*next;
	class List	*Head,	*Tail;   // static ȭ��Ű�簡 �� �� ������ �� �����ٵ�...
								 // But static ȭ ��Ű�� ���Ḯ��Ʈ ������Ʈ�� �Ѱ��� ���� ����!
public:
	List(void);
	List( char *key );
	~List();

	char	* getKey(void);
	void	setKey(char *key);
	List	* getHead(void);
	List	* getTail(void);
	List	* getNext(void);
	List	* getPrev(void);
	void	init_LPSTR( char *key );
	int		allocSpace( int );
	List	* findNode( char *key );
	int		deleteNode( char *key );
	int		deleteNode( List *ptr );
	int		deleteNode();
	List	* insertNode( char *key , char *t );
	List	* insertNode( char *key , List *t );
	List	* insertNode( char *key );
	char	* popNode();
	void	printfNode();
	void	delete_All(void);

	//	Browser �� List Method
	char *	GetPosURL(int	nPos);
	int		DeleteFromPos(int	nPos);
};

// ����!  List �� ��ü������ ������ ������ �����..
typedef	List * PList;







#endif