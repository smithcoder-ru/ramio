/*
 * Copyright (C) 2016-2021 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio Examples, a Qt-based casual C++ classes for quick application writing.
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

#include "Tasks.h"
#include <QtCore/QVariant>
#include <QtGui/QColor>

RMETA_DATA_IMPL(TaskRecord)
RMETA_DATA_FIELD_C(text, String, "Текст")
RMETA_DATA_FIELD_C(time, DateTime, "Время")
RMETA_DATA_FKEY_ID_C(userId, "Пользователь")
RMETA_DATA_FIELD_C(state, Int, "Состояние")
RMETA_DATA_FIELD_C(color, String, "Цвет")
RMETA_DATA_FUNCTION(TaskRecord, stateStr, String, "StateStr", "Состояние")
RMETA_DATA_END

QVariant TaskRecord::stateStr() const
{
	if (state/2%2)
		return state%2 ? "Завершённая" : "Архивиная";
	if (state%2)
		return "Выполненная";
	return "Активная";
}

GENERATE_SOURCE_METACLASS(Task, TaskRecord)

MetaTaskSet::MetaTaskSet(QObject* parent)
		: Base(QStringLiteral("Tasks"), QStringLiteral("Task"), parent)
{
	colorFunction = [](const Ramio::AbstractMetaItemData& data, const Ramio::Meta::Property&) -> QVariant {
		return QColor(static_cast<const TaskRecord&>(data).color);};
	this->meta_.functions[Ramio::Meta::FunctionRoles::BackgroundRole] = &colorFunction;
}

MetaTaskSet::~MetaTaskSet() = default;
