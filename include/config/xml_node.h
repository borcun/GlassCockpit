#pragma once

#include <list>
#include <string>
#include <libxml/tree.h>

#ifndef LIBXML_TREE_ENABLED
#error "XMLNode requires LIBXML_TREE_ENABLED (fatal)."
#endif

// XMLNode encapsulates the xmlNode type from libxml-2, and wraps it in  a more object-oriented API.
class XMLNode {
public:
  /// default constructor
  XMLNode(void);
  /// constructor with parameter
  explicit XMLNode(xmlNode *node);
  /// destructor
  virtual ~XMLNode();
  /** Get a child node. If this node has no such child, the returned
   * XMLNode will be have IsValid() == false. */
  XMLNode getChild(const std::string &name);
  /** Return a list of all children nodes */
  std::list<XMLNode> getChildList(void);
  /** Return a list of named children nodes */
  std::list<XMLNode> getChildList(const std::string &name);
  /** Determine if this node has a child node */
  bool hasChild(const std::string &name);
  bool hasProperty(const std::string &name);
  std::string getProperty(const std::string &name);
  
  /** Get the node name */
  std::string getName(void);
  /** Get the text contents of this node */
  std::string getText(void);
  /** Get the text contents as a double */
  double getTextAsDouble(void);
  /** Get the text contents as an int */
  int getTextAsInt(void);
  /** Get the text contents as a boolean */
  bool getTextAsBool(void);
  /** Get the text as a pair of doubles. The text needs to be in the format x,y where x, y are two doubles */
  void getTextAsCoord(double &x, double &y);
  /** Is this node valid, correctly initialized, and refers to a node that exists */
  bool isValid(void);		

private:
  /// xml node references
  xmlNode *m_node = nullptr;
};
