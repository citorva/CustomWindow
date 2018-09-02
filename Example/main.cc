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
#include <QMouseEvent>
#include <QPushButton>

#include "CustomWindow.hh"

class MainWindow : public CustomWindow::CustomWindow
{
public:
    MainWindow() : CustomWindow::CustomWindow()
    {
        setFrameRemoved(true);
        hideSystemMenu();
        setTitleBarSize(0);
        resize(200,200);

        setStyleSheet("background: #e91e63; color: black;");

        m_QuitButton = new QPushButton("Click me!", this);
        m_QuitButton->setStyleSheet("background: #b0003a; color: white; border: none; line-height: 48px; height: 48px; min-width: 96px;");

        m_MoveButton = new QWidget(this);
        declareCaption(m_MoveButton);
        m_MoveButton->setStyleSheet("background: #b0003a; color: white; border: none; line-height: 32px; height: 32px;");

        connect(m_QuitButton, &QPushButton::clicked, this, &QWidget::close);
    }

    virtual ~MainWindow()
    {
        delete m_QuitButton;
        delete m_MoveButton;
    }

protected:
    void resizeEvent(QResizeEvent *event) {
        QSize wSize = event->size();
        QSize bSize = m_QuitButton->size();
        QPoint bPos = QPoint((wSize.width()-bSize.width())/2, (wSize.height()-bSize.height())/2);
        QRect wClient = clientGeometry(CALCSIZE_USE_BORDER | CALCSIZE_USE_TITLEBAR);

        m_QuitButton->move(bPos);
        m_MoveButton->move(wClient.left(),wClient.top());
        m_MoveButton->resize(wClient.width(), m_MoveButton->height());
    }

private:
    QPushButton *m_QuitButton;
    QWidget *m_MoveButton;
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow *w = new MainWindow();

    w->show();

    return app.exec();
}
