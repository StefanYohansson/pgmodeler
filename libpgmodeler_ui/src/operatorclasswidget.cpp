#include "operatorclasswidget.h"

OperatorClassWidget::OperatorClassWidget(QWidget *parent): BaseObjectWidget(parent, OBJ_OPCLASS)
{
	try
	{
		QStringList tipos;
		QGridLayout *grid=NULL;

		Ui_OperatorClassWidget::setupUi(this);

		family_sel=NULL;
		operator_sel=NULL;
		function_sel=NULL;
		data_type=NULL;
		storage_type=NULL;
		elements_tab=NULL;

		family_sel=new ObjectSelectorWidget(OBJ_OPFAMILY, false, this);
		operator_sel=new ObjectSelectorWidget(OBJ_OPERATOR, true, this);
		function_sel=new ObjectSelectorWidget(OBJ_FUNCTION, true, this);
		data_type=new TipoPgSQLWidget(this);
		storage_type=new TipoPgSQLWidget(this, trUtf8("Storage Type"));
		elements_tab=new ObjectTableWidget(ObjectTableWidget::ALL_BUTTONS, true, this);

		elements_tab->setColumnCount(4);
		elements_tab->setHeaderLabel(trUtf8("Object"),0);
		elements_tab->setHeaderIcon(QPixmap(":/icones/icones/table.png"),0);

		elements_tab->setHeaderLabel(trUtf8("Type"),1);
		elements_tab->setHeaderIcon(QPixmap(":/icones/icones/usertype.png"),1);

		elements_tab->setHeaderLabel(trUtf8("Support/Strategy"),2);
		elements_tab->setHeaderLabel(trUtf8("Recheck"),3);

		grid=new QGridLayout;
		grid->setContentsMargins(0,0,0,0);
		grid->addWidget(def_class_lbl,0,2,1,1);
		grid->addWidget(def_class_chk,0,3,1,1);
		grid->addWidget(indexing_lbl,0,0,1,1);
		grid->addWidget(indexing_cmb,0,1,1,1);
		grid->addWidget(family_lbl,2,0,1,1);
		grid->addWidget(family_sel,2,1,1,4);
		grid->addWidget(data_type,4,0,1,5);
		grid->addWidget(elements_grp,5,0,1,5);
		this->setLayout(grid);
		configureFormLayout(grid, OBJ_OPCLASS);

		grid=dynamic_cast<QGridLayout *>(elements_grp->layout());
		grid->addWidget(function_sel, 1,1,1,4);
		grid->addWidget(operator_sel, 2,1,1,4);
		grid->addWidget(storage_type, 5,0,1,5);
		grid->addWidget(elements_tab, 6,0,1,4);

		connect(parent_form->aplicar_ok_btn,SIGNAL(clicked(bool)), this, SLOT(applyConfiguration(void)));
		connect(elem_type_cmb, SIGNAL(currentIndexChanged(int)), this, SLOT(selectElementType(int)));
		connect(elements_tab, SIGNAL(s_rowAdded(int)), this, SLOT(handleElement(int)));
		connect(elements_tab, SIGNAL(s_rowUpdated(int)), this, SLOT(handleElement(int)));
		connect(elements_tab, SIGNAL(s_rowEdited(int)), this, SLOT(editElement(int)));

		parent_form->setMinimumSize(540, 590);
		selectElementType(0);

		IndexingType::getTypes(tipos);
		indexing_cmb->addItems(tipos);
	}
	catch(Exception &e)
	{
		throw Exception(e.getErrorMessage(),e.getErrorType(),__PRETTY_FUNCTION__,__FILE__,__LINE__, &e);
	}
}

void OperatorClassWidget::hideEvent(QHideEvent *event)
{
	function_sel->clearSelector();
	operator_sel->clearSelector();
	stg_num_sb->setValue(1);
	recheck_chk->setChecked(false);
	elements_tab->removeRows();
	selectElementType(0);
	BaseObjectWidget::hideEvent(event);
}

void OperatorClassWidget::selectElementType(int elem_type)
{
	unsigned sel_idx=static_cast<unsigned>(elem_type);

	function_lbl->setVisible(sel_idx==OperatorClassElement::FUNCTION_ELEM);
	function_sel->setVisible(sel_idx==OperatorClassElement::FUNCTION_ELEM);

	operator_lbl->setVisible(sel_idx==OperatorClassElement::OPERATOR_ELEM);
	operator_sel->setVisible(sel_idx==OperatorClassElement::OPERATOR_ELEM);
	recheck_chk->setVisible(sel_idx==OperatorClassElement::OPERATOR_ELEM);

	storage_type->setVisible(sel_idx==OperatorClassElement::STORAGE_ELEM);

	stg_num_lbl->setVisible(sel_idx!=OperatorClassElement::STORAGE_ELEM);
	stg_num_sb->setVisible(sel_idx!=OperatorClassElement::STORAGE_ELEM);
}

void OperatorClassWidget::editElement(int lin_idx)
{
	OperatorClassElement elem;

	//Get the element from the selected line
	elem=elements_tab->getRowData(lin_idx).value<OperatorClassElement>();

	elem_type_cmb->setCurrentIndex(elem.getElementType());
	function_sel->setSelectedObject(elem.getFunction());
	operator_sel->setSelectedObject(elem.getOperator());
	recheck_chk->setChecked(elem.isRecheck());
	stg_num_sb->setValue(elem.getStrategyNumber());
	storage_type->definirAtributos(elem.getStorage(),this->model);
}

