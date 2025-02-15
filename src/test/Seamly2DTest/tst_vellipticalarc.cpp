/************************************************************************
 **
 **  @file   tst_vellipticalarc.cpp
 **  @author Valentina Zhuravska <zhuravska19(at)gmail.com>
 **  @date   12 2, 2016
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentine project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2015 Seamly2D project
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

#include "tst_vellipticalarc.h"
#include "../vgeometry/vellipticalarc.h"
#include "../vlayout/vabstractpiece.h"

#include <QtGlobal>
#include <QtTest>

//---------------------------------------------------------------------------------------------------------------------
TST_VEllipticalArc::TST_VEllipticalArc(QObject *parent) : AbstractTest(parent)
{}

//---------------------------------------------------------------------------------------------------------------------
void TST_VEllipticalArc::CompareTwoWays_data()
{
    QTest::addColumn<QPointF>("c");
    QTest::addColumn<qreal>("radius1");
    QTest::addColumn<qreal>("radius2");
    QTest::addColumn<qreal>("f1");
    QTest::addColumn<qreal>("f2");
    QTest::addColumn<qreal>("rotationAngle");

    QTest::newRow("Test case 1") << QPointF() << 100. << 200. << 0. << 90.0 << 0.;
    QTest::newRow("Test case 2") << QPointF() << 100. << 200. << 0. << 180.0 << 0.;
    QTest::newRow("Test case 3") << QPointF() << 100. << 200. << 0. << 270.0 << 0.;
    QTest::newRow("Test case 4") << QPointF() << 100. << 200. << 0. << 360.0 << 0.;
    QTest::newRow("Test case 5") << QPointF(10, 10) << 100. << 200. << 0. << 90.0 << 80.;
    QTest::newRow("Test case 6") << QPointF(10, 10) << 100. << 200. << 0. << 180.0 << 80.;
    QTest::newRow("Test case 7") << QPointF(10, 10) << 100. << 200. << 0. << 270.0 << 80.;
    QTest::newRow("Test case 8") << QPointF(10, 10) << 100. << 200. << 0. << 360.0 << 80.;
    QTest::newRow("Test case 9") << QPointF() << 100. << 200. << 0. << 90.0 << 80.;
    QTest::newRow("Test case 10") << QPointF() << 100. << 200. << 0. << 180.0 << 80.;
    QTest::newRow("Test case 11") << QPointF() << 100. << 200. << 0. << 270.0 << 80.;
    QTest::newRow("Test case 12") << QPointF() << 100. << 200. << 0. << 360.0 << 80.;
    QTest::newRow("Test case 13") << QPointF(10, 10) << 100. << 200. << 0. << 90.0 << 80.;
    QTest::newRow("Test case 14") << QPointF(10, 10) << 100. << 200. << 0. << 180.0 << 80.;
    QTest::newRow("Test case 15") << QPointF(10, 10) << 100. << 200. << 0. << 270.0 << 80.;
    QTest::newRow("Test case 16") << QPointF(10, 10) << 100. << 200. << 0. << 360.0 << 80.;
}

//---------------------------------------------------------------------------------------------------------------------
// cppcheck-suppress unusedFunction
void TST_VEllipticalArc::CompareTwoWays()
{
    QFETCH(QPointF, c);
    QFETCH(qreal, radius1);
    QFETCH(qreal, radius2);
    QFETCH(qreal, f1);
    QFETCH(qreal, f2);
    QFETCH(qreal, rotationAngle);

    const VPointF center(c);

    VEllipticalArc arc1(center, radius1, radius2, f1, f2, rotationAngle);
    const qreal length = arc1.GetLength();

    VEllipticalArc arc2(length, center, radius1, radius2, f1, rotationAngle);

    const qreal lengthEps = ToPixel(0.1, Unit::Mm); // computing error

    const QString errorLengthMsg =
            QString("Difference between real and computing lengthes bigger than eps = %1. l1 = %2; l2 = %3");
    QVERIFY2(qAbs(arc2.GetLength() - length) <= lengthEps,
             qUtf8Printable(errorLengthMsg.arg(lengthEps).arg(arc2.GetLength()).arg(length)));
    QVERIFY2(qAbs(arc1.GetLength() - arc2.GetLength()) <= lengthEps,
             qUtf8Printable(errorLengthMsg.arg(lengthEps).arg(arc2.GetLength()).arg(arc2.GetLength())));

    const qreal angleEps = 0.4;
    const QString errorAngleMsg =
            QString("Difference between real and computing angles bigger than eps = %1. f1 = %2; f2 = %3");
    // compare angles
    const qreal diff = qAbs(arc1.GetEndAngle() - arc2.GetEndAngle());
    QVERIFY2(qAbs(diff - 360.0*(diff/360.0)) <= angleEps,
             qUtf8Printable(errorAngleMsg.arg(angleEps).arg(arc1.GetEndAngle()).arg(arc2.GetEndAngle())));
}

//---------------------------------------------------------------------------------------------------------------------
// cppcheck-suppress unusedFunction
void TST_VEllipticalArc::NegativeArc()
{
    const VPointF center;
    const qreal radius1 = 100;
    const qreal radius2 = 200;
    const qreal f1 = 1;
    const qreal f2 = 181;
    const qreal rotationAngle = 0;

    // Full ellipse
    const qreal h = ((radius1-radius2)*(radius1-radius2))/((radius1+radius2)*(radius1+radius2));
    const qreal length = M_PI*(radius1+radius2)*(1+3*h/(10+qSqrt(4-3*h)))/2;
    VEllipticalArc arc(-length, center, radius1, radius2, f1, rotationAngle);

    const qreal eps = ToPixel(0.45, Unit::Mm); // computing error
    const QString errorMsg =
            QString("Difference between real and computing lengthes bigger than eps = %1.  v1 = %2; v2 = %3");


            QVERIFY2(qAbs(arc.GetLength() + length) <= eps,
                     qUtf8Printable(errorMsg.arg(eps).arg(arc.GetLength()).arg(length)));

            const qreal angleEps = 0.4;
            QVERIFY2(arc.GetEndAngle() - f2 <= angleEps,
                     qUtf8Printable(errorMsg.arg(eps).arg(arc.GetEndAngle()).arg(f2)));
}

// cppcheck-suppress unusedFunction
//---------------------------------------------------------------------------------------------------------------------
void TST_VEllipticalArc::TestGetPoints1_data()
{
    TestData();
}

//---------------------------------------------------------------------------------------------------------------------
void TST_VEllipticalArc::TestGetPoints2_data()
{
    TestData();
}

//---------------------------------------------------------------------------------------------------------------------
void TST_VEllipticalArc::TestGetPoints3_data()
{
    TestData();
}

//---------------------------------------------------------------------------------------------------------------------
void TST_VEllipticalArc::TestGetPoints4_data()
{
    TestData();
}

//---------------------------------------------------------------------------------------------------------------------
void TST_VEllipticalArc::TestData()
{
    QTest::addColumn<qreal>("radius1");
    QTest::addColumn<qreal>("radius2");
    QTest::addColumn<qreal>("startAngle");
    QTest::addColumn<qreal>("endAngle");
    QTest::addColumn<qreal>("rotationAngle");

    QTest::newRow("Full circle: radiuses 10, 20; start 0") << 10.0 << 20.0 << 0.0 << 360.0 << 0.0;
    QTest::newRow("Full circle: radiuses 150, 200; start 0") << 150.0 << 200.0 << 0.0 << 360.0 << 0.0;
    QTest::newRow("Full circle: radiuses 150, 200, rotation 30; start 0") << 150.0 << 200.0 << 0.0 << 360.0 << 30.0;
    QTest::newRow("Full circle: radiuses 1500, 1000; start 0") << 1500.0 << 1000.0 << 0.0 << 360.0 << 0.0;
    QTest::newRow("Full circle: radiuses 1500, 1000, rotation 50; start 0") << 1500.0 << 1000.0 << 0.0 << 360.0 << 50.0;
    QTest::newRow("Full circle: radiuses 15000, 10000, rotation 90; start 0") << 15000.0 << 10000.0 << 0.0 << 360.0
                                                                              << 90.0;

    QTest::newRow("Full circle: radiuses 10, 20; start 90") << 10.0 << 20.0 << 90.0 << 90.0 << 0.0;
    QTest::newRow("Full circle: radiuses 150, 200; start 90") << 150.0 << 200.0 << 90.0 << 90.0 << 0.0;
    QTest::newRow("Full circle: radiuses 150, 200, rotation 30; start 90") << 150.0 << 200.0 << 90.0 << 90.0 << 30.0;
    QTest::newRow("Full circle: radiuses 1500, 1000; start 90") << 1500.0 << 1000.0 << 90.0 << 90.0 << 0.0;
    QTest::newRow("Full circle: radiuses 1500, 1000, rotation 50; start 90") << 1500.0 << 1000.0 << 90.0 << 90.0
                                                                             << 50.0;
    QTest::newRow("Full circle: radiuses 15000, 10000, rotation 90; start 90") << 15000.0 << 10000.0 << 90.0 << 90.0
                                                                              << 90.0;

    QTest::newRow("Arc less than 45 degree, radiuses 100, 50") << 100.0 << 50.0 << 0.0 << 10.5 << 0.0;
    QTest::newRow("Arc less than 45 degree, radiuses 150, 50, rotation 180") << 150.0 << 50.0 << 0.0 << 10.5 << 180.0;
    QTest::newRow("Arc less than 45 degree, radiuses 1500, 800, rotation 90") << 1500.0 << 800.0 << 0.0 << 10.5 << 90.0;
    QTest::newRow("Arc less than 45 degree, radiuses 15000, 10000, rotation 40")
            << 50000.0 << 10000.0 << 0.0 << 10.5 << 40.0;
    QTest::newRow("Arc less than 45 degree, radiuses 15000, 10000") << 15000.0 << 10000.0 << 0.0 << 10.5 << 0.0;

    QTest::newRow("Arc 45 degree, radiuses 100, 50, rotation 45") << 100.0 << 50.0 << 0.0 << 45.0 << 45.0;
    QTest::newRow("Arc 45 degree, radiuses 150, 15, rotation 30") << 150.0 << 15.0 << 0.0 << 45.0 << 30.0;
    QTest::newRow("Arc 45 degree, radiuses 1500, 150, rotation 45") << 1500.0 << 150.0 << 0.0 << 45.0 << 45.0;
    QTest::newRow("Arc 45 degree, radiuses 50000, 50000") << 50000.0 << 50000.0 << 0.0 << 45.0 << 0.0;
    QTest::newRow("Arc 45 degree, radiuses 90000, 50000, rotation 270") << 90000.0 << 50000.0 << 0.0 << 45.0 << 270.0;

    QTest::newRow("Arc less than 90 degree, radiuses 100, 400, rotation 50") << 100.0 << 400.0 << 0.0 << 75.0 << 50.0;
    QTest::newRow("Arc less than 90 degree, radiuses 150, 400, rotation 90") << 150.0 << 400.0 << 0.0 << 75.0 << 90.0;
    QTest::newRow("Arc less than 90 degree, radiuses 1500, 50000, rotation 180")
            << 1500.0 << 50000.0 << 0.0 << 75.0 << 180.0;
    QTest::newRow("Arc less than 90 degree, radiuses 50000, 5000, rotation 30")
            << 50000.0 << 5000.0 << 0.0 << 75.0 << 30.0;
    QTest::newRow("Arc less than 90 degree, radiuses 90000, 50000, rotation 30")
            << 90000.0 << 50000.0 << 0.0 << 75.0 << 30.0;

    QTest::newRow("Arc 90 degree, radiuses 100, 50, rotation 30") << 100.0 << 50.0 << 0.0 << 90.0 << 30.0;
    QTest::newRow("Arc 90 degree, radiuses 150, 400") << 150.0 << 400.0 << 0.0 << 90.0 << 0.0;
    QTest::newRow("Arc 90 degree, radiuses 1500, 800, rotation 70") << 1500.0 << 800.0 << 0.0 << 90.0 << 70.0;
    QTest::newRow("Arc 90 degree, radiuses 50000, 5000, rotation 30") << 50000.0 << 5000.0 << 0.0 << 90.0 << 30.0;
    QTest::newRow("Arc 90 degree, radiuses 90000, 50000, rotation 235") << 90000.0 << 50000.0 << 0.0 << 90.0 << 235.0;

    QTest::newRow("Arc less than 135 degree, radiuses 100, 50, rotation 60") << 100.0 << 50.0 << 0.0 << 110.6 << 60.0;
    QTest::newRow("Arc less than 135 degree, radiuses 150, 400, rotation 300")
            << 150.0 << 400.0 << 0.0 << 110.6 << 300.0;
    QTest::newRow("Arc less than 135 degree, radiuses 1500, 800, rotation 360")
            << 1500.0 << 800.0 << 0.0 << 110.6 << 360.0;
    QTest::newRow("Arc less than 135 degree, radiuses 50000, 5000, rotation 290")
            << 50000.0 << 5000.0 << 0.0 << 110.6 << 290.0;
    QTest::newRow("Arc less than 135 degree, radiuses 90000, 50000") << 90000.0 << 50000.0 << 0.0 << 110.6 << 0.0;

    QTest::newRow("Arc 135 degree, radiuses 100, 50") << 100.0 << 50.0 << 0.0 << 135.0 << 0.0;
    QTest::newRow("Arc 135 degree, radiuses 150, 400") << 150.0 << 400.0 << 0.0 << 135.0 << 0.0;
    QTest::newRow("Arc 135 degree, radiuses 1500, 800") << 1500.0 << 800.0 << 0.0 << 135.0 << 0.0;
    QTest::newRow("Arc 135 degree, radiuses 50000, 5000, rotation 20") << 50000.0 << 5000.0 << 0.0 << 135.0 << 20.0;
    QTest::newRow("Arc 135 degree, radiuses 90000, 50000") << 90000.0 << 50000.0 << 0.0 << 135.0 << 0.0;

    QTest::newRow("Arc less than 180 degree, radiuses 100, 50") << 100.0 << 50.0 << 0.0 << 160.7 << 0.0;
    QTest::newRow("Arc less than 180 degree, radiuses 150, 400") << 150.0 << 400.0 << 0.0 << 160.7 << 0.0;
    QTest::newRow("Arc less than 180 degree, radiuses 1500, 800") << 1500.0 << 800.0 << 0.0 << 160.7 << 0.0;
    QTest::newRow("Arc less than 180 degree, radiuses 50000, 5000, rotation 270")
            << 50000.0 << 5000.0 << 0.0 << 160.7 << 270.0;
    QTest::newRow("Arc less than 180 degree, radiuses 90000, 50000") << 90000.0 << 50000.0 << 0.0 << 160.7 << 0.0;

    QTest::newRow("Arc 180 degree, radiuses 100, 50") << 100.0 << 50.0 << 0.0 << 180.0 << 0.0;
    QTest::newRow("Arc 180 degree, radiuses 150, 400") << 150.0 << 400.0 << 0.0 << 180.0 << 0.0;
    QTest::newRow("Arc 180 degree, radiuses 1500, 800") << 1500.0 << 800.0 << 0.0 << 180.0 << 0.0;
    QTest::newRow("Arc 180 degree, radiuses 50000, 5000, rotation 60") << 50000.0 << 5000.0 << 0.0 << 180.0 << 60.0;
    QTest::newRow("Arc 180 degree, radiuses 90000, 50000") << 90000.0 << 50000.0 << 0.0 << 180.0 << 0.0;

    QTest::newRow("Arc less than 270 degree, radiuses 100, 50") << 100.0 << 50.0 << 0.0 << 150.3 << 0.0;
    QTest::newRow("Arc less than 270 degree, radiuses 150, 400") << 150.0 << 400.0 << 0.0 << 150.3 << 0.0;
    QTest::newRow("Arc less than 270 degree, radiuses 1500, 800") << 1500.0 << 800.0 << 0.0 << 150.3 << 0.0;
    QTest::newRow("Arc less than 270 degree, radiuses 50000, 5000, rotation 20")
            << 50000.0 << 5000.0 << 0.0 << 150.3 << 20.0;
    QTest::newRow("Arc less than 270 degree, radiuses 90000, 50000") << 90000.0 << 50000.0 << 0.0 << 150.3 << 0.0;

    QTest::newRow("Arc 270 degree, radiuses 100, 50") << 100.0 << 50.0 << 0.0 << 270.0 << 0.0;
    QTest::newRow("Arc 270 degree, radiuses 150, 400") << 150.0 << 400.0 << 0.0 << 270.0 << 0.0;
    QTest::newRow("Arc 270 degree, radiuses 1500, 800") << 1500.0 << 800.0 << 0.0 << 270.0 << 0.0;
    QTest::newRow("Arc 270 degree, radiuses 50000, 5000, rotation 90") << 50000.0 << 5000.0 << 0.0 << 270.0 << 90.0;
    QTest::newRow("Arc 270 degree, radiuses 90000, 50000") << 90000.0 << 50000.0 << 0.0 << 270.0 << 0.0;

    QTest::newRow("Arc less than 360 degree, radiuses 100, 50") << 100.0 << 50.0 << 0.0 << 340.0 << 0.0;
    QTest::newRow("Arc less than 360 degree, radiuses 150, 400") << 150.0 << 400.0 << 0.0 << 340.0 << 0.0;
    QTest::newRow("Arc less than 360 degree, radiuses 1500, 800") << 1500.0 << 800.0 << 0.0 << 340.0 << 0.0;
    QTest::newRow("Arc less than 360 degree, radiuses 50000, 5000, rotation 30")
            << 50000.0 << 5000.0 << 0.0 << 340.0 << 30.0;
    QTest::newRow("Arc less than 360 degree, radiuses 90000, 50000") << 90000.0 << 50000.0 << 0.0 << 340.0 << 0.0;

    QTest::newRow("Arc start 90 degree, angle 45 degree, radiuses 100, 50") << 100.0 << 50.0 << 90.0 << 135.0 << 0.0;
    QTest::newRow("Arc start 90 degree, angle 45 degree, radiuses 150, 400") << 150.0 << 400.0 << 90.0 << 135.0 << 0.0;
    QTest::newRow("Arc start 90 degree, angle 45 degree, radiuses 1500, 800")
            << 1500.0 << 800.0 << 90.0 << 135.0 << 0.0;
    QTest::newRow("Arc start 90 degree, angle 45 degree, radiuses 50000, 5000")
            << 50000.0 << 5000.0 << 90.0 << 135.0 << 0.0;
    QTest::newRow("Arc start 90 degree, angle 45 degree, radiuses 90000, 50000")
            << 90000.0 << 50000.0 << 90.0 << 135.0 << 0.0;
}

//---------------------------------------------------------------------------------------------------------------------
// cppcheck-suppress unusedFunction
void TST_VEllipticalArc::TestGetPoints1()
{
    //Any point must satisfy the equation of ellipse
    QFETCH(qreal, radius1);
    QFETCH(qreal, radius2);
    QFETCH(qreal, startAngle);
    QFETCH(qreal, endAngle);
    QFETCH(qreal, rotationAngle);

    const VPointF center;
    VEllipticalArc arc(center, radius1, radius2, startAngle, endAngle, rotationAngle);

    QVector<QPointF> points = arc.getPoints();
    if (qFuzzyIsNull(rotationAngle))
    { // equation of ellipse will be different when rotation angle isn't 0 so we can't use this test in this case
        const qreal eps = 0.05;

        for (auto p : points)
        {
            const qreal equationRes = p.rx()*p.rx()/(radius1*radius1) + p.ry()*p.ry()/(radius2*radius2);
            const qreal diff = qAbs(equationRes - 1);
            const QString errorMsg = QString("Broken the first rule. Any point must satisfy the equation of ellipse."
                                             "diff = '%1' > eps = '%2'").number(diff).number(eps);
            QVERIFY2( diff <= eps, qUtf8Printable(errorMsg));
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------
// cppcheck-suppress unusedFunction
void TST_VEllipticalArc::TestGetPoints2()
{
    // Distance from the any point to the focus1 plus distance from this point to the focus2 should be the same.
    QFETCH(qreal, radius1);
    QFETCH(qreal, radius2);
    QFETCH(qreal, startAngle);
    QFETCH(qreal, endAngle);
    QFETCH(qreal, rotationAngle);

    const VPointF center;
    VEllipticalArc arc(center, radius1, radius2, startAngle, endAngle, rotationAngle);
    QVector<QPointF> points = arc.getPoints();

    const qreal c = qSqrt(qAbs(radius2*radius2 - radius1*radius1));
    // distance from the center to the focus

    QPointF focus1 = static_cast<QPointF>(center);
    QPointF focus2 = static_cast<QPointF>(center);

    if (radius1 < radius2)
    {
        focus1.setY(focus1.ry() + c);
        QLineF line(static_cast<QPointF>(center), focus1);
        line.setAngle(line.angle() + rotationAngle);
        focus1 = line.p2();

        focus2.setY(focus2.ry() - c);
        line.setP2(focus2);
        line.setAngle(line.angle() + rotationAngle);
        focus2 = line.p2();
    }
    else
    {
        focus1.setX(focus1.rx() + c);
        QLineF line(static_cast<QPointF>(center), focus1);
        line.setAngle(line.angle() + rotationAngle);
        focus1 = line.p2();

        focus2.setX(focus2.rx() - c);
        line.setP2(focus2);
        line.setAngle(line.angle() + rotationAngle);
        focus2 = line.p2();
    }

    QPointF ellipsePoint(center.x() + radius1, center.y());
    QLineF line(static_cast<QPointF>(center), ellipsePoint);
    line.setAngle(line.angle() + rotationAngle);
    ellipsePoint = line.p2();

    const QLineF distance1(focus1, ellipsePoint);
    const QLineF distance2(focus2, ellipsePoint);

    const qreal distance = distance1.length() + distance2.length();
    const qreal eps = distance * 1.1 / 100; // computing error 1.1 % from origin distance
    for (int i=0; i < points.size(); ++i)
    {
        const QLineF rLine1(focus1, points.at(i));
        const QLineF rLine2(focus2, points.at(i));
        const qreal resultingDistance = rLine1.length()+rLine2.length();
        const qreal diff = qAbs(resultingDistance - distance);
        const QString errorMsg = QString("Broken the first rule, part 2. Distance from the any point to the focus1"
                                         " plus distance from this point to the focus2 should be the same. Problem"
                                         " with point '%1'. The disired distance is '%2', but resulting distance"
                                         " is '%3'. Difference is '%4' and it biggest than eps '%5')").number(i)
                                         .number(distance).number(resultingDistance).number(diff).number(eps);
        QVERIFY2( diff <= eps, qUtf8Printable(errorMsg));
    }
}

//---------------------------------------------------------------------------------------------------------------------
// cppcheck-suppress unusedFunction
void TST_VEllipticalArc::TestGetPoints3()
{
    // Compare full ellipse square with square of VAbstractDetail
    QFETCH(qreal, radius1);
    QFETCH(qreal, radius2);
    QFETCH(qreal, startAngle);
    QFETCH(qreal, endAngle);
    QFETCH(qreal, rotationAngle);

    const VPointF center;
    VEllipticalArc arc(center, radius1, radius2, startAngle, endAngle, rotationAngle);
    QVector<QPointF> points = arc.getPoints();

    if (VFuzzyComparePossibleNulls(arc.AngleArc(), 360.0))
    {// calculated full ellipse square
        const qreal ellipseSquare = M_PI * radius1 * radius2;
        const qreal epsSquare = ellipseSquare * 1.7 / 100; // computing error 0.5 % from origin squere
        const qreal arcSquare = qAbs(VAbstractPiece::sumTrapezoids(points)/2.0);
        const qreal diffSquare = qAbs(ellipseSquare - arcSquare);
        const QString errorMsg1 = QString("Broken the second rule. Interpolation has too big computing error. "
                                          "Difference ='%1' bigger than eps = '%2'.").arg(diffSquare).arg(epsSquare);
        QVERIFY2(diffSquare <= epsSquare, qUtf8Printable(errorMsg1));
    }
}

//---------------------------------------------------------------------------------------------------------------------
// cppcheck-suppress unusedFunction
void TST_VEllipticalArc::TestGetPoints4()
{
    // Compare real full ellipse length with calculated
    QFETCH(qreal, radius1);
    QFETCH(qreal, radius2);
    QFETCH(qreal, startAngle);
    QFETCH(qreal, endAngle);
    QFETCH(qreal, rotationAngle);

    const VPointF center;
    VEllipticalArc arc(center, radius1, radius2, startAngle, endAngle, rotationAngle);

    if (VFuzzyComparePossibleNulls(arc.AngleArc(), 360.0))
    {// calculated full ellipse length
        const qreal h = ((radius1-radius2)*(radius1-radius2))/((radius1+radius2)*(radius1+radius2));
        const qreal ellipseLength =  M_PI*(radius1+radius2)*(1+3*h/(10+qSqrt(4-3*h)));
        const qreal epsLength = ellipseLength*0.5/100; // computing error
        VEllipticalArc arc(center, radius1, radius2, 0, 360, 0);
        const qreal arcLength = arc.GetLength();
        const qreal diffLength = qAbs(arcLength - ellipseLength);
        const QString errorMsg2 = QString("Difference between real and computing lengthes "
                                          "(diff = '%1') bigger than eps = '%2'.").arg(diffLength).arg(epsLength);
        QVERIFY2(diffLength <= epsLength, qUtf8Printable(errorMsg2));
    }
}

//---------------------------------------------------------------------------------------------------------------------
void TST_VEllipticalArc::TestRotation_data()
{
    QTest::addColumn<QPointF>("center");
    QTest::addColumn<qreal>("radius1");
    QTest::addColumn<qreal>("radius2");
    QTest::addColumn<qreal>("startAngle");
    QTest::addColumn<qreal>("endAngle");
    QTest::addColumn<qreal>("rotationAngle");
    QTest::addColumn<QPointF>("rotatePoint");
    QTest::addColumn<qreal>("degrees");
    QTest::addColumn<QString>("prefix");

    QTest::newRow("Test el arc 1") << QPointF() << 10. << 20.0 << 1. << 91. << 0.<< QPointF() << 90. << "_r";
    QTest::newRow("Test el arc 2") << QPointF() << 10. << 20.0 << 0. << 90. << 0.<< QPointF() << 90. << "_r";
    QTest::newRow("Test el arc 3.2") << QPointF(10, 10) << 10. << 20.0 << 0. << 90. << 0.<< QPointF() << 90. << "_r";
    QTest::newRow("Test el arc 3.1") << QPointF(10, 10) << 10. << 20.0 << 1. << 91. << 0.<< QPointF() << 90. << "_r";
    QTest::newRow("Test el arc 3") << QPointF(10, 10) << 10. << 20.0 << 1. << 91. << 90.<< QPointF() << 90. << "_r";
    QTest::newRow("Test el arc 4") << QPointF(10, 10) << 10. << 20.0 << 0. << 90. << 90.<< QPointF() << 90. << "_r";
    QTest::newRow("Test el arc 5") << QPointF(10, 10) << 10. << 20.0 << 0. << 180. << 90.<< QPointF() << 90. << "_r";
    QTest::newRow("Test el arc 6") << QPointF(10, 10) << 10. << 20.0 << 1. << 181. << 90.<< QPointF() << 90. << "_r";
    QTest::newRow("Test el arc 7") << QPointF(10, 10) << 10. << 20.0 << 0. << 270. << 90.<< QPointF() << 90. << "_r";
    QTest::newRow("Test el arc 8") << QPointF(10, 10) << 10. << 20.0 << 1. << 271. << 90.<< QPointF() << 90. << "_r";
    QTest::newRow("Test el arc 9") << QPointF(10, 10) << 10. << 20.0 << 0. << 360. << 90.<< QPointF() << 90. << "_r";
}

//---------------------------------------------------------------------------------------------------------------------
void TST_VEllipticalArc::TestRotation()
{
    QFETCH(QPointF, center);
    QFETCH(qreal, radius1);
    QFETCH(qreal, radius2);
    QFETCH(qreal, startAngle);
    QFETCH(qreal, endAngle);
    QFETCH(qreal, rotationAngle);
    QFETCH(QPointF, rotatePoint);
    QFETCH(qreal, degrees);
    QFETCH(QString, prefix);

    const VEllipticalArc arcOrigin(VPointF(center), radius1, radius2, startAngle, endAngle, rotationAngle);
    const VEllipticalArc rotatedArc = arcOrigin.Rotate(rotatePoint, degrees, prefix);

    QVERIFY2(qAbs(arcOrigin.AngleArc() - rotatedArc.AngleArc()) <= 1.6,
            qUtf8Printable(QString("a1 = %1, a2 - %2").arg(arcOrigin.AngleArc()).arg(rotatedArc.AngleArc())));

    QString errorLengthMsg =
            QString("Difference between real and computing lengthes bigger than eps = %1. l1 = %2; l2 = %3");
    QVERIFY2(qAbs(arcOrigin.GetLength() - rotatedArc.GetLength()) <= ToPixel(1, Unit::Mm),
             qUtf8Printable(errorLengthMsg.arg(ToPixel(1, Unit::Mm))
                            .arg(arcOrigin.GetLength())
                            .arg(rotatedArc.GetLength())));

    QCOMPARE(arcOrigin.GetRadius1(), rotatedArc.GetRadius1());
    QCOMPARE(arcOrigin.GetRadius2(), rotatedArc.GetRadius2());
    QCOMPARE(arcOrigin.GetRotationAngle(), rotatedArc.GetRotationAngle());
    const QString errorMsg = QString("The name doesn't contain the prefix '%1'.").arg(prefix);
    QVERIFY2(rotatedArc.name().endsWith(prefix), qUtf8Printable(errorMsg));
}

//---------------------------------------------------------------------------------------------------------------------
void TST_VEllipticalArc::TestFlip_data()
{
    QTest::addColumn<VEllipticalArc>("elArc");
    QTest::addColumn<QLineF>("axis");
    QTest::addColumn<QString>("prefix");

    const VEllipticalArc elArc(VPointF(), 10., 20.0, 1., 91., 0.);

    QLineF axis(QPointF(600, 30), QPointF(600, 1800));

    QTest::newRow("Vertical axis") << elArc << axis << "a2";

    axis = QLineF(QPointF(600, 30), QPointF(1200, 30));

    QTest::newRow("Horizontal axis") << elArc << axis << "a2";

    axis = QLineF(QPointF(600, 30), QPointF(600, 1800));
    axis.setAngle(45);

    QTest::newRow("Diagonal axis") << elArc << axis << "a2";
}

//---------------------------------------------------------------------------------------------------------------------
void TST_VEllipticalArc::TestFlip()
{
    QFETCH(VEllipticalArc, elArc);
    QFETCH(QLineF, axis);
    QFETCH(QString, prefix);

    const VEllipticalArc res = elArc.Flip(axis, prefix);

    const QString errorMsg = QString("The name doesn't contain the prefix '%1'.").arg(prefix);
    QVERIFY2(res.name().endsWith(prefix), qUtf8Printable(errorMsg));

    QCOMPARE(qRound(elArc.GetLength()*-1), qRound(res.GetLength()));
    QCOMPARE(elArc.GetRadius1(), res.GetRadius1());
    QCOMPARE(elArc.GetRadius2(), res.GetRadius2());
}
