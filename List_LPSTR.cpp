#include "List_LPSTR.h"




List::List() : key(NULL)
{
	Head = this;
	Tail = (PList)malloc(sizeof(List));
	Tail ->key = NULL;

	Head ->next = Tail;
	Head ->prev = Head;
	Tail ->next = Tail;
	Tail ->prev = Head;
}

List::List( char *key )   :   key(NULL)
{
	Head = this;
	Tail = (PList )malloc(sizeof(List));
	Tail ->key = NULL;

	Head ->next = Tail;
	Head ->prev = Head;
	Tail ->next = Tail;
	Tail ->prev = Head;
	insertNode( key );
}

List::~List()
{
	//	소멸자서 List 를 완전히 제거하므로...
	//	밖에서 이 클래스를 쓸 때 한 노드를 직접 delete 로 제거하면 안 되고,
	//	반드시 deleteNode 함수를 써야한다.
	List::delete_All();
	free(Tail);
}

char	*List::getKey(void)
{
	return	key;
}

void	List::setKey(char *key)
{
	List::key = (char *)malloc(strlen(key) + 1);
	::strcpy( List::key , key );
}

PList	List::getHead(void)
{
	return	Head;
}

PList	List::getTail(void)
{
	return	Tail;
}

PList	List::getNext(void)
{
	return	next;
}

PList	List::getPrev(void)
{
	return	prev;
}

void	List::init_LPSTR( char *key )
{
	List::key = (char *)malloc( ::strlen(key) + 1 );
	::strcpy(List::key , key);
}

int		List::allocSpace( int size )
{
	if( ( key = (char*)malloc( size )) == NULL )
	{
		printf("Memory allocation error!");
		return	0;
	}
	return	1;
}

List *	List::findNode( char *key )
{
	PList	s;
	s = Head ->next;
	while( strcmp(s ->key, key) != 0 && s != Tail )
		s = s ->next;
	return	s;
}

int		List::deleteNode( PList ptr )
{
	if( ptr == Head || ptr == Tail )
		return	NULL;
	ptr ->prev ->next = ptr ->next;
	ptr ->next ->prev = ptr ->prev;
	if( ptr ->key )
		free(ptr ->key);
	free(ptr);
	return	1;
}

//  전해진 문자열에 해당하는 나중에 들어간 것부터 일치하는 노드를 삭제
int		List::deleteNode( char *key )
{
	PList	s;
	s = List::findNode(key);
	if( s != Tail )    // if find
	{
		s ->prev ->next = s ->next;
		s ->next ->prev = s ->prev;
		if( s ->key )
			free(s ->key);
		free(s);
		return	1;
	}
	return	NULL;
}

int		List::deleteNode()
{
	PList	s;
	s = Head ->next;
	s ->next ->prev = Head;
	Head ->next = s ->next;
	free( s ->key );
	free(s);
	return	1;
}

List *	List::insertNode( char *key, char *t )
{
	PList	s;
	PList	i = NULL;
	s = List::findNode(t);
	if( s != Tail )       //  if find
	{
		i = (PList)malloc(sizeof(List));
		i ->key = (char *)malloc( strlen(key) + 1 );
		strcpy(i ->key, key);
		s ->prev ->next = i;
		i ->prev = s ->prev;
		s ->prev = i;
		i ->next = s;
		i ->Head = List::Head;
		i ->Tail = List::Tail;
	}
	return	i;
}

List *	List::insertNode( char *key, PList t )
{
	PList	i;
	if( t == Head )
		return	NULL;
	i = (PList )malloc(sizeof(List));
	i ->key = (char *)malloc( strlen(key) + 1 );
	strcpy(i ->key , key);
	t ->prev ->next = i;
	i ->prev  =  t ->prev;
	t ->prev  =  i;
	i ->next  =  t;
	i ->Head  =  List::Head;
	i ->Tail  =  List::Tail;
	return	i;
}

PList	List::insertNode( char *key )
{
	PList	i = ( PList )malloc(sizeof(List));
	i ->key = (char *)malloc( strlen(key) + 1 );
	strcpy(i ->key, key);

	Head ->next ->prev = i;		//  노드 연결
	i ->next = Head ->next;
	Head ->next = i;
	i ->prev  =  Head;

	i ->Head  =  List::Head;
	i ->Tail  =  List::Tail;

	return	i;
}

char *	List::popNode()
{
	PList	i = Head ->next;
	char *	result = i ->key ;
	
	i ->next ->prev   =   Head;
	Head ->next   =   i ->next;

	free(i);
	return	result;
}

void	List::printfNode()
{
	PList	s = Tail ->prev;
	puts("");
	while( s != Head )
	{
		printf("%s\n", s ->key );
		s  =  s ->prev;
	}
}

void	List::delete_All(void)
{
	PList	p;
	PList	s;
	p = Head ->next;
	while( p != Tail )
	{
		s = p;
		p = p ->next;
		if( s ->key )		//  만약의 error 를 방지
			free(s ->key);
		free(s);
	}
	Head ->next = Tail;		//  별 필요없는 코드.. 노드 연결
	Tail ->prev = Head;
}

char	*List::GetPosURL(int	nPos)
{
	char	*pStr = NULL;
	PList	pL = Head ->next;
	while(--nPos)
	{
		pL = pL ->next;
	}
	pStr = (char *)malloc(sizeof(strlen(pL->key) * sizeof(char)));
	strcpy(pStr, pL ->key);
	return	pStr;
}

int		List::DeleteFromPos(int	nPos)
{
//	while(nPos--
//	List::Head ->
	PList	deleteNode = NULL;
	PList	pp = Head ->next;
	while(nPos--)
	{
		pp = pp ->next;
	}

	deleteNode = pp ->prev;
	pp ->prev = Head;
	Head ->next = pp;

	while(deleteNode != Head)
	{
		PList	pDel = deleteNode;
		deleteNode = deleteNode ->prev;

		//	Node 삭제시 절대 delete keyword 를 쓰는 게 아니다.
		//	반드시 deleteNode 메소드 사용.
		pDel ->deleteNode(pDel);
	}

	return	0;

}