void OperatorClassWidget::showElementData(OperatorClassElement elem, int lin_idx)
{
	unsigned elem_type;

	elem_type=elem.getElementType();

	if(elem_type==OperatorClassElement::FUNCTION_ELEM)
	{
		elements_tab->setCellText(QString::fromUtf8(elem.getFunction()->getSignature()), lin_idx, 0);
		elements_tab->setCellText(QString::fromUtf8(elem.getFunction()->getTypeName()), lin_idx, 1);
	}
	else if(elem_type==OperatorClassElement::OPERATOR_ELEM)
	{
		elements_tab->setCellText(QString::fromUtf8(elem.getOperator()->getSignature()), lin_idx, 0);
		elements_tab->setCellText(QString::fromUtf8(elem.getOperator()->getTypeName()), lin_idx, 1);
	}
	else
	{
		elements_tab->setCellText(*elem.getStorage(), lin_idx, 0);
		elements_tab->setCellText(QString::fromUtf8(BaseObject::getTypeName(OBJ_TYPE)), lin_idx, 1);
	}

	if(elem_type!=OperatorClassElement::STORAGE_ELEM)
		elements_tab->setCellText(QString("%1").arg(elem.getStrategyNumber()), lin_idx, 2);
	else
		elements_tab->setCellText("-", lin_idx, 2);

	if(elem_type==OperatorClassElement::OPERATOR_ELEM)
	{
		if(elem.isRecheck())
			elements_tab->setCellText(trUtf8("Yes"), lin_idx, 3);
		else
			elements_tab->setCellText(trUtf8("No"), lin_idx, 3);
	}
	else
		elements_tab->setCellText("-", lin_idx, 3);

	//Define as the line data the element itself
	elements_tab->setRowData(QVariant::fromValue<OperatorClassElement>(elem), lin_idx);
}

void OperatorClassWidget::handleElement(int lin_idx)
{
	OperatorClassElement elem;
	unsigned elem_type;

	elem_type=elem_type_cmb->currentIndex();

	try
	{
		if(elem_type==OperatorClassElement::FUNCTION_ELEM)
			elem.setFunction(dynamic_cast<Function *>(function_sel->getSelectedObject()), stg_num_sb->value());
		else  if(elem_type==OperatorClassElement::OPERATOR_ELEM)
			elem.setOperator(dynamic_cast<Operator *>(operator_sel->getSelectedObject()), stg_num_sb->value(), recheck_chk->isChecked());
		else
			elem.setStorage(storage_type->obterTipoPgSQL());

		showElementData(elem, lin_idx);

		function_sel->clearSelector();
		operator_sel->clearSelector();
		stg_num_sb->setValue(1);
		recheck_chk->setChecked(false);
		elements_tab->clearSelection();
	}
	catch(Exception &e)
	{
		//In case of error removes the recently added table line
		if(elements_tab->getCellText(lin_idx, 0).isEmpty())
			elements_tab->removeRow(lin_idx);

		throw Exception(e.getErrorMessage(),e.getErrorType(),__PRETTY_FUNCTION__,__FILE__,__LINE__, &e);
	}
}

void OperatorClassWidget::setAttributes(DatabaseModel *model, OperationList *op_list, Schema *schema, OperatorClass *op_class)
{
	PgSQLType type;
	unsigned i, count;

	BaseObjectWidget::setAttributes(model, op_list, op_class, schema);

	family_sel->setModel(model);
	function_sel->setModel(model);
	operator_sel->setModel(model);
	storage_type->definirAtributos(type, model);

	if(op_class)
	{
		type=op_class->getDataType();
		family_sel->setSelectedObject(op_class->getFamily());
		def_class_chk->setChecked(op_class->isDefault());
		indexing_cmb->setCurrentIndex(indexing_cmb->findText(~(op_class->getIndexingType())));

		elements_tab->blockSignals(true);
		count=op_class->getElementCount();
		for(i=0; i < count; i++)
		{
			elements_tab->addRow();
			showElementData(op_class->getElement(i), i);
		}
		elements_tab->blockSignals(false);
		elements_tab->clearSelection();
	}

	data_type->definirAtributos(type, model);
}

void OperatorClassWidget::applyConfiguration(void)
{
	try
	{
		OperatorClass *op_class=NULL;
		unsigned i, count;

		startConfiguration<OperatorClass>();

		op_class=dynamic_cast<OperatorClass *>(this->object);
		op_class->setDefault(op_class->isDefault());
		op_class->setFamily(dynamic_cast<OperatorFamily *>(family_sel->getSelectedObject()));
		op_class->setIndexingType(IndexingType(indexing_cmb->currentText()));
		op_class->setDataType(data_type->obterTipoPgSQL());

		op_class->removeElements();
		count=elements_tab->getRowCount();

		for(i=0; i < count; i++)
			op_class->addElement(elements_tab->getRowData(i).value<OperatorClassElement>());

		BaseObjectWidget::applyConfiguration();
		finishConfiguration();
	}
	catch(Exception &e)
	{
		cancelConfiguration();
		throw Exception(e.getErrorMessage(),e.getErrorType(),__PRETTY_FUNCTION__,__FILE__,__LINE__, &e);
	}
}

