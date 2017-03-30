#pragma once
#include <Qt\qwidget.h>
#include <MyModel.h>

class DebugSlider;
class MeGlWindow;

class MeWidget : public QWidget
{
	Q_OBJECT

	DebugSlider* lightXSlider;
	DebugSlider* lightYSlider;
	DebugSlider* lightZSlider;

	MeGlWindow* meGlWindow;

	MyModel theModel;

	private slots:
	void sliderValueChanged();

public:
	MeWidget();
};

