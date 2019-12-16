/*
 * Copyright (C) 2016-2019 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "ItemSet.h"
#include "AbstractMetaSet.h"

namespace Ramio {

template<typename TYPE, typename METAITEMSET, typename METAITEM, bool> struct CacheMapStruct;

template<typename METAITEM, typename METASTRUCTDATA, bool CACHEDID = true>
class DLL_EXPORT MetaItemSet : public StructItemSet<METASTRUCTDATA>, public AbstractMetaSet
{
	Q_DISABLE_COPY(MetaItemSet)
	using Base = StructItemSet<METASTRUCTDATA>;
	inline METAITEM* itemByIdBase(RMetaPKey id) {return static_cast<METAITEM*>(Base::itemById(id));}
public:
	MetaItemSet(QString setName, QString itemName, QObject* parent = Q_NULLPTR);
	~MetaItemSet() Q_DECL_OVERRIDE {this->clear();}

	const QList<METAITEM*>& items() Q_DECL_NOTHROW {return items_;}
	const QList<const METAITEM*>& items() const Q_DECL_NOTHROW {
		return reinterpret_cast<const QList<const METAITEM*>&>(const_cast<MetaItemSet*>(this)->items());}

	inline typename QList<METAITEM*>::iterator begin() Q_DECL_NOTHROW {return items_.begin();}
	inline typename QList<METAITEM*>::iterator end() Q_DECL_NOTHROW {return items_.end();}
	inline typename QList<const METAITEM*>::const_iterator begin() const Q_DECL_NOTHROW {return items().begin();}
	inline typename QList<const METAITEM*>::const_iterator end() const Q_DECL_NOTHROW {return items().end();}

	AbstractMetaItemData* createMetaItemData() const Q_DECL_OVERRIDE {return new METASTRUCTDATA();}

	METAITEM* createItem() const Q_DECL_OVERRIDE {return new METAITEM();}
	METAITEM* createItem(const ItemData& data) const Q_DECL_OVERRIDE {return new METAITEM(static_cast<const METASTRUCTDATA&>(data));}
	METAITEM* createItem(ItemData&& data) const Q_DECL_OVERRIDE {return new METAITEM(static_cast<METASTRUCTDATA&&>(std::move(data)));}
	StructItem<MetaItemData>* createMetaItem() const Q_DECL_OVERRIDE {return reinterpret_cast<StructItem<MetaItemData>*>(createItem());}
	StructItem<MetaItemData>* createMetaItem(const MetaItemData& data) const Q_DECL_OVERRIDE {return reinterpret_cast<StructItem<MetaItemData>*>(createItem(data));}

	void addMetaItem(StructItem<MetaItemData>* item) Q_DECL_OVERRIDE {this->addItem(reinterpret_cast<StructItem<METASTRUCTDATA>*>(item));}

	AbstractSet* aSet() Q_DECL_OVERRIDE {return this;}
	AbstractMetaSet* mSet() Q_DECL_OVERRIDE {return this;}
	AbstractSet* createTemporaryItemSet(QObject* parent = Q_NULLPTR) const Q_DECL_OVERRIDE {return createTemporarySet(parent);}
	AbstractMetaSet* createTemporaryMetaSet(QObject* parent = Q_NULLPTR) const Q_DECL_OVERRIDE {return createTemporarySet(parent);}

	using SortFunction = bool (*)(const METAITEM*, const METAITEM*);
	void sort(SortFunction function) { bool r = ItemObserver::startReload(); std::sort(items_.begin(), items_.end(), function); if (r) ItemObserver::finishReload();}
	void sort(std::function<bool(const METAITEM* t1, const METAITEM* t2)>* function){
		bool r = ItemObserver::startReload(); std::sort(items_.begin(), items_.end(), function); if (r) ItemObserver::finishReload();}

	inline const MetaItemSet& asConst() Q_DECL_NOTHROW {return *const_cast<const MetaItemSet*>(this);}

	METAITEM* itemById(RMetaPKey id) Q_DECL_OVERRIDE {return idCache_.findItem(id, &MetaItemSet::itemByIdBase, *this);}
	const METAITEM* itemById(RMetaPKey id) const {return const_cast<MetaItemSet*>(this)->itemById(id);}

protected:
	void doOnItemAdding(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemAdding(item);idCache_.add(item.id(), static_cast<METAITEM*>(&item));}
	void doOnItemChanging(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemChanged(item);idCache_.remove(item.id());}
	void doOnItemChanged(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemChanged(item);idCache_.add(item.id(), static_cast<METAITEM*>(&item));}
	void doOnItemRemoving(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemRemoving(item);idCache_.remove(item.id());}
private:
	MetaItemSet<METAITEM, METASTRUCTDATA>* createTemporarySet(QObject* parent) const {
		return new MetaItemSet<METAITEM, METASTRUCTDATA>(meta_.setName, meta_.itemName, parent);}
														// meta_.cloneTypeDescription(),
	QList<METAITEM*> items_;
private: // qdoc bug fix
	CacheMapStruct<RMetaPKey, MetaItemSet, METAITEM, CACHEDID> idCache_;
};

template<typename METASTRUCTDATA>
class DLL_EXPORT BaseItem : public StructItem<METASTRUCTDATA>
{
	using Base = StructItem<METASTRUCTDATA>;
public:
	explicit BaseItem(ItemObserver* watcher = Q_NULLPTR) : Base(watcher) {}
	BaseItem(const METASTRUCTDATA& data, ItemObserver* watcher = Q_NULLPTR) : Base(data, watcher){}
	BaseItem(METASTRUCTDATA&& data, ItemObserver* watcher = Q_NULLPTR) : Base(std::move(data), watcher) {}
	~BaseItem() Q_DECL_OVERRIDE { this->beforeDeleted(); }

	const RMetaShort& type() const {return Base::data().type;}
	const RMetaShort& state() const {return Base::data().state;}
	const RMetaInt& flags() const {return Base::data().flags;}
};

template<typename METAITEM, typename METASTRUCTDATA, bool CACHEDID = true, bool CACHEDUUID = false>
class DLL_EXPORT MetaBaseItemSet : public MetaItemSet<METAITEM, METASTRUCTDATA, CACHEDID>
{
	using Base = MetaItemSet<METAITEM, METASTRUCTDATA, CACHEDID>;
	METAITEM* itemByUuidBase(const RMetaUuid& uid) {for (auto* item: Base::items()) if (item->uuid() == uid) return item; return Q_NULLPTR;}
public:
	MetaBaseItemSet(QString setName, QString itemName, std::unique_ptr<Meta::TypeDescription> typeDescription =
			std::unique_ptr<Meta::TypeDescription>(), QObject* parent = Q_NULLPTR);
	MetaBaseItemSet(QString setName, QString itemName, QObject* parent = Q_NULLPTR)
		: MetaBaseItemSet(setName, itemName, std::unique_ptr<Meta::TypeDescription>(), parent) {}

	METAITEM* itemByUuid(const RMetaUuid& uid) {return uuidCache_.findItem(uid, &MetaBaseItemSet::itemByUuidBase, *this);}
	const METAITEM* itemByUuid(const RMetaUuid& uid) const {return const_cast<MetaBaseItemSet*>(this)->itemByUuid(uid);}

protected:
	void doOnItemAdding(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemAdding(item);uuidCache_.add(static_cast<BaseItem<METASTRUCTDATA>&>(item).uuid(), static_cast<METAITEM*>(&item));}
	void doOnItemChanging(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemChanged(item);uuidCache_.remove(static_cast<BaseItem<METASTRUCTDATA>&>(item).uuid());}
	void doOnItemChanged(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemChanged(item);uuidCache_.add(static_cast<BaseItem<METASTRUCTDATA>&>(item).uuid(), static_cast<METAITEM*>(&item));}
	void doOnItemRemoving(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemRemoving(item);uuidCache_.remove(static_cast<BaseItem<METASTRUCTDATA>&>(item).uuid());}

private: // qdoc bug fix
	CacheMapStruct<const RMetaUuid&, MetaBaseItemSet, METAITEM, CACHEDUUID> uuidCache_;
};

} // Ramio::

#include "MetaItemSet.inl"
