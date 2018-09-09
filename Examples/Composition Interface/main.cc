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

#include <QGroupBox>
#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QWidget>
#include <QLayout>
#include <QSignalMapper>

#include "CustomWindow.hh"

class MainWindow : public CustomWindow::CustomWindow
{
public:
	MainWindow() : CustomWindow::CustomWindow()
	{
		mMarginTopValue = 0;
		mMargingBotValue = 0;
		mMarginLeftValue = 0;
		mMarginRightValue = 0;
		mTitleBarValue = 0;
		mBorderValue = 0;

		setGeometryFlags(CALCSIZE_USE_BORDER | CALCSIZE_USE_TITLEBAR);

		mMainLayout = new QVBoxLayout();

		mThemeBox = new QGroupBox("Theme", this);
		mMainLayout->addWidget(mThemeBox);

		mDWMCompositionBox = new QGroupBox("DWM Composition", this);
		mMainLayout->addWidget(mDWMCompositionBox);

		mDragAreaBox = new QGroupBox("Drag window area");
		mMainLayout->addWidget(mDragAreaBox);

		mMainLayout->setContentsMargins(QMargins(8, 8, 8, 8));

		setLayout(mMainLayout);

		// Theme group

		mThemeBoxLayout = new QVBoxLayout();

		mDWMSignal = new QCheckBox("DWM Activated", this);
		mDWMSignal->setEnabled(false);
		mThemeBoxLayout->addWidget(mDWMSignal);

		mThemeSignal = new QCheckBox("Theme activated", this);
		mThemeSignal->setEnabled(false);
		mThemeBoxLayout->addWidget(mThemeSignal);

		mEnableComposition = new QCheckBox("Enable DWM Composition", this);
		mThemeBoxLayout->addWidget(mEnableComposition);

		mHideSystemButtons = new QCheckBox("Hide system menu (close/iconize/maximize button)");
		mThemeBoxLayout->addWidget(mHideSystemButtons);

		mThemeBox->setLayout(mThemeBoxLayout);

		// DWM Composition Area

		{

			mDWMCompositionLayout = new QVBoxLayout();

			mCalcsizeTitlebar = new QCheckBox("Avoid titlebar", this);
			mDWMCompositionLayout->addWidget(mCalcsizeTitlebar);

			mCalcsizeBorders = new QCheckBox("Avoid borders", this);
			mDWMCompositionLayout->addWidget(mCalcsizeBorders);

			mCalcsizeMargins = new QCheckBox("Avoid margins", this);
			mDWMCompositionLayout->addWidget(mCalcsizeMargins);

			// Margins Area
			mMarginLayout = new QHBoxLayout();

			{
				mMarginLabel = new QLabel("Margins", this);
				mMarginLayout->addWidget(mMarginLabel);

				mMarginGrid = new QGridLayout(this);

				// Margin top

				mMarginTopLayout = new QHBoxLayout();

				mMarginTopLabel = new QLabel("Top", this);
				mMarginTopLayout->addWidget(mMarginTopLabel);

				mMarginTopSpinBox = new QSpinBox(this);
				mMarginTopSpinBox->setSuffix(" px");
				mMarginTopLayout->addWidget(mMarginTopSpinBox);

				mMarginGrid->addLayout(mMarginTopLayout, 1, 1);

				// Margin bottom

				mMarginBotLayout = new QHBoxLayout();

				mMarginBotLabel = new QLabel("Bottom", this);
				mMarginBotLayout->addWidget(mMarginBotLabel);

				mMarginBotSpinBox = new QSpinBox(this);
				mMarginBotSpinBox->setSuffix(" px");
				mMarginBotLayout->addWidget(mMarginBotSpinBox);

				mMarginGrid->addLayout(mMarginBotLayout, 1, 2);

				// Margin left

				mMarginLeftLayout = new QHBoxLayout();

				mMarginLeftLabel = new QLabel("Left", this);
				mMarginLeftLayout->addWidget(mMarginLeftLabel);

				mMarginLeftSpinBox = new QSpinBox(this);
				mMarginLeftSpinBox->setSuffix(" px");
				mMarginLeftLayout->addWidget(mMarginLeftSpinBox);

				mMarginGrid->addLayout(mMarginLeftLayout, 2, 1);

				// Margin right

				mMarginRightLayout = new QHBoxLayout();

				mMarginRightLabel = new QLabel("Right", this);
				mMarginRightLayout->addWidget(mMarginRightLabel);

				mMarginRightSpinBox = new QSpinBox(this);
				mMarginRightSpinBox->setSuffix(" px");
				mMarginRightLayout->addWidget(mMarginRightSpinBox);

				mMarginGrid->addLayout(mMarginRightLayout, 2, 2);

				mMarginLayout->addLayout(mMarginGrid);
			}

			mDWMCompositionLayout->addLayout(mMarginLayout);

			// Title bar & border

			mTitleBarBorderLayout = new QHBoxLayout();

			{
				mTitleBarLabel = new QLabel("Title bar");
				mTitleBarBorderLayout->addWidget(mTitleBarLabel);

				mTitleBarSpinBox = new QSpinBox(this);
				mTitleBarSpinBox->setMinimum(-1);
				mTitleBarSpinBox->setSuffix(" px");
				mTitleBarBorderLayout->addWidget(mTitleBarSpinBox);

				mBorderLabel = new QLabel("Border");
				mTitleBarBorderLayout->addWidget(mBorderLabel);

				mBorderSpinBox = new QSpinBox(this);
				mBorderSpinBox->setMinimum(-1);
				mBorderSpinBox->setSuffix(" px");
				mTitleBarBorderLayout->addWidget(mBorderSpinBox);
			}

			mDWMCompositionLayout->addLayout(mTitleBarBorderLayout);

			mDWMCompositionBox->setLayout(mDWMCompositionLayout);

		}

		// Drag window area

		mDraggableAreaLayout = new QVBoxLayout();

		mEnableMovableArea = new QCheckBox("Enable draggable window area", this);
		mDraggableAreaLayout->addWidget(mEnableMovableArea);

		mMovableArea = new QWidget(this);
		mMovableArea->setStyleSheet("background: #6f6f6f;");
		mMovableArea->setMinimumHeight(32);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
		mMovableArea->setSizePolicy(sizePolicy);
		mDraggableAreaLayout->addWidget(mMovableArea);

		mDragAreaBox->setLayout(mDraggableAreaLayout);

		updateForm();

		connect(this, &CustomWindow::CustomWindow::themeChanged, this, &MainWindow::onEvent);
		connect(this, &CustomWindow::CustomWindow::compositionChanged, this, &MainWindow::onEvent);
		connect(mEnableComposition, &QCheckBox::released, this, &MainWindow::onEvent);
		connect(mEnableMovableArea, &QCheckBox::released, this, &MainWindow::onEvent);
		connect(mHideSystemButtons, &QCheckBox::released, this, &MainWindow::onEvent);
		connect(mCalcsizeTitlebar, &QCheckBox::released, this, &MainWindow::onEvent);
		connect(mCalcsizeBorders, &QCheckBox::released, this, &MainWindow::onEvent);
		connect(mCalcsizeMargins, &QCheckBox::released, this, &MainWindow::onEvent);
		connect(mMarginTopSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::marginTopSpinBoxValueChanged);
		connect(mMarginBotSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::marginBotSpinBoxValueChanged);
		connect(mMarginLeftSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::marginLeftSpinBoxValueChanged);
		connect(mMarginRightSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::marginRightSpinBoxValueChanged);
		connect(mTitleBarSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::titleBarSpinBoxValueChanged);
		connect(mBorderSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::borderSpinBoxValueChanged);
    }

