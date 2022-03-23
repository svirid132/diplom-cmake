//
// Created by Пользователь on 23.03.2022.
//

#ifndef DIPLOM_CMAKE_LINEEDIT_H
#define DIPLOM_CMAKE_LINEEDIT_H


#include <QtCore/QArgument>
#include <QtWidgets/QLineEdit>

class LineEdit : public QLineEdit {

    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void enterEvent(QEvent *event) override;

    void leaveEvent(QEvent *event) override;

public:
    explicit LineEdit(QWidget* parent = nullptr);
    explicit LineEdit(const QString& text, QWidget* parent = nullptr);
    bool isOver;
};


#endif //DIPLOM_CMAKE_LINEEDIT_H
