/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtLocation module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qdeclarativegeoshape.h"

#include <QtLocation/QGeoRectangle>
#include <QtLocation/QGeoCircle>

QT_BEGIN_NAMESPACE

/*!
    \qmlbasictype geoshape
    \inqmlmodule QtLocation 5.0
    \ingroup qml-QtLocation5-basictypes
    \since Qt Location 5.0

    \brief A geoshape type represents an abstract geographic area.

    The \c geoshape type represents an abstract geographic area.  It includes attributes and
    methods common to all geographic areas.  To create objects that represent a valid geographic
    area use \l {QtLocation5::georectangle}{georectangle} or
    \l {QtLocation5::geocircle}{geocircle}.

    The \c isValid attribute can be used to test if the geoshape represents a valid geographic
    area.

    The \c isEmpty attribute can be used to test if the geoshape represents a region with a
    geomatrical area of 0.

    The \l contains() method can be used to test if a \l {QtLocation5::coordinate}{coordinate} is
    within the geoshape.

    \section2 Example Usage

    Use properties of type \l variant to store a \c {geoshape}.  To create a \c geoshape use one
    of the methods described below.

    To create a \c geoshape value, specify it as a "shape()" string:

    \qml
    import QtLocation

    Item {
        property variant region: "shape()"
    }
    \endqml

    or with the \l {QtLocation5::QtLocation}{QtLocation.shape()} function:

    \qml
    import QtLocation 5.0

    Item {
        property variant region: QtLocation.shape()
    }
    \endqml

    When integrating with C++, note that any QGeoShape value passed into QML from C++ is
    automatically converted into a \c geoshape value, and vice-versa.

    \section2 Methods

    \section3 contains()

    \code
    bool contains(coordinate coord)
    \endcode

    Returns true if the \l {QtLocation5::coordinate}{coordinate} specified by \a coord is within
    this geoshape; Otherwise returns false.
*/

GeoShapeValueType::GeoShapeValueType(QObject *parent)
:   QQmlValueTypeBase<QGeoShape>(qMetaTypeId<QGeoShape>(), parent)
{
}

GeoShapeValueType::~GeoShapeValueType()
{
}

GeoShapeValueType::ShapeType GeoShapeValueType::type() const
{
    return static_cast<GeoShapeValueType::ShapeType>(v.type());
}

bool GeoShapeValueType::isValid() const
{
    return v.isValid();
}

bool GeoShapeValueType::isEmpty() const
{
    return v.isEmpty();
}

bool GeoShapeValueType::contains(const QGeoCoordinate &coordinate) const
{
    return v.contains(coordinate);
}

QString GeoShapeValueType::toString() const
{
    switch (v.type()) {
    case QGeoShape::UnknownType:
        return QStringLiteral("QGeoShape()");
    case QGeoShape::RectangleType: {
        QGeoRectangle r = v;
        return QStringLiteral("QGeoRectangle({%1, %2}, {%3, %4})")
            .arg(r.topLeft().latitude())
            .arg(r.topLeft().longitude())
            .arg(r.bottomRight().latitude())
            .arg(r.bottomRight().longitude());
    }
    case QGeoShape::CircleType: {
        QGeoCircle c = v;
        return QStringLiteral("QGeoCircle({%1, %2}, %3)")
            .arg(c.center().latitude())
            .arg(c.center().longitude())
            .arg(c.radius());
    }
    }

    return QStringLiteral("QGeoShape(%1)").arg(v.type());
}

void GeoShapeValueType::setValue(const QVariant &value)
{
    if (value.userType() == qMetaTypeId<QGeoShape>())
        v = value.value<QGeoShape>();
    else if (value.userType() == qMetaTypeId<QGeoRectangle>())
        v = value.value<QGeoRectangle>();
    else if (value.userType() == qMetaTypeId<QGeoCircle>())
        v = value.value<QGeoCircle>();
    else
        v = QGeoShape();

    onLoad();
}

bool GeoShapeValueType::isEqual(const QVariant &other) const
{
    if (other.userType() == qMetaTypeId<QGeoShape>())
        return v == other.value<QGeoShape>();
    else if (other.userType() == qMetaTypeId<QGeoRectangle>())
        return v == other.value<QGeoRectangle>();
    else if (other.userType() == qMetaTypeId<QGeoCircle>())
        return v == other.value<QGeoCircle>();
    else
        return false;
}

GeoShapeValueType::GeoShapeValueType(int userType, QObject *parent)
:   QQmlValueTypeBase<QGeoShape>(userType, parent)
{
    QMetaType::construct(userType, &v, 0);
}

QT_END_NAMESPACE
