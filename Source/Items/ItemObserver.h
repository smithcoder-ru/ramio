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

#include <QtCore/QObject>
#include "Item.h"

namespace Ramio {

class DLL_EXPORT ItemObserver : public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY(ItemObserver)
	friend class Item;
public:
	ItemObserver(QObject* parent = Q_NULLPTR);
	~ItemObserver() Q_DECL_OVERRIDE;

	virtual bool contains(const Item& item) const = 0;
	virtual int count() const = 0;
	virtual bool isEmpty() const = 0;
	virtual void clear() = 0;

	void refresh() {emit reloading();  emit reloaded();}

signals:
	void adding(const Item& item);
	void added(const Item& item);
	void changing(const Item& item);
	void changed(const Item& item);
	void deleting(const Item& item);
	void deleted(const Item& item);

	void reloading();
	void reloaded();

protected:
	void addItem(Item& item);
	void changingItem(Item& item);
	void changedItem(Item& item);
	void removeItem(Item& item);
	void dropItem(Item& item);

	virtual void doOnItemAdding(Item& item) = 0;
	virtual void doOnItemChanging(Item& item) = 0;
	virtual void doOnItemChanged(Item& item) = 0;
	virtual void doOnItemRemoving(Item& item) = 0;
};

} // Ramio::
