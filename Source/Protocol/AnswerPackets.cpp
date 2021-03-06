/*
 * Copyright (C) 2016-2021 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, a Qt-based casual C++ classes for quick development of a prototype application.
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

#include "AnswerPackets.h"
#include "ProtocolStr.h"
#include <Items/AbstractMetaSet.h>
#include <Items/MetaItemSerialization.h>

namespace Ramio {

void Proto::APLogin::serialize(Proto::XmlDocument& msg) const
{
	AnswerPacket::serialize(msg);
	msg.deParameters.setAttribute(UsernameAtr, name);
	msg.deParameters.setAttribute(UUIDAtr, uuid);
	msg.deParameters.setAttribute(SessionKeyAtr, sessionKey);
}

void Proto::APLogin::deserialize(const Proto::XmlDocument& msg)
{
	AnswerPacket::deserialize(msg);
	name = msg.deParameters.attribute(UsernameAtr);
	uuid = msg.deParameters.attribute(UUIDAtr);
	sessionKey = msg.deParameters.attribute(SessionKeyAtr);
}


Proto::APGetDataObject::APGetDataObject(QString v_dataSetName, QString v_itemName, QString v_id, QString v_uuid, qint64 pid)
	: AnswerPacket(PacketType::Query, qint32(Queries::GetDataObject), pid),
	  dataSetName(std::move(v_dataSetName)),
	  itemName(std::move(v_itemName)),
	  itemId(std::move(v_id)),
	  itemUuid(std::move(v_uuid))
{
}

void Proto::APGetDataObject::createFromData(const Meta::Description& meta, const ItemData& data)
{
	Ramio::Serialization::serialize(meta, data, fields);
}

void Proto::APGetDataObject::updateData(const Meta::Description& meta, ItemData& data) const
{
	Ramio::Serialization::deserialize(meta, data, fields);
}

void Proto::APGetDataObject::serialize(Proto::XmlDocument &msg) const
{
	AnswerPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	QDomElement deItem = msg.deData.ownerDocument().createElement(itemName);
	for (auto it = fields.begin(); it !=fields.end(); ++it)
		deItem.setAttribute(it.key(), it.value());
	msg.deData.appendChild(deItem);
}

void Proto::APGetDataObject::deserialize(const Proto::XmlDocument &msg)
{
	AnswerPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);
	if (!itemName.isEmpty())
	{
		QDomElement deItem = msg.deData.firstChildElement(itemName);
		if (!deItem.isNull())
			for (int i = 0; i < deItem.attributes().count(); i++)
				fields.insert(deItem.attributes().item(i).toAttr().name(), deItem.attributes().item(i).toAttr().value());
	}
}

Proto::APGetDataSet::APGetDataSet(const AbstractMetaSet &v_set, qint64 pid)
	: AnswerPacket(PacketType::Query, qint32(Queries::GetDataSet), pid), set(&v_set),
	  dataSetName(set->meta().setName)
{
}

void Proto::APGetDataSet::serialize(Proto::XmlDocument& msg) const
{
	AnswerPacket::serialize(msg);
	if (set)
	{
		msg.deParameters.setAttribute(DataSetNameAtr, set->meta().setName);
		QDomElement deSet = msg.deData.ownerDocument().createElement(set->meta().setName);
		set->serialize(deSet);
		msg.deData.appendChild(deSet);
	}
}

void Proto::APGetDataSet::deserialize(const Proto::XmlDocument& msg)
{
	AnswerPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
}

void Proto::APCreateDataObject::serialize(Proto::XmlDocument& msg) const
{
	AnswerPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	msg.deParameters.setAttribute(ItemUuidAtr, itemUuid);
	msg.deParameters.setAttribute(ItemIdAtr, itemId);
}

void Proto::APCreateDataObject::deserialize(const Proto::XmlDocument& msg)
{
	AnswerPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);
	itemUuid = msg.deParameters.attribute(ItemUuidAtr);
	itemId = msg.deParameters.attribute(ItemIdAtr);
}

void Proto::APSaveDataObject::serialize(Proto::XmlDocument& msg) const
{
	AnswerPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	msg.deParameters.setAttribute(ItemUuidAtr, itemUuid);
	msg.deParameters.setAttribute(ItemIdAtr, itemId);
}

void Proto::APSaveDataObject::deserialize(const Proto::XmlDocument& msg)
{
	AnswerPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);
	itemUuid = msg.deParameters.attribute(ItemUuidAtr);
	itemId = msg.deParameters.attribute(ItemIdAtr);
}

void Proto::APDeleteDataObject::serialize(Proto::XmlDocument &msg) const
{
	AnswerPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	msg.deParameters.setAttribute(ItemUuidAtr, itemUuid);
	msg.deParameters.setAttribute(ItemIdAtr, itemId);
}

void Proto::APDeleteDataObject::deserialize(const Proto::XmlDocument &msg)
{
	AnswerPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);
	itemUuid = msg.deParameters.attribute(ItemUuidAtr);
	itemId = msg.deParameters.attribute(ItemIdAtr);
}

} // Ramio::
