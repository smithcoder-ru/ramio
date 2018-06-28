/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, a Qt-based casual C++ classes for quick application writing.
 *
 * Ramio is free software; you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation;
 * either version 3 of the License, or (at your option) any later version.
 *
 * Ramio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Ramio; see the file LICENSE. If not, see <http://www.gnu.org/licenses/>.
 */

#include "UISets.h"
// All Qt gui classes
#include <QtWidgets>
#include <QStringBuilder>

namespace Ramio {

QString fullParentName(const QWidget* w)
{
	QString result = w->objectName();
	const QWidget* parent = w->parentWidget();
	while (parent)
	{
		result=parent->objectName().append("/").append(result);
		parent = parent->parentWidget();
	}
	return result;
}

#define FPN QString(fpn)

void UISets::saveWidget(const QWidget* w) const
{
	const QString fpn = fullParentName(w).append("/");

	if (const auto* splitter = dynamic_cast<const QSplitter*>(w))
		settings_->setValue(FPN.append("State"), splitter->saveState());
	else if  (const auto* table = dynamic_cast<const QTableView*>(w))
		settings_->setValue(FPN.append("HorizontalHeaderState"), table->horizontalHeader()->saveState());
	else if  (const auto* edit = dynamic_cast<const QLineEdit*>(w))
		settings_->setValue(FPN.append("Text"), edit->text());
	else if  (const auto* box = dynamic_cast<const QSpinBox*>(w))
		settings_->setValue(FPN.append("Value"), box->value());
	else if  (const auto* box = dynamic_cast<const QCheckBox*>(w))
		settings_->setValue(FPN.append("Value"), box->checkState());
	else
		Q_ASSERT_X(0, "UISets","type not support");
}

void UISets::loadWidget(QWidget* w) const
{
	const QString fpn = fullParentName(w).append("/");

	if (auto* splitter = dynamic_cast<QSplitter*>(w))
	{
		QByteArray data = settings_->value(FPN.append("State")).toByteArray();
		if (!data.isEmpty()) splitter->restoreState(data);
	}
	else if (auto* table = dynamic_cast<QTableView*>(w))
	{
		QByteArray data = settings_->value(FPN.append("HorizontalHeaderState")).toByteArray();
		if (!data.isEmpty()) table->horizontalHeader()->restoreState(data);
	}
	else if (auto* edit = dynamic_cast<QLineEdit*>(w))
	{
		QString data = settings_->value(FPN.append("HorizontalHeaderState")).toString();
		if (!data.isEmpty()) edit->setText(data);
	}
	else if (auto* box = dynamic_cast<QSpinBox*>(w))
	{
		bool ok = false;
		int data = settings_->value(FPN.append("Value")).toInt(&ok);
		if (ok) box->setValue(data);
	}
	else if (auto* box = dynamic_cast<QCheckBox*>(w))
	{
		bool ok = false;
		int data = settings_->value(FPN.append("Value")).toInt(&ok);
		if (ok) box->setCheckState(Qt::CheckState(data));
	}
	else
		Q_ASSERT_X(0, "UISets","type not support");
}

void UISets::saveGeometry(const QWidget* w) const
{
	settings_->setValue(fullParentName(w).append("/Geometry"), w->saveGeometry());
}

void UISets::loadGeometry(QWidget* w) const
{
	QByteArray data = settings_->value(fullParentName(w).append("/Geometry")).toByteArray();
	if (!data.isEmpty()) w->restoreGeometry(data);
}

UISets::UISets(const QString& targetName)
{
	QString name = qApp->applicationDirPath() % QLatin1Literal("/Config/") % targetName % QLatin1Literal(".UISets.ini");
	settings_.reset(new QSettings(name, QSettings::IniFormat));
}

UISets::~UISets()
{
	settings_->sync();
}

UISets& UISets::uiSets(const QString& targetName)
{
	static UISets result(targetName);
	return result;
}

const UISets& uiSets(const QString& targetName)
{
	return UISets::uiSets(targetName);
}

} // Ramio::
