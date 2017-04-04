/*
 * Copyright 2013,2015-2017 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MOCKAPPLICATIONINFO_H
#define MOCKAPPLICATIONINFO_H

#include <ApplicationInfoInterface.h>

#include <QUrl>

using namespace unity::shell::application;

class UNITY_API MockApplicationInfo: public ApplicationInfoInterface
{
    Q_OBJECT
public:
    MockApplicationInfo(const QString &appId, const QString& name, const QString& comment, const QUrl& icon, QObject* parent = 0);

    void close() override {}

    QString appId() const override;
    QString name() const override;
    QString comment() const override;
    QUrl icon() const override;
    bool focused() const override;

    QString splashTitle() const override;
    QUrl splashImage() const override;
    bool splashShowHeader() const override;
    QColor splashColor() const override;
    QColor splashColorHeader() const override;
    QColor splashColorFooter() const override;

    Qt::ScreenOrientations supportedOrientations() const override;
    bool rotatesWindowContents() const override;

    bool isTouchApp() const override;
    bool exemptFromLifecycle() const override;
    void setExemptFromLifecycle(bool exemptFromLifecycle) override;

    QSize initialSurfaceSize() const override { return QSize(); }
    void setInitialSurfaceSize(const QSize &) override {}

    int surfaceCount() const override;

    ApplicationInstanceListInterface* instanceList() const override { return nullptr; }

private:
    QString m_appId;
    QString m_name;
    QString m_comment;
    QUrl m_icon;
    bool m_focused;
    bool m_exemptFromLifecycle;
};

#endif // MOCKAPPLICATIONINFO_H
