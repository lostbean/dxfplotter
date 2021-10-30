#pragma once

#include <config/config.h>

#include <model/application.h>

#include <view/dialogs/settings/entry.h>

#include <uic/dialogs/settings/ui_settings.h>

#include <QDialog>

namespace view::settings
{

class TreeModel;

class Settings : public QDialog, private Ui::Settings
{
private:
	class NodeVisitor;

	void setupUi();

	model::Application &m_app;
	// Modified config
	config::Config m_newConfig;
	std::unique_ptr<TreeModel> m_model;

public:
	explicit Settings(model::Application &app);
	~Settings();

	config::Config &&newConfig();

protected Q_SLOTS:
	void currentChanged(const QModelIndex &index, const QModelIndex &previous);
	void addItem(const QModelIndex &index);
	void removeItem(const QModelIndex &index);
};

}
