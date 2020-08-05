#include "stdafx.h"
#include "CRandom.h"

CRandom g_random;

CRandom::CRandom() :mt(time(NULL))
{
}

CRandom::~CRandom()
{
}

