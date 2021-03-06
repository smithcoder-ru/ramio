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

#pragma once

#include <Items/MetaItems.h>

struct UserRecord : Ramio::MetaItemData
{
	RMString login;
	RMString password;

	RMETA_DATA_START(MetaItemData)
	RMETA_DATA_FIELD_C(login, String, "Имя")
	RMETA_DATA_FIELD_C(password, String, "Пароль")
	RMETA_DATA_END

	UserRecord() = default;
	UserRecord(QString a, QString b) : login(std::move(a)), password(std::move(b)) {}
};

class User : public Ramio::StructItem<UserRecord>
{
	using Base = Ramio::StructItem<UserRecord>;
public:
	User(Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(watcher) {}
	User(const UserRecord& data, Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(data, watcher) {}
	User(UserRecord&& data, Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(std::forward<UserRecord>(data), watcher) {}
	~User() Q_DECL_OVERRIDE  { this->beforeDeleted(); }

	QString shortDesc() const Q_DECL_OVERRIDE;
};

GENERATE_HEADER_METASET(MetaUserSet, User, UserRecord)
