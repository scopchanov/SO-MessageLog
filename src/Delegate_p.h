#ifndef DELEGATE_P_H
#define DELEGATE_P_H

#include <qglobal.h>

class DelegatePrivate
{
	DelegatePrivate();

	inline QRect timestampBox(const QStyleOptionViewItem &option,
							  const QModelIndex &index) const;
	inline qreal timestampFontPointSize(const QFont &f) const;
	inline QRect messageBox(const QStyleOptionViewItem &option) const;

	QSize iconSize;
	QMargins margins;
	int spacingHorizontal;
	int spacingVertical;

	friend class Delegate;
};

#endif // DELEGATE_P_H
