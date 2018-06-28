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

#pragma once

#include "Protocol.h"
#include <Items/AbstractMetaSet.h>

namespace Ramio {
namespace Proto {

struct DLL_EXPORT APLogin : public AnswerPacket
{
	QString name;
	QString uuid;

	APLogin(qint64 pid = 0) : AnswerPacket(PacketType::Query, qint32(Queries::Login), pid) {}
	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};


struct DLL_EXPORT APGetDataSet : public AnswerPacket
{
	const Ramio::AbstractMetaSet* set = Q_NULLPTR;

	QString dataSetName;

	APGetDataSet(qint64 pid = 0) : AnswerPacket(PacketType::Query, qint32(Queries::GetDataSet), pid) {}
	APGetDataSet(const Ramio::AbstractMetaSet& v_set, qint64 pid = 0)
		: AnswerPacket(PacketType::Query, qint32(Queries::GetDataSet), pid), set(&v_set),
		  dataSetName(set->meta().setName) {}

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct DLL_EXPORT APCreateDataObject : public AnswerPacket
{
	QString dataSetName;
	QString itemName;
	QString itemId;
	QString itemUuid;

	APCreateDataObject(qint64 pid = 0) : AnswerPacket(PacketType::Query, qint32(Queries::CreateDataObject), pid) {}

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct DLL_EXPORT APSaveDataObject : public AnswerPacket
{
	QString dataSetName;
	QString itemName;
	QString itemId;
	QString itemUuid;

	APSaveDataObject(qint64 pid = 0) : AnswerPacket(PacketType::Query, qint32(Queries::SaveDataObject), pid) {}

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct DLL_EXPORT APDeleteDataObject : public AnswerPacket
{
	QString dataSetName;
	QString itemName;
	QString itemId;
	QString itemUuid;

	APDeleteDataObject(qint64 pid = 0) : AnswerPacket(PacketType::Query, qint32(Queries::DeleteDataObject), pid) {}

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

} // Proto::
} // Ramio::
