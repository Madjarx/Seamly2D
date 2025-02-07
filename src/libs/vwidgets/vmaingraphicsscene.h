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
 **  @file   vmaingraphicsscene.h
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

#ifndef VMAINGRAPHICSSCENE_H
#define VMAINGRAPHICSSCENE_H

#include <qcompilerdetection.h>
#include <QGraphicsScene>
#include <QMetaObject>
#include <QObject>
#include <QPointF>
#include <QRectF>
#include <QString>
#include <QTransform>
#include <QVector>
#include <QtGlobal>

#include "../vmisc/def.h"

/**
 * @brief The VMainGraphicsScene class main scene.
 */
class VMainGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit      VMainGraphicsScene(QObject *parent = nullptr);
    explicit      VMainGraphicsScene(const QRectF & sceneRect, QObject * parent = nullptr);
    qint32        getHorScrollBar() const;
    void          setHorScrollBar(const qint32 &value);
    qint32        getVerScrollBar() const;
    void          setVerScrollBar(const qint32 &value);
    QTransform    transform() const;
    void          setCurrentTransform(const QTransform &transform);
    void          swapTransforms();
    void          SetDisableTools(bool disable, const QString &draftBlockName);
    QPointF       getScenePos() const;

    QRectF        visibleItemsBoundingRect() const;
    void          InitOrigins();
    void          setOriginsVisible(bool visible);

public slots:
    void          chosenItem(quint32 id, const SceneObject &type);
    void          SelectedItem(bool selected, quint32 object, quint32 tool);
    void          EnableItemMove(bool move);
    void          enablePiecesMode(bool mode);
    void          ItemsSelection(const SelectionType &type);
    void          HighlightItem(quint32 id);

    void          ToggleLabelSelection(bool enabled);
    void          TogglePointSelection(bool enabled);
    void          ToggleLineSelection(bool enabled);
    void          ToggleArcSelection(bool enabled);
    void          ToggleElArcSelection(bool enabled);
    void          ToggleSplineSelection(bool enabled);
    void          ToggleSplinePathSelection(bool enabled);
    void          ToggleNodeLabelSelection(bool enabled);
    void          ToggleNodePointSelection(bool enabled);
    void          togglePieceSelection(bool enabled);

    void          ToggleLabelHover(bool enabled);
    void          TogglePointHover(bool enabled);
    void          ToggleLineHover(bool enabled);
    void          ToggleArcHover(bool enabled);
    void          ToggleElArcHover(bool enabled);
    void          ToggleSplineHover(bool enabled);
    void          ToggleSplinePathHover(bool enabled);
    void          ToggleNodeLabelHover(bool enabled);
    void          ToggleNodePointHover(bool enabled);
    void          togglePieceHover(bool enabled);

protected:
    virtual void  mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void  mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void  mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

signals:
    /**
     * @brief mouseMove send new mouse position.
     * @param scenePos new mouse position.
     */
    void          mouseMove(const QPointF &scenePos);

    void          MouseLeftPressed();
    void          MouseLeftReleased();
    void          ItemClicked(QGraphicsItem* pItem);

    /**
     * @brief ChosenObject send option choosed object.
     * @param id object id.
     * @param type object scene type.
     */
    void          ChosenObject(quint32 id, SceneObject type);
    void          SelectedObject(bool selected, quint32 object, quint32 tool);
    void          DisableItem(bool disable, const QString &draftBlockName);
    void          EnableToolMove(bool move);
    void          pieceLockedChanged(quint32 id, bool lock);
    void          curvePiecesMode(bool mode);
    void          ItemSelection(const SelectionType &type);
    void          highlightPiece(quint32 id);

    void          enableTextItemSelection(bool enable);
    void          EnablePointItemSelection(bool enable);
    void          EnableLineItemSelection(bool enable);
    void          EnableArcItemSelection(bool enable);
    void          EnableElArcItemSelection(bool enable);
    void          EnableSplineItemSelection(bool enable);
    void          EnableSplinePathItemSelection(bool enable);
    void          EnableNodeLabelItemSelection(bool enabled);
    void          EnableNodePointItemSelection(bool enabled);
    void          EnableDetailItemSelection(bool enabled);

    void          enableTextItemHover(bool enable);
    void          EnablePointItemHover(bool enable);
    void          EnableArcItemHover(bool enable);
    void          EnableElArcItemHover(bool enable);
    void          EnableSplineItemHover(bool enable);
    void          EnableSplinePathItemHover(bool enable);
    void          EnableNodeLabelItemHover(bool enabled);
    void          EnableNodePointItemHover(bool enabled);
    void          EnableDetailItemHover(bool enabled);
    void          EnableLineItemHover(bool enabled);
    void          DimensionsChanged();
    void          LanguageChanged();

private:
    /** @brief horScrollBar value horizontal scroll bar. */
    qint32        horScrollBar;

    /** @brief verScrollBar value vertical scroll bar. */
    qint32        verScrollBar;

    /** @brief _transform view transform value. */
    QTransform    m_previousTransform;
    QTransform    m_currentTransform;
    QPointF       scenePos;
    QVector<QGraphicsItem *> origins;
};

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief getHorScrollBar return scene horizontal scrollbar.
 * @return horizontal scrollbar.
 */
inline qint32 VMainGraphicsScene::getHorScrollBar() const
{
    return horScrollBar;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief setHorScrollBar set scene horizontal scrollbar.
 * @param value horizontal scrollbar.
 */
inline void VMainGraphicsScene::setHorScrollBar(const qint32 &value)
{
    horScrollBar = value;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief getVerScrollBar return scene vertical scrollbar.
 * @return vertical scrollbar.
 */
inline qint32 VMainGraphicsScene::getVerScrollBar() const
{
    return verScrollBar;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief setVerScrollBar set scene vertical scrollbar.
 * @param value vertical scrollbar.
 */
inline void VMainGraphicsScene::setVerScrollBar(const qint32 &value)
{
    verScrollBar = value;
}

#endif // VMAINGRAPHICSSCENE_H
