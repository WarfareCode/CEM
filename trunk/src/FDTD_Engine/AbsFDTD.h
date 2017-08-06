#ifndef ABS_FDTD_H
#define ABS_FDTD_H

class AbsFDTD
{
	public:
	virtual void InitializeEngine(int x, int y, int z) = 0;
	virtual void UpdateFields(double time) = 0;
};

#endif