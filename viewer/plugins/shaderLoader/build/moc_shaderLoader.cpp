/****************************************************************************
** Meta object code from reading C++ file 'shaderLoader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../shaderLoader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shaderLoader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ShaderLoader_t {
    QByteArrayData data[44];
    char stringdata0[667];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ShaderLoader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ShaderLoader_t qt_meta_stringdata_ShaderLoader = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ShaderLoader"
QT_MOC_LITERAL(1, 13, 24), // "createDefaultShadersVSFS"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 26), // "createDefaultShadersVSGSFS"
QT_MOC_LITERAL(4, 66, 24), // "createShaderFromTemplate"
QT_MOC_LITERAL(5, 91, 13), // "attachShaders"
QT_MOC_LITERAL(6, 105, 4), // "name"
QT_MOC_LITERAL(7, 110, 21), // "openFilesInTextEditor"
QT_MOC_LITERAL(8, 132, 14), // "switchStatusVS"
QT_MOC_LITERAL(9, 147, 14), // "switchStatusGS"
QT_MOC_LITERAL(10, 162, 14), // "switchStatusFS"
QT_MOC_LITERAL(11, 177, 21), // "switchStatusWireframe"
QT_MOC_LITERAL(12, 199, 20), // "switchStatusShowAxes"
QT_MOC_LITERAL(13, 220, 21), // "switchStatusShowLight"
QT_MOC_LITERAL(14, 242, 11), // "resetCamera"
QT_MOC_LITERAL(15, 254, 13), // "cameraPreset1"
QT_MOC_LITERAL(16, 268, 13), // "cameraPreset2"
QT_MOC_LITERAL(17, 282, 13), // "cameraPreset3"
QT_MOC_LITERAL(18, 296, 13), // "cameraPreset4"
QT_MOC_LITERAL(19, 310, 13), // "cameraPreset5"
QT_MOC_LITERAL(20, 324, 10), // "loadObject"
QT_MOC_LITERAL(21, 335, 4), // "file"
QT_MOC_LITERAL(22, 340, 21), // "changeBackgroundColor"
QT_MOC_LITERAL(23, 362, 12), // "loadTexture0"
QT_MOC_LITERAL(24, 375, 12), // "loadTexture1"
QT_MOC_LITERAL(25, 388, 12), // "loadTexture2"
QT_MOC_LITERAL(26, 401, 12), // "loadTexture3"
QT_MOC_LITERAL(27, 414, 12), // "showTextures"
QT_MOC_LITERAL(28, 427, 15), // "setLightAmbient"
QT_MOC_LITERAL(29, 443, 15), // "setLightDiffuse"
QT_MOC_LITERAL(30, 459, 16), // "setLightSpecular"
QT_MOC_LITERAL(31, 476, 21), // "setLightPositionWorld"
QT_MOC_LITERAL(32, 498, 19), // "setLightPositionEye"
QT_MOC_LITERAL(33, 518, 18), // "resetLightPosition"
QT_MOC_LITERAL(34, 537, 17), // "switchLightRotate"
QT_MOC_LITERAL(35, 555, 18), // "setMaterialAmbient"
QT_MOC_LITERAL(36, 574, 18), // "setMaterialDiffuse"
QT_MOC_LITERAL(37, 593, 19), // "setMaterialSpecular"
QT_MOC_LITERAL(38, 613, 11), // "editUniform"
QT_MOC_LITERAL(39, 625, 2), // "id"
QT_MOC_LITERAL(40, 628, 11), // "uniformMult"
QT_MOC_LITERAL(41, 640, 2), // "up"
QT_MOC_LITERAL(42, 643, 11), // "executeTest"
QT_MOC_LITERAL(43, 655, 11) // "compareTest"

    },
    "ShaderLoader\0createDefaultShadersVSFS\0"
    "\0createDefaultShadersVSGSFS\0"
    "createShaderFromTemplate\0attachShaders\0"
    "name\0openFilesInTextEditor\0switchStatusVS\0"
    "switchStatusGS\0switchStatusFS\0"
    "switchStatusWireframe\0switchStatusShowAxes\0"
    "switchStatusShowLight\0resetCamera\0"
    "cameraPreset1\0cameraPreset2\0cameraPreset3\0"
    "cameraPreset4\0cameraPreset5\0loadObject\0"
    "file\0changeBackgroundColor\0loadTexture0\0"
    "loadTexture1\0loadTexture2\0loadTexture3\0"
    "showTextures\0setLightAmbient\0"
    "setLightDiffuse\0setLightSpecular\0"
    "setLightPositionWorld\0setLightPositionEye\0"
    "resetLightPosition\0switchLightRotate\0"
    "setMaterialAmbient\0setMaterialDiffuse\0"
    "setMaterialSpecular\0editUniform\0id\0"
    "uniformMult\0up\0executeTest\0compareTest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShaderLoader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      40,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  214,    2, 0x0a /* Public */,
       3,    0,  215,    2, 0x0a /* Public */,
       4,    0,  216,    2, 0x0a /* Public */,
       5,    0,  217,    2, 0x0a /* Public */,
       5,    1,  218,    2, 0x0a /* Public */,
       7,    0,  221,    2, 0x0a /* Public */,
       8,    0,  222,    2, 0x0a /* Public */,
       9,    0,  223,    2, 0x0a /* Public */,
      10,    0,  224,    2, 0x0a /* Public */,
      11,    0,  225,    2, 0x0a /* Public */,
      12,    0,  226,    2, 0x0a /* Public */,
      13,    0,  227,    2, 0x0a /* Public */,
      14,    0,  228,    2, 0x0a /* Public */,
      15,    0,  229,    2, 0x0a /* Public */,
      16,    0,  230,    2, 0x0a /* Public */,
      17,    0,  231,    2, 0x0a /* Public */,
      18,    0,  232,    2, 0x0a /* Public */,
      19,    0,  233,    2, 0x0a /* Public */,
      20,    0,  234,    2, 0x0a /* Public */,
      20,    1,  235,    2, 0x0a /* Public */,
      22,    0,  238,    2, 0x0a /* Public */,
      23,    0,  239,    2, 0x0a /* Public */,
      24,    0,  240,    2, 0x0a /* Public */,
      25,    0,  241,    2, 0x0a /* Public */,
      26,    0,  242,    2, 0x0a /* Public */,
      27,    0,  243,    2, 0x0a /* Public */,
      28,    0,  244,    2, 0x0a /* Public */,
      29,    0,  245,    2, 0x0a /* Public */,
      30,    0,  246,    2, 0x0a /* Public */,
      31,    0,  247,    2, 0x0a /* Public */,
      32,    0,  248,    2, 0x0a /* Public */,
      33,    0,  249,    2, 0x0a /* Public */,
      34,    0,  250,    2, 0x0a /* Public */,
      35,    0,  251,    2, 0x0a /* Public */,
      36,    0,  252,    2, 0x0a /* Public */,
      37,    0,  253,    2, 0x0a /* Public */,
      38,    1,  254,    2, 0x0a /* Public */,
      40,    1,  257,    2, 0x0a /* Public */,
      42,    0,  260,    2, 0x0a /* Public */,
      43,    0,  261,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::QString,
    QMetaType::Void,

       0        // eod
};

