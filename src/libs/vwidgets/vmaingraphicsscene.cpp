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
 **  @file   vmaingraphicsscene.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   November 15, 2013
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

#include "vmaingraphicsscene.h"

#include <QBrush>
#include <QEvent>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSimpleTextItem>
#include <QLineF>
#include <QPen>
#include <QStaticStringData>
#include <QStringData>
#include <QStringDataPtr>
#include <Qt>

#include "global.h"
#include "../vmisc/vcommonsettings.h"
#include "../vmisc/vabstractapplication.h"

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief VMainGraphicsScene default constructor.
 */
VMainGraphicsScene::VMainGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
    , horScrollBar(0)
    , verScrollBar(0)
    , m_previousTransform(QTransform())
    , m_currentTransform(QTransform())
    , scenePos(QPointF())
    , origins()
{}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief VMainGraphicsScene constructor.
 * @param sceneRect scene rect.
 * @param parent parent object.
 */
VMainGraphicsScene::VMainGraphicsScene(const QRectF & sceneRect, QObject * parent)
    :QGraphicsScene ( sceneRect, parent )
    , horScrollBar(0)
    , verScrollBar(0)
    , m_previousTransform(QTransform())
    , m_currentTransform(QTransform())
    , scenePos()
    , origins()
{}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief mouseMoveEvent handle mouse move events.
 * @param event mouse move event.
 */
void VMainGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    scenePos = event->scenePos();
    emit mouseMove(event->scenePos());
    QGraphicsScene::mouseMoveEvent(event);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief mousePressEvent mouse press events.
 * @param event mouse press event
 */
void VMainGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->type() != QEvent::GraphicsSceneMouseDoubleClick)
    {
        emit MouseLeftPressed();
    }

    QGraphicsScene::mousePressEvent(event);

    QTransform t;
    QGraphicsItem* pItem = itemAt(event->scenePos(), t);
    emit ItemClicked(pItem);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->type() != QEvent::GraphicsSceneMouseDoubleClick)
    {
        emit MouseLeftReleased();
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::InitOrigins()
{
    origins.clear();

    QColor orginColor = (QColor(qApp->Settings()->getAxisOrginColor()));
    QPen originsPen(orginColor, widthHairLine, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QBrush axisTextBrush(orginColor);
    const qreal arrowAngle = 35.0;
    const qreal arrowLength = 12.0;

    {
        // X axis
        const QLineF lineX(QPointF(25, 0), QPointF(-5, 0));
        QGraphicsLineItem *xLine1 = new QGraphicsLineItem(lineX);
        xLine1->setPen(originsPen);
        xLine1->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        xLine1->setZValue(-1.0);
        addItem(xLine1);
        origins.append(xLine1);

        // Arrow left side
        QLineF arrowLeftLine = lineX;
        arrowLeftLine.setAngle(arrowLeftLine.angle()-arrowAngle);
        arrowLeftLine.setLength(arrowLength);
        QGraphicsLineItem *xLine2 = new QGraphicsLineItem(arrowLeftLine);
        xLine2->setPen(originsPen);
        xLine2->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        xLine2->setZValue(-1.0);
        addItem(xLine2);
        origins.append(xLine2);

        // Arrow right side
        QLineF arrowRightLine = lineX;
        arrowRightLine.setAngle(arrowRightLine.angle()+arrowAngle);
        arrowRightLine.setLength(arrowLength);
        QGraphicsLineItem *xLine3 = new QGraphicsLineItem(arrowRightLine);
        xLine3->setPen(originsPen);
        xLine3->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        xLine3->setZValue(-1.0);
        addItem(xLine3);
        origins.append(xLine3);

        // X axis text
        QGraphicsSimpleTextItem *xOrigin = new QGraphicsSimpleTextItem(QStringLiteral("X"), xLine1);
        xOrigin->setBrush(axisTextBrush);
        xOrigin->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        xOrigin->setZValue(-1.0);
        xOrigin->setPos(25, -(xOrigin->boundingRect().height()/2));
        origins.append(xOrigin);
    }

    {
        // Y axis
        const QLineF lineY(QPointF(0, 25), QPointF(0, -5));
        QGraphicsLineItem *yLine1 = new QGraphicsLineItem(lineY);
        yLine1->setPen(originsPen);
        yLine1->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        yLine1->setZValue(-1.0);
        addItem(yLine1);
        origins.append(yLine1);

        // Arrow left side
        QLineF arrowLeftLine = lineY;
        arrowLeftLine.setAngle(arrowLeftLine.angle()-arrowAngle);
        arrowLeftLine.setLength(arrowLength);
        QGraphicsLineItem *yLine2 = new QGraphicsLineItem(arrowLeftLine);
        yLine2->setPen(originsPen);
        yLine2->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        yLine2->setZValue(-1.0);
        addItem(yLine2);
        origins.append(yLine2);

        // Arrow right side
        QLineF arrowRightLine = lineY;
        arrowRightLine.setAngle(arrowRightLine.angle()+arrowAngle);
        arrowRightLine.setLength(arrowLength);
        QGraphicsLineItem *yLine3 = new QGraphicsLineItem(arrowRightLine);
        yLine3->setPen(originsPen);
        yLine3->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        yLine3->setZValue(-1.0);
        addItem(yLine3);
        origins.append(yLine3);

        // Y axis text
        QGraphicsSimpleTextItem *yOrigin = new QGraphicsSimpleTextItem(QStringLiteral("Y"), yLine1);
        yOrigin->setBrush(axisTextBrush);
        yOrigin->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        yOrigin->setZValue(-1.0);
        yOrigin->setPos(-(yOrigin->boundingRect().width()/2), 25);
        origins.append(yOrigin);
    }
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::setOriginsVisible(bool visible)
{
    foreach (QGraphicsItem *item, origins)
    {
        item->setVisible(visible);
    }
}

//---------------------------------------------------------------------------------------------------------------------
QPointF VMainGraphicsScene::getScenePos() const
{
    return scenePos;
}

//---------------------------------------------------------------------------------------------------------------------
QRectF VMainGraphicsScene::visibleItemsBoundingRect() const
{
    QRectF rect;
    foreach(QGraphicsItem *item, items())
    {
        if(not item->isVisible())
        {
            continue;
        }
        rect = rect.united(item->sceneBoundingRect());
    }
    return rect;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief transform return view transformation.
 * @return view transformation.
 */
QTransform VMainGraphicsScene::transform() const
{
    return m_currentTransform;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief setCurrentTransform set view transformation.
 * @param transform view transformation.
 */
void VMainGraphicsScene::setCurrentTransform(const QTransform &transform)
{
    m_previousTransform = m_currentTransform;
    m_currentTransform = transform;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief swapTransforms.
 */
void VMainGraphicsScene::swapTransforms()
{
    QTransform tempTransform = m_currentTransform;
    m_currentTransform = m_previousTransform;
    m_previousTransform = tempTransform;
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::SetDisableTools(bool disable, const QString &draftBlockName)
{
    emit DisableItem(disable, draftBlockName);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief chosenItem emit ChosenObject signal.
 * @param id object id.
 * @param type object scene type.
 */
void VMainGraphicsScene::chosenItem(quint32 id, const SceneObject &type)
{
    emit ChosenObject(id, type);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::SelectedItem(bool selected, quint32 object, quint32 tool)
{
    emit SelectedObject(selected, object, tool);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::EnableItemMove(bool move)
{
    emit EnableToolMove(move);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::enablePiecesMode(bool mode)
{
    emit curvePiecesMode(mode);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ItemsSelection(const SelectionType &type)
{
    emit ItemSelection(type);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::HighlightItem(quint32 id)
{
    emit highlightPiece(id);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ToggleLabelSelection(bool enabled)
{
    emit enableTextItemSelection(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::TogglePointSelection(bool enabled)
{
    emit EnablePointItemSelection(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ToggleLineSelection(bool enabled)
{
    emit EnableLineItemSelection(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ToggleArcSelection(bool enabled)
{
    emit EnableArcItemSelection(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ToggleElArcSelection(bool enabled)
{
    emit EnableElArcItemSelection(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ToggleSplineSelection(bool enabled)
{
    emit EnableSplineItemSelection(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ToggleSplinePathSelection(bool enabled)
{
    emit EnableSplinePathItemSelection(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ToggleNodeLabelSelection(bool enabled)
{
    emit EnableNodeLabelItemSelection(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ToggleNodePointSelection(bool enabled)
{
    emit EnableNodePointItemSelection(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::togglePieceSelection(bool enabled)
{
    emit EnableDetailItemSelection(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ToggleLabelHover(bool enabled)
{
    emit enableTextItemHover(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::TogglePointHover(bool enabled)
{
    emit EnablePointItemHover(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ToggleLineHover(bool enabled)
{
    emit EnableLineItemHover(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ToggleArcHover(bool enabled)
{
    emit EnableArcItemHover(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ToggleElArcHover(bool enabled)
{
    emit EnableElArcItemHover(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ToggleSplineHover(bool enabled)
{
    emit EnableSplineItemHover(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ToggleSplinePathHover(bool enabled)
{
    emit EnableSplinePathItemHover(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ToggleNodeLabelHover(bool enabled)
{
    emit EnableNodeLabelItemHover(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::ToggleNodePointHover(bool enabled)
{
    emit EnableNodePointItemHover(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VMainGraphicsScene::togglePieceHover(bool enabled)
{
    emit EnableDetailItemHover(enabled);
}
