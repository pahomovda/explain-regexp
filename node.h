﻿#ifndef NODE_H
#define NODE_H
#include <QtCore>
#include "nodeType.h"
#include "nodepattern.h"
#include "variant.h"
#include "patterncontainer.h"

/*!
 * \brief Класс, содержащий сведения об узле
 * Класс, содержащий сведения об узле. Потомки переопределяют методы tagName(),type(),hasArg(), а также добавляют необходимые им поля для хранения данных об узле.
 */
class node
{
private:
    QVector<node *> childs; ///<Ссылки на потомков
public:
    node();
	~node();

	/*!
	 * Возвращает название тега, переопределяется потомками
	 * \return название тега
	 */
    virtual QString tagName()=0 ;
	
	/*!
	 * Возвращает тип тега, переопределяется потомками
	 * \return тип тега
	 */
    virtual nodeType type()=0;
	
	/*!
	 * Проверяет, содержит ли узел необходимый атрибут
	 * \param[in] arg название атрибута (xml)
	 * \return true если атрибут присутствует в узле
	 */
    virtual bool hasArg(QString & arg) = 0;


	/*!
	 * Генерирует описание для заданного узла
	 * \param[in]	patterns	контейнер, содержащий шаблоны
	 * \param[in]	parent		указатель на родителя (для проверки условий применимости шаблонов). По умолчанию 0
	 * \param[in,out]	num			номер узла по порядку, если num отрицательно – не вести нумерацию
	 * \return строка-описание
	 */
    QString description(const patternContainer & patterns, int num=-1, node * parent=0, QString form = QString());
	
	/*!
	 * Выбирает наиболее подходящий шаблон для узла из структуры nodePattern
	 * \param[in]	_nodePattern	список шаблонов узла с условиями применения
	 * \param[in]	parent		ссылка на родителя для проверки условий
	 * \param[in]	form	требуемая форма (пустая строка – стандартная форма)
	 * \param[in]	num	номер узла по порядку, если num отрицательно – не вести нумерацию
	 * \return строка-описание
	 */
	QString pattern(const nodePattern & _nodePattern, node * parent=0, QString form = QString());
    
	/*!
	 * Проверяет, соответствует ли узел, условию применимости альтернативного шаблона
	 * \param[in]	pattern	альтернативный шаблон
	 * \param[in]	parent	ссылка на родителя
	 * \return	true если шаблон подходит
	 */
	bool check(const variant & pattern, node * parent = 0);

	/*!
	 * добавляет ребенка к вершине дерева
	 * \param[in] child указатель адрес ребенка
	 * \return номер ребенка
	 */
	int addChild(node * child);

	/*!
	 * возвращает указатель на ребенка с номером n
	 * \param[in] n номер ребенка
	 * \return указатель на ребенка
	 */
	node * child(int n);
};

#endif // NODE_H
