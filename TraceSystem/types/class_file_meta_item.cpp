#include "class_file_meta_item.h"

Class_File_Meta_Item::Class_File_Meta_Item(QObject *parent) : QObject(parent)
{
    this->p_tabWidget = NULL;
    this->p_textView = NULL;
    this->p_treeWidget = NULL;
    this->p_highlight = NULL;
    this->encodingOfFile = ENCODING_ANSI;
}

Class_File_Meta_Item::~Class_File_Meta_Item()
{
    this->filenameFull.clear();
    delete this->p_treeWidget;
    delete this->p_textView;
    delete this->p_tabWidget;
    delete this->p_highlight;
}

Class_File_Meta_Item::Class_File_Meta_Item(const Class_File_Meta_Item &obj) : QObject()
{
    this->filenameFull = obj.filenameFull;
    this->p_tabWidget = obj.p_tabWidget;
    this->p_textView = obj.p_textView;
    this->p_treeWidget = obj.p_treeWidget;
    this->p_highlight = obj.p_highlight;
    this->encodingOfFile = obj.encodingOfFile;
}

Class_File_Meta_Item &Class_File_Meta_Item::operator=(const Class_File_Meta_Item &obj)
{
    if (this != &obj)//проверка на ссылку на самого себя
    {
        this->filenameFull = obj.filenameFull;
        this->p_tabWidget = obj.p_tabWidget;
        this->p_textView = obj.p_textView;
        this->p_treeWidget = obj.p_treeWidget;
        this->p_highlight = obj.p_highlight;
        this->encodingOfFile = obj.encodingOfFile;
    }
    return *this;
}

