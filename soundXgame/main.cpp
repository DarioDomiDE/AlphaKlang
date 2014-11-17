#include "projectGrafics.h"
#include "projectMacros.h"
#include "projectClasses.h"
#include "Ground.h"
#include "Fountain.h"

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
ConID* testID;
void LoadContent(void)
{
	AUDIO->LoadeBackgroundAudio("testtrack.mp3");
	AUDIO->Play();

	ground = Ground::getInstance();
	//ground->Init();

	fountain = new Fountain();
	//fountain->Init();
	

	IGObject* tempObject = SCENE->camera->SetTarget((new Cubus("X-7.png",true)));

	int i = -1;
	Vector3 position = Vector3(10, 0, 0);
	(new Cubus())->LoadTexture("X-7.png")				->move(position.x,position.y,i++);
	(new Cubus())->LoadTexture("X-512.jpg")				->move(position.x,position.y,i++);
	(new Cubus())->LoadTexture("Deckelblech128-1.png")	->move(position.x,position.y,i++);
	(new Cubus())->LoadTexture("Deckelblech-2s.png")	->move(position.x,position.y,i++);
	(new Cubus())->LoadTexture("Deckelblech128-2.png")	->move(position.x,position.y,i++);
	//(new Cubus("X-7.tga",false))->move(i,tempObject->getTransform()->position.y,i++);
	
	//SCENE->camera->SetTarget(tempObject);
	
	
	//(new Sprite())->move(0,2,0);
	//(new Sprite())->LoadTexture("Deckelblech128.tga")->move(2,2,0);

	SCENE->camera->Mode(FIRSTPERSON);
}

GobID switcher=0;
//Main-Cycle:
////////////////////////////////////////////////////////
void UpdateCycle(void)
{
	UPDATE->DoAllTheUpdates();

	if(INPUT->Mouse.RIGHT.CLICK)
	{
		SCENE->camera->SetTarget(SCENE->Object(switcher));
		if(++switcher>=SCENE->ObjectsCount())
			switcher=0;
	}
	
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
	//if(key=='m')
	//	testID = SCENE->Object(switcher)->conXtor->AddConnection(SCENE->Object(switcher+1));
	if(key == 27) // ESC
		glutExit();

	//if(key=='o')
		//SCENE->camera->Mode(ORTHOGRAFIC);

	//if(key=='p')
		//SCENE->camera->Mode(PERSPECTIVE);

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



