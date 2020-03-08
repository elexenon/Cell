// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef PROCESSING_H
#define PROCESSING_H

class ProcessingWidget : public QWidget{
    Q_OBJECT
    Q_PROPERTY(qreal offset READ offset WRITE setOffset)
public:
    explicit ProcessingWidget(QWidget *parent = nullptr) noexcept;
    ~ProcessingWidget() noexcept = default;

private:
    void
    init();

    void
    setEventConnections();

    inline void
    setOffset(qreal offset) { mOffset = offset; update(); }

    inline qreal
    offset() { return mOffset; }

    qreal mOffset;
    qreal mDiam;
    QPropertyAnimation animi;

protected:
    virtual void
    paintEvent(QPaintEvent *event) override;
};

#endif // PROCESSING_H
