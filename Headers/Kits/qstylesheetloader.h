/*
 *  CREATED BY HENGYIYU 2019/10/5
 */
#pragma once

#include <QFile>
#include <QtCore/qglobal.h>

#if defined(QSTYLESHEETLOADER_LIBRARY)
#  define QSTYLESHEETLOADER_EXPORT Q_DECL_EXPORT
#else
#  define QSTYLESHEETLOADER_EXPORT Q_DECL_IMPORT
#endif

class QSTYLESHEETLOADER_EXPORT QStyleSheetLoader
{
public:
    explicit QStyleSheetLoader(const QString &DIR); // Must use absolute directory!
    void setStyleSheetName(const QString name);
    const QString styleSheet() const;
    ~QStyleSheetLoader();
private:
    QFile *loader;
    QString DIR;
    QString fileName;
};
