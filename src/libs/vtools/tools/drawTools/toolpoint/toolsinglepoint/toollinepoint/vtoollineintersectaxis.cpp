/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017  Seamly, LLC                                       *
 *                                                                         *
 *   https://github.com/fashionfreedom/seamly2d                            *
 *                                                                         *
 ***************************************************************************
 **
 **  Seamly2D is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Seamly2D is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 **************************************************************************

 ************************************************************************
 **
 **  @file   vtoollineintersectaxis.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   19 10, 2014
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentine project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2013-2015 Seamly2D project
 **  <https://github.com/fashionfreedom/seamly2d> All Rights Reserved.
 **
 **  Seamly2D is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Seamly2D is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 *************************************************************************/

#include "vtoollineintersectaxis.h"

#include "vtoollinepoint.h"
#include "../ifc/ifcdef.h"
#include "../ifc/exception/vexception.h"
#include "../vgeometry/vpointf.h"
#include "../vmisc/vabstractapplication.h"
#include "../vmisc/vcommonsettings.h"
#include "../vpatterndb/vcontainer.h"
#include "../vpatterndb/vtranslatevars.h"
#include "../vwidgets/vmaingraphicsscene.h"
#include "../../../vdrawtool.h"
#include "../../../../vabstracttool.h"
#include "../../../../../dialogs/tools/dialogtool.h"
#include "../../../../../dialogs/tools/dialoglineintersectaxis.h"
#include "../../../../../visualization/visualization.h"
#include "../../../../../visualization/line/vistoollineintersectaxis.h"

#include <QLine>
#include <QMessageBox>
#include <QSharedPointer>
#include <QStaticStringData>
#include <QStringData>
#include <QStringDataPtr>
#include <new>

template <class T> class QSharedPointer;

const QString VToolLineIntersectAxis::ToolType = QStringLiteral("lineIntersectAxis");

//---------------------------------------------------------------------------------------------------------------------
VToolLineIntersectAxis::VToolLineIntersectAxis(VAbstractPattern *doc, VContainer *data, const quint32 &id,
                                               const QString &lineType, const QString &lineWeight,
                                               const QString &lineColor,
                                               const QString &formulaAngle, const quint32 &basePointId,
                                               const quint32 &firstPointId, const quint32 &secondPointId,
                                               const Source &typeCreation, QGraphicsItem *parent)
    : VToolLinePoint(doc, data, id, lineType, lineWeight, lineColor, QString()
    , basePointId, 0, parent)
    , formulaAngle(formulaAngle)
    , firstPointId(firstPointId)
    , secondPointId(secondPointId)
{
    ToolCreation(typeCreation);
}

//---------------------------------------------------------------------------------------------------------------------
void VToolLineIntersectAxis::setDialog()
{
    SCASSERT(not m_dialog.isNull())
    m_dialog->setModal(true);
    QSharedPointer<DialogLineIntersectAxis> dialogTool = m_dialog.objectCast<DialogLineIntersectAxis>();
    SCASSERT(not dialogTool.isNull())
    const QSharedPointer<VPointF> p = VAbstractTool::data.GeometricObject<VPointF>(m_id);
    dialogTool->setLineType(m_lineType);
    dialogTool->setLineWeight(m_lineWeight);
    dialogTool->setLineColor(lineColor);
    dialogTool->SetAngle(formulaAngle);
    dialogTool->SetBasePointId(basePointId);
    dialogTool->SetFirstPointId(firstPointId);
    dialogTool->SetSecondPointId(secondPointId);
    dialogTool->SetPointName(p->name());
}

//---------------------------------------------------------------------------------------------------------------------
VToolLineIntersectAxis *VToolLineIntersectAxis::Create(QSharedPointer<DialogTool> dialog, VMainGraphicsScene *scene,
                                                       VAbstractPattern *doc, VContainer *data)
{
    SCASSERT(not dialog.isNull())
    QSharedPointer<DialogLineIntersectAxis> dialogTool = dialog.objectCast<DialogLineIntersectAxis>();
    SCASSERT(not dialogTool.isNull())
    const QString pointName     = dialogTool->getPointName();
    const QString lineType      = dialogTool->getLineType();
    const QString lineWeight    = dialogTool->getLineWeight();
    const QString lineColor     = dialogTool->getLineColor();
    QString formulaAngle        = dialogTool->GetAngle();
    const quint32 basePointId   = dialogTool->GetBasePointId();
    const quint32 firstPointId  = dialogTool->GetFirstPointId();
    const quint32 secondPointId = dialogTool->GetSecondPointId();

    VToolLineIntersectAxis *point = Create(0, pointName, lineType, lineWeight, lineColor, formulaAngle,
                                           basePointId, firstPointId, secondPointId, 5, 10, true,
                                           scene, doc, data, Document::FullParse, Source::FromGui);
    if (point != nullptr)
    {
        point->m_dialog = dialogTool;
    }
    return point;
}

