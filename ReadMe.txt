CBaseImage :	��� �׷��� Ŭ������ ���� Ŭ�����Դϴ�.�������� ����� �̿��Ͽ� ���α׷����Ͽ����ϴ�.

��� View Ŭ������ CbaseImage *m_pBaseImage; �� ������ �ֽ��ϴ�. �� ���ϸ� ������ JPG , BMP �� ������ ������ ����� �� �ֽ��ϴ�. e ����� ������
%. GIF �� ��Ÿ ���� ���˱��� Ȯ�� ������ ���� ������

CBaseBitmap :	��Ʈ�� ó�� ���� Ŭ�����Դϴ�..
CBaseJPG : Jpeg ���� ó�� ���� Ŭ�����Դϴ�..

Pseudo Code >
CBaseImage *pImage = new CbaseBitmap
pImage ->Load( bstr );	// load files
pImage = NULL;	//	free

pImage = new CbaseJPG();	// load instance
pImage ->Load( bstr );	// load files
Load �ÿ� ���� ������ BMP , JPG ���� Ȯ���ϴ� ���� ����
pImage = NULL;	// Psuedo Code
 <C CODE> a
delete pImage;
	SendMessage(���� Ŭ����, WM_DELIMAGE);
���� Ŭ���� :: OnDelImage()
{
m_pImage = NULL;	//	delete�� ���� ǥ��
}

�� �� ��� Ŭ������ �θ�� CObject
OOP ==> C Code
CBaseBitmap : CBaseImage
CBaseJPG : CBaseImage

CBaseImage *p = new CBaseJPG;
CBaseImage *p = new CBaseBitmap;

�� �������� (CBaseJPG *)p ->LoadJPG() �Լ� ���� �Ұ�
�ذ�å : ���� ��ȭ --> CBaseImage::LoadJPG() = 0; ����

�� �ٸ� ���� ... LoadJPG() �� CBaseBitmap ������ �������־�� ��..
�ֳ��ϸ� ���������Լ��� �������̵� ���� �ʾ����Ƿ� Derived Ŭ������
�������� Ŭ�����μ� instantiate �� ���� ����.

�ذ�å : ���� ��ȭ --> CBaseImage::LoadJpg �� �׳� virtual �� ����



������ ���� �޼��� ��ȯ�� ���Ͽ� ������ �ذ�...
1. CMovieDialog ����� ��Ÿ���� �ʱ�ȭ�� ������ �Ҹ� ���� ������ �ڵ带 �ڽ� �����쿡�� �� �� ���� ������
������ �ڵ�� �θ� �����쿡 CMovieDialog �� �������� ��Ÿ���ִ� User Defined Message �� ���Ͽ�
������ �۾��� �θ� �����쿡�� �����մϴ�.

2. CmovieDialog::OnNCDestroy() ���� ������ �۾��� �����ϴ� ��ȵ� ���� �� �����ϴ�.
