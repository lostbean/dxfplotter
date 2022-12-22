#pragma once

#include <model/application.h>

#include <uic/ui_mainwindow.h>

#include <QMainWindow>
#include <QActionGroup>

class QComboBox;


namespace view
{

namespace view3d
{

class Viewport;

}

class MainWindow : public QMainWindow, private Ui::MainWindow
{
private:
	model::Application &m_app;

	view3d::Viewport *m_viewport3d;

	QActionGroup m_openedDocumentActions;

	QWidget *setupLeftPanel();
	QWidget *setupCenterPanel();
	void setupToolBar();
	void setupUi();
	void setupMenuActions();
	void setupOpenedDocumentActions();

	void setDocumentToolsEnabled(bool enabled);

	QString defaultFileName(const QString &extension) const;

public:
	explicit MainWindow(model::Application &app);

protected Q_SLOTS:
	void openFile();
	void saveFile();
	void saveAsFile();
	void exportFile();
	void exportAsFile();
	void openSettings();
	void transformSelection();
	void mirrorSelection();
	void setSelectionOrigin();
	void documentChanged(model::Document *newDocument);
	void displayError(const QString &message);

signals:
	void simulate();
};

}
