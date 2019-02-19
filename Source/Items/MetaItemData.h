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

#include "ItemData.h"
#include "MetaDescription.h"

#define RMETA_OBJECT_START(ItemType) \
	using Base = ItemType; \
	QList<Ramio::Meta::Property> registerMetaFields() Q_DECL_OVERRIDE { \
	QList<Ramio::Meta::Property> res = Base::registerMetaFields(); \

#define RMETA_OBJECT_FIELD(name, type, protoname, prettyname, relationtype) \
	res.append(Ramio::Meta::Property(ptrdiff_t(reinterpret_cast<char*>(&name)-reinterpret_cast<char*>(this)),\
	quint8(sizeof(name)), QStringLiteral(#name), Ramio::Meta::Type::type, \
	QStringLiteral(protoname), prettyname, Ramio::Meta::FieldType::relationtype));

	// Experemtnal
#define RMETA_OBJECT_FUNCTION(ItemDataStruct, name, type, protoname, prettyname, relationtype) \
	{typedef QVariant (ItemDataStruct::*dataFunction)(const ItemDataStruct& ) const; \
	dataFunction memfunc_ptr = &ItemDataStruct::name; \
	dataFunction* prtfnk= &memfunc_ptr; \
	ptrdiff_t diffnk = *((ptrdiff_t*)(prtfnk));\
	res.append(Ramio::Meta::Property(diffnk, quint8(sizeof(ptrdiff_t)), QStringLiteral(#name), Ramio::Meta::Type::type, \
	QStringLiteral(protoname), prettyname, Ramio::Meta::FieldType::relationtype));}

#define RMETA_OBJECT_END \
	return res; }

namespace Ramio {

struct DLL_EXPORT BaseMetaItemData
{
	virtual QList<Meta::Property> registerMetaFields() {return {};}
};

struct DLL_EXPORT MetaItemData : public ItemData, public BaseMetaItemData
{
	using Base = ItemData;
	QList<Meta::Property> registerMetaFields() Q_DECL_OVERRIDE;
	virtual BaseMetaItemData* extendedData() {return Q_NULLPTR;}
	virtual const BaseMetaItemData* extendedData() const {return Q_NULLPTR;}
};

template<typename BASEMETAITEMDATA, typename EXTENDEDTDATA>
struct ExtendedItemData : public BASEMETAITEMDATA
{
	EXTENDEDTDATA extended;
	QList<Meta::Property> registerMetaFields() Q_DECL_OVERRIDE
	{
		QList<Meta::Property> res = BASEMETAITEMDATA::registerMetaFields();
		Q_FOREACH(Meta::Property pr, extended.registerMetaFields())
		{
			pr.dif=pr.dif+ptrdiff_t(reinterpret_cast<char*>(&extended)-reinterpret_cast<char*>(this));
			pr.relationtype = Meta::FieldType::Extended;
			res.append(pr);
		}
		return res;
	}
	BaseMetaItemData* extendedData() Q_DECL_OVERRIDE {return &extended;}
	const BaseMetaItemData* extendedData() const Q_DECL_OVERRIDE {return &extended;}
};

} // Ramio::
