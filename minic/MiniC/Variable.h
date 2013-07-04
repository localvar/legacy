#ifndef __VARIBLE_H__
#define __VARIBLE_H__

union tagVARIABLE
{
	void vValue;
	int nValue;
	float fValue;
};

typedef union tagVARIABLE VARIABLE;
typedef VARIABLE* PVARIABLE;

/*
typedef struct tagVARIABLE
{
	int nType;
	union
	{
		double dValue;
		int nValue;
		void vValue;
	}Value;
}VARIABLE;
typedef VARIABLE* PVARIABLE;
*/

extern PVARIABLE VarTable;
extern PVARIABLE pLocalVar;
extern PVARIABLE pTempVar;
/*extern PVARIABLE pTopVar;*/

#endif  __VARIBLE_H__
