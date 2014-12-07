#include "projectGrafics.h"
#include "projectMacros.h"

#include "VoxelMap.h"
//#include "Voxel.h"


Voxel::Voxel(void)
{
	position.iX=position.Yps=size.ix=size.yps=0;
	x=&position.iX;
	y=&position.Yps;
	w=&size.ix;
	h=&size.yps;
	farb.s32 = 0;
}

void
Voxel::SetParentVoxmap(VoxelMap* map)
{
	vMapObject = map;
}

Voxel::~Voxel(void)
{
//	delete vMapObject;
}

VectorF
Voxel::GetPosition(void)
{
	VectorF neu;
	neu.x =  position.iX * MainDimensions->x;
	neu.y = position.Yps * MainDimensions->x;
	return neu;
}

void
Voxel::SetPosition(VectorF setter)
{
	position = setter/MainDimensions->x; 
}

VectorF
Voxel::GetSize(void)
{
	VectorF neu;
	neu.x = size.ix * MainDimensions->y;
	neu.y = size.yps * MainDimensions->y;
	return neu;
}

void
Voxel::SetSize(VectorF setter)
{
	size.ix = (setter/MainDimensions->y).x; 
	size.yps = (setter/MainDimensions->y).y;
}


void Voxel::SetNeighbours(int ol,int or,int ur,int ul)
{
	OL=ol;
	OR=or;
	UR=ur;
	UL=ul;
}



//void Voxel::fDraw(VectorF offset)
//{		
//	GLfloat F=((float)factor/255)+(1.0f-(offset.y/SCREENHEIGHT));
//
//		farb.s32 = color;	
//		glColor4f((GLfloat)farb.Bytss[0]/255,(GLfloat)farb.Bytss[1]/255,(GLfloat)farb.Bytss[2]/255,0.1f);
//
//		glVertex2f((position.iX*MainDimensions->y)*F + offset.x ,								(position.Yps*MainDimensions->y)*F +								offset.y);
//		glVertex2f((position.iX*MainDimensions->y)*F + offset.x + (size.ix*MainDimensions->x)*F ,	(position.Yps*MainDimensions->y)*F+								offset.y);
//		glVertex2f((position.iX*MainDimensions->y)*F + offset.x + (size.ix*MainDimensions->x)*F ,	(position.Yps*MainDimensions->y)*F+ (size.yps*MainDimensions->x)*F +	offset.y);
//		glVertex2f((position.iX*MainDimensions->y)*F + offset.x ,								(position.Yps*MainDimensions->y)*F+ (size.yps*MainDimensions->x )*F+	offset.y);
//}

//void Voxel::fDrawBlure(VectorF offset)
//{
//		GLfloat F=((float)factor/255)+(1.0f-(offset.y/SCREENHEIGHT));
//	//farb.FromArgb(OL);
//	//glColor4b(farb.R,farb.G,farb.B,farb.A);
//		farb.s32=OL;
//		glColor4f((GLfloat)farb.Bytss[0]/255,(GLfloat)farb.Bytss[1]/255,(GLfloat)farb.Bytss[2]/255,(GLfloat)farb.Bytss[3]/255);
//		glVertex2f((position.iX*MainDimensions->y)*F + offset.x ,								(position.Yps*MainDimensions->y)*F +								offset.y);
//		
//		
//		//farb.FromArgb(OR);
//		//glColor4b(farb.R,farb.G,farb.B,farb.A);
//		farb.s32=OR;
//		glColor4f((GLfloat)farb.Bytss[0]/255,(GLfloat)farb.Bytss[1]/255,(GLfloat)farb.Bytss[2]/255,(GLfloat)farb.Bytss[3]/255);
//		glVertex2f((position.iX*MainDimensions->y)*F + offset.x + (size.ix*MainDimensions->x)*F ,	(position.Yps*MainDimensions->y)*F +								offset.y);
//		
//		//farb.FromArgb(UR);
//		//glColor4b(farb.R,farb.G,farb.B,farb.A);
//		farb.s32=UR;
//		glColor4f((GLfloat)farb.Bytss[0]/255,(GLfloat)farb.Bytss[1]/255,(GLfloat)farb.Bytss[2]/255,(GLfloat)farb.Bytss[3]/255);
//		glVertex2f((position.iX*MainDimensions->y)*F+ offset.x + (size.ix*MainDimensions->x)*F ,	(position.Yps*MainDimensions->y)*F + (size.yps*MainDimensions->x)*F  +	offset.y);
//		
//		//farb.FromArgb(UL);
//		//glColor4b(farb.R,farb.G,farb.B,farb.A);
//		farb.s32=UL;
//		glColor4f((GLfloat)farb.Bytss[0]/255,(GLfloat)farb.Bytss[1]/255,(GLfloat)farb.Bytss[2]/255,(GLfloat)farb.Bytss[3]/255);
//		glVertex2f((position.iX*MainDimensions->y)*F + offset.x ,								(position.Yps*MainDimensions->y)*F + (size.yps*MainDimensions->x)*F  +	offset.y);
//}


