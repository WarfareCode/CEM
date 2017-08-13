#ifndef ABS_FDTD_H
#define ABS_FDTD_H

class AbsFDTD
{
	public:
	virtual void InitializeEngine(int x, int y, int z) = 0;
	virtual void UpdateFields(double time) = 0;
	virtual double * getEField()=0;
	virtual double getEField(int index)=0;
	virtual double  *getHField()=0;
	virtual double getHField(int index)=0;
	virtual int getDataSize()=0;
	virtual double getImpedance()=0;
};

#endif
