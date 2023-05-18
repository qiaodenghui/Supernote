/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * docx is a free library to work with docx files.
 */

#ifndef docx_H
#define docx_H

#include <cstdio>
#include <cstdlib>
#include <string>

#include "constants.hpp"
#include "docxiterator.hpp"
#include "pugixml.hpp"
#include "zip.h"
#include "docx_global.h"

// TODO: Use container-iterator design pattern!

namespace docx {
// Run contains runs in a paragraph
class DOCX_EXPORT Run {
  private:
    friend class IteratorHelper;
    // Store the parent node (a paragraph)
    pugi::xml_node parent;
    // And store current node also
    pugi::xml_node current;

  public:
    Run();
    Run(pugi::xml_node, pugi::xml_node);
    void set_parent(pugi::xml_node);
    void set_current(pugi::xml_node);

    std::string get_text() const;
    bool set_text(const std::string &) const;
    bool set_text(const char *) const;

    Run &next();
    bool has_next() const;
};

// Paragraph contains a paragraph
// and stores runs
class DOCX_EXPORT Paragraph {
  private:
    friend class IteratorHelper;
    // Store parent node (usually the body node)
    pugi::xml_node parent;
    // And store current node also
    pugi::xml_node current;
    // A paragraph consists of runs
    Run run;

  public:
    Paragraph();
    Paragraph(pugi::xml_node, pugi::xml_node);
    void set_parent(pugi::xml_node);
    void set_current(pugi::xml_node);

    Paragraph &next();
    bool has_next() const;

    Run &runs();
    Run &add_run(const std::string &, docx::formatting_flag = docx::none);
    Run &add_run(const char *, docx::formatting_flag = docx::none);
    Paragraph &insert_paragraph_after(const std::string &,
                                      docx::formatting_flag = docx::none);
    Paragraph &append_paragraph(const std::string &,
                                      docx::formatting_flag = docx::none);
};

// TableCell contains one or more paragraphs
class DOCX_EXPORT TableCell {
  private:
    friend class IteratorHelper;
    pugi::xml_node parent;
    pugi::xml_node current;

    Paragraph paragraph;

  public:
    TableCell();
    TableCell(pugi::xml_node, pugi::xml_node);

    void set_parent(pugi::xml_node);
    void set_current(pugi::xml_node);

    Paragraph &paragraphs();

    TableCell &next();
    bool has_next() const;
};

// TableRow consists of one or more TableCells
class DOCX_EXPORT TableRow {
    friend class IteratorHelper;
    pugi::xml_node parent;
    pugi::xml_node current;

    TableCell cell;

  public:
    TableRow();
    TableRow(pugi::xml_node, pugi::xml_node);
    void set_parent(pugi::xml_node);
    void set_current(pugi::xml_node);

    TableCell &cells();

    bool has_next() const;
    TableRow &next();
};

// Table consists of one or more TableRow objects
class DOCX_EXPORT Table {
  private:
    friend class IteratorHelper;
    pugi::xml_node parent;
    pugi::xml_node current;

    TableRow row;

  public:
    Table();
    Table(pugi::xml_node, pugi::xml_node);
    void set_parent(pugi::xml_node);
    void set_current(pugi::xml_node);

    Table &next();
    bool has_next() const;

    TableRow &rows();
};

// Document contains whole the docx file
// and stores paragraphs
class DOCX_EXPORT Document {
  private:
    friend class IteratorHelper;
    std::string directory;
    Paragraph paragraph;
    Table table;
    pugi::xml_document document;

  public:
    Document();
    Document(std::string);
    void file(std::string);
    void open();
    void save() const;

    Paragraph &paragraphs();
    Table &tables();
};
} // namespace docx

#endif
