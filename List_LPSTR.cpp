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
	//	�Ҹ��ڼ� List �� ������ �����ϹǷ�...
	//	�ۿ��� �� Ŭ������ �� �� �� ��带 ���� delete �� �����ϸ� �� �ǰ�,
	//	�ݵ�� deleteNode �Լ��� ����Ѵ�.
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

//  ������ ���ڿ��� �ش��ϴ� ���߿� �� �ͺ��� ��ġ�ϴ� ��带 ����
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

	Head ->next ->prev = i;		//  ��� ����
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
		if( s ->key )		//  ������ error �� ����
			free(s ->key);
		free(s);
	}
	Head ->next = Tail;		//  �� �ʿ���� �ڵ�.. ��� ����
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

		//	Node ������ ���� delete keyword �� ���� �� �ƴϴ�.
		//	�ݵ�� deleteNode �޼ҵ� ���.
		pDel ->deleteNode(pDel);
	}

	return	0;

}



