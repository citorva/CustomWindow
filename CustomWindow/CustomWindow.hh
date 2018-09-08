// CustomWindow
// Copyright (C) 2018 Citorva
//
// Based on Adaedra QDwm
// Copyright (C) 2011 Adaedra
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

#ifndef CustomWindow_HH_
#define CustomWindow_HH_

#include <QWidget>
#include <QStyle>
#include <QMargins>

#ifdef Q_OS_WIN
    #include <Windows.h>
    #include <WindowsX.h>
    #include <Uxtheme.h>
    #include <dwmapi.h>
    #include <vector>
#endif

#if (QT_VERSION == QT_VERSION_CHECK(5, 11, 1))
#error Qt bug for version 5.11.1. See https://bugreports.qt.io/browse/QTBUG-69074?jql=project%20%3D%20QTBUG%20AND%20text%20~%20nativeEvent%20AND%20affectedVersion%20%3D%205.11.1 for more information
#endif

#define CALCSIZE_USE_BORDER     0x0001
#define CALCSIZE_USE_MARGIN     0x0002
#define CALCSIZE_USE_TITLEBAR   0x0004
#define CALCSIZE_DEFAULT        0x0007

namespace CustomWindow {

enum Sizing {
    contentSizing,
    borderSizing,
    defaultSizing
};

class CustomWindow : public QWidget {
#ifdef Q_OS_WIN
	Q_OBJECT

	Q_PROPERTY(bool frameRemoved READ isFrameRemoved WRITE setFrameRemoved)
	Q_PROPERTY(QMargins extraMargins READ extraMargins WRITE setExtraMargins)
	Q_PROPERTY(int borderSize READ borderSize WRITE setBorderSize)
	Q_PROPERTY(int titleBarSize READ titleBarSize WRITE setTitleBarSize)
	Q_PROPERTY(int geometryFlags READ geometryFlags WRITE setGeometryFlags)
#endif

public:
    CustomWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::Window);

#ifdef Q_OS_WIN
    void hideSystemMenu(void);
    void showSystemMenu(void);
	void setSystemMenu(bool hide = false);
	bool haveSystemMenu(void) const;
	bool isGeometryFlagsActivated(int flag) const;

	// Write
	void setFrameRemoved(bool isRemoved);
	void setExtraMargins(const QMargins& margins);
	void setBorderSize(int size);
	void setTitleBarSize(int size);
	void setGeometryFlags(int flags);

	// Read
	bool isFrameRemoved(void) const;
	QMargins extraMargins(void) const;
    QRect clientGeometry(void) const;
	int borderSize(void) const;
    int titleBarSize(void) const;
	int geometryFlags(void) const;

    // Sizing
    void setSizing(Sizing method);
    void resize(int w, int h, Sizing method = defaultSizing);
    void resize(const QSize &size, Sizing method = defaultSizing);
    QSize size(Sizing method = defaultSizing) const;
    Sizing sizing(void) const;

	// Static
	static bool isAeroActivated(void);
	static bool isThemeActivated(void);

    void declareCaption(const QWidget* widget);
	void removeCaption(const QWidget* widget);

	void setLayout(QLayout* layout);

signals:
	void themeChanged(void);
	void compositionChanged(void);

protected:
    bool nativeEvent(const QByteArray &eventType, void* message, long* result);
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent* eve);
	void mouseMoveEvent(QMouseEvent* eve);
	void mouseReleaseEvent(QMouseEvent* eve);

private:
    void updateMargins(HWND hWnd = nullptr);
    void updateFrame(HWND hWnd = nullptr);
	long ncHitTest(MSG* wMsg);
	void paintWinFrame(void);
	
	void ncMouseMove(int cx, int cy);
	void ncMousePress(int cx, int cy);
	void ncMouseRelease(int cx, int cy);
	bool hasControls(int cx, int cy);

    bool isCaption(int cx, int cy) const;

	void updateLayoutMargins(void);

	bool mFrameRemoved;
    bool mCanMove;
	QMargins mMargins;

    POINT mStartPos;
	int mBorderSize;
    int mTitleBarSize;

    std::vector<const QWidget*> mCaptions;

	QStyle::SubControl mTitleBarHover;
	QStyle::State mTitleBarState;
    Sizing mSizingMethod;

	QMargins *mLayoutMargins;

	int mGeometryFlags = CALCSIZE_DEFAULT;
#endif
};

}
	
#endif
