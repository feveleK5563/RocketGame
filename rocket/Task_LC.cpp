//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "Task_LC.h"
#include "MyGameMain.h"

namespace  LC
{
	//-----------------------------------------------------------------------------
	//uú»v^XN¶¬ÉPñ¾¯s¤
	bool  Object::Initialize(  )
	{
		__super::Initialize(defGroupName,  defName,  true);	//X[p[NXú»

		//f[^ú»
		MyGameMain_Initalize( );


		//^XNÌ¶¬

		return  true;
	}
	//-----------------------------------------------------------------------------
	//uI¹v^XNÁÅÉPñ¾¯s¤
	bool  Object::Finalize()
	{
		//f[^^XNðú
		MyGameMain_Finalize( );

		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//ø«p¬^XNÌ¶¬
		}

		return  true;
	}
	//-----------------------------------------------------------------------------
	//uÀsvPt[És¤
	void  Object::UpDate()
	{
		MyGameMain_UpDate( );
	}
	//-----------------------------------------------------------------------------
	//uQc`ævPt[És¤
	void  Object::Render2D_AF()
	{
		MyGameMain_Render2D( );
	}

//
//î{IÉÏXsvÈ\bh
//
	//-----------------------------------------------------------------------------
	//^XN¶¬û
	Object::SP  Object::Create(bool  gameEnginePushBack_)
	{
		Object::SP  ob  =  Object::SP(new  Object( ));
		if(ob){
			ob->me  =  ob;
			if (gameEnginePushBack_) {
				ge->PushBack(ob);//Q[GWÉo^
			}
			if( !ob->B_Initialize( ) ){
				ob->Kill( );//CjVCYÉ¸sµ½çKill
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