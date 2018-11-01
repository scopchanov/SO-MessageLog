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

#include "MainWindow.h"
#include "MessageList.h"
#include <QBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QWidget(parent)
{
	auto *layoutMain = new QVBoxLayout(this);
	auto *groupAdd = new QGroupBox(tr("Add message"), this);
	auto *layoutToolbar = new QHBoxLayout(groupAdd);
	auto *messageList = new MessageList(this);
	auto *cmbType = new QComboBox(this);
	auto *editMessage = new QLineEdit(this);
	auto *btnPost = new QPushButton(tr("Post"), this);
	auto *btnDeleteAll = new QPushButton(tr("Delete All"), this);

	cmbType->addItem(QIcon(QPixmap(":/pix/images/icons/48/information.png")), "I");
	cmbType->addItem(QIcon(QPixmap(":/pix/images/icons/48/warning.png")), "W");
	cmbType->addItem(QIcon(QPixmap(":/pix/images/icons/48/error.png")), "E");

	editMessage->setPlaceholderText(tr("Enter message here..."));

	layoutToolbar->addWidget(cmbType);
	layoutToolbar->addWidget(editMessage);
	layoutToolbar->addWidget(btnPost);

	messageList->addMessage(tr("This is some text of an info message"),
							QPixmap(":/pix/images/icons/48/information.png"),
							QDateTime::currentDateTime());
	messageList->addMessage(tr("This is some text of a warning message"),
							QPixmap(":/pix/images/icons/48/warning.png"),
							QDateTime::currentDateTime());
	messageList->addMessage(tr("This is some text of an error message"),
							QPixmap(":/pix/images/icons/48/error.png"),
							QDateTime::currentDateTime());

	layoutMain->addWidget(groupAdd);
	layoutMain->addWidget(messageList);
	layoutMain->addWidget(btnDeleteAll);

	resize(640, 480);

	connect(btnPost, &QPushButton::clicked, [messageList, cmbType, editMessage](){
		messageList->addMessage(editMessage->text(),
								cmbType->itemIcon(cmbType->currentIndex()).pixmap(48, 48),
								QDateTime::currentDateTime());
	});

	connect(btnDeleteAll, &QPushButton::clicked, messageList, &MessageList::clearAll);
}
