/**
MIT License

Copyright (c) 2018 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "MessageList.h"
#include "Delegate.h"
#include <QStandardItemModel>
#include <QDateTime>

MessageList::MessageList(QWidget *parent) :
	QListView(parent)
{
	auto *delegate = new Delegate(this);
	QPalette p(palette());

	p.setBrush(QPalette::WindowText, QColor("#303030"));
	p.setBrush(QPalette::Base, QColor("#F0F1F2"));
	p.setBrush(QPalette::Light, QColor("#FFFFFF"));
	p.setBrush(QPalette::Midlight, QColor("#D3D6D8"));
	p.setBrush(QPalette::Mid, QColor("#C5C9Cb"));
	p.setBrush(QPalette::Dark, QColor("#9AA0A4"));
	p.setBrush(QPalette::Text, QColor("#616b71"));
	p.setBrush(QPalette::Highlight, QColor("#E2E4E5"));

	delegate->setContentsMargins(8, 8, 8, 8);
	delegate->setIconSize(32, 32);
	delegate->setHorizontalSpacing(8);
	delegate->setVerticalSpacing(4);

	setPalette(p);
	setFont(QFont("MSShellDlg 2", 12));
	setModel(new QStandardItemModel(this));
	setItemDelegate(delegate);
}

void MessageList::addMessage(const QString &text, const QPixmap &pixmap,
							 const QDateTime &dateTime)
{
	auto *item = new QStandardItem(QIcon(pixmap), text);

	item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	item->setData(dateTime.toString("yyyy-MM-dd"), Qt::UserRole);

	static_cast<QStandardItemModel *>(model())->appendRow(item);
	scrollToBottom();
}

void MessageList::clearAll()
{
	static_cast<QStandardItemModel *>(model())->clear();
}