void ShaderLoader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShaderLoader *_t = static_cast<ShaderLoader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createDefaultShadersVSFS(); break;
        case 1: _t->createDefaultShadersVSGSFS(); break;
        case 2: _t->createShaderFromTemplate(); break;
        case 3: _t->attachShaders(); break;
        case 4: _t->attachShaders((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->openFilesInTextEditor(); break;
        case 6: _t->switchStatusVS(); break;
        case 7: _t->switchStatusGS(); break;
        case 8: _t->switchStatusFS(); break;
        case 9: _t->switchStatusWireframe(); break;
        case 10: _t->switchStatusShowAxes(); break;
        case 11: _t->switchStatusShowLight(); break;
        case 12: _t->resetCamera(); break;
        case 13: _t->cameraPreset1(); break;
        case 14: _t->cameraPreset2(); break;
        case 15: _t->cameraPreset3(); break;
        case 16: _t->cameraPreset4(); break;
        case 17: _t->cameraPreset5(); break;
        case 18: _t->loadObject(); break;
        case 19: _t->loadObject((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 20: _t->changeBackgroundColor(); break;
        case 21: _t->loadTexture0(); break;
        case 22: _t->loadTexture1(); break;
        case 23: _t->loadTexture2(); break;
        case 24: _t->loadTexture3(); break;
        case 25: _t->showTextures(); break;
        case 26: _t->setLightAmbient(); break;
        case 27: _t->setLightDiffuse(); break;
        case 28: _t->setLightSpecular(); break;
        case 29: _t->setLightPositionWorld(); break;
        case 30: _t->setLightPositionEye(); break;
        case 31: _t->resetLightPosition(); break;
        case 32: _t->switchLightRotate(); break;
        case 33: _t->setMaterialAmbient(); break;
        case 34: _t->setMaterialDiffuse(); break;
        case 35: _t->setMaterialSpecular(); break;
        case 36: _t->editUniform((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->uniformMult((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 38: { QString _r = _t->executeTest();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 39: _t->compareTest(); break;
        default: ;
        }
    }
}

const QMetaObject ShaderLoader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ShaderLoader.data,
      qt_meta_data_ShaderLoader,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ShaderLoader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShaderLoader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ShaderLoader.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Plugin"))
        return static_cast< Plugin*>(this);
    if (!strcmp(_clname, "edu.upc.fib.graug.Plugin/1.0"))
        return static_cast< Plugin*>(this);
    return QObject::qt_metacast(_clname);
}

int ShaderLoader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 40)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 40;
    }
    return _id;
}

QT_PLUGIN_METADATA_SECTION const uint qt_section_alignment_dummy = 42;

#ifdef QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0x8c, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    'x',  0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x06, 0x00, 'P',  'l',  'u',  'g',  'i',  'n', 
    0x1b, 0x06, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x0c, 0x00, 'S',  'h',  'a',  'd',  'e',  'r', 
    'L',  'o',  'a',  'd',  'e',  'r',  0x00, 0x00,
    0xba, ' ',  0xa1, 0x00, 0x07, 0x00, 'v',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x11, 0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, 0x95, 0x0d, 0x00, 0x00,
    0x08, 0x00, 'M',  'e',  't',  'a',  'D',  'a', 
    't',  'a',  0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, '\\', 0x00, 0x00, 0x00,
    ' ',  0x00, 0x00, 0x00, 'P',  0x00, 0x00, 0x00,
    '@',  0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0x8c, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    'x',  0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x06, 0x00, 'P',  'l',  'u',  'g',  'i',  'n', 
    0x15, 0x06, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x9b, 0x09, 0x00, 0x00,
    0x09, 0x00, 'c',  'l',  'a',  's',  's',  'N', 
    'a',  'm',  'e',  0x00, 0x0c, 0x00, 'S',  'h', 
    'a',  'd',  'e',  'r',  'L',  'o',  'a',  'd', 
    'e',  'r',  0x00, 0x00, '1',  0x00, 0x00, 0x00,
    0x05, 0x00, 'd',  'e',  'b',  'u',  'g',  0x00,
    0xba, ' ',  0xa1, 0x00, 0x07, 0x00, 'v',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, ' ',  0x00, 0x00, 0x00,
    '<',  0x00, 0x00, 0x00, '\\', 0x00, 0x00, 0x00,
    'h',  0x00, 0x00, 0x00
};
#endif // QT_NO_DEBUG

QT_MOC_EXPORT_PLUGIN(ShaderLoader, ShaderLoader)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