void Voxel::vDraw(VectorPF P_offset)
{		
	VectorF offset = *VectorF::Zero;
	offset.x = *P_offset.x;
	offset.y = *P_offset.y;

	GLfloat F=((float)factor/255)+(1.0f-(offset.y/SCREENHEIGHT)) * *factorPointer;
	
	farb.s32 = color;	
	glColor4f((GLfloat)farb.Bytss[0]/255,(GLfloat)farb.Bytss[1]/255,(GLfloat)farb.Bytss[2]/255,0.5f);
	
	glVertex3f((position.iX*MainDimensions->y+offset.x)*F,									(position.Yps*MainDimensions->y+offset.y)*F , *TheOtherZED);
	glVertex3f((position.iX*MainDimensions->y+offset.x)*F + (size.ix*MainDimensions->x)*F,	(position.Yps*MainDimensions->y+offset.y)*F , *TheOtherZED);
	glVertex3f((position.iX*MainDimensions->y+offset.x)*F + (size.ix*MainDimensions->x)*F,	(position.Yps*MainDimensions->y+offset.y)*F + (size.yps*MainDimensions->x )*F, *TheOtherZED);
	glVertex3f((position.iX*MainDimensions->y+offset.x)*F,									(position.Yps*MainDimensions->y+offset.y)*F + (size.yps*MainDimensions->x )*F, *TheOtherZED);
}



void Voxel::vDrawBunt(VectorPF offset)
{
	GLfloat F=((float)factor/255)+(1.0f-(*offset.y/SCREENHEIGHT)) * *factorPointer;
	int l = (int)*x-1;
	l=(l>=0)?l:0;
	int r = (int)*x+1;
	r = (r<vMapObject->mapWidth)?r:vMapObject->mapWidth-1;
	int o = (int)*y-1;
	o=(o>=0)?o:0;
	int u = (int)*y+1;
	u=(u<vMapObject->mapHeight)?u:vMapObject->mapHeight-1;  

	farb.s32=OL;
//	farb.s32 = vMapObject->GetVoxel(l,o)->farb.s32;
	glColor4f((GLfloat)farb.Bytss[0]/255,(GLfloat)farb.Bytss[1]/255,(GLfloat)farb.Bytss[2]/255,0.5f);
	glVertex3f((position.iX*MainDimensions->y+*offset.x)*F,								(position.Yps*MainDimensions->y+*offset.y)*F, *TheOtherZED);
	
	farb.s32=OR;
//	farb.s32 = vMapObject->GetVoxel(r,o)->farb.s32;
	glColor4f((GLfloat)farb.Bytss[0]/255,(GLfloat)farb.Bytss[1]/255,(GLfloat)farb.Bytss[2]/255,0.5f);
	glVertex3f((position.iX*MainDimensions->y+*offset.x)*F + (size.ix*MainDimensions->x)*F ,(position.Yps*MainDimensions->y+*offset.y)*F, *TheOtherZED);
	
	farb.s32=UR;
//	farb.s32 = vMapObject->GetVoxel(r,u)->farb.s32;
	glColor4f((GLfloat)farb.Bytss[0]/255,(GLfloat)farb.Bytss[1]/255,(GLfloat)farb.Bytss[2]/255,0.5f);
	glVertex3f((position.iX*MainDimensions->y+*offset.x)*F + (size.ix*MainDimensions->x)*F ,(position.Yps*MainDimensions->y+*offset.y)*F + (size.yps*MainDimensions->x)*F, *TheOtherZED);
	
	farb.s32=UL;
//	farb.s32 = vMapObject->GetVoxel(l,u)->farb.s32;
	glColor4f((GLfloat)farb.Bytss[0]/255,(GLfloat)farb.Bytss[1]/255,(GLfloat)farb.Bytss[2]/255,0.5f);
	glVertex3f((position.iX*MainDimensions->y+*offset.x)*F,								(position.Yps*MainDimensions->y+*offset.y)*F  + (size.yps*MainDimensions->x)*F, *TheOtherZED);
}



void Voxel::vDrawByte(VectorPF offset)
{

		GLfloat F=((float)factor/255)+(1.0f-(*offset.y/SCREENHEIGHT)) * *factorPointer;

		farb.s32=OL;
		glColor4b(farb.Bytss[0],farb.Bytss[1],farb.Bytss[2],farb.Bytss[3]);
		glVertex3f((position.iX*MainDimensions->y+*offset.x)*F,								(position.Yps*MainDimensions->y+*offset.y)*F, *TheOtherZED);
		
		farb.s32=OR;
		glColor4b(farb.Bytss[0],farb.Bytss[1],farb.Bytss[2],farb.Bytss[3]);
		glVertex3f((position.iX*MainDimensions->y+*offset.x)*F + (size.ix*MainDimensions->x)*F ,(position.Yps*MainDimensions->y+*offset.y)*F, *TheOtherZED);
		
		farb.s32=UR;
		glColor4b(farb.Bytss[0],farb.Bytss[1],farb.Bytss[2],farb.Bytss[3]);
		glVertex3f((position.iX*MainDimensions->y+*offset.x)*F + (size.ix*MainDimensions->x)*F ,(position.Yps*MainDimensions->y+*offset.y)*F + (size.yps*MainDimensions->x)*F, *TheOtherZED);
		
		farb.s32=UL;
		glColor4b(farb.Bytss[0],farb.Bytss[1],farb.Bytss[2],farb.Bytss[3]);
		glVertex3f((position.iX*MainDimensions->y+*offset.x)*F,								(position.Yps*MainDimensions->y+*offset.y)*F  + (size.yps*MainDimensions->x)*F, *TheOtherZED);
}