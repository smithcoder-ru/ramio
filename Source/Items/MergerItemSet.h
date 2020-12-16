/*
 * Copyright (C) 2016-2020 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "StructItemSet.h"

namespace Ramio {

template<typename STRUCTITEM>
class MergerItemSet : public AbstractSet
{
	using Base = AbstractSet;
public:
	MergerItemSet(const AbstractSet& set1, const AbstractSet& set2, QObject* parent = Q_NULLPTR);

	const QList<STRUCTITEM*>& items() {return items_;}
	const QList<const STRUCTITEM*>& items() const {
		return reinterpret_cast<const QList<const STRUCTITEM*>&>(const_cast<MergerItemSet*>(this)->items());}

	void reload();

protected:
	Item* createItem() const Q_DECL_OVERRIDE {return Q_NULLPTR;}
	Item* createItem(const ItemData& data) const Q_DECL_OVERRIDE {return Q_NULLPTR;}
	Item* createItem(ItemData&& data) const Q_DECL_OVERRIDE {return Q_NULLPTR;}
	AbstractSet* createTemporaryItemSet(QObject* parent = Q_NULLPTR) const Q_DECL_OVERRIDE {return Q_NULLPTR;}
	void onAdded(const Item& item);
	void onChanged(const Item& item);
	void onRemoved(const Item& item);

private:
	const AbstractSet& otherSet(const AbstractSet& set) {if (&set == &set1_) return set2_; return set1_;}

private:
	const AbstractSet& set1_;
	const AbstractSet& set2_;
	QList<STRUCTITEM*> items_;
};

template<typename STRUCTITEM>
class MultiMergerItemSet : public AbstractSet
{
	using Base = AbstractSet;
public:
	MultiMergerItemSet(QList<const AbstractSet*> sets = QList<const AbstractSet*>(), QObject* parent = Q_NULLPTR);

	const QList<STRUCTITEM*>& items() {return items_;}
	const QList<const STRUCTITEM*>& items() const {
		return reinterpret_cast<const QList<const STRUCTITEM*>&>(const_cast<MultiMergerItemSet*>(this)->items());}

	const QList<const AbstractSet*>& sets() {return sets_;}
	void addSet(const AbstractSet& set);

	void reload();

protected:
	Item* createItem() const Q_DECL_OVERRIDE {return Q_NULLPTR;}
	Item* createItem(const ItemData& data) const Q_DECL_OVERRIDE {return Q_NULLPTR;}
	Item* createItem(ItemData&& data) const Q_DECL_OVERRIDE {return Q_NULLPTR;}
	AbstractSet* createTemporaryItemSet(QObject* parent = Q_NULLPTR) const Q_DECL_OVERRIDE {return Q_NULLPTR;}
	void onAdded(const Item& item);
	void onChanged(const Item& item);
	void onRemoved(const Item& item);

private:
	QList<const AbstractSet*> sets_;
	QList<STRUCTITEM*> items_;
};

} // Ramio::

#include "MergerItemSet.inl"
