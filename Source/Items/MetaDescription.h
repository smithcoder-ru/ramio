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

#pragma once

#include "MetaTypes.h"
#include "ItemData.h"
#include <QtCore/QMap>
#include <QtCore/QVector>
#include <QtCore/QVariant>
#include <QtCore/QScopedPointer>
#include <memory>
class QDebug;

namespace Ramio {

struct AbstractMetaItemData;

namespace Meta {

enum class FieldRole : quint8
{
	Field = 0,
	PKey,
	Type,
	Flags,
	FKey,
	Extended,
	Value,
	Function
};

struct RAMIO_LIB_EXPORT Property
{
	friend class QVertor;
	Property() = default;
public:
	Property(ptrdiff_t diff, size_t size, QString name, Ramio::Meta::Type type, QString protoname,
			 QString prettyname = emptyString, Ramio::Meta::FieldRole role = FieldRole::Field,
			 QString specialfieldrole = emptyString);
/// Смещение от начала структуры и размер
	ptrdiff_t diff;
	quint8 size;
	Ramio::Meta::Type type;
	Ramio::Meta::FieldRole role;
/// Специальное поле, зависит от роли переменной
	QString special;
/// имя переменной
	QString name;
/// имя переменной для бд, сериализации
	QString protoname;
/// наименование переменной, заголовок таблиц
	QString prettyname;
};

QDebug operator << (QDebug dbg, const Property& pr);

struct RAMIO_LIB_EXPORT TypeDescription
{
	TypeDescription(bool fixedTypeCount = false);
	virtual ~TypeDescription();

	virtual TypeDescription* clone() const {return new TypeDescription(fixedTypeCount);}

	virtual const QString& typeName(RMType);
	virtual QList<RMType> supportedTypes();
	virtual const QStringList& supportedTypeNames();

	const bool fixedTypeCount;
};

enum class FunctionRoles
{
	UnsetRole,
	DecorationRole = 1, // Qt::DecorationRole
	BackgroundRole = 8, // Qt::BackgroundRole
	InnerPointerRole = 0x0100, // Qt::UserRole
// for self using
	UserRole = 0x0200
};


struct RAMIO_LIB_EXPORT Description
{
	QString itemName;
	QString setName;
	QString schemeName;
	QVector<Property> properties;
	QMap<QString, const Description*> relations;
	QMap<FunctionRoles, std::function<QVariant(const Ramio::AbstractMetaItemData&, const Property&)>*> functions;
	std::shared_ptr<TypeDescription> typeDescription;
	std::function<BaseItemData*()>* createDataFunction = Q_NULLPTR;
	size_t size;

	const QString& fieldProtoName(const QString& name) const; // empty for not finded
	qint8 fieldIndex(const QString& name) const; // -1 for not finded
	ptrdiff_t fieldDiff(const QString& name) const; // 0 for not finded
	ptrdiff_t fieldDiff(const QString& name, Ramio::Meta::Type type) const; // 0 for not finded
	QList<quint8> fieldIndexes(const QStringList& names, bool logNotFinded) const;
	inline QList<quint8> fieldIndexes(const QStringList& names) const {return fieldIndexes(names, false);}
	bool contains(const QString& name) const {return fieldIndex(name) >= 0;}

	template<typename FIELDTYPE>
	FIELDTYPE& valueRef(const QString& name, Data& data) const {
		Q_ASSERT(fieldIndex(name) >= 0);
		const Meta::Property& pr = properties[fieldIndex(name)];
		return CAST_DATAREL_TO_TYPEREL(FIELDTYPE);}

	template<typename FIELDTYPE>
	const FIELDTYPE& valueConstRef(const QString& name, const ItemData& data) const {
		return valueRef<FIELDTYPE>(name, const_cast<ItemData&>(data));}

	void setRelation(const QString& name, const Description* desc) {relations[name] = desc;}
};

} // Meta::
} // Ramio::
