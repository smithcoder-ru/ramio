/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include <QtWidgets/QToolBar>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>

#define UI_MARGIN_PX 2
#define UI_SPACING_PX 1

#define UI_SET_MARGINSPACING(layout) \
	layout->setMargin(UI_MARGIN_PX); \
	layout->setSpacing(UI_SPACING_PX);

#define UI_SET_ZERO_MARGINSPACING(layout) \
	layout->setMargin(0); \
	layout->setSpacing(0);

#define UI_CREATE_VLAUOUT(layout) \
	auto* layout = new QVBoxLayout(this); \
	UI_SET_MARGINSPACING(layout)

#define UI_CREATE_HLAUOUT(layout) \
	auto* layout = new QHBoxLayout(this); \
	UI_SET_MARGINSPACING(layout)

#define UI_CREATE_VLAUOUT_ZERO_MARGINSPACING(layout) \
	auto* layout = new QVBoxLayout(this); \
	UI_SET_ZERO_MARGINSPACING(layout)

#define UI_CREATE_HLAUOUT_ZERO_MARGINSPACING(layout) \
	auto* layout = new QHBoxLayout(this); \
	UI_SET_ZERO_MARGINSPACING(layout)

#define UI_CREATE_GLAUOUT(layout) \
	auto* layout = new QGridLayout(this); \
	UI_SET_MARGINSPACING(layout)

#define UI_CREATE_TOOLBAR(text) \
	auto* toolbar = new QToolBar(this); \
	auto* toolbarLabel = new QLabel(text, toolbar); \
	toolbar->addWidget(toolbarLabel); \
	layout->setMenuBar(toolbar);

#define UI_CREATE_TOOLBAR_STRECH \
	{ auto* strechWidget = new QWidget(); \
	strechWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); \
	toolbar->addWidget(strechWidget); }

#define SHOW_WIDGET_GLOBAL_MODAL(widget) \
	widget->setAttribute(Qt::WA_DeleteOnClose, true); \
	widget->setWindowModality(Qt::ApplicationModal); \
	if (widget->windowState() == Qt::WindowMaximized) widget->showMaximized(); else widget->show();

#define SHOW_MODAL_DIALOG_WIDGET(widget) \
	widget->setWindowModality(Qt::ApplicationModal); \
	widget->setWindowFlags(Qt::Dialog); \
	widget->setAttribute(Qt::WA_DeleteOnClose); \
	widget->show();

#define PREPARE_TABLE(table) LOAD_CHECK_WIDGET(table, \
	table->setSortingEnabled(true); \
	table->setAutoScroll(false); \
	table->setSelectionBehavior(QAbstractItemView::SelectRows); \
	table->setSelectionMode(QAbstractItemView::SingleSelection); \
	table->horizontalHeader()->setHighlightSections(false); \
	table->horizontalHeader()->setStretchLastSection(true); \
	table->setTabKeyNavigation(false); \
	)

