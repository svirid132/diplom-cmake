//
// Created by Пользователь on 22.03.2022.
//

#ifndef DIPLOM_CMAKE_PUSHBUTTON_H
#define DIPLOM_CMAKE_PUSHBUTTON_H

#include <QPushButton>

class PushButton : public QPushButton
{
public:
    explicit PushButton(QWidget* parent = nullptr);
    explicit PushButton(const QString& text, QWidget* parent = nullptr);
    virtual ~PushButton();

    //text + paddingW + iconW
    virtual QSize sizeHint() const override;
    void setText(const QString& text);
    void error();

protected:
    virtual void paintEvent(QPaintEvent* e) override;

private:
    QString text;
    QFont font;
    QSize sizeIcon;
    bool isError;

    struct Padding {
        int left = 15;
        int rigth = 15;
        int width() const { return left + rigth; }
    } padding;
};


#endif //DIPLOM_CMAKE_PUSHBUTTON_H
