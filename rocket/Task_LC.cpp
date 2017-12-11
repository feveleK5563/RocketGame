//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "Task_LC.h"
#include "MyGameMain.h"

namespace  LC
{
	//-----------------------------------------------------------------------------
	//�u�������v�^�X�N�������ɂP�񂾂��s������
	bool  Object::Initialize(  )
	{
		__super::Initialize(defGroupName,  defName,  true);	//�X�[�p�[�N���X������

		//���f�[�^������
		MyGameMain_Initalize( );


		//���^�X�N�̐���

		return  true;
	}
	//-----------------------------------------------------------------------------
	//�u�I���v�^�X�N���Ŏ��ɂP�񂾂��s������
	bool  Object::Finalize()
	{
		//���f�[�^���^�X�N���
		MyGameMain_Finalize( );

		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//�������p���^�X�N�̐���
		}

		return  true;
	}
	//-----------------------------------------------------------------------------
	//�u���s�v�P�t���[�����ɍs������
	void  Object::UpDate()
	{
		MyGameMain_UpDate( );
	}
	//-----------------------------------------------------------------------------
	//�u�Q�c�`��v�P�t���[�����ɍs������
	void  Object::Render2D_AF()
	{
		MyGameMain_Render2D( );
	}

//������������������������������������������������������������������������������������
//��{�I�ɕύX�s�v�ȃ��\�b�h
//������������������������������������������������������������������������������������
	//-----------------------------------------------------------------------------
	//�^�X�N��������
	Object::SP  Object::Create(bool  gameEnginePushBack_)
	{
		Object::SP  ob  =  Object::SP(new  Object( ));
		if(ob){
			ob->me  =  ob;
			if (gameEnginePushBack_) {
				ge->PushBack(ob);//�Q�[���G���W���ɓo�^
			}
			if( !ob->B_Initialize( ) ){
				ob->Kill( );//�C�j�V�����C�Y�Ɏ��s������Kill
			}
			return  ob;
		}
		return nullptr;
	}
	//-----------------------------------------------------------------------------
	bool  Object::B_Initialize( )
	{
		return  this->Initialize( );
	}
	//-----------------------------------------------------------------------------
	Object::~Object( ){		this->B_Finalize( );	}
	bool  Object::B_Finalize( )
	{	
		auto  rtv = this->Finalize( );
		return  rtv;
	}
	//-----------------------------------------------------------------------------
	Object::Object( ){	}
}