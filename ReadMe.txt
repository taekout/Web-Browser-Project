CBaseImage :	모든 그래픽 클래스의 기초 클래스입니다.다형성의 기법을 이용하여 프로그래밍하였습니다.

모든 View 클래스는 CbaseImage *m_pBaseImage; 를 가지고 있습니다. 이 파일만 있으면 JPG , BMP 두 종류의 파일을 출력할 수 있습니다. e 사용이 간편함
%. GIF 외 기타 파일 포맷까지 확장 가능할 수도 있음…

CBaseBitmap :	비트맵 처리 위한 클래스입니다..
CBaseJPG : Jpeg 파일 처리 위한 클래스입니다..

Pseudo Code >
CBaseImage *pImage = new CbaseBitmap
pImage ->Load( bstr );	// load files
pImage = NULL;	//	free

pImage = new CbaseJPG();	// load instance
pImage ->Load( bstr );	// load files
Load 시엔 파일 형식이 BMP , JPG 임을 확인하는 과정 포함
pImage = NULL;	// Psuedo Code
 <C CODE> a
delete pImage;
	SendMessage(포함 클래스, WM_DELIMAGE);
포함 클래스 :: OnDelImage()
{
m_pImage = NULL;	//	delete된 것을 표시
}

그 외 모든 클래스의 부모는 CObject
OOP ==> C Code
CBaseBitmap : CBaseImage
CBaseJPG : CBaseImage

CBaseImage *p = new CBaseJPG;
CBaseImage *p = new CBaseBitmap;

그 과정에서 (CBaseJPG *)p ->LoadJPG() 함수 접근 불가
해결책 : 설계 변화 --> CBaseImage::LoadJPG() = 0; 선언

또 다른 문제 ... LoadJPG() 를 CBaseBitmap 에서도 정의해주어야 함..
왜냐하면 순수가상함수를 오버라이드 하지 않았으므로 Derived 클래스도
순수가상 클래스로서 instantiate 될 수가 없다.

해결책 : 설계 변화 --> CBaseImage::LoadJpg 를 그냥 virtual 로 선언



윈도우 간의 메세지 교환을 통하여 문제점 해결...
1. CMovieDialog 실행시 나타나는 초기화와 마지막 소멸 관련 마무리 코드를 자식 윈도우에서 할 수 없는 성질의
마무리 코드는 부모 윈도우에 CMovieDialog 가 끝났음을 나타내주는 User Defined Message 를 통하여
마무리 작업을 부모 윈도우에서 실행합니다.

2. CmovieDialog::OnNCDestroy() 에서 마무리 작업을 실행하는 방안도 있을 것 같습니다.
