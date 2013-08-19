/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "bar_p.h"
#include <QPainter>
#include <QGraphicsSceneEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

Bar::Bar(QBarSet *barset, int index, QGraphicsItem *parent) : QGraphicsRectItem(parent),
    m_index(index),
    m_barset(barset),
    m_hovering(false)
{
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
    setAcceptHoverEvents(true);
}

Bar::~Bar()
{
    // End hover event, if bar is deleted during it
    if (m_hovering) {
        emit hovered(false, m_barset);
        emit hovered(false, m_index, m_barset);
    }
}

void Bar::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    emit clicked(m_index, m_barset);
    QGraphicsItem::mousePressEvent(event);
}

void Bar::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    m_hovering = true;
    emit hovered(true, m_barset);
    emit hovered(true, m_index, m_barset);

}

void Bar::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    m_hovering = false;
    emit hovered(false, m_barset);
    emit hovered(false, m_index, m_barset);
}

#include "moc_bar_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