    virtual ~MainWindow()
    {}

public slots:
	void onEvent()
	{
		updateForm();
	}
	
	void marginTopSpinBoxValueChanged(int val)
	{
		mMarginTopValue = val;
		updateForm();
	}
	void marginBotSpinBoxValueChanged(int val)
	{
		mMargingBotValue = val;
		updateForm();
	}
	void marginLeftSpinBoxValueChanged(int val)
	{
		mMarginLeftValue = val;
		updateForm();
	}
	void marginRightSpinBoxValueChanged(int val)
	{
		mMarginRightValue = val;
		updateForm();
	}
	void titleBarSpinBoxValueChanged(int val)
	{
		mTitleBarValue = val;
		updateForm();
	}
	void borderSpinBoxValueChanged(int val)
	{
		mBorderValue = val;
		updateForm();
	}
private:
	void updateForm(void)
	{
		mDWMSignal->setChecked(isAeroActivated());
		mThemeSignal->setChecked(isThemeActivated());

		mEnableComposition->setEnabled(mThemeSignal->isChecked());

		mMarginTopSpinBox->setEnabled(mDWMSignal->isChecked());
		mMarginBotSpinBox->setEnabled(mDWMSignal->isChecked());
		mMarginLeftSpinBox->setEnabled(mDWMSignal->isChecked());
		mMarginRightSpinBox->setEnabled(mDWMSignal->isChecked());
		mTitleBarSpinBox->setEnabled(mEnableComposition->isChecked() && mThemeSignal->isChecked());
		mBorderSpinBox->setEnabled(mEnableComposition->isChecked() && mThemeSignal->isChecked());

		if (mEnableComposition->isChecked() && mThemeSignal->isChecked())
		{
			mMarginTopSpinBox->setMinimum(-mBorderValue-mTitleBarValue);
			mMarginBotSpinBox->setMinimum(-mBorderValue);
			mMarginLeftSpinBox->setMinimum(-mBorderValue);
			mMarginRightSpinBox->setMinimum(-mBorderValue);
		}
		else
		{
			mMarginTopSpinBox->setMinimum(-1);
			mMarginBotSpinBox->setMinimum(-1);
			mMarginLeftSpinBox->setMinimum(-1);
			mMarginRightSpinBox->setMinimum(-1);
		}

		mCalcsizeTitlebar->setEnabled(mEnableComposition->isChecked() && mThemeSignal->isChecked());
		mCalcsizeBorders->setEnabled(mEnableComposition->isChecked() && mThemeSignal->isChecked());
		mCalcsizeMargins->setEnabled(mThemeSignal->isChecked());
		mEnableMovableArea->setEnabled(mEnableComposition->isChecked() && mThemeSignal->isChecked());

		int flags = 0;

		if (mCalcsizeTitlebar->isChecked())
			flags |= CALCSIZE_USE_TITLEBAR;
		if (mCalcsizeBorders->isChecked())
			flags |= CALCSIZE_USE_BORDER;
		if (mCalcsizeMargins->isChecked())
			flags |= CALCSIZE_USE_MARGIN;

		setGeometryFlags(flags);

		setFrameRemoved(mEnableComposition->isChecked());

		setSystemMenu(mHideSystemButtons->isChecked());

		setExtraMargins(QMargins(mMarginLeftValue, mMarginTopValue, mMarginRightValue, mMargingBotValue));
		setTitleBarSize(mTitleBarValue);
		setBorderSize(mBorderValue);

		if (mEnableMovableArea->isChecked())
			declareCaption(mMovableArea);
		else
			removeCaption(mMovableArea);

		repaint();
	}

