#include "projectGrafics.h"
#include "projectMacros.h"
#include "projectClasses.h"


//Global Declerations:
////////////////////////////////////////////
//vars:
int wnd;
void* font;

//Objects:
Ground* ground;
Fountain* fountain;


//Functions:
void Init(void);
void GlInit(void);
void LoadContent(void);
void UpdateCycle(void);
void RenderCycle(void);
void OnDisplay(void);
void OnIdle(void);
void OnReshape(int,int);
void MouseMoveFunc(int,int);
void MouseClicks(int,int,int,int);
void MouseWheelFunc(int,int,int,int);
void processSpecialKeys(int,int,int);
void keyboardInput(unsigned char,int,int);
void MouseHoverWindow(int);
void GamePadFunc(unsigned,int,int,int);
int prepareForExit(void);
// unsigned create_shader(const char* shaderCodeFileName,GLenum type);


////////////////////////////////////////////
//Entrypoint:
int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	Init();

	glutMainLoop();
	
	return prepareForExit();
}

int prepareForExit(void)
{
	//deletions:
	delete font;

	return 0;
}

void Init(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
	wnd = glutCreateWindow("-soundXgame-");
	font = GLUT_BITMAP_HELVETICA_18;

	glutDisplayFunc(OnDisplay);
	glutReshapeFunc(OnReshape);
	glutIdleFunc(OnIdle);

	glutMotionFunc(MouseMoveFunc);
	glutPassiveMotionFunc(MouseMoveFunc);
	glutMouseFunc(MouseClicks);
	glutMouseWheelFunc(MouseWheelFunc);
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(keyboardInput);
	glutEntryFunc(MouseHoverWindow);

	// hide mouse cursor
	glutSetCursor(GLUT_CURSOR_NONE); 
	
	GLenum glewError = glewInit();
	if( glewError != GLEW_OK )
		std::cerr << "Unable to init GLew";

	GlInit();

	LoadContent();
}

void GlInit(void)
{
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	// enable Multisample Antialiasing
    glEnable(GL_MULTISAMPLE_ARB);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//shader
	//glEnableVertexAttribArray( atribut_coordinate2 );
}

SpectrumAnalyzer* analyzerID;
ConID* testID;
int i1,i2,i3;
int cycle1 = 127;
int cycle2 = 255;
int cycle3 = 127;
void LoadContent(void)
{
i1 = -1;
i2 = -2;
i3 = 1;
	AUDIO->LoadeBackgroundAudio("testtrack3.mp3");
	AUDIO->Play();

	ground = Ground::getInstance();
	ground->IsVisible = true;

	fountain = new Fountain();
	

	data32 col = data32();
	col.byte[0] = 255;
	col.byte[1] = 200;
	col.byte[2] = 150;
	col.byte[3] = 100;
	int i = -1;


	
	//VoxGrid* vObject = new VoxGrid("drei_.ppm");
	//vObject->AddConnectable<VoxControl>();
	//vObject->GetConnected<VoxControl>()->Connection()->SetName("voxels");
	//vObject->AddConnectable<CamTargetRotator>();





	
	
	

	SCENE->camera->Mode(FIRSTPERSON);




	analyzerID = new SpectrumAnalyzer();
	analyzerID->AddConnectable<CamTargetRotator>();
	//SCENE->Object(analyzerID->GetID())->move(10,1,10);
	SCENE->camera->SetTarget(analyzerID);
}



GobID switcher=0;
//Main-Cycle:
////////////////////////////////////////////////////////
void UpdateCycle(void)
{
	//color test flashing krams....
	//if(cycle1<0||cycle1>255)
	//	i1= -i1;
	//if(cycle2<0||cycle2>255)
	//	i2= -i2;
	//if(cycle3<0||cycle3>255)
	//	i3= -i3;

	//cycle1+=i1;
	//cycle2+=i2;
	//cycle3+=i3;

	//((Cubus*)SCENE->Object((unsigned)1))->color.byte[1] = cycle1;
	//((Cubus*)SCENE->Object((unsigned)1))->color.byte[2] = cycle2;
	//((Cubus*)SCENE->Object((unsigned)1))->color.byte[3] = cycle3;
	//((Cubus*)SCENE->Object((unsigned)1))->color.byte[0] = (255-cycle1);

	//data32 col = ((Cubus*)SCENE->Object((unsigned)0))->color;
	//printf("color: %i,%i,%i,%i\n",col.byte[1] ,col.byte[2] ,col.byte[3] ,col.byte[0] );
	//___________________________________________________________



	//Update:
	UPDATE->DoAllTheUpdates();

	if(INPUT->Mouse.RIGHT.CLICK)
	{
		SCENE->camera->SetTarget(SCENE->Object(switcher));
		if(++switcher>=SCENE->ObjectsCount())
			switcher=0;
	}

	if(INPUT->Mouse.WheelV==WHEEL::UP)
	{	analyzerID->fallOffAmount += 0.01f;
	printf("FallOffAmount: %f",analyzerID->fallOffAmount);}
	if(INPUT->Mouse.WheelV==WHEEL::DOWN)
	{	analyzerID->fallOffAmount -= 0.01f;
	printf("FallOffAmount: %f",analyzerID->fallOffAmount);}
}

void RenderCycle(void)
{
	SCENE->DrawSky();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//ground->Draw();

	SCENE->DrawAll();
		
	glutSwapBuffers();
}


//GL-DisplayCallbacks
////////////////////////////////////////////////////////
void OnDisplay(void)
{
	UpdateCycle();
	RenderCycle();
	INPUT->PerFrameReset();
	AUDIO->PerFrameReset();
}

void OnIdle(void)
{
	OnDisplay();
}

void OnReshape(GLsizei size_x,GLsizei size_y)
{
	if(size_y == 0)
		size_y = 1;

	INPUT->SaveViewportRectangle(0,0,size_x,size_y);
	SCENE->camera->Aspect((float)size_x/(float)size_y);
}


//GL-InputFunctions;
///////////////////////////////////////////////////
//Keyboard:
void keyboardInput(unsigned char key,int x,int y)
{
	/* Switches Cam-Modes..*/
	if(key=='o')
	{	
		SCENE->camera->Mode(FIRSTPERSON);
	}
	if(key=='p')
	{	
		SCENE->camera->Mode(FOLLOWTARGET);
	}
	if(key == 27) // ESC
		glutExit();


	INPUT->notifyKey(key);
}
void processSpecialKeys(int key, int xx, int yy)
{
	INPUT->notifySpecialKey(key);
}

//Mouse:
void MouseMoveFunc(int X,int Y)
{
	INPUT->notifyMouse(X,Y);
}

void MouseClicks(int button,int state,int X,int Y)
{
	INPUT->UpdateMouseButtons(button,state,X,Y);
}

void MouseWheelFunc(int wheel,int state,int X,int Y)
{
	INPUT->UpdateMouseWheel(wheel,state,X,Y);
}

void MouseHoverWindow(int)
{

}



