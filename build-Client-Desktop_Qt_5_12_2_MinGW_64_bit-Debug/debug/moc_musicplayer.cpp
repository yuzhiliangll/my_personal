/****************************************************************************
** Meta object code from reading C++ file 'musicplayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Client/musicplayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'musicplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MusicPlayer_t {
    QByteArrayData data[31];
    char stringdata0[438];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MusicPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MusicPlayer_t qt_meta_stringdata_MusicPlayer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MusicPlayer"
QT_MOC_LITERAL(1, 12, 16), // "playStateChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 15), // "DurationChanged"
QT_MOC_LITERAL(4, 46, 15), // "PositionChanged"
QT_MOC_LITERAL(5, 62, 19), // "VolumeWidgetChanged"
QT_MOC_LITERAL(6, 82, 13), // "VolumeChanged"
QT_MOC_LITERAL(7, 96, 17), // "updateVolumeLabel"
QT_MOC_LITERAL(8, 114, 5), // "value"
QT_MOC_LITERAL(9, 120, 10), // "ChangedLRC"
QT_MOC_LITERAL(10, 131, 9), // "LRCIsShow"
QT_MOC_LITERAL(11, 141, 14), // "resetLRCLabels"
QT_MOC_LITERAL(12, 156, 9), // "PlayMusic"
QT_MOC_LITERAL(13, 166, 18), // "mediaStatusChanged"
QT_MOC_LITERAL(14, 185, 25), // "QMediaPlayer::MediaStatus"
QT_MOC_LITERAL(15, 211, 6), // "status"
QT_MOC_LITERAL(16, 218, 8), // "PlayPrev"
QT_MOC_LITERAL(17, 227, 8), // "PlayNext"
QT_MOC_LITERAL(18, 236, 14), // "ChangePlayMode"
QT_MOC_LITERAL(19, 251, 19), // "handleMusicDataRecv"
QT_MOC_LITERAL(20, 271, 5), // "array"
QT_MOC_LITERAL(21, 277, 13), // "DownLoadMusic"
QT_MOC_LITERAL(22, 291, 9), // "musicName"
QT_MOC_LITERAL(23, 301, 10), // "artistName"
QT_MOC_LITERAL(24, 312, 9), // "albumName"
QT_MOC_LITERAL(25, 322, 16), // "showDownloadList"
QT_MOC_LITERAL(26, 339, 18), // "promptForMusicName"
QT_MOC_LITERAL(27, 358, 22), // "promptForBatchDownload"
QT_MOC_LITERAL(28, 381, 19), // "handleBatchDownload"
QT_MOC_LITERAL(29, 401, 7), // "content"
QT_MOC_LITERAL(30, 409, 28) // "onBatchDownloadButtonClicked"

    },
    "MusicPlayer\0playStateChanged\0\0"
    "DurationChanged\0PositionChanged\0"
    "VolumeWidgetChanged\0VolumeChanged\0"
    "updateVolumeLabel\0value\0ChangedLRC\0"
    "LRCIsShow\0resetLRCLabels\0PlayMusic\0"
    "mediaStatusChanged\0QMediaPlayer::MediaStatus\0"
    "status\0PlayPrev\0PlayNext\0ChangePlayMode\0"
    "handleMusicDataRecv\0array\0DownLoadMusic\0"
    "musicName\0artistName\0albumName\0"
    "showDownloadList\0promptForMusicName\0"
    "promptForBatchDownload\0handleBatchDownload\0"
    "content\0onBatchDownloadButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MusicPlayer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  119,    2, 0x0a /* Public */,
       3,    0,  120,    2, 0x0a /* Public */,
       4,    0,  121,    2, 0x0a /* Public */,
       5,    0,  122,    2, 0x0a /* Public */,
       6,    0,  123,    2, 0x0a /* Public */,
       7,    1,  124,    2, 0x0a /* Public */,
       9,    0,  127,    2, 0x0a /* Public */,
      10,    0,  128,    2, 0x0a /* Public */,
      11,    0,  129,    2, 0x0a /* Public */,
      12,    0,  130,    2, 0x0a /* Public */,
      13,    1,  131,    2, 0x0a /* Public */,
      16,    0,  134,    2, 0x0a /* Public */,
      17,    0,  135,    2, 0x0a /* Public */,
      18,    0,  136,    2, 0x0a /* Public */,
      19,    1,  137,    2, 0x0a /* Public */,
      21,    3,  140,    2, 0x0a /* Public */,
      25,    0,  147,    2, 0x0a /* Public */,
      26,    0,  148,    2, 0x08 /* Private */,
      27,    0,  149,    2, 0x08 /* Private */,
      28,    1,  150,    2, 0x08 /* Private */,
      30,    0,  153,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   22,   23,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   29,
    QMetaType::Void,

       0        // eod
};

void MusicPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MusicPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->playStateChanged(); break;
        case 1: _t->DurationChanged(); break;
        case 2: _t->PositionChanged(); break;
        case 3: _t->VolumeWidgetChanged(); break;
        case 4: _t->VolumeChanged(); break;
        case 5: _t->updateVolumeLabel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->ChangedLRC(); break;
        case 7: _t->LRCIsShow(); break;
        case 8: _t->resetLRCLabels(); break;
        case 9: _t->PlayMusic(); break;
        case 10: _t->mediaStatusChanged((*reinterpret_cast< QMediaPlayer::MediaStatus(*)>(_a[1]))); break;
        case 11: _t->PlayPrev(); break;
        case 12: _t->PlayNext(); break;
        case 13: _t->ChangePlayMode(); break;
        case 14: _t->handleMusicDataRecv((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 15: _t->DownLoadMusic((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 16: _t->showDownloadList(); break;
        case 17: _t->promptForMusicName(); break;
        case 18: _t->promptForBatchDownload(); break;
        case 19: _t->handleBatchDownload((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 20: _t->onBatchDownloadButtonClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer::MediaStatus >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MusicPlayer::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_MusicPlayer.data,
    qt_meta_data_MusicPlayer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MusicPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MusicPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MusicPlayer.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MusicPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
