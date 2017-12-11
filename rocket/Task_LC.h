#pragma warning(disable:4996)
#pragma once
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include  "MyPG.h"

namespace  LC
{
	//�^�X�N�Ɋ��蓖�Ă�O���[�v���ƌŗL��
	const  string  defGroupName(	"�{��");	//�O���[�v��
	const  string  defName(			"�{��");	//�^�X�N��
	//-----------------------------------------------------------------------------
	class  Object  :  public  BTask
	{
	//�ύX�s����������������������������������������������������
	public:
		virtual  ~Object( );
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		static  Object::SP  Create(bool gameEnginePushBack_);	//�������� ������true�Ń^�X�N�V�X�e���֎����o�^
	private:

		Object( );
		bool  B_Initialize( );
		bool  B_Finalize( );
		bool  Initialize( );	//�u�������v�^�X�N�������ɂP�񂾂��s������
		void  UpDate( );		//�u���s�v�P�t���[�����ɍs������
		void  Render2D_AF();	//�u2D�`��v�P�t���[�����ɍs������
		bool  Finalize();		//�u�I���v�^�X�N���Ŏ��ɂP�񂾂��s������
	//�ύX������������������������������������������������������
	public:
		//�ǉ��������ϐ��E���\�b�h�͂����ɒǉ�����
	};
}