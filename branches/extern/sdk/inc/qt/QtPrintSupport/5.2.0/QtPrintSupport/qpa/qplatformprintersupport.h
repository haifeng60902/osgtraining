/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef QPLATFORMPRINTERSUPPORT_H
#define QPLATFORMPRINTERSUPPORT_H
//
//  W A R N I N G
//  -------------
//
// This file is part of the QPA API and is not meant to be used
// in applications. Usage of this API may make your code
// source and binary incompatible with future versions of Qt.
//

#include <QtPrintSupport/qprinter.h>

#include <QtCore/qlist.h>
#include <QtCore/qhash.h>

QT_BEGIN_NAMESPACE

#ifndef QT_NO_PRINTER

typedef QHash<QString, QString> PrinterOptions;

class QPrintEngine;

class Q_PRINTSUPPORT_EXPORT QPlatformPrinterSupport
{
public:
    QPlatformPrinterSupport();
    virtual ~QPlatformPrinterSupport();

    virtual QPrintEngine *createNativePrintEngine(QPrinter::PrinterMode printerMode);
    virtual QPaintEngine *createPaintEngine(QPrintEngine *, QPrinter::PrinterMode printerMode);
    virtual QList<QPrinter::PaperSize> supportedPaperSizes(const QPrinterInfo &) const;
    virtual QList<QPair<QString, QSizeF> > supportedSizesWithNames(const QPrinterInfo &printerInfo) const;
    virtual QList<QPrinterInfo> availablePrinters();
    virtual QPrinterInfo defaultPrinter();
    virtual QPrinterInfo printerInfo(const QString &printerName);

    virtual QString printerOption(const QPrinterInfo &printer, const QString &key) const;
    virtual PrinterOptions printerOptions(const QPrinterInfo &printer) const;

    static QPrinter::PaperSize convertQSizeFToPaperSize(const QSizeF &sizef);
    static QSizeF convertPaperSizeToQSizeF(QPrinter::PaperSize paperSize);

protected:
    static int printerIndex(const QPrinterInfo &printer);
    static QPrinterInfo createPrinterInfo(const QString &name, const QString &description,
                                          const QString &location, const QString &makeAndModel,
                                          bool isDefault, int index);

    QList<QPrinterInfo> m_printers;
};

#endif // QT_NO_PRINTER

QT_END_NAMESPACE

#endif // QPLATFORMPRINTERSUPPORT_H
