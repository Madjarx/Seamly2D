/******************************************************************************
 *   @file   dialogline.h
 **  @author Douglas S Caskey
 **  @date   21 Mar, 2023
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Seamly2D project, a pattern making
 **  program to create and model patterns of clothing.
 **  Copyright (C) 2017-2023 Seamly2D project
 **  <https://github.com/fashionfreedom/seamly2d> All Rights Reserved.
 **
 **  Seamly2D is free software: you can redistribute it and/or modify
 **  You should have received a copy of the GNU General Public License
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 *****************************************************************************/

/************************************************************************
 **
 **  @file   dialogline.h
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

#ifndef DIALOGLINE_H
#define DIALOGLINE_H

#include <qcompilerdetection.h>
#include <QMetaObject>
#include <QObject>
#include <QString>
#include <QtGlobal>

#include "../vmisc/def.h"
#include "dialogtool.h"

namespace Ui
{
    class DialogLine;
}

/**
 * @brief The DialogLine class dialog for ToolLine. Help create line and edit option.
 */
class DialogLine : public DialogTool
{
    Q_OBJECT
public:
    DialogLine(const VContainer *data, const quint32 &toolId, QWidget *parent = nullptr);
    virtual ~DialogLine() Q_DECL_OVERRIDE;

    quint32        getFirstPoint() const;
    void           setFirstPoint(const quint32 &value);

    quint32        getSecondPoint() const;
    void           setSecondPoint(const quint32 &value);

    QString        getLineType() const;
    void           setLineType(const QString &value);

    QString        getLineWeight() const;
    void           setLineWeight(const QString &value);

    QString        getLineColor() const;
    void           setLineColor(const QString &value);

public slots:
    virtual void   ChosenObject(quint32 id, const SceneObject &type) Q_DECL_OVERRIDE;
    virtual void   PointNameChanged() Q_DECL_OVERRIDE;

protected:
    virtual void   ShowVisualization() Q_DECL_OVERRIDE;
    /**
     * @brief SaveData Put dialog data in local variables
     */
    virtual void   SaveData() Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(DialogLine)

    /** @brief ui keeps information about user interface */
    Ui::DialogLine *ui;
};

#endif // DIALOGLINE_H
