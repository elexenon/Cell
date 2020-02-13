// This Module Declares Entity Class For Document Of Cell.
//
// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This File May Be Used Under The Terms Of The GNU General Public License
// version 3.0 As Published By The Free Software Foundation And Appearing In
// The File LICENSE Included In The Packaging Of This File.
#ifndef CELLPROJECT_H
#define CELLPROJECT_H

#include <QMetaType>
#include <QTextStream>

class CellProjectEntity{
public:
    enum CellProjectEntityType{
        _CELLDEEPLEARNING, _PREDICTEARTHQUAKE,
        _CPP             , _PYTHON,
        _EMPTY
    };
    explicit CellProjectEntity();
    ~CellProjectEntity() = default;

    static const QString getType(CellProjectEntityType type);

    inline
    void setName(const QString &name) { this->m_name = name; }

    inline
    void setPath(const QString &path) { this->m_path = path; }

    inline
    void setType(const CellProjectEntityType &type) { this->m_type = type; }

    inline
    void setsize(const int &size) { this->m_size = size; }

    inline
    void setModifiedTime(const QString &time) { this->m_modifiedTime = time; }

    inline const QString&
    name() { return m_name; }

    inline const QString&
    path() { return m_path; }

    inline const CellProjectEntityType&
    type() { return m_type; }

    inline const int&
    size() { return m_size; }

    inline const QString&
    modifiedTime() { return m_modifiedTime; }

    void print();
private:
    CellProjectEntityType m_type;
    QString               m_name;
    QString               m_modifiedTime;
    QString               m_path;
    int                   m_size;
};

Q_DECLARE_METATYPE(CellProjectEntity);

#endif // CELLPROJECT_H
