// OdbScrpt.h
#pragma once

#include "resource.h"

class CMainFrame;
CMainFrame& WtlGetMainWnd();
extern CAppModule theModule;

#define DIMOF(array) (sizeof(array)/sizeof((array)[0]))