# CustomWindow

Qt implementation of custom DWM window

This project is a fork of Adaedra QDwm (https://sourceforge.net/projects/qdwm/) adapted for Qt 5

# How to use

You need to download the projet and copy files `CustomWindow.hh` and `CustomWindow.cc` to your project. Then, you need to configure the linker and add these library: `dwmapi` and `uxtheme`

This class work like all widgets objects and adds the following functions:

## Functions

- `void hideSystemMenu(void);` Hide system menu (Remove Close/Maximize/Minimize buttons of the title bar)
- `void showSystemMenu(void);` Show system menu
- `bool haveSystemMenu(void) const;` Check if the system menu is visible
- `void setFrameRemoved(bool isRemoved);` Remove frame (Enable non client aera drawing)
- `bool isFrameRemoved(void) const;`
- `void setExtraMargins(const QMargins& margins);`
- `QMargins extraMargins(void) const;`
- `void setBorderSize(int size);`
- `int borderSize(void) const;`
- `void setTitleBarSize(int size);`
- `int titleBarSize(void) const;`

- `QRect clientGeometry(const int calcFlags = CALCSIZE_DEFAULT) const;`

- `void setSizing(Sizing method);`
- `void resize(int w, int h, Sizing method = defaultSizing);`
- `void resize(const QSize &size, Sizing method = defaultSizing);`
- `QSize size(Sizing method = defaultSizing) const;`
- `Sizing sizing(void) const;`

- `static bool isAeroActivated(void);`
- `static bool isThemeActivated(void);`

- `void declareCaption(const QWidget* widget);`
