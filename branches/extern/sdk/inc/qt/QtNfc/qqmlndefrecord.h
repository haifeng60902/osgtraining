/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtNfc module of the Qt Toolkit.
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

#ifndef QQMLNDEFRECORD_H
#define QQMLNDEFRECORD_H

#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include <QtNfc/QNdefRecord>

QT_BEGIN_NAMESPACE

class QQmlNdefRecordPrivate;

class Q_NFC_EXPORT QQmlNdefRecord : public QObject
{
    Q_OBJECT

    Q_DECLARE_PRIVATE(QQmlNdefRecord)

    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(TypeNameFormat typeNameFormat READ typeNameFormat WRITE setTypeNameFormat NOTIFY typeNameFormatChanged)
    Q_PROPERTY(QNdefRecord record READ record WRITE setRecord NOTIFY recordChanged)

    Q_ENUMS(TypeNameFormat)
public:
    enum TypeNameFormat {
        Empty = QNdefRecord::Empty,
        NfcRtd = QNdefRecord::NfcRtd,
        Mime = QNdefRecord::Mime,
        Uri = QNdefRecord::Uri,
        ExternalRtd = QNdefRecord::ExternalRtd,
        Unknown = QNdefRecord::Unknown
    };

    explicit QQmlNdefRecord(QObject *parent = 0);
    explicit QQmlNdefRecord(const QNdefRecord &record, QObject *parent = 0);

    QString type() const;
    void setType(const QString &t);

    void setTypeNameFormat(TypeNameFormat typeNameFormat);
    TypeNameFormat typeNameFormat() const;

    QNdefRecord record() const;
    void setRecord(const QNdefRecord &record);

Q_SIGNALS:
    void typeChanged();
    void typeNameFormatChanged();
    void recordChanged();

private:
    QQmlNdefRecordPrivate *d_ptr;
};

void Q_NFC_EXPORT qRegisterNdefRecordTypeHelper(const QMetaObject *metaObject,
                                                         QNdefRecord::TypeNameFormat typeNameFormat,
                                                         const QByteArray &type);

Q_NFC_EXPORT QQmlNdefRecord *qNewDeclarativeNdefRecordForNdefRecord(const QNdefRecord &record);

template<typename T>
bool qRegisterNdefRecordType(QNdefRecord::TypeNameFormat typeNameFormat, const QByteArray &type)
{
    qRegisterNdefRecordTypeHelper(&T::staticMetaObject, typeNameFormat, type);
    return true;
}

#define Q_DECLARE_NDEFRECORD(className, typeNameFormat, type) \
static bool _q_##className##_registered = qRegisterNdefRecordType<className>(typeNameFormat, type);

QT_END_NAMESPACE

#endif // QQMLNDEFRECORD_H
