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
\class TipoPgSQLWidget
\brief Definição da classe que implementa o formulário de
 edição de tipos nativos do PostgreSQL. Este formulário
 é compartilhado por vários outros por isso a necessidade
 de se criar esta classe com esse fim específico evitando
 a redundância de código e de objetos gráficos.
*/

#ifndef TIPOPGSQL_WIDGET_H
#define TIPOPGSQL_WIDGET_H

#include <QtGui>
#include "ui_tipopgsqlwidget.h"
#include "pgsqltypes.h"
#include "syntaxhighlighter.h"
#include "databasemodel.h"

class TipoPgSQLWidget: public QWidget, public Ui::TipoPgSQLWidget {
		Q_OBJECT

	private:
		//! \brief Tipo configurado pelo formulário
		PgSQLType tipo;

		//! \brief Destacador de sintaxe usado para destacar o formato do tipo
		SyntaxHighlighter *destaque_fmt;

	public:
		TipoPgSQLWidget(QWidget * parent = 0, const QString &rotulo="");

		/*! \brief Método utilitário disponibilizado para as demais classes o qual
			obtém a lista de tipos do modelo em questão dando a possiblidade
			de quais tipos obter */
		static void obterTiposPgSQL(QComboBox *combo, DatabaseModel *modelo,
																unsigned conf_tipo_usr=UserTypeConfig::ALL_USER_TYPES,
																bool tipo_oid=true, bool pseudo=true);

	private slots:
		/*! \brief Atualiza o formato do tipo   medida que os campos
			do formulário são modificados */
		void atualizarFormatoTipo(void);

	public slots:
		void definirAtributos(PgSQLType tipo, DatabaseModel *modelo,
													unsigned conf_tipo_usr=UserTypeConfig::ALL_USER_TYPES,
													bool tipo_oid=true, bool pseudo=true);

		//! \brief Obtém o tipo configurado no formulário
		PgSQLType obterTipoPgSQL(void);
};

#endif
