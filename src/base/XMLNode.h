#pragma once

#include <list>
#include <string>
#include <libxml/tree.h>

#ifndef LIBXML_TREE_ENABLED
#error "XMLNode requires LIBXML_TREE_ENABLED (fatal)."
#endif

/** XMLNode encapsulates the xmlNode type from libxml-2, and wraps it in 
 * a more object-oriented API. */
class XMLNode {
public:
  XMLNode();		
  /** Initialize with an existing libxml-2 xmlNode */
  XMLNode(xmlNode *node);
  virtual ~XMLNode();
  
  /** Return a list of all children nodes */
  std::list<XMLNode> GetChildList();	
  /** Return a list of named children nodes */
  std::list<XMLNode> GetChildList(const std::string &name);
  /** Determine if this node has a child node */
  bool HasChild(const std::string &name);
  /** Get a child node. If this node has no such child, the returned
   * XMLNode will be have IsValid() == false. */
  XMLNode GetChild(const std::string &name);
  /** Is this node valid, correctly initialized, and refers to a node
   * that exists */
  bool IsValid();		
  /** Get the node name */
  std::string GetName();
  /** Get the text contents of this node */
  std::string GetText();
  /** Get the text contents as a double */
  double GetTextAsDouble();
  /** Get the text contents as an int */
  int GetTextAsInt();
  /** Get the text contents as a boolean */
  bool GetTextAsBool();
  /** Get the text as a pair of doubles. The text needs to be in the 
   * format x,y where x, y are two doubles */
  void GetTextAsCoord(double &x, double &y);

  bool HasProperty(const std::string &name);
  std::string GetProperty(const std::string &name);

private:
  xmlNode *m_node = nullptr;
};
