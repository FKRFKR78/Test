/**
 * @file test_creationclass.h
 */

/*****************************************************************************
**  $Id: test_creationclass.h 8865 2008-02-04 18:54:02Z andrew $
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

#ifndef TEST_CREATIONCLASS_H
#define TEST_CREATIONCLASS_H

#include "dl_creationadapter.h"
#include<QList>


/**
 * This class takes care of the entities read from the file.
 * Usually such a class would probably store the entities.
 * this one just prints some information about them to stdout.
 *
 * @author Andrew Mustun
 */
class Test_CreationClass : public DL_CreationAdapter {
public:
    Test_CreationClass();
    QList<DL_LineData>mline_data;
    virtual void addBlock(const DL_BlockData&);
    virtual void addXLine(const DL_XLineData&);
    virtual void addSpline(const DL_SplineData&);
    virtual void addLayer(const DL_LayerData& data);
    virtual void addPoint(const DL_PointData& data);
    virtual void addLine(const DL_LineData& data);
    virtual void addArc(const DL_ArcData& data);
    virtual void addCircle(const DL_CircleData& data);
    virtual void addPolyline(const DL_PolylineData& data);
    virtual void addVertex(const DL_VertexData& data);
    virtual void add3dFace(const DL_3dFaceData& data);
    virtual void addArcAlignedText(const DL_ArcAlignedTextData& data);
    virtual void addMText(const DL_MTextData&);
    virtual void addText(const DL_TextData&);
    virtual void addHatch(const DL_HatchData&);
    virtual void addHatchEdge(const DL_HatchEdgeData&);
    void printAttributes();
};
/*
 *    virtual void addLayer(const DL_LayerData&) {}
    virtual void addLinetype(const DL_LinetypeData&) {}
    virtual void addLinetypeDash(double) {}
    virtual void addBlock(const DL_BlockData&) {}
    virtual void endBlock() {}
    virtual void addTextStyle(const DL_StyleData&) {}
    virtual void addPoint(const DL_PointData&) {}
    virtual void addLine(const DL_LineData&) {}
    virtual void addXLine(const DL_XLineData&) {}
    virtual void addRay(const DL_RayData&) {}
    virtual void addArc(const DL_ArcData&) {}
    virtual void addCircle(const DL_CircleData&) {}
    virtual void addEllipse(const DL_EllipseData&) {}
    virtual void addPolyline(const DL_PolylineData&) {}
    virtual void addVertex(const DL_VertexData&) {}
    virtual void addSpline(const DL_SplineData&) {}
    virtual void addControlPoint(const DL_ControlPointData&) {}
    virtual void addFitPoint(const DL_FitPointData&) {}
    virtual void addKnot(const DL_KnotData&) {}
    virtual void addInsert(const DL_InsertData&) {}
    virtual void addMText(const DL_MTextData&) {}
    virtual void addMTextChunk(const std::string&) {}
    virtual void addText(const DL_TextData&) {}
    virtual void addArcAlignedText(const DL_ArcAlignedTextData&) {}
    virtual void addAttribute(const DL_AttributeData&) {}
    virtual void addDimAlign(const DL_DimensionData&,
                             const DL_DimAlignedData&) {}
    virtual void addDimLinear(const DL_DimensionData&,
                              const DL_DimLinearData&) {}
    virtual void addDimRadial(const DL_DimensionData&,
                              const DL_DimRadialData&) {}
    virtual void addDimDiametric(const DL_DimensionData&,
                              const DL_DimDiametricData&) {}
    virtual void addDimAngular(const DL_DimensionData&,
                              const DL_DimAngularData&) {}
    virtual void addDimAngular3P(const DL_DimensionData&,
                              const DL_DimAngular3PData&) {}
    virtual void addDimOrdinate(const DL_DimensionData&,
                             const DL_DimOrdinateData&) {}
    virtual void addLeader(const DL_LeaderData&) {}
    virtual void addLeaderVertex(const DL_LeaderVertexData&) {}
    virtual void addHatch(const DL_HatchData&) {}
    virtual void addTrace(const DL_TraceData&) {}
    virtual void add3dFace(const DL_3dFaceData&) {}
    virtual void addSolid(const DL_SolidData&) {}
 * */
#endif
