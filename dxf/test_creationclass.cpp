/*
 * @file test_creationclass.cpp
 */

/*****************************************************************************
**  $Id: test_creationclass.cpp 8865 2008-02-04 18:54:02Z andrew $
**
**  This is part of the dxflib library
**  Copyright (C) 2001 Andrew Mustun
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU Library General Public License as
**  published by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Library General Public License for more details.
**
**  You should have received a copy of the GNU Library General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/

#include "test_creationclass.h"

#include <iostream>
#include <stdio.h>


/**
 * Default constructor.
 */
Test_CreationClass::Test_CreationClass() {}

/**
 * Sample implementation of the method which handles layers.
 */
void Test_CreationClass::addBlock(const DL_BlockData &data)
{
    printf("Block case: %d,%s,%6.3f,%6.3f,%6.3f\n",data.flags,data.name.c_str(),data.bpx,data.bpy,data.bpz);
    printAttributes();
}
void Test_CreationClass::addXLine(const DL_XLineData &data)
{
    printf("XLine base: %6.3f,%6.3f,%6.3f; direction: %6.3f\n",data.bx,data.by,data.bz,data.dx,data.dy,data.dz);
    printAttributes();
}
void Test_CreationClass::addSpline(const DL_SplineData&data)
{
    std::cout << "SPine :";
    std::string s = "begin :" + std::to_string(data.tangentStartX) + "," + std::to_string(data.tangentStartY) + "," + std::to_string(data.tangentStartZ) + ",";
    s = s +" end: "+ std::to_string(data.tangentEndX) + "," + std::to_string(data.tangentEndY) + "," + std::to_string(data.tangentEndZ) + ", degree:"+std::to_string(data.degree);
    std::cout << s << std::endl;
    printAttributes();
}
void Test_CreationClass::addHatch(const DL_HatchData&data)
{
    printf("Hatch case: %d,%s,%6.3f,%6.3f\n",data.numLoops,data.pattern.c_str(),data.originX,data.originY);
    printAttributes();
}
void Test_CreationClass::addHatchEdge(const DL_HatchEdgeData&data)
{
    printf("vertices\n");
    for (int i = 0; i < data.vertices.size(); i++)
        printf("%6.3f,%6.3f\n", data.vertices[i][0], data.vertices[i][0]);
    printAttributes();
}
void Test_CreationClass::addMText(const DL_MTextData&data)//多行文字
{
    printf("MText:stype: text: %s\n", data.text.c_str());
    printAttributes();
}
void Test_CreationClass::addText(const DL_TextData&data)//文字
{
    printf("Text:stype: %s ,text: %s\n", data.style.c_str(), data.text.c_str());
    printAttributes();
}
void Test_CreationClass::addArcAlignedText(const DL_ArcAlignedTextData& data)//圆弧文字
{
    printf("Arc Aligned Text:%6.3f ,font: %s, stype: %s ,text: %s \n", data.radius, data.font.c_str(), data.style.c_str(), data.text.c_str());
    printAttributes();
}

void Test_CreationClass::addLayer(const DL_LayerData& data) //识别图层
{
    printf("LAYER: %s flags: %d\n", data.name.c_str(), data.flags);
    printAttributes();
}
/**
 * Sample implementation of the method which handles point entities.
 */
void Test_CreationClass::addPoint(const DL_PointData& data) //识别点
{
    printf("POINT    (%6.3f, %6.3f, %6.3f)\n",
           data.x, data.y, data.z);
    printAttributes();
}

/**
 * Sample implementation of the method which handles line entities.
 */
void Test_CreationClass::addLine(const DL_LineData& data) //识别直线
{
    mline_data.push_back(data);
    printf("LINE     (%6.3f, %6.3f, %6.3f) (%6.3f, %6.3f, %6.3f)\n",
           data.x1, data.y1, data.z1, data.x2, data.y2, data.z2);
    printAttributes();
}

/**
 * Sample implementation of the method which handles arc entities.
 */
void Test_CreationClass::addArc(const DL_ArcData& data) //识别圆弧，圆心，半径，两个角度
{
    printf("ARC      (%6.3f, %6.3f, %6.3f) %6.3f, %6.3f, %6.3f\n",
           data.cx, data.cy, data.cz,
           data.radius, data.angle1, data.angle2);
    printAttributes();
}

/**
 * Sample implementation of the method which handles circle entities.
 */
void Test_CreationClass::addCircle(const DL_CircleData& data) //识别圆，圆心，半径
{
    printf("CIRCLE   (%6.3f, %6.3f, %6.3f) %6.3f\n",
           data.cx, data.cy, data.cz,
           data.radius);
    printAttributes();
}


/**
 * Sample implementation of the method which handles polyline entities.
 */
void Test_CreationClass::addPolyline(const DL_PolylineData& data)     //识别多边形
{
    printf("POLYLINE \n");
    printf("flags: %d\n", (int)data.flags);
    printAttributes();
}


/**
 * Sample implementation of the method which handles vertices.
 */
void Test_CreationClass::addVertex(const DL_VertexData& data) //识别顶点
{
    printf("VERTEX   (%6.3f, %6.3f, %6.3f) %6.3f\n",
           data.x, data.y, data.z,
           data.bulge);
    printAttributes();
}


void Test_CreationClass::add3dFace(const DL_3dFaceData& data) {
    printf("3DFACE\n");
    for (int i=0; i<4; i++) {
        printf("   corner %d: %6.3f %6.3f %6.3f\n", 
            i, data.x[i], data.y[i], data.z[i]);
    }
    printAttributes();
}


void Test_CreationClass::printAttributes() {
    printf("  Attributes: Layer: %s, ", attributes.getLayer().c_str());
    printf(" Color: ");
    if (attributes.getColor()==256)	{
        printf("BYLAYER");
    } else if (attributes.getColor()==0) {
        printf("BYBLOCK");
    } else {
        printf("%d", attributes.getColor());
    }
    printf(" Width: ");
    if (attributes.getWidth()==-1) {
        printf("BYLAYER");
    } else if (attributes.getWidth()==-2) {
        printf("BYBLOCK");
    } else if (attributes.getWidth()==-3) {
        printf("DEFAULT");
    } else {
        printf("%d", attributes.getWidth());
    }
    printf(" Type: %s\n", attributes.getLinetype().c_str());
}
    
    

// EOF
