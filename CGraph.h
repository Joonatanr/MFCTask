#pragma once


typedef struct 
{
	float xValue;
	float yValue;
} GraphicPair;

class CGraph 
{

private:
	int leftMargin;
	int upperMargin;
	int width = 600;
	int height = 300;

	GraphicPair measurementValues[600];

public:
	CGraph();
	CGraph(int lMargin, int uMargin);
	void draw(CClientDC* pDC);
};