	QGroupBox *mThemeBox,
			  *mDWMCompositionBox,
			  *mDragAreaBox;

	QCheckBox *mDWMSignal,
			  *mThemeSignal,
			  *mEnableComposition,
			  *mEnableMovableArea,
			  *mHideSystemButtons,
			  *mCalcsizeTitlebar,
			  *mCalcsizeBorders,
			  *mCalcsizeMargins;

	QLabel	  *mMarginLabel,
			  *mMarginTopLabel,
			  *mMarginBotLabel,
			  *mMarginLeftLabel,
			  *mMarginRightLabel,
			  *mTitleBarLabel,
			  *mBorderLabel;

	QSpinBox  *mMarginTopSpinBox,
			  *mMarginBotSpinBox,
			  *mMarginLeftSpinBox,
			  *mMarginRightSpinBox,
			  *mTitleBarSpinBox,
			  *mBorderSpinBox;

	QWidget   *mMovableArea;

	QHBoxLayout *mMarginLayout,
				*mMarginTopLayout,
				*mMarginBotLayout,
				*mMarginLeftLayout,
				*mMarginRightLayout,
				*mTitleBarBorderLayout;

	QVBoxLayout *mMainLayout,
				*mThemeBoxLayout,
				*mDWMCompositionLayout,
				*mDraggableAreaLayout;

	QGridLayout *mMarginGrid;

	QSignalMapper *mSignalMapper;

	int mMarginTopValue,
		mMargingBotValue,
		mMarginLeftValue,
		mMarginRightValue,
		mTitleBarValue,
		mBorderValue;
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow *w = new MainWindow();

    w->show();

    return app.exec();
}
