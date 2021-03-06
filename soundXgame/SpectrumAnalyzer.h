#ifndef _SPECTRUM_ANALYZER_H_
#define _SPECTRUM_ANALYZER_H_

#include "igobject.h"
#include "Cubus.h"
#include "UpdateManager.h"
#include "Ground.h"
#include "IEditable.h"

#define SPECTRUM_SIZE (128)

class SpectrumAnalyzer :
	public Cubus,
	public IUpdateble
{
private: 
	
	short bandWidth;
	Cubus* bands[SPECTRUM_SIZE];
	float* fftData;
	bool _CHANGEDposition,_CHANGEDrotation,_CHANGEDscale;
	virtual void ChangeColor(int band,float changefactor);
	virtual void ChangeSize(int band,float changefactor);
	void drawOnce(void);

public:
	void SetFalloff(float);
	float ChartHeight;
	SpectrumAnalyzer(void);
	virtual ~SpectrumAnalyzer(void);
	virtual void Initialize(void);
	float fallOffAmount;
	virtual void DoEarly(void);
	virtual void DoUpdate(void);
	virtual void DoLate(void);
	virtual void draw(void);
	virtual Vector3 move(float,float,float);
	virtual Vector3 rotate(Vector3);
	virtual Vector3 scale(float,float,float);
	
};

#endif
