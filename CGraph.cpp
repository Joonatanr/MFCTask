#include "pch.h"
#include "CGraph.h"

	
/* Default constructor. */
CGraph::CGraph()
{
		leftMargin = 1;
		upperMargin = 1;
		
		/* Lets just initialize these to default values for now. */
		height = 300;
		width = 600;

		xMin = 0;
		xMax = 10;
		yMin = -10;
		yMax = 10;

		for (int x = 0; x < 600; x++) 
		{
			measurementValues[x].xValue = 0.0;
			measurementValues[x].yValue = 0.0;
		}
}

CGraph::CGraph(int lMargin, int uMargin) : CGraph()
{
		leftMargin = lMargin;
		upperMargin = uMargin;
}

void CGraph::setMeasurementValues(GraphicPair* values, float yMin, float yMax, float xMin, float xMax) 
{
	for (int x = 0; x < 600; x++) 
	{
		measurementValues[x] = values[x];
	}

	this->yMin = yMin;
	this->yMax = yMax;
	this->xMin = xMin;
	this->xMax = xMax;
}

void CGraph::draw(CClientDC* pDC)
{
	COLORREF backColor = RGB(255, 255, 255);	

	int xOffset = leftMargin * 30;
	int yOffset = upperMargin * 30;

	//pDC->Rectangle(xOffset, yOffset, width - xOffset, height - yOffset);
	
	/* Use a white rectangle as background. */
	pDC->FillSolidRect(xOffset, yOffset, width, height, backColor);

	/* Draw the axes. */
	pDC->MoveTo(xOffset, yOffset);
	pDC->LineTo(xOffset, yOffset + height);

	/* We need to discover first if there is a zero axis. */
	if (yMin <= 0.0) 
	{
		/* We need the point for 0.... */
		POINT zeroAxisStart;
		POINT zeroAxisEnd;

		if (translateCoordinateIntoPixel(xMin, 0.0, &zeroAxisStart) == true) 
		{
			if (translateCoordinateIntoPixel(xMax, 0.0, &zeroAxisEnd) == true) 
			{
				pDC-> MoveTo(zeroAxisStart);
				pDC->LineTo(zeroAxisEnd);
			}
		}
	}

	/* So now we draw the datapoints. */
	for (int x = 0; x < (600 - 1); x++) 
	{
		POINT p1;
		POINT p2;

		if (translateCoordinateIntoPixel(measurementValues[x].xValue, measurementValues[x].yValue, &p1) == true) 
		{
			if (translateCoordinateIntoPixel(measurementValues[x+1].xValue, measurementValues[x+1].yValue, &p2) == true)
			{
				pDC->MoveTo(p1);
				pDC->LineTo(p2);
			}
		}
	}
}


/* Function for translating between coordinate systems. */
bool CGraph::translateCoordinateIntoPixel(float valueX, float valueY, POINT * out) 
{	
	/* First check if we are in range. */
	if (valueX < xMin || valueX > xMax) 
	{
		return false;
	}

	if (valueY < yMin || valueY > yMax) 
	{
		return false;
	}

	float yValueRange = yMax - yMin;
	float xValueRange = xMax - xMin;
	/* Note that width and height equal the pixel value ranges. */

	float yCoefficient = height / yValueRange;
	float xCoefficient = width / xValueRange;


	float translatedX = valueX - xMin;
	float translatedY = valueY - yMin;

	translatedX = translatedX * xCoefficient;
	translatedY = height - (translatedY * yCoefficient);

	translatedX += (leftMargin * 30);
	translatedY += (upperMargin * 30);

	out->x = translatedX;
	out->y = translatedY;

	return true;
}