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

	float xMin, xMax, yMin, yMax;

	GraphicPair measurementValues[600];

	bool translateCoordinateIntoPixel(float valueX, float valueY, POINT* out);

public:
	CGraph();
	CGraph(int lMargin, int uMargin);
	void setMeasurementValues(GraphicPair* values, float yMin, float yMax, float xMin, float xMax);
	void draw(CClientDC* pDC);

};