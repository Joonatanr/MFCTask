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

void CGraph::draw(CClientDC* pDC)
{
	COLORREF borderColor = RGB(255, 0, 0);
	CPen borderPen(PS_SOLID, 7, borderColor);

	int xOffset = leftMargin * 30;
	int yOffset = upperMargin * 30;

	pDC->Rectangle(xOffset, yOffset, width - xOffset, height - yOffset);
}