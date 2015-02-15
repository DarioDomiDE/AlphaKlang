#include "projectGrafics.h"
#include "projectMacros.h"
#include "projectClasses.h"

#include "globalfunctions.h"

using namespace ProjectMappe;

void
ProjectMappe::_backButtonClick(IConnectable* sender)
{
	//GUI->Element("Editor-Panel")->isVisible(false);
	//SceneGraph::getInstance()->camera->Mode(lastCamMode);
}

void ProjectMappe::OnLoadContent(void)
{
	// Background Music
	//unsigned int brummsound;
	//AUDIO->LoadeSampleToBank(brummsound,"brumm_s16.wav");
	AUDIO->LoadeBackgroundAudio("Music/Background_v05.wav");
//	AUDIO->LoadeBackgroundAudio("09-cpu_-_in_the_future.mp3");
	AUDIO->BackgroundMusicVolume(1.0);

	// Gameplay Elements
	Ground* ground = Ground::getInstance();
	(new SkyBox())->SetName("Skybox");
	//ShaderObj* shaderObj = new ShaderObj();

	/* Fountain
	Fountain* fountain = new Fountain();
	fountain->SetPosition(Vector3(-40, 0, 0));
	fountain->size = 50;
	fountain->createRange();
	fountain->SetClambt(0,-1,1);
	fountain->SetThreshold(0,0.33);
	fountain->sensitivity = 5;	  */

	// GUI
	(new MusicControllerPanel())->isVisible(false);
	


	// GUI -> Main Menu
	GuiObject* menu = new GuiObject("GUI/panel_menu.png");
	menu->SetName("Main-Menu");
	menu->scale(Vector3(256,256,1));
	menu->AddConnectable<ButtonControl>();
	menu->GetConnected<ButtonControl>(1)->PositionOnPanel = VectorF(100,150);
	menu->GetConnected<ButtonControl>(1)->SizeScaledPanel = VectorF(0.4,0);
	menu->GetConnected<ButtonControl>(1)->SetText("  Play game");
	menu->AddConnectable<ButtonControl>();
	menu->GetConnected<ButtonControl>(2)->PositionOnPanel = VectorF(100,220);	
	menu->GetConnected<ButtonControl>(2)->SizeScaledPanel = VectorF(0.4,0);
	menu->GetConnected<ButtonControl>(2)->SetText("  Show FPS");
	menu->AddConnectable<ButtonControl>();
	menu->GetConnected<ButtonControl>(3)->PositionOnPanel = VectorF(100,290);	
	menu->GetConnected<ButtonControl>(3)->SizeScaledPanel = VectorF(0.4,0);
	menu->GetConnected<ButtonControl>(3)->SetText("      Exit");
	menu->isVisible(true);

	// Qualle
	(new AnimatedSprite<36,3>("SpriteSheets/Q2_1872x516.png",12,3,25,true))->SetName("Q2animated");
	SCENE->Object("Q2animated")->move(0,5,0);
	SCENE->Object("Q2animated")->IsGrounded(false);
	SCENE->Object("Q2animated")->AddConnectable<ObjectMover<8>>();
	SCENE->Object("Q2animated")->GetConnected<ObjectMover<8>>()->AddWaypoint(SCENE->Object("Q2animated")->getTransform()->position);
	SCENE->Object("Q2animated")->GetConnected<ObjectMover<8>>()->AddWaypoint(SCENE->Object("Q2animated")->getTransform()->position+Utility::GlobalZ*10);
	SCENE->Object("Q2animated")->GetConnected<ObjectMover<8>>()->AddWaypoint(SCENE->Object("Q2animated")->getTransform()->position+Utility::GlobalZ*10+Utility::GlobalX*10);
	SCENE->Object("Q2animated")->GetConnected<ObjectMover<8>>()->AddWaypoint(SCENE->Object("Q2animated")->getTransform()->position+Utility::GlobalX*10);
	SCENE->Object("Q2animated")->GetConnected<ObjectMover<8>>()->AddWaypoint(SCENE->Object("Q2animated")->getTransform()->position+(Utility::GlobalZ-Utility::GlobalX).normalized()*10);
	SCENE->Object("Q2animated")->GetConnected<ObjectMover<8>>()->AddWaypoint(SCENE->Object("Q2animated")->getTransform()->position+(Utility::GlobalZ+Utility::GlobalX).normalized()*10);
	SCENE->Object("Q2animated")->GetConnected<ObjectMover<8>>()->AddWaypoint(SCENE->Object("Q2animated")->getTransform()->position+(Utility::GlobalX-Utility::GlobalZ).normalized()*10);
	SCENE->Object("Q2animated")->GetConnected<ObjectMover<8>>()->AddWaypoint(SCENE->Object("Q2animated")->getTransform()->position+(-(Utility::GlobalX + Utility::GlobalZ)).normalized()*10);
	SCENE->Object("Q2animated")->GetConnected<ObjectMover<8>>()->SetSpeed(3);
	SCENE->Object("Q2animated")->AlwaysFaceMovingdirection = true;
	SCENE->Object("Q2animated")->GetConnected<ObjectMover<8>>()->IsActive = true;


	(new SpectrumAnalyzer())->SetName("SpectrumAnalyzer");
	SCENE->Object("SpectrumAnalyzer")->move(0, 0, -35.0f);
	SCENE->Object("SpectrumAnalyzer")->scale(40.0f * 3.5f/128.0f, 0.3f, 2.0f); // 90 ground-tiles * 3.5m width * 128 bands
	((SpectrumAnalyzer*)SCENE->Object("SpectrumAnalyzer"))->Initialize();

	// Kubus -> fliegender Cube
	new IPrimitivObject();
	GobID temp = SCENE->Object("last created")->GetID();
	((IPrimitivObject*)SCENE->Object(temp))->SetPrimitiv<ICubic>();
	SCENE->Object(temp)->LoadTexture("X-7.png");
	SCENE->Object(temp)->move(5,20,-5);
	SCENE->Object(temp)->GetOrAdd<SmoothObjectMover>()->movingVector.SetMAX(Vector3(10,25,20));
	SCENE->Object(temp)->GetOrAdd<SmoothObjectMover>()->movingVector.SetMIN(Vector3(-15,21,-30));
	SCENE->Object(temp)->GetOrAdd<SmoothObjectMover>()->movingVector.SetMOVE(Vector3(Circle/100,Circle/200,Circle/150));
	SCENE->Object(temp)->GetConnected<SmoothObjectMover>()->IsActive = true;
	SCENE->Object(temp)->isVisible(true);
	SCENE->Object(temp)->SetName("PrimitivKubus");
	SCENE->Object(temp)->AlwaysFaceMovingdirection = true;
	(new ParticleSystem<100>("Particles/Der Blaue Dunst_512x512.png"))->SetName("PrimitivKubus-emission");
	SCENE->Object("PrimitivKubus-emission")->AlwaysFaceMovingdirection=true;
	SCENE->Object("PrimitivKubus-emission")->AddConnectable<ObjectFollower>();
	SCENE->Object("PrimitivKubus-emission")->GetConnected<ObjectFollower>()->SetTarget(SCENE->Object(temp));
	SCENE->Object("PrimitivKubus-emission")->IsGrounded(false);
	((ParticleSystem<100>*)SCENE->Object("PrimitivKubus-emission"))->emittingFrequency = 0.001f;
	((ParticleSystem<100>*)SCENE->Object("PrimitivKubus-emission"))->lifetime = 1.6f;
	((ParticleSystem<100>*)SCENE->Object("PrimitivKubus-emission"))->InitialSize = 0.7f;
	((ParticleSystem<100>*)SCENE->Object("PrimitivKubus-emission"))->ValueChangeReleasepoint = 0.6;
	SCENE->Object(temp)->AddConnectable<primitivSwitcher>();
	SCENE->Object("PrimitivKubus-emission")->SetColor(160,180,255,66);
	SCENE->Object("PrimitivKubus-emission")->IsVisible = true;
	
	/*
	Vector3[] pos = Vector3[18];
		pos[0] = new Vector3(0,0,0);
		pos[1] = new Vector3(5,0,5);

	for(int i = 1; i < 18; i++)
	{
		char dig = (char)(((int)'0')+i);
		(new Cubus("X-7.png"))->SetName("AUDIO01");
		SCENE->Object("AUDIO0" + dig)->GetOrAdd<AudioEmitter>()->LoadeSample("mp3/15-Audio.mp3");
		SCENE->Object("AUDIO01")->move(pos[i]);
		SCENE->Object("AUDIO01")->AddConnectable<MusicScaler>();
		SCENE->Object("AUDIO01")->IsGrounded(true);
		SCENE->Object("AUDIO01")->AddConnectable<MusicScaler>();
		SCENE->Object("AUDIO01")->GetConnected<MusicScaler>()->sensitivity=2;
		SCENE->Object("AUDIO01")->GetConnected<MusicScaler>()->SetThreshold(0,0.02f);
	}
	*/





	Vector3  CubeSpwns[22] = {
								Vector3(0,0,0),Vector3(0,0,0),Vector3(-45,2,45),Vector3(-15,2,50),
								Vector3(-40,2,15),Vector3(-22,2,31),Vector3(-10,2,10),Vector3(0,0,0),
								Vector3(21,2,50),Vector3(15,2,25),Vector3(37,2,30),Vector3(50,2,15),
								Vector3(22,2,-8),Vector3(15,2,-27),Vector3(50,2,-30),Vector3(0,0,0),
								Vector3(45,2,-50),Vector3(0,0,0),Vector3(50,2,40),Vector3(-30,2,-45),
								Vector3(-23,-2,-28),Vector3(-33,2,-50)
							};
	char tempString[16];
	char tempString2[32];
	for(int i = 1;i<22;i++)
	{

		if(i != 1 && i != 2 && i != 3 && i != 4 && i != 8 && i != 16 && i != 18)
		{
			sprintf_s(tempString, sizeof(tempString),"AUDIO_%i",i);
			sprintf_s(tempString2, sizeof(tempString2),"mp3/%i-Audio.mp3",i);

			new IPrimitivObject();
			GobID id = SCENE->Object("last created")->GetID();
			SCENE->Object(id)->SetName(&tempString[0]);
			((IPrimitivObject*)SCENE->Object(id))->SetPrimitiv<ICubic>(); // cube or which obj
			SCENE->Object(id)->LoadTexture("X-7.png"); // load texture
			SCENE->Object(id)->AddConnectable<AudioEmitter>()->LoadeSample(&tempString2[0]); 
			// load music
			SCENE->Object(id)->GetConnected<AudioEmitter>()->Set3Dparameter(30, 200);
			SCENE->Object(id)->move(CubeSpwns[i]); // moving to coordinate
			SCENE->Object(id)->IsGrounded(true); // grounded
			SCENE->Object(id)->AddConnectable<MusicScaler>(); // scale to music	->
			SCENE->Object(id)->GetConnected<MusicScaler>()->SetLineBounds(0, 0, 4, 3);
			SCENE->Object(id)->GetConnected<MusicScaler>()->sensitivity=15;
			SCENE->Object(id)->GetConnected<MusicScaler>()->SetClambt(0,-1.1);
			SCENE->Object(id)->GetConnected<MusicScaler>()->SetThreshold(0,0.0002f);   
		//	SCENE->Object(id)->GetConnected<AudioEmitter>()->PlayAudio(); // play audio
		}
	}

	

	// Cubus - fliegender Cube
	(new Cubus("X-7.png"))->SetName("AUDIO11");
	SCENE->Object("AUDIO11")->GetOrAdd<AudioEmitter>()->LoadeSample("mp3/16-Audio.mp3");
	SCENE->Object("AUDIO11")->AddConnectable<MusicScaler>();
	SCENE->Object("AUDIO11")->GetConnected<AudioEmitter>()->Set3Dparameter(30,200);
	SCENE->Object("AUDIO11")->GetConnected<AudioEmitter>()->AudioVolume(1);
	SCENE->Object("AUDIO11")->GetConnected<AudioEmitter>()->PlayAudio();
	SCENE->Object("AUDIO11")->move(12,0,-18);
	SCENE->Object("AUDIO11")->IsGrounded(false);
	SCENE->Object("AUDIO11")->AddConnectable<SmoothObjectMover>();
	SCENE->Object("AUDIO11")->GetConnected<SmoothObjectMover>()->movingVector.SetMIN(Vector3(-40,20,-40));
	SCENE->Object("AUDIO11")->GetConnected<SmoothObjectMover>()->movingVector.SetMAX(Vector3(40,30,40));
	SCENE->Object("AUDIO11")->AlwaysFaceMovingdirection=true;
	(new ParticleSystem<100>("Particles/kubismus.png"))->SetName("AUDIO11-emission");
	SCENE->Object("AUDIO11-emission")->AlwaysFaceMovingdirection=true;
	SCENE->Object("AUDIO11-emission")->AddConnectable<ObjectFollower>();
	SCENE->Object("AUDIO11-emission")->GetConnected<ObjectFollower>()->SetTarget(SCENE->Object("AUDIO11"));
	SCENE->Object("AUDIO11-emission")->IsGrounded(false);
	((ParticleSystem<100>*)SCENE->Object("AUDIO11-emission"))->emittingFrequency = 0.001f;
	((ParticleSystem<100>*)SCENE->Object("AUDIO11-emission"))->lifetime = 1.6f;
	((ParticleSystem<100>*)SCENE->Object("AUDIO11-emission"))->InitialSize = 0.7f;
	((ParticleSystem<100>*)SCENE->Object("AUDIO11-emission"))->ValueChangeReleasepoint = 0.6;
	SCENE->Object("AUDIO11-emission")->SetColor(160,180,255,66);
	SCENE->Object("AUDIO11-emission")->IsVisible = true;
	SCENE->Object("AUDIO11")->GetConnected<AudioEmitter>()->PlayAudio();

	// Play all loaded Audios
	AUDIO->Play();

	// Music Cube
	(new Cubus("Particles/kubismus.png"))->SetName("muckubus");
	SCENE->Object("muckubus")->GetOrAdd<AudioEmitter>()->LoadeSample("mp3/20-Audio.mp3",false);
	SCENE->Object("muckubus")->AddConnectable<Randomover>();
	SCENE->Object("muckubus")->GetConnected<Randomover>()->SetYoffset(75);
	SCENE->Object("muckubus")->AddConnectable<MusicInteractor>();
	SCENE->Object("muckubus")->GetConnected<MusicInteractor>()->GetLineData(0)->threshold = 1.5;
	SCENE->Object("muckubus")->GetConnected<MusicInteractor>()->GetLineData(1)->threshold = 0.03f;
	SCENE->Object("muckubus")->GetConnected<AudioEmitter>()->PlayAudio();
	SCENE->Object("muckubus")->GetConnected<AudioEmitter>()->AudioVolume(1);
	SCENE->Object("muckubus")->GetConnected<MusicInteractor>()->automaticFallOffAdjust=false;
	SCENE->Object("muckubus")->IsGrounded(true);
	// Just some Music Cubes
	unsigned obj;
	float x,y,z;
	x=y=z=0;
	x = 15.0f;
	for(int i = 0;i<15;i++)
	{
		x-=((float)i);
		z+=(2.f*(float)i/15.0f);
		obj = (new Cubus("Bleche/Deckelblech-2s.png"))->GetID();
		SCENE->Object(obj)->move(x,y,z);
		SCENE->Object(obj)->AddConnectable<Randomover>();
		SCENE->Object(obj)->GetConnected<Randomover>()->SetYoffset(75);
		SCENE->Object(obj)->GetConnected<Randomover>()->SetRotation(true);
		SCENE->Object(obj)->GetConnected<Randomover>()->SetMoving(true);
		SCENE->Object(obj)->GetOrAdd<AudioEmitter>();
		SCENE->Object(obj)->GetConnected<AudioEmitter>()->LoadeSample("mp3/3-Audio.mp3",false);
		SCENE->Object(obj)->GetConnected<AudioEmitter>()->PlayAudio();
		SCENE->Object(obj)->AddConnectable<MusicInteractor>();
		SCENE->Object(obj)->GetConnected<MusicInteractor>()->automaticFallOffAdjust=false;
		SCENE->Object(obj)->SetName("Brummer");
		SCENE->Object(obj)->IsVisible=true;
		SCENE->Object(obj)->GetConnected<AudioEmitter>()->AudioVolume(1);
		SCENE->Object(obj)->IsGrounded(true);
	}
	  
	

	// Spectrum Analyzer


	/*string particleImages[3];
	particleImages[0] = "particle1_128x128.png";
	particleImages[1] = "particle2_128x128.png";
	particleImages[2] = "particle3_128x128.png";*/
	
	//// Particles
	//(new ParticleSystem<150>("Particles/kubismus.png"))->SetName("ParticleSystem");
	//SCENE->Object("ParticleSystem")->AddConnectable<ObjectMover<3>>();
	//SCENE->Object("ParticleSystem")->GetConnected<ObjectMover<3>>()->AddWaypoint(Vector3(-20,0,40));
	//SCENE->Object("ParticleSystem")->GetConnected<ObjectMover<3>>()->AddWaypoint(Vector3(40,0,-20));
	//SCENE->Object("ParticleSystem")->GetConnected<ObjectMover<3>>()->AddWaypoint(Vector3(-40,0,20));
	//SCENE->Object("ParticleSystem")->GetConnected<ObjectMover<3>>()->IsActive = true;
	//SCENE->Object("ParticleSystem")->IsGrounded(false);
	//SCENE->Object("ParticleSystem")->move(0,0,0);
	//SCENE->Object("ParticleSystem")->rotate(3,0.2,-1);
	//SCENE->Object("ParticleSystem")->scale(7.5,7.5,0);
	//SCENE->Object("ParticleSystem")->getTransform()->speed = 20.f;
	//((ParticleSystem<150>*)SCENE->Object("ParticleSystem"))->SetColor(128,128,255,25);
	//((ParticleSystem<150>*)SCENE->Object("ParticleSystem"))->IsVisible = true;


	
	// Camera
	SCENE->camera->ModeSocket->GetCameraMode<PointAndClick>()->IsActive=false;
	SCENE->camera->ModeSocket->AddCameraMode<Edit>()->IsActive=false;
	SCENE->camera->ModeSocket->GetCameraMode<Edit>()->BindGuiObject(menu);
	SCENE->camera->ModeSocket->AddCameraMode<StrangeChaoticView>()->IsActive=false;
	

	SCENE->camera->Mode(FIRSTPERSON);
	SCENE->camera->SetTarget(SCENE->Object("Q2animated"));

	// Show Menu
	SCENE->camera->Mode(Edit::ID);




	//SCENE->camera->ModeSocket->GetCameraMode<TargetGrabber>()->GrabTarget();
	//SCENE->camera->ModeSocket->GetCameraMode<TargetGrabber>()->Mode(TargetGrabber::MODE::ROTATE);

	//AUDIO->BackgroundMusicVolume(0.95);
	//AUDIO->Volume(1);
	AUDIO->Play();
}


/* An Update-event handler */
void 
ProjectMappe::UpdateCycle(void)
{ 
	/*let UPTATE call every object signed in for update it's update-Functions.*/
	UPDATE->DoTheUpdates();
	
	//  <<-- here is a good place for putting update-code when testing new classes or functions which need update.
	//		 but don't implementing IUpdateble-Interface yet,... or for counting a counter..., or ... output to console the last updated values... 
}

/* A Draw Event Handler */
void 
ProjectMappe::RenderCycle(void)
{
	/*let SCENE draws all IDrawable objects contained..  */
	SCENE->DrawAll();

	//  <<-- need to manually draw some object 3D... do it here.



	/*when all 3D-objects finished drawing to the Frame buffer, The GUI-Drawer will switch Matrices and View to 2D-mode,
	 *and goes on drawing 2D-Overlays to the Frame, if there where some GUI-Object loaded...  */ 
	GUI->DrawGUI();

	// <<-- manually drawing 2D can be done here...


}	//->when this function returns, Frame-buffers will swap and the Next frame will begin...  