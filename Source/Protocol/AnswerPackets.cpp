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

#include "AnswerPackets.h"
#include "ProtocolStr.h"
#include <Items/AbstractMetaSet.h>

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

void Proto::APGetDataSet::serialize(Proto::XmlDocument& msg) const
{
	AnswerPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, set->meta().setName);
	QDomElement deSet = msg.deData.ownerDocument().createElement(set->meta().setName);
	set->serialize(deSet);
	msg.deData.appendChild(deSet);
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
