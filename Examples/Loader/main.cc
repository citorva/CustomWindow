// Sample code of usage of CustomWindow
// Copyright (C) 2018 Citorva
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <QApplication>
#include <QLabel>
#include <QPainter>

#include "CustomWindow.hh"

class StaticImage : public QWidget
{
public:
	StaticImage(QWidget *parent) : QWidget(parent)
	{}

	StaticImage(QImage image, QWidget *parent) : QWidget(parent)
	{
		mImage = image;
		resize(mImage.size());
	}

	void AssignImage(QImage image)
	{
		mImage = image;
		resize(mImage.size());
	}

protected:

	void paintEvent(QPaintEvent *evt)
	{
		QPainter p(this);

		p.drawImage(QPoint(0, 0), mImage);
	}

private:
	QImage mImage;
};

class MainWindow : public CustomWindow::CustomWindow
{
public:
	MainWindow() : CustomWindow::CustomWindow()
	{
		setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
		setFrameRemoved(true);
        hideSystemMenu();
        setTitleBarSize(0);
		setBorderSize(0);
		enableTransluentBackground(QColor(0,0,0),.5);
        resize(512,288);

		setResizable(false);

        //setStyleSheet("background: black;");

		banner = new StaticImage(QImage(":/fg-img.png"), this);
		banner->move(QPoint(0, 0));

		declareCaption(this);
    }

    virtual ~MainWindow()
    {
    }

private:
	StaticImage *banner;
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow *w = new MainWindow();

    w->show();

    return app.exec();
}
