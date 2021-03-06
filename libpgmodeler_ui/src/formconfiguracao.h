/*
# PostgreSQL Database Modeler (pgModeler)
#
# Copyright 2006-2013 - Raphael Araújo e Silva <rkhaotix@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation version 3.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# The complete text of GPLv3 is at LICENSE file on source code root directory.
# Also, you can get the complete GNU General Public License at <http://www.gnu.org/licenses/>
*/

/**
\ingroup libpgmodeler_ui
\class FormConfiguracao
\brief Formulario que reúne todos os widgets de configuração.
*/

#ifndef FORM_CONFIGURACAO_H
#define FORM_CONFIGURACAO_H

#include "ui_formconfiguracao.h"
#include "appearanceconfigwidget.h"
#include "generalconfigwidget.h"
#include "connectionsconfigwidget.h"
#include "pluginsconfigwidget.h"

class FormConfiguracao: public QDialog, public Ui::FormConfiguracao {
	private:
		Q_OBJECT

		MessageBox msg_box;
		GeneralConfigWidget *conf_geral;
		AppearanceConfigWidget *conf_aparencia;
		ConnectionsConfigWidget *conf_conexoes;
		PluginsConfigWidget *conf_plugins;


	public:
		static const int	WGT_CONF_GERAL=0,
											WGT_CONF_APARENCIA=1,
											WGT_CONF_CONEXOES=2,
											WGT_CONF_PLUGINS=3;

		FormConfiguracao(QWidget * parent = 0, Qt::WindowFlags f = 0);
		BaseConfigWidget *obterWidgetConfiguracao(unsigned idx);

	public slots:
		void aplicarConfiguracao(void);
		void carregarConfiguracao(void);
		void close(void);

	private slots:
		void restaurarPadroes(void);
};

#endif
