QT = core gui widgets
SOURCES = \
    main.cc \
    CustomWindow.cc
HEADERS = \
    CustomWindow.hh
LIBS += -ldwmapi -luxtheme

!win32 {
  error(Can be built only under Windows.)
}

win32-g++ {
  message(Using mingw.)
}

win32-msvc2005|win32-msvc2008|win32-msvc2010 {
  message(Using visual.)
}
