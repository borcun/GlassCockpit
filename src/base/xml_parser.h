#pragma once

#include <libxml/parser.h>
#include "xml_node.h"

/** XMLParser is a thin wrapper around libxml-2, supporting reading, parsing
 * and extracting data from XML files. It is intended that classes to read
 * specific types of XML documents (such as PropertyLists) inherit from this
 * class, adding extra validation and data extraction methods.
 */
class XMLParser {
public:
  XMLParser(void);
  virtual ~XMLParser();

  /** Read an XML file into the parser */
  bool read(const char *filename);
  /** Get a particular node from the XML document
   * Note: should be a unique path, otherwise the first
   * matching node will be found */
  XMLNode getNode(const std::string &path);
  /** Check if the XML document has a particular node */
  bool hasNode(const std::string &path);
  /** Heirarchically print the tree for debugging.
   * Call as PrintTree(0, 0) - its recursive. */
  void print(xmlNode *aNode, const std::string &indentation);

protected:
  /** The libxml-2 XML document structure */
  xmlDoc *m_xml_doc;
  /** The root (top level) node of the XML document */
  xmlNode *m_xml_root_node;
};
