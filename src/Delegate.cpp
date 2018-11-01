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

#include "Delegate.h"
#include <QPainter>
#include <QDebug>

Delegate::Delegate(QObject *parent) :
	QStyledItemDelegate(parent)
{

}

void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyleOptionViewItem opt = option;
	initStyleOption(&opt, index);

	int bottomEdge = opt.rect.bottom();
	bool lastIndex = (index.model()->rowCount() - 1) == index.row();
	QFont f(opt.font);

	f.setPointSize(10);

	painter->save();
	painter->setClipping(true);
	painter->setClipRect(opt.rect);
	painter->setFont(opt.font);

	// Draw background
	painter->fillRect(opt.rect, opt.state & QStyle::State_Selected ?
						  opt.palette.highlight().color() :
						  opt.palette.light().color());

	// Draw bottom line
	painter->setPen(lastIndex ? opt.palette.dark().color() : opt.palette.mid().color());
	painter->drawLine(lastIndex ? 0 : 8, bottomEdge, opt.rect.right(), bottomEdge);

//	opt.widget->style()->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter);

	// Draw message icon
	painter->drawPixmap(8, opt.rect.y() + 8, opt.icon.pixmap(32, 32));

	// Draw message text
	painter->setPen(opt.palette.windowText().color());
	painter->drawText(opt.rect.adjusted(48, 32, 0, 0), Qt::TextSingleLine, opt.text);

	// Draw timestamp
	painter->setFont(f);
	painter->setPen(opt.palette.text().color());
	painter->drawText(opt.rect.adjusted(48, 8, 0, -32), Qt::TextSingleLine, index.data(Qt::UserRole).toString());

	painter->restore();
}

QSize Delegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	return QSize(index.data(Qt::SizeHintRole).toSize().width(), 64);
}
