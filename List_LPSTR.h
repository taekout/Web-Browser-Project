#ifndef		LIST_LPSTR_H__
#define		LIST_LPSTR_H__
/*
	설계를 변화시킬 것..
	malloc(CList) ==> X
	malloc(struct _list) ==> O

  POSITION 을 이용한 접근 메카니즘 구현
  typedef	PVOID	POSITION;
*/
class List
{
	char	*key;
	class List	*prev,	*next;
	class List	*Head,	*Tail;   // static 화시키든가 할 수 있으면 더 나을텐데...
								 // But static 화 시키면 연결리스트 오브젝트를 한개만 선언 가능!
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

	//	Browser 용 List Method
	char *	GetPosURL(int	nPos);
	int		DeleteFromPos(int	nPos);
};

// 주의!  List 그 자체적으로 포인터 변수로 선언됨..
typedef	List * PList;







#endif