/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtOpenGL module of the Qt Toolkit.
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

#ifndef QGLPIXELBUFFER_P_H
#define QGLPIXELBUFFER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of the QLibrary class.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//

#include "QtOpenGL/qglpixelbuffer.h"
#include <private/qgl_p.h>
#include <private/qglpaintdevice_p.h>

QT_BEGIN_NAMESPACE

class QEglContext;
class QOpenGLFramebufferObject;

class QGLPBufferGLPaintDevice : public QGLPaintDevice
{
public:
    virtual QPaintEngine* paintEngine() const {return pbuf->paintEngine();}
    virtual QSize size() const {return pbuf->size();}
    virtual QGLContext* context() const;
    virtual void beginPaint();
    virtual void endPaint();
    void setPBuffer(QGLPixelBuffer* pb);
    void setFbo(GLuint fbo);
private:
    QGLPixelBuffer* pbuf;
};

class QGLPixelBufferPrivate {
    Q_DECLARE_PUBLIC(QGLPixelBuffer)
public:
    QGLPixelBufferPrivate(QGLPixelBuffer *q) : q_ptr(q), invalid(true), qctx(0), widget(0), fbo(0), blit_fbo(0), pbuf(0), ctx(0)
    {
    }
    bool init(const QSize &size, const QGLFormat &f, QGLWidget *shareWidget);
    void common_init(const QSize &size, const QGLFormat &f, QGLWidget *shareWidget);
    bool cleanup();

    QGLPixelBuffer *q_ptr;
    bool invalid;
    QGLContext *qctx;
    QGLPBufferGLPaintDevice glDevice;
    QGLWidget *widget;
    QOpenGLFramebufferObject *fbo;
    QOpenGLFramebufferObject *blit_fbo;
    QGLFormat format;

    QGLFormat req_format;
    QPointer<QGLWidget> req_shareWidget;
    QSize req_size;

    //stubs
    void *pbuf;
    void *ctx;
};

QT_END_NAMESPACE

#endif // QGLPIXELBUFFER_P_H