//---------------------------------------------------------------------------------------------------------------------
VToolLineIntersectAxis *VToolLineIntersectAxis::Create(const quint32 _id, const QString &pointName,
                                                       const QString &lineType, const QString &lineWeight,
                                                       const QString &lineColor,
                                                       QString &formulaAngle, quint32 basePointId,
                                                       quint32 firstPointId, quint32 secondPointId,
                                                       qreal mx, qreal my, bool showPointName, VMainGraphicsScene *scene,
                                                       VAbstractPattern *doc, VContainer *data, const Document &parse,
                                                       const Source &typeCreation)
{
    const QSharedPointer<VPointF> basePoint = data->GeometricObject<VPointF>(basePointId);
    QLineF axis = QLineF(static_cast<QPointF>(*basePoint), QPointF(basePoint->x()+100, basePoint->y()));
    axis.setAngle(CheckFormula(_id, formulaAngle, data));

    const QSharedPointer<VPointF> firstPoint = data->GeometricObject<VPointF>(firstPointId);
    const QSharedPointer<VPointF> secondPoint = data->GeometricObject<VPointF>(secondPointId);
    QLineF line(static_cast<QPointF>(*firstPoint), static_cast<QPointF>(*secondPoint));

    QPointF fPoint = FindPoint(axis, line);

    if (fPoint == QPointF())
    {
        const QString msg = tr("<b><big>Can't find intersection point %1 of</big></b><br>"
                               "<b><big>Line and Axis</big></b><br><br>"
                               "Using origin point as a place holder until pattern is corrected.")
                               .arg(pointName);

        QMessageBox msgBox(qApp->getMainWindow());
        msgBox.setWindowTitle(tr("Intersect Line and Axis"));
        msgBox.setWindowFlags(msgBox.windowFlags() & ~Qt::WindowContextHelpButtonHint);
        msgBox.setWindowIcon(QIcon(":/toolicon/32x32/line_intersect_axis.png"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(msg);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }

    quint32 id = _id;
    VPointF *p = new VPointF(fPoint, pointName, mx, my);
    p->setShowPointName(showPointName);

    if (typeCreation == Source::FromGui)
    {
        id = data->AddGObject(p);
        data->AddLine(basePointId, id);
        data->AddLine(firstPointId, id);
        data->AddLine(id, secondPointId);
    }
    else
    {
        data->UpdateGObject(id, p);
        data->AddLine(basePointId, id);
        data->AddLine(firstPointId, id);
        data->AddLine(id, secondPointId);
        if (parse != Document::FullParse)
        {
            doc->UpdateToolData(id, data);
        }
    }

    if (parse == Document::FullParse)
    {
        VDrawTool::AddRecord(id, Tool::LineIntersectAxis, doc);
        VToolLineIntersectAxis *point = new VToolLineIntersectAxis(doc, data, id, lineType, lineWeight, lineColor, formulaAngle,
                                                                   basePointId, firstPointId, secondPointId,
                                                                   typeCreation);
        scene->addItem(point);
        InitToolConnections(scene, point);
        VAbstractPattern::AddTool(id, point);
        doc->IncrementReferens(basePoint->getIdTool());
        doc->IncrementReferens(firstPoint->getIdTool());
        doc->IncrementReferens(secondPoint->getIdTool());
        return point;
    }
    return nullptr;
}

//---------------------------------------------------------------------------------------------------------------------
QPointF VToolLineIntersectAxis::FindPoint(const QLineF &axis, const QLineF &line)
{
    QPointF fPoint;
    QLineF::IntersectType intersect = axis.intersects(line, &fPoint);
    if (intersect == QLineF::UnboundedIntersection || intersect == QLineF::BoundedIntersection)
    {
        if(VFuzzyComparePossibleNulls(axis.angle(), line.angle())
           || VFuzzyComparePossibleNulls(qAbs(axis.angle() - line.angle()), 180))
        {
            return QPointF();
        }
        else
        {
            return fPoint;
        }
    }
    else
    {
        return QPointF();
    }
}

//---------------------------------------------------------------------------------------------------------------------
QString VToolLineIntersectAxis::FirstLinePoint() const
{
    return VAbstractTool::data.GetGObject(firstPointId)->name();
}

//---------------------------------------------------------------------------------------------------------------------
QString VToolLineIntersectAxis::SecondLinePoint() const
{
    return VAbstractTool::data.GetGObject(secondPointId)->name();
}

//---------------------------------------------------------------------------------------------------------------------
VFormula VToolLineIntersectAxis::GetFormulaAngle() const
{
    VFormula fAngle(formulaAngle, getData());
    fAngle.setCheckZero(false);
    fAngle.setToolId(m_id);
    fAngle.setPostfix(degreeSymbol);
    return fAngle;
}

//---------------------------------------------------------------------------------------------------------------------
void VToolLineIntersectAxis::SetFormulaAngle(const VFormula &value)
{
    if (value.error() == false)
    {
        formulaAngle = value.GetFormula(FormulaType::FromUser);

        QSharedPointer<VGObject> obj = VAbstractTool::data.GetGObject(m_id);
        SaveOption(obj);
    }
}

//---------------------------------------------------------------------------------------------------------------------
quint32 VToolLineIntersectAxis::GetFirstPointId() const
{
    return firstPointId;
}

//---------------------------------------------------------------------------------------------------------------------
void VToolLineIntersectAxis::SetFirstPointId(const quint32 &value)
{
    if (value != NULL_ID)
    {
        firstPointId = value;

        QSharedPointer<VGObject> obj = VAbstractTool::data.GetGObject(m_id);
        SaveOption(obj);
    }
}

//---------------------------------------------------------------------------------------------------------------------
quint32 VToolLineIntersectAxis::GetSecondPointId() const
{
    return secondPointId;
}

//---------------------------------------------------------------------------------------------------------------------
void VToolLineIntersectAxis::SetSecondPointId(const quint32 &value)
{
    if (value != NULL_ID)
    {
        secondPointId = value;

        QSharedPointer<VGObject> obj = VAbstractTool::data.GetGObject(m_id);
        SaveOption(obj);
    }
}

//---------------------------------------------------------------------------------------------------------------------
void VToolLineIntersectAxis::ShowVisualization(bool show)
{
    ShowToolVisualization<VisToolLineIntersectAxis>(show);
}

//---------------------------------------------------------------------------------------------------------------------
void VToolLineIntersectAxis::showContextMenu(QGraphicsSceneContextMenuEvent *event, quint32 id)
{
    try
    {
        ContextMenu<DialogLineIntersectAxis>(event, id);
    }
    catch(const VExceptionToolWasDeleted &e)
    {
        Q_UNUSED(e)
        return;//Leave this method immediately!!!
    }
}

//---------------------------------------------------------------------------------------------------------------------
void VToolLineIntersectAxis::SaveDialog(QDomElement &domElement)
{
    SCASSERT(not m_dialog.isNull())
    QSharedPointer<DialogLineIntersectAxis> dialogTool = m_dialog.objectCast<DialogLineIntersectAxis>();
    SCASSERT(not dialogTool.isNull())
    doc->SetAttribute(domElement, AttrName,       dialogTool->getPointName());
    doc->SetAttribute(domElement, AttrLineType,   dialogTool->getLineType());
    doc->SetAttribute(domElement, AttrLineWeight, dialogTool->getLineWeight());
    doc->SetAttribute(domElement, AttrLineColor,  dialogTool->getLineColor());
    doc->SetAttribute(domElement, AttrAngle,      dialogTool->GetAngle());
    doc->SetAttribute(domElement, AttrBasePoint,  QString().setNum(dialogTool->GetBasePointId()));
    doc->SetAttribute(domElement, AttrP1Line,     QString().setNum(dialogTool->GetFirstPointId()));
    doc->SetAttribute(domElement, AttrP2Line,     QString().setNum(dialogTool->GetSecondPointId()));
}

//---------------------------------------------------------------------------------------------------------------------
void VToolLineIntersectAxis::SaveOptions(QDomElement &tag, QSharedPointer<VGObject> &obj)
{
    VToolLinePoint::SaveOptions(tag, obj);

    doc->SetAttribute(tag, AttrType,      ToolType);
    doc->SetAttribute(tag, AttrAngle,     formulaAngle);
    doc->SetAttribute(tag, AttrBasePoint, basePointId);
    doc->SetAttribute(tag, AttrP1Line,    firstPointId);
    doc->SetAttribute(tag, AttrP2Line,    secondPointId);
}

//---------------------------------------------------------------------------------------------------------------------
void VToolLineIntersectAxis::ReadToolAttributes(const QDomElement &domElement)
{
    m_lineType    = doc->GetParametrString(domElement, AttrLineType,   LineTypeSolidLine);
    m_lineWeight  = doc->GetParametrString(domElement, AttrLineWeight, "0.35");
    lineColor     = doc->GetParametrString(domElement, AttrLineColor,  ColorBlack);
    basePointId   = doc->GetParametrUInt(domElement,   AttrBasePoint,  NULL_ID_STR);
    firstPointId  = doc->GetParametrUInt(domElement,   AttrP1Line,     NULL_ID_STR);
    secondPointId = doc->GetParametrUInt(domElement,   AttrP2Line,     NULL_ID_STR);
    formulaAngle  = doc->GetParametrString(domElement, AttrAngle,      "");
}

//---------------------------------------------------------------------------------------------------------------------
void VToolLineIntersectAxis::SetVisualization()
{
    if (not vis.isNull())
    {
        VisToolLineIntersectAxis *visual = qobject_cast<VisToolLineIntersectAxis *>(vis);
        SCASSERT(visual != nullptr)

        visual->setObject1Id(firstPointId);
        visual->setPoint2Id(secondPointId);
        visual->setAxisPointId(basePointId);
        visual->SetAngle(qApp->TrVars()->FormulaToUser(formulaAngle, qApp->Settings()->GetOsSeparator()));
        visual->setLineStyle(lineTypeToPenStyle(m_lineType));
        visual->setLineWeight(m_lineWeight);
        visual->RefreshGeometry();
    }
}

//---------------------------------------------------------------------------------------------------------------------
QString VToolLineIntersectAxis::makeToolTip() const
{
    const QSharedPointer<VPointF> basePoint = VAbstractTool::data.GeometricObject<VPointF>(basePointId);
    const QSharedPointer<VPointF> firstPoint = VAbstractTool::data.GeometricObject<VPointF>(firstPointId);
    const QSharedPointer<VPointF> secondPoint = VAbstractTool::data.GeometricObject<VPointF>(secondPointId);
    const QSharedPointer<VPointF> current = VAbstractTool::data.GeometricObject<VPointF>(m_id);

    const QLineF curLine(static_cast<QPointF>(*basePoint), static_cast<QPointF>(*current));
    const QLineF firstToCur(static_cast<QPointF>(*firstPoint), static_cast<QPointF>(*current));
    const QLineF curToSecond(static_cast<QPointF>(*current), static_cast<QPointF>(*secondPoint));

    const QString toolTip = QString("<table>"
                                    "<tr> <td><b>  %10:</b> %11</td> </tr>"
                                    "<tr> <td><b>%1:</b> %2 %3</td> </tr>"
                                    "<tr> <td><b> %4:</b> %5°</td> </tr>"
                                    "<tr> <td><b>%6:</b> %7 %3</td> </tr>"
                                    "<tr> <td><b>%8:</b> %9 %3</td> </tr>"
                                    "</table>")
                                    .arg(tr("Length"))
                                    .arg(qApp->fromPixel(curLine.length()))
                                    .arg(UnitsToStr(qApp->patternUnit(), true))
                                    .arg(tr("Angle"))
                                    .arg(curLine.angle())
                                    .arg(QString("%1->%2").arg(firstPoint->name(), current->name()))
                                    .arg(qApp->fromPixel(firstToCur.length()))
                                    .arg(QString("%1->%2").arg(current->name(), secondPoint->name()))
                                    .arg(qApp->fromPixel(curToSecond.length()))
                                    .arg(tr("Name"))
                                    .arg(current->name());

    return toolTip;
}